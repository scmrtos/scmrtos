//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M0+
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision: 559 $
//*     $Date:: 2012-12-03 #$
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
//*     GCC STM32L0XX Samples by Anton B. Gusev aka AHTOXA, Copyright (c) 2015

#include "pin.h"
#include <scmRTOS.h>

// Process types
typedef OS::process<OS::pr0, 300> TProc0;
typedef OS::process<OS::pr1, 300> TProc1;
typedef OS::process<OS::pr2, 300> TProc2;

// Process objects
TProc0 Proc0;
TProc1 Proc1;
TProc2 Proc2;

// STM32 NUCLEO-L053R8 board pins
typedef Pin<'A', 5> GreenLED;
typedef Pin<'C', 13> ButtonPin;
typedef Pin<'B', 8> Pin1;   // marked as "SCL/D15" on NUCLEO-L053R8 board
typedef Pin<'A', 9> Pin2;   // marked as "D8" on NUCLEO-L053R8 board

// Event Flags to test
OS::TEventFlag ef;
OS::TEventFlag timerEvent;

int main()
{
	// configure IO pins
	GreenLED::Mode(OUTPUT);
	GreenLED::Off();
	Pin1::Mode(OUTPUT);
	Pin1::Off();
	Pin2::Mode(OUTPUT);
	Pin2::Off();

	// run
	OS::run();
}

namespace OS
{
template<>
OS_PROCESS void TProc0::exec()
{
	for (;;)
	{
		ef.wait();
		Pin1::Off();
	}
}

template<>
OS_PROCESS void TProc1::exec()
{
	for (;;)
	{
		timerEvent.wait();
		Pin2::Off();
	}
}

template<>
OS_PROCESS void TProc2::exec()
{
	static int counter = 1000;
	for (;;)
	{
		if (!--counter)
			counter = 1000;
		GreenLED::On(counter < 50);
		sleep(1);
		Pin1::On();
		ef.signal();
	}
}
}

void OS::system_timer_user_hook()
{
	Pin2::On();
	timerEvent.signal_isr();
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
