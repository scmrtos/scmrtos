//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   GCC (GPL)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 3.05
//*
//*     $Revision: 196 $
//*     $Date:: 2008-06-19 #$
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009

#include "stm32f10x.h"
#include "pin.h"
#include <scmRTOS.h>

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 300> TProc1;
typedef OS::process<OS::pr1, 300> TProc2;
typedef OS::process<OS::pr2, 300> TProc3;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------
//
//      IO Pins
//
Pin<'B', 0> PB0;
Pin<'B', 1> PB1;
//---------------------------------------------------------------------------
//
//      Event Flags to test
//
OS::TEventFlag ef;
OS::TEventFlag TimerEvent;

int main()
{
	// configure IO pins
	PB0.Direct(OUTPUT);
	PB0.Off();
	PB1.Direct(OUTPUT);
	PB1.Off();

	// run
	OS::Run();
}

namespace OS
{
	template <>
	OS_PROCESS void TProc1::Exec()
	{
		for(;;)
		{
			ef.Wait();
			PB0.Off();
		}
	}

	template <>
	OS_PROCESS void TProc2::Exec()
	{
		for(;;)
		{
			TimerEvent.Wait();
			PB1.Off();
        }
    }

	template <>
	OS_PROCESS void TProc3::Exec()
	{
		for (;;)
		{
			Sleep(1);
			PB0.On();
			ef.Signal();
		}
	}
}

void OS::SystemTimerUserHook()
{
	OS::TISRW ISRW;
	PB1.On();
	TimerEvent.SignalISR();
}
