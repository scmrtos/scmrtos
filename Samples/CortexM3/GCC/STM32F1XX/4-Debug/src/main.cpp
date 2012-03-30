//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00a
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
//*     GCC port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2011

#include "stm32f10x.h"
#include "pin.h"
#include <scmRTOS.h>

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 300> TProc0;
typedef OS::process<OS::pr1, 300> TProc1;
typedef OS::process<OS::pr2, 300> TProc2;

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc0 Proc0;
TProc1 Proc1;
TProc2 Proc2;
//---------------------------------------------------------------------------
//
//      IO Pins (as for STM32-VLD development board)
//
Pin<'C', 9> green_led;
Pin<'C', 8> blue_led;

//---------------------------------------------------------------------------
//
//      Event Flags to test
//
OS::TEventFlag event;
OS::TEventFlag timer_event;

int main()
{
    // configure IO pins
    green_led.Direct(OUTPUT);
    green_led.Off();
    blue_led.Direct(OUTPUT);
    blue_led.Off();

    // run
    OS::run();
}

/**
 * Waste some time (payload emulation).
 */
NOINLINE void waste_time()
{
	for (volatile int i = 0; i < 0x3FF; i++) ;
}

/**
 * Stack angry function.
 * Eats approximately (12 * count) bytes from caller process stack.
 * Called by different processes some time after start.
 * Stack usage changes can be observed in debug terminal.
 */
NOINLINE int waste_stack(int count)
{
	volatile int arr[2];
	arr[0] = TIM2->CNT;	// any volatile register
	arr[1] = count ? waste_stack(count - 1) : TIM2->CNT;
	return (arr[0] + arr[1]) / 2;
}

namespace OS
{
    template <>
    OS_PROCESS void TProc0::exec()
    {
        for(;;)
        {
        	// green led "ON" time = context switch time (~9.6us at 24MHz)
        	event.wait();
            green_led.Off();

            // waste some time (simulate payload)
            waste_time();

            // waste some stack (increasing with time)
            tick_count_t t = (OS::get_tick_count() % 40000) / 5000;
            waste_stack(t);
        }
    }

    template <>
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
            sleep(10);
            green_led.On();
            event.signal();
            // waste time (2x Proc0)
            waste_time();
            waste_time();
        }
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
        for (;;)
        {
            timer_event.wait();

            // increase load, one step at every 5 seconds after start,
            // resetting at 8th step.
            tick_count_t t = (OS::get_tick_count() % 40000) / 5000;
            for (uint32_t i = 0; i < t; i++)
                waste_time();

            // blue led "ON" time ~ Proc2 load
            blue_led.Off();
        }
    }
}

void OS::system_timer_user_hook()
{
    static const int reload_value = 10;	// 100 Hz
    static int counter = reload_value;
    if (!--counter)
    {
        counter = reload_value;
        blue_led.On();
        timer_event.signal_isr();
    }
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
