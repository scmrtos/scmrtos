//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision: 196 $
//*     $Date:: 2008-06-19 #$
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2012
//*
//*
//*     Demo based on STM32F103RB microcontroller from ST: www.st.com
//*

#include <scmRTOS.h>
#include <stdio.h>
#include <ST/iostm32f10xxB.h>

typedef TProfiler<0> TProfilerBase;

//---------------------------------------------------------------------------
class TProcProfiler : public TProfilerBase
{
public:
    TProcProfiler() {/* Timer initialization can be here */}
    void get_results(timeout_t acquire_period);
};

//---------------------------------------------------------------------------
template<>
uint32_t TProfilerBase::time_interval()
{
     static uint16_t  prev_ticks;

     uint16_t  ticks = TIM3_CNT;
     uint16_t  diff = ticks - prev_ticks;
     prev_ticks = ticks;
     return diff;
}

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 512> TProc1;
typedef OS::process<OS::pr1, 512> TProc2;
typedef OS::process<OS::pr2, 512> TProc3;
typedef OS::process<OS::pr3, 1024> TBackgroundProc;

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
TBackgroundProc BackgroundProc;


OS::TEventFlag ef;
OS::TEventFlag Timer_B_Ovf;

TProcProfiler Profiler;

//---------------------------------------------------------------------------
//
void main()
{
    // Setup STM32F103 Timer3.
    RCC_APB1ENR_bit.TIM3EN = 1; // Enable TIM3 clock.
    TIM3_CR1 = 0;               // Count up to ARR, no divisor, auto reload.
    TIM3_ARR = 0xFFFF;          // Period (full scale).
    TIM3_PSC = 79;              // Set prescaler to 80: 1us tick @ 8MHz HSI. 65.536 ms period
    TIM3_EGR_bit.UG = 1;        // Generate an update event to reload the prescaler value immediately.
    TIM3_CR1_bit.CEN = 1;       // Run timer.
    
    //-----------------------------------------------------------------------
    OS::run();
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc1::exec()
{
    for(;;)
    {
        ef.wait();
    }     
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc2::exec()
{
    for(;;)
    {
        Timer_B_Ovf.wait();
    }
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc3::exec()
{
    for(;;)
    {
        OS::sleep(10);
        ef.signal();
    }
}
//---------------------------------------------------------------------------
template<> void TBackgroundProc::exec()
{
    for(;;)
    {
        // Every 1 second get profiler results.
        Profiler.get_results(500);  
    }
}
//---------------------------------------------------------------------------
void OS::system_timer_user_hook()
{
    static int cnt=0;
    if (++cnt == 25)
    {
        cnt = 0;
        Timer_B_Ovf.signal_isr();
    }
}
//---------------------------------------------------------------------------
void OS::idle_process_user_hook()
{
}

//---------------------------------------------------------------------------
void OS::context_switch_user_hook()
{
    Profiler.advance_counters(); 
}

//---------------------------------------------------------------------------
void TProcProfiler::get_results(timeout_t acquire_period)
{
    OS::sleep(acquire_period);
    TProfiler::process_data();
    printf("------------------------------\n");
    for(uint_fast8_t i = 0; i < OS::PROCESS_COUNT; ++i)
    {
        size_t slack = OS::get_proc(i)->stack_slack() * sizeof(stack_item_t);
        double cpu = Profiler.get_result(i)/100.0;
        printf("Proc pr%d | CPU %5.2f | Slack %d\n", scmRTOS_PRIORITY_ORDER ? scmRTOS_PROCESS_COUNT-i : i, cpu, slack);
    }
}

