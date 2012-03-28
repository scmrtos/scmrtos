//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: LPC2xxx (NXP)
//*
//*     TOOLKIT:   GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 3.11
//*
//*     $Revision: 256 $
//*     $Date:: 2010-01-22 #$
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2012
//*     lpc2xxx GCC parts by Anton B. Gusev aka AHTOXA, Copyright (c) 2010-2012

#include <scmRTOS.h>

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 800> TProc1;
typedef OS::process<OS::pr1, 800> TProc2;
typedef OS::process<OS::pr2, 800> TProc3;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------
dword tick_count;				// global variable for OS::GetTickCount testing

//---------------------------------------------------------------------------
//
//      Test objects
//
struct TMamont					//  data type for sending by message
{
	enum TSource
	{
		PROC_SRC,
		ISR_SRC
	}
	src;
	int data;
};

OS::message<TMamont> MamontMsg;  // OS::message object

int main()
{
	OS::Run();
}

namespace OS
{
	template <>
	OS_PROCESS void TProc1::Exec()
	{
		for(;;)
		{
			MamontMsg.wait();				// wait for message
			TMamont Mamont = MamontMsg;		// read message content into local TMamont variable

			if (Mamont.src == TMamont::PROC_SRC)
			{
				IOSET0 = (1 << 11);			// show that message received from other process
			}
			else
			{
				IOSET0 = (1 << 11);			// show that message received from isr
				IOCLR0 = (1 << 11);
				IOSET0 = (1 << 11);
			}
				// turn off led2
		}
	}

	template <>
	OS_PROCESS void TProc2::Exec()
	{
		for(;;)
		{
			tick_count += OS::GetTickCount();
			Sleep(100);
        }
    }

	template <>
	OS_PROCESS void TProc3::Exec()
	{
		for (;;)
		{
			Sleep(1);
			TMamont m;						// create message content
			m.src  = TMamont::PROC_SRC;
			m.data = 5;
			MamontMsg = m;					// put the content to the OS::message object
			IOCLR0 = (1 << 11);				// turn LED on
			MamontMsg.send();				// send the message
		}
	}
}

void OS::SystemTimerUserHook() { }

void OS::IdleProcessUserHook() { }

OS_INTERRUPT void Timer_ISR()
{
	OS::TISRW ISRW;

	T1IR = T1IR;						// clear int flag

	TMamont m;							// create message content
	m.src  = TMamont::ISR_SRC;
	m.data = 10;
	MamontMsg = m;						// put the content to the OS::message object
	IOCLR0 = (1 << 11);					// turn LED on
	MamontMsg.sendISR();				// send the message

	IRQ_DONE();
}

#define	OSC             (12000000UL)
#define	CCLK            (OSC * 5)
#define	PCLK            (CCLK)

#define	RTOS_TICK_RATE	(1000)			// Hz
#define	TEST_TIMER_RATE	(100)			// Hz

#define PLLSTAT_PLOCK	(0x400)
#define VIC_TIMER1		(5)

#define PCONP_PCTIM0    (0x00000002)
#define PCONP_PCTIM1    (0x00000004)


#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
extern "C" void ContextSwitcher_ISR();
#endif

extern "C" int  __low_level_init(void)
{
	MEMMAP = 1;

	PLLCFG = (1<<5) | (CCLK / OSC - 1);     // psel = 1; msel = (CCLK / OSC - 1)
	PLLFEED = 0xAA;
	PLLFEED = 0x55;

	PLLCON = 1;                             // PLLE=1, Enable PLL
	PLLFEED = 0xAA;
	PLLFEED = 0x55;

	while(!(PLLSTAT & PLLSTAT_PLOCK)) ;     // wait for lock

	PLLCON = 3;                             // PLLC = 1, PLLE = 1, Connect PLL
	PLLFEED = 0xAA;
	PLLFEED = 0x55;

	VPBDIV = 1;                             // pclk = cclk

	MAMCR=0x02;
	MAMTIM=0x04;

// ***************************************************************************
// ** GPIO
// ***************************************************************************
	IODIR0  |= (1<<10) | (1<<11);            // Test pins (P0.10 and P0.11) -> output
	IOSET0  = (1<<10) | (1<<11);             // leds off

// ***************************************************************************
// ** TIMER0
// ***************************************************************************
//  RTOS system timer
	PCONP |= PCONP_PCTIM0;
	T0IR = 0xFFFFFFFF;                      // clear int requests

	T0PR = 0;								// prescaler
	T0MR0 = PCLK / RTOS_TICK_RATE;          // int at TICK_RATE
	T0MCR = (1UL<<1) | (11UL<<0);           // MR0INT = 1, MR0RES = 1
	T0TCR = (1UL<<0);                       // CE = 1, enable timer

// ***************************************************************************
// ** TIMER1
// ***************************************************************************
//   EventFlag test timer
	PCONP |= PCONP_PCTIM1;
	T1IR = 0xFFFFFFFF;                      // clear int requests

	T1PR = 0;								// prescaler
	T1MR0 = PCLK / TEST_TIMER_RATE;          // int at TICK_RATE
	T1MCR = (1UL<<1) | (11UL<<0);           // MR0INT = 1, MR0RES = 1
	T1TCR = (1UL<<0);                       // CE = 1, enable timer

//***************************************************************************
// ** VIC
//***************************************************************************
	// initialize VIC
	VICIntEnClr = 0xFFFFFFFF;
	VICVectAddr = 0;
	VICIntSelect = 0;

	// Set periodical timer interrupt with highest priority
	VICVectAddr0 = (dword)Timer_ISR;
	VICVectCntl0 = (1<<5) | VIC_TIMER1;

	// Set system timer interrupt vector with little bit higher priority than context switcher
	VICVectAddr14 = (dword)OS::SystemTimer_ISR;
	VICVectCntl14 = (1<<5) | SYSTEM_TIMER_INT;
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
	// Set context switcher interrupt handler with lowest possible priority
	VICVectAddr15 = (dword)ContextSwitcher_ISR;
	VICVectCntl15 = (1<<5) | CONTEXT_SWITCH_INT;

	VICIntEnable =  (1UL<<SYSTEM_TIMER_INT) | (1UL<<CONTEXT_SWITCH_INT) | (1UL<<VIC_TIMER1);
#else
	VICIntEnable =  (1UL<<SYSTEM_TIMER_INT) | (1UL<<VIC_TIMER1);
#endif

	VICVectAddr = 0;    // Reset VIC logic
	return 1;
}

