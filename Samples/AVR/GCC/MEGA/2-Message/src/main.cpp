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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2008-2012

//---------------------------------------------------------------------------
#include <avr/io.h>

#include "pin_macros.h"

#include <scmRTOS.h>

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
// for analog comparator initialisation in main()
#include <util/delay.h>
#endif


//---------------------------------------------------------------------------
//      Sample target
//  The sample is intended for following AVR microcontrollers:
//      atmega48..atmega328
//      atmega64, atmega128
//      atmega640..atmega2561
//  Some changes in register names may be needed for other AVRs.

#if defined(TIMSK1)
#  define TIMER1_IE_REG TIMSK1
#elif defined(TIMSK)
#  define TIMER1_IE_REG TIMSK
#else
#  error "Timer1 interrupt mask register not defined"
#endif

//---------------------------------------------------------------------------
//  "Hello, scope!" pins in pin_macros.h notation.
#define TIMER1_ISR      D,5,H
#define TIMER1_TO_PROC1 B,0,H
#define PROC1           B,1,H
#define PROC2           B,2,H
#define PROC3           B,3,H
#define TIMER_HOOK      B,4,H
#define IDLE_HOOK       B,5,H
#define MAMONT_TRUNK    C,5,H


//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 120> TProc1;
typedef OS::process<OS::pr1, 160> TProc2;
typedef OS::process<OS::pr2, 120> TProc3;

// Explicit specialization of function must precede its first use. But ...
// avoid GCC bug ( http://gcc.gnu.org/bugzilla/show_bug.cgi?id=15867 )
#if 0
    template<> void TProc1::exec();
    template<> void TProc2::exec();
    template<> void TProc3::exec();
#endif

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

//---------------------------------------------------------------------------

struct TMamont                   //  data type for sanding by message
{
    enum TSource
    {
        PROC_SRC,
        ISR_SRC
    }
    src;
    int data;                    //
};                               //

TMamont Mamont;                  // global test object for recieve data from message

OS::message<TMamont> MamontMsg;  // OS::message object

//---------------------------------------------------------------------------
int main()
{
    TCCR1B = (1 << WGM12) | (1 << CS10);    // CTC mode, clk/1
    OCR1A  = 40000U;
    TIMER1_IE_REG = (1 << OCIE1A); // Timer1 OC interrupt enable

    // Start System Timer
    TIMER0_CS_REG  = (1 << CS01) | (1 << CS00); // clk/64
    TIMER0_IE_REG |= (1 << TOIE0);

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    // Setup analog comparator as software interrupt source
    #if PORT_TOGGLE_BY_PIN_WRITE    // see pin_macros.h for PORT_TOGGLE_BY_PIN_WRITE definition and sing
    ACSR = (1 << ACBG);     // Ref ON, interrupt on both edges
    #else
    ACSR = (1 << ACBG) | (1 << ACIS1);  // Ref ON, falling edge
    #endif
    DRIVER(RAISE_PIN,OUT);  // AIN1 - output
    // analog comparator propagation and synchronization delay
    _delay_us(2);
    ACSR |= (1 << ACI); // needed for chips with improved sbi/cbi behavior
    ACSR |= (1 << ACIE);
#endif

    DRIVER(TIMER1_ISR,OUT);
    DRIVER(TIMER_HOOK,OUT);
    DRIVER(IDLE_HOOK,OUT);
    DRIVER(MAMONT_TRUNK,OUT);
    //
    OS::run();
}


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc1::exec()
{
    DRIVER(PROC1,OUT);
    DRIVER(TIMER1_TO_PROC1,OUT);
    for(;;) {
      	//--------------------------------------------------
        //            Message test
        //
        //     Receive data as message
        //
        OFF(PROC1);
        MamontMsg.wait();			// wait for message
        ON(PROC1);
        OFF(TIMER1_TO_PROC1);
        MamontMsg.out(Mamont);		// read message content to global test object
        if(Mamont.src == TMamont::PROC_SRC) {
            OFF(MAMONT_TRUNK);
        } else {
            OFF(MAMONT_TRUNK);
            ON(MAMONT_TRUNK);
            OFF(MAMONT_TRUNK);
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
        OFF(PROC2);
        sleep(20);
        ON(PROC2);
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
        sleep(1);
        ON(PROC3);
        TMamont m;           // create message content
        m.src  = TMamont::PROC_SRC;
        m.data = 5;
        MamontMsg = m;       // put the content to the OS::message object
        ON(MAMONT_TRUNK);
        MamontMsg.send();    // send the message
    }
} // TProc3::exec()

} // namespace OS


//---------------------------------------------------------------------------
#if scmRTOS_IDLE_HOOK_ENABLE
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
OS_INTERRUPT void TIMER1_COMPA_vect()
{
    ON(TIMER1_ISR);
    ON(TIMER1_TO_PROC1);

    OS::TISRW_SS ISRW;

    ENABLE_NESTED_INTERRUPTS();

    //--------------------------------------------------
    //            Message test
    //
    //     Send data as message
    //
    TMamont m;           // create message content

    m.src  = TMamont::ISR_SRC;
    m.data = 10;
    MamontMsg = m;       // put the content to the OS::message object
    ON(MAMONT_TRUNK);
    MamontMsg.send_isr();    // send the message

    OFF(TIMER1_ISR);
}

//------    end of file  main.cpp   -------------------------------------------

