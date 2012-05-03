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
//*     Version: 4.00
//*
//*     $Revision: 445 $
//*     $Date:: 2011-09-29 #$
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
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2012
//*     LPC17xx samples by Oleksandr O. Redchuk aka ReAl, Copyright (c) 2012

#include "LPC17xx.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_timer.h"

#include <scmRTOS.h>

#include "Pin.h"

//---------------------------------------------------------------------------
//      Sample compilation options
//
//  See http://real.kiev.ua/scmrtos/1-eventflag/ for details (in Ukrainian, Russian and English)
//
//  PROC2_HIGHER_THAN_PROC3
//  1 - Proc2 ef.signal() wakes up Proc3, but Proc3 becomes active after Proc2 sleep().
//  Execution path:
//      IdleProcess -> Proc2 -> Proc3 -> IdleProcess
//  0 - Proc2 ef.signal() wakes up Proc3 and switches execution from Proc2 to Proc3.
//  Execution path:
//      IdleProcess -> Proc2 -> Proc3 -> Proc2 -> IdleProcess
//
//  PROC2_LONG_PULSE
//  1 - PROC2 pulse long. Good scope waveforms for 5-ms timebase (PROC2-PROC3 "generator" overview)
//  0 - PROC2 pulse short, defined by ef.Signal() execution time and PROC2-PROC3 task switching.

#define PROC2_HIGHER_THAN_PROC3 1
#define PROC2_LONG_PULSE 0

//---------------------------------------------------------------------------
//      "Hello, scope!" pins in Pin.h template notation.
//
//  SK_MLPC1768 board pins

typedef Pin<'0', 0,'H',OUTPUT>	TIMER_ISR;       /* X5.pin10 */
typedef Pin<'0', 1,'H',OUTPUT>	TIMER_TO_PROC1;  /* X5.pin9  */
typedef Pin<'0',10,'H',OUTPUT>	PROC1;           /* X5.pin12 */
typedef Pin<'0',11,'H',OUTPUT>	PROC2;           /* X5.pin11 */
typedef Pin<'2',13,'H',OUTPUT>	PROC3;           /* X5.pin14 */
typedef Pin<'2',12,'H',OUTPUT>	TIMER_HOOK;      /* X5.pin13 */
typedef Pin<'2',11,'H',OUTPUT>	IDLE_HOOK;       /* X5.pin16 */


//---------------------------------------------------------------------------
//
//      Process types
//
// demonstrate process switching from Proc2 to Proc3 in sleep() or ef.signal() call
#if PROC2_HIGHER_THAN_PROC3
# define PROC2_PRIO OS::pr1
# define PROC3_PRIO OS::pr2
#else
# define PROC2_PRIO OS::pr2
# define PROC3_PRIO OS::pr1
#endif

typedef OS::process<OS::pr0, 300> TProc1;
typedef OS::process<PROC2_PRIO, 300> TProc2;
typedef OS::process<PROC3_PRIO, 300> TProc3;

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

//---------------------------------------------------------------------------
//
//      Event Flags to test
//
OS::TEventFlag ef;
OS::TEventFlag TimerEvent;

tick_count_t tick_count;        // global variable for OS::GetTickCount testing

int main()
{
    // Configure IO pins with default mode and selector
    TIMER_ISR::Init();
    TIMER_TO_PROC1::Init();
    PROC1::Init();
    PROC2::Init();
    PROC3::Init();
    TIMER_HOOK::Init();
    IDLE_HOOK::Init();

    // Setup timer for TimerEvent generation
    // Timer 1, 25 MHz timer clock.
    // Interrupt rate slightly higher than 200 Hz for better scope view
    LPC_SC->PCONP   |= CLKPWR_PCONP_PCTIM1;
    LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & ~(0x03 << CLKPWR_PCLKSEL_TIMER1))
                     | (CLKPWR_PCLKSEL_CCLK_DIV_4 << CLKPWR_PCLKSEL_TIMER1);
    LPC_TIM1->CTCR = 0;

    LPC_TIM1->PR = 0;
    LPC_TIM1->PC = 0;
    LPC_TIM1->TC = 0;
    LPC_TIM1->MR0 = SYSTICKFREQ / 4 / 200.4 - 1;
    LPC_TIM1->MCR = TIM_RESET_ON_MATCH(0) | TIM_INT_ON_MATCH(0);
    LPC_TIM1->EMR = TIM_EM_SET(0, TIM_EM_TOGGLE);
    LPC_TIM1->TCR = (1 << 0);

    NVIC->IP[ TIMER1_IRQn ] = 0x80; // Middle priority
    NVIC->ISER[0] = (1 << TIMER1_IRQn);

    // run
    OS::run();
}

namespace OS
{
    template <>
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
            PROC1::Off();
            TimerEvent.wait();
            PROC1::On();
            TIMER_TO_PROC1::Off();
        }
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
        for(;;) {
            sleep(9);
            PROC2::On();
#if PROC2_LONG_PULSE
            sleep(1);
#endif
            ef.signal();
            PROC2::Off();
        }
    }

    template <>
    OS_PROCESS void TProc3::exec()
    {
        for(;;) {
            ef.wait();
            tick_count = OS::get_tick_count();
            PROC3::On();
            sleep( tick_count & 0x800  ?  2  :  3  );
            PROC3::Off();
        }
    }
}


//---------------------------------------------------------------------------
#if  scmRTOS_SYSTIMER_HOOK_ENABLE
void OS::system_timer_user_hook()
{
    TCritSect cs;
    TIMER_HOOK::Cpl();
}
#endif

//---------------------------------------------------------------------------
#if  scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
    TCritSect cs;
    IDLE_HOOK::Cpl();
}
#endif

OS_INTERRUPT void TIMER1_IRQHandler()
{
    OS::TISRW ISRW;
    
    // Clear all sources for the timer (we used just one in this simple sample)
    LPC_TIM1->IR = 0x3F;

    TIMER_ISR::On();
    TIMER_TO_PROC1::On();
    TimerEvent.signal_isr();
    TIMER_ISR::Off();
}


