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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007-2012

//---------------------------------------------------------------------------
#include <avr/io.h>

#include "pin_macros.h"

#include <scmRTOS.h>

#include "debug.h"

//---------------------------------------------------------------------------
//      Sample target
//  The sample is intended for following AVR microcontrollers:
//      atmega48..atmega328
//      atmega640..atmega2561
//  Some changes in register names may be needed for other AVRs.
//  Controller must be clocked by crystal because of UART usage.
//  Recommended frequencies are 7.3728 MHz and 14.7456 MHz 

//---------------------------------------------------------------------------
// System Timer divider for F_CPU
// CTC mode: clk/64, 1000 Hz interrupt rate
#define SYSTEM_TIMER_DIVIDER (64*1000U)


//---------------------------------------------------------------------------
//  "Hello, scope!" pins in pin_macros.h notation.
#define TIMER2_ISR      D,5,H
#define TIMER2_TO_PROC1 B,0,H
#define PROC1           B,1,H
#define PROC2           B,2,H
#define PROC3           B,3,H
#define TIMER_HOOK      C,4,H
#define IDLE_HOOK       C,5,H

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

//---------------------------------------------------------------------------
tick_count_t tick_count;        // global variable for OS::GetTickCount testing

OS::TEventFlag Timer2_Ovf;  // set in TIMER1_COMPA_vect(), waited in Proc1
OS::TEventFlag ef;      // set in Proc3, waited in Proc2

//---------------------------------------------------------------------------
int main()
{
    // Start System Timer
    OCR0A   = (F_CPU + SYSTEM_TIMER_DIVIDER/2) / SYSTEM_TIMER_DIVIDER;
    TCCR0A  = (1 << WGM01);
    TCCR0B  = (1 << CS01) | (1 << CS00); 
    TIMSK0 |= (1 << OCIE0A);

    // Start Timer 2 -- Free running, clk/64
    // wobbles with Timer 1 OC1A intewrrupt (System Timer)
    TCCR2A  = 0;
    TCCR2B  = (1 << CS22); 
    TIMSK2 |= (1 << TOIE2);
#if scmRTOS_SYSTIMER_HOOK_ENABLE
    DRIVER(TIMER_HOOK,OUT);
#endif
#if scmRTOS_IDLE_HOOK_ENABLE
    DRIVER(IDLE_HOOK,OUT);
#endif
    //
    OS::run();
}

/**
 * Waste some time (payload emulation).
 * Execution time approximately (64 * count) CPU clocks
 */
void waste_time(uint8_t count)
{
    uint8_t start = TCNT2;
    while ( (uint8_t)(TCNT2 - start) < count ) ;
}

/**
 * Stack hungry function.
 * Eats approximately (8 * count) bytes from caller process stack.
 * Called by different processes some time after start.
 * Stack usage changes can be observed in debug terminal.
 */
NOINLINE uint8_t waste_stack(uint_fast8_t count)
{
	volatile uint8_t arr[4];
	arr[0] = TCNT0;	// any volatile register
	arr[1] = TCNT0;
	arr[2] = TCNT0;
	arr[3] = count ? waste_stack(count - 1) : TCNT0;
	return arr[0] ^ arr[1] ^ arr[2] ^ arr[3];
}


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc1::exec()
{
    const int max_request = 10;
    const int increment_period = 1000;
    int increment_div = increment_period;
    uint8_t request = 0;

    DRIVER(PROC1,OUT);
    DRIVER(TIMER2_ISR,OUT);
    DRIVER(TIMER2_TO_PROC1,OUT);

    for(;;) {
        OFF(PROC1);
        Timer2_Ovf.wait();
        ON(PROC1);
        OFF(TIMER2_TO_PROC1);
        if (request < max_request) {
            waste_stack(request);
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

template<> OS_PROCESS void TProc2::exec()
{
    DRIVER(PROC2,OUT);
    for(;;) {
        sleep(4);
        ON(PROC2);
        ef.signal();
        uint8_t request = (OS::get_tick_count() / 1024) % 8;
        waste_time(request * 10);
        OFF(PROC2);
    }
} // TProc2::exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc3::exec()
{
    DRIVER(PROC3,OUT);
    for(;;) {
        OFF(PROC3);
        ef.wait();
        ON(PROC3);
        waste_time(50);
    }
} // TProc3::exec()

} // namespace OS


//---------------------------------------------------------------------------
#if scmRTOS_SYSTIMER_HOOK_ENABLE
void OS::system_timer_user_hook()
{
#if  scmRTOS_SYSTIMER_NEST_INTS_ENABLE  &&  !PORT_TOGGLE_BY_PIN_WRITE
    TCritSect cs;
#endif
    CPL(TIMER_HOOK);
}
#endif // scmRTOS_SYSTIMER_HOOK_ENABLE

//---------------------------------------------------------------------------
#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
#if  !PORT_TOGGLE_BY_PIN_WRITE
    TCritSect cs;
#endif
    CPL(IDLE_HOOK);
}
#endif // scmRTOS_IDLE_HOOK_ENABLE

//---------------------------------------------------------------------------
OS_INTERRUPT void TIMER2_OVF_vect()
{
    ON(TIMER2_ISR);
    ON(TIMER2_TO_PROC1);

    OS::TISRW ISRW;

    Timer2_Ovf.signal_isr();

    OFF(TIMER2_ISR);
}

//------    end of file  main.cpp   -------------------------------------------
