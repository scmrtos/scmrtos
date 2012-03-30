//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STM8 (STMicroelectronics)
//*
//*     TOOLKIT:   EWSTM8 (IAR Systems)
//*
//*     PURPOSE:   STM8/IAR Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2010, Harry E. Zhurov
//*
//*     Permission is hereby granted, free of charge, to any person 
//*     obtaining  a copy of this software and associated documentation 
//*     files (the "Software"), to deal in the Software without restriction, 
//*     including without limitation the rights to use, copy, modify, merge, 
//*     publish, distribute, sublicense, and/or sell copies of the Software, 
//*     and to permit persons to whom the Software is furnished to do so, 
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included 
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//******************************************************************************
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011

//---------------------------------------------------------------------------
#include <scmRTOS.h>

#include "pin.h"

//---------------------------------------------------------------------------
//  "Hello, scope!" pins
Pin<'B', 0> IDLE_HOOK;
Pin<'B', 1> PROC1;
Pin<'B', 2> PROC2;
Pin<'B', 3> PROC3;
Pin<'B', 4> TIMER_HOOK;
Pin<'B', 5> TIMER3_ISR;
Pin<'B', 6> TIMER3_TO_PROC1;
Pin<'B', 7> SLON_TRUNK;


//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 120> TProc1;
typedef OS::process<OS::pr1, 160> TProc2;
typedef OS::process<OS::pr2, 120> TProc3;

template<> void TProc1::exec();
template<> void TProc2::exec();
template<> void TProc3::exec();

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

//---------------------------------------------------------------------------
// System timer setup parameters
static const uint32_t systick_freq = 1000;
static const uint8_t  tim4_prescaler_power = 6;
static const uint32_t tim4_divider = (1UL << tim4_prescaler_power) * systick_freq;

//---------------------------------------------------------------------------
tick_count_t tick_count;          // global variable for OS::GetTickCount testing


//------------------------------------------------------------------------------
//
//   Message "body"
//
//
class TSlon
{
public:
    TSlon() { }
    virtual void eat() = 0;      // feed the slon. For non-russians: slon == elephant ;)
};

//------------------------------------------------------------------------------
class TAfricanSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;

        SLON_TRUNK.On();
        SLON_TRUNK.Off();
    }
};

//------------------------------------------------------------------------------
class TIndianSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;

        SLON_TRUNK.On();
        SLON_TRUNK.Off();
        SLON_TRUNK.On();
        SLON_TRUNK.Off();
    }
};

//------------------------------------------------------------------------------

TAfricanSlon African;
TIndianSlon  Indian;

OS::channel<TSlon*, 8> SlonQueue; // OS::channel object for 8 'TSlon*' items

OS::TEventFlag Timer3_Ovf;

//---------------------------------------------------------------------------
int main()
{
    CLK->CKDIVR = 0;
    
    // Setup user timer interrupt
    // 1001 periods per second (per 1000 OS timer ticks) for better scope view
    TIM3->PSCR = 0;		// clk/1
    TIM3->ARRH = (F_MASTER / 1001) >> 8;
    TIM3->ARRL = (uint8_t)(F_MASTER / 1001);
    TIM3->CR1 = TIM3_CR1_CEN;
    TIM3->EGR = 0;
    TIM3->IER = TIM3_IER_UIE;

    // GPIO setup -- push-pull outputs
#if 0
    IDLE_HOOK.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
    PROC1.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
    PROC2.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
    PROC3.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
    TIMER_HOOK.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
    TIMER3_ISR.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
    TIMER3_TO_PROC1.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
    SLON_TRUNK.Mode(GPIO_MODE_OUT_PP_LOW_FAST);
#else
    // Direct setup for all pins -> for correct code size comparsion with
    // AVR samples
    GPIOB->CR1 = 0xFF;
    GPIOB->CR2 = 0xFF;
    GPIOB->DDR = 0xFF;
#endif
    
    // Start System Timer
    // TODO: Set lowest priority for system timer ISR
    TIM4->PSCR = tim4_prescaler_power;
    TIM4->ARR = (F_MASTER + tim4_divider/2) / tim4_divider  - 1;
    TIM4->CR1 = TIM4_CR1_CEN;
    TIM4->EGR = 0;
    TIM4->IER = TIM4_IER_UIE;

    OS::run();
}


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc1::exec()
{
    for(;;)
    {
        PROC1.Off();
        Timer3_Ovf.wait();
        PROC1.On();
        TIMER3_TO_PROC1.Off();
        SlonQueue.push(&African);
    }
} // TProc1::exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc2::exec()
{
    for(;;)
    {
        tick_count = OS::get_tick_count();
        PROC2.Off();
        sleep( static_cast<uint16_t>(tick_count) & 0x200  ?  1  :  2  );
        PROC2.On();
        SlonQueue.push(&Indian);
    }
} // TProc2::exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc3::exec()
{
    for(;;)
    {
        //--------------------------------------------------
        //
        //            Channel test
        //
        //
        //     Get data through channel
        //
        TSlon *p;
        PROC3.Off();
        SlonQueue.pop(p);     // get pointer from queue
        PROC3.On();
        p->eat();             // feed the appropriate Slon
    }
} // TProc3::exec()

} // namespace OS


//---------------------------------------------------------------------------
#if scmRTOS_SYSTIMER_HOOK_ENABLE
void OS::system_timer_user_hook()
{
    TCritSect cs;    // STM8 can complement bit atomically (BCPL), but IAR/STM8 1.30 can't :-(
    TIMER_HOOK.Cpl();
}
#endif // scmRTOS_SYSTIMER_HOOK_ENABLE

//---------------------------------------------------------------------------
#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
    TCritSect cs;
    IDLE_HOOK.Cpl();
}
#endif // scmRTOS_IDLE_HOOK_ENABLE

INTERRUPT_HANDLER(Timer3_period_ISR, ITC_IRQ_TIM3_OVF)
{
    TIMER3_ISR.On();
    TIM3->SR1 &= (uint8_t)~TIM3_SR1_UIF;

    OS::TISRW ISRW;

    TIMER3_TO_PROC1.On();

    Timer3_Ovf.signal_isr();
    TIMER3_ISR.Off();
}

//------    end of file  main.cpp   -------------------------------------------

