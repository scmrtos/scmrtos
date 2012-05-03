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
//*                Sample '4-Debug' main module.
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011-2012

//---------------------------------------------------------------------------

#include <scmRTOS.h>

#include "pin.h"

#include "debug.h"

//---------------------------------------------------------------------------
// System Timer divider for F_CPU
// clk/64, reload for 1000 Hz interrupt rate
static const uint32_t systick_freq = 1000;
static const uint8_t  tim4_prescaler_power = 6;
static const uint32_t tim4_divider = (1UL << tim4_prescaler_power) * systick_freq;

//---------------------------------------------------------------------------
//  "Hello, scope!" pins
Pin<'B', 0> IDLE_HOOK;
Pin<'B', 1> PROC1;
Pin<'B', 2> PROC2;
Pin<'B', 3> PROC3;
Pin<'B', 4> TIMER_HOOK;
Pin<'B', 5> TIMER3_ISR;
Pin<'B', 6> TIMER3_TO_PROC1;

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

//---------------------------------------------------------------------------
tick_count_t tick_count;        // global variable for OS::GetTickCount testing

OS::TEventFlag Timer3_Ovf;  // set in Timer3_period_ISR(), waited in Proc1
OS::TEventFlag ef;          // set in Proc3, waited in Proc2

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

/**
 * Waste some time (payload emulation).
 * Execution time approximately (??? * count) CPU clocks
 */
void waste_time(unsigned count)
{
    volatile unsigned i = 0;
    while ( ++i < count )  {}
}

/**
 * Stack hungry function.
 * Called by different processes some time after start.
 * Stack usage changes can be observed in debug terminal.
 */
uint8_t waste_stack(uint_fast8_t count)
{
    const uint8_t stack_portion = 8;
    volatile uint8_t arr[stack_portion];
    for (uint8_t i = 0; i < stack_portion-1; ++i) 
        arr[i] = TIM4->CNTR;
    arr[stack_portion-1] = count ? waste_stack(count - 1) : TIM4->CNTR;
    uint8_t temp=arr[0];
    for (uint8_t i = 1; i < stack_portion; ++i) temp ^= arr[i];
    return temp;
}


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc1::exec()
{
    const int max_request = 10;
    const int increment_period = 1000;
    int increment_div = increment_period;
    volatile uint8_t dev_null;
    uint8_t request = 0;

    for(;;) {
        PROC1.Off();
        Timer3_Ovf.wait();
        PROC1.On();
        TIMER3_TO_PROC1.Off();
        if (request < max_request) {
            dev_null = waste_stack(request);
            if (--increment_div == 0) {
                increment_div = increment_period;
                ++request;
	    }
        } else {
           waste_time(50);
        }
    }
} // TProc1::exec()

} // namespace OS

//---------------------------------------------------------------------------
namespace OS {
  
template<> void TProc2::exec()
{
    for(;;) {
        PROC2.Off();
        sleep(4);
        PROC2.On();
        ef.signal();
        uint8_t request = (OS::get_tick_count() / 1024) % 8;
        waste_time(request * 100);
    }
} // TProc2::exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc3::exec()
{
    for(;;) {
        PROC3.Off();
        ef.wait();
        PROC3.On();
        waste_time(500);
    }
} // TProc3::exec()

} // namespace OS


//---------------------------------------------------------------------------
#if  scmRTOS_SYSTIMER_HOOK_ENABLE
void OS::system_timer_user_hook()
{
    TCritSect cs;    // STM8 can complement bit atomically (BCPL), but IAR/STM8 1.30 can't :-(
    TIMER_HOOK.Cpl();
}
#endif

//---------------------------------------------------------------------------
#if  scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
    TCritSect cs;
    IDLE_HOOK.Cpl();
}
#endif


//---------------------------------------------------------------------------

INTERRUPT_HANDLER(Timer3_period_ISR, ITC_IRQ_TIM3_OVF)
{
    TIMER3_ISR.On();
    TIM3->SR1 &= ~TIM3_SR1_UIF;

    OS::TISRW ISRW;

    TIMER3_TO_PROC1.On();

    Timer3_Ovf.signal_isr();
    TIMER3_ISR.Off();
}

//------    end of file  main.cpp   -------------------------------------------

