//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   avr-gcc (GNU)
//*
//*     PURPOSE:   avr-gcc Port Test File
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007

//---------------------------------------------------------------------------
#include <avr/io.h>
#include <util/delay.h>

#include <pin_macros.h>

#include <scmRTOS.h>


//---------------------------------------------------------------------------
//	Sample compiling options
//
//  PROC2_HIGHER_THAN_PROC3
//  1 -	Proc2 ef.signal() wakes up Proc3, but Proc3 becomes active after Proc2 Sleep().
//	Execution path:
//		IdleProcess -> Proc2 -> Proc3 -> IdleProcess
//  0 -	Proc2 ef.signal() wakes up Proc3 and switch execution from Proc2 to Proc3.
//	Execution path:
//		IdleProcess -> Proc2 -> Proc3 -> Proc2 -> IdleProcess
//
//  PROC2_LONG_PULSE
//  1 -	PROC2 pulse long. Good scope waveforms for 5-ms timebase (PROC2-PROC3 "generator" overview)
//  0 - PROC2 pulse short, defined by ef.Signal() execution time and PROC2-PROC3 task switching.

#define PROC2_HIGHER_THAN_PROC3 0
#define PROC2_LONG_PULSE 0

//---------------------------------------------------------------------------
//	"Hello, scope!" pins (ATmega168)
#define TIMER1_ISR D,5,H	// pin 11 @ DIP
#define TIMER1_TO_PROC1 B,0,H	// pin 14 @ DIP
#define PROC1 B,1,H	// pin 15 @ DIP
#define PROC2 B,2,H	// pin 16 @ DIP
#define PROC3 B,3,H	// pin 17 @ DIP
#define TIMER_HOOK B,4,H	// pin 18 @ DIP
#define IDLE_HOOK B,5,H	// pin 19 @ DIP


//---------------------------------------------------------------------------
//
//      Process types
//

// demonstrate process switching from Proc2 to Proc3 in Sleep() or ef.Signal() call
#if PROC2_HIGHER_THAN_PROC3
# define PROC2_PRIO OS::pr1
# define PROC3_PRIO OS::pr2
#else
# define PROC2_PRIO OS::pr2
# define PROC3_PRIO OS::pr1
#endif

typedef OS::process<OS::pr0, 100> TProc1;
typedef OS::process<PROC2_PRIO, 100> TProc2;
typedef OS::process<PROC3_PRIO, 100> TProc3;

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

//---------------------------------------------------------------------------
dword tick_count;		// global variable for OS::GetTickCount testing

OS::TEventFlag Timer1_Ovf;	// set in TIMER1_COMPA_vect(), waited in Proc1
OS::TEventFlag ef;		// set in Proc3, waited in Proc2

//---------------------------------------------------------------------------
int main()
{
	TCCR1B = (1 << WGM12) | (1 << CS10);	// CTC mode, clk/1
	OCR1A  = 40000U;
	TIMSK1 = (1 << OCIE1A);	// Timer1 OC interrupt enable

	// Start System Timer
	TCCR0B = (1 << CS01) | (1 << CS00);	// clk/64
	TIMSK0 |= (1 << TOIE0);

	DRIVER(TIMER1_ISR,OUT);
	DRIVER(TIMER_HOOK,OUT);
	DRIVER(IDLE_HOOK,OUT);
	//
	OS::Run();
}


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc1::Exec()
{
	DRIVER(PROC1,OUT);
	DRIVER(TIMER1_TO_PROC1,OUT);
	for(;;) {
		OFF(PROC1);
		Timer1_Ovf.Wait();
		ON(PROC1);
		OFF(TIMER1_TO_PROC1);
	}
} // TProc1::Exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc2::Exec()
{
	DRIVER(PROC2,OUT);
	for(;;) {
		Sleep(10);
		ON(PROC2);
#if PROC2_LONG_PULSE
		Sleep(1);
#endif
		ef.Signal();
		OFF(PROC2);
	}
} // TProc2::Exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc3::Exec()
{
	DRIVER(PROC3,OUT);
	for(;;) {
		ef.Wait();
		tick_count = OS::GetTickCount();
		ON(PROC3);
		Sleep( static_cast<word>(tick_count) & 0x200  ?  2  :  3  );
		OFF(PROC3);
	}
} // TProc3::Exec()

} // namespace OS


//---------------------------------------------------------------------------
void OS::SystemTimerUserHook()
{
#if  scmRTOS_SYSTIMER_NEST_INTS_ENABLE  &&  !PORT_TOGGLE_BY_PIN_WRITE
	TCritSect cs;
#endif
	CPL(TIMER_HOOK);
}


//---------------------------------------------------------------------------
void OS::IdleProcessUserHook()
{
#if  !PORT_TOGGLE_BY_PIN_WRITE
	TCritSect cs;
#endif
	CPL(IDLE_HOOK);
}


//---------------------------------------------------------------------------
OS_INTERRUPT void TIMER1_COMPA_vect()
{
	ON(TIMER1_ISR);
	ON(TIMER1_TO_PROC1);

	OS::TISRW_SS ISRW;

	ENABLE_NESTED_INTERRUPTS();

	Timer1_Ovf.SignalISR();

	OFF(TIMER1_ISR);
}

//------	end of file  main.cpp	-------------------------------------------
