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


//---------------------------------------------------------------------------
//      Sample target
//  The sample is intended for following AVR microcontrollers:
//      atmega48..atmega328
//      atmega64, atmega128
//      atmega640..atmega2561
//  Some changes in register names may be needed for other AVRs.
//
//  The sample is also intended to show how to use scmRTOS v3.xx oriented
//  sources with scmRTOS v4.00
//  1. Add
//      #include "scmRTOS_310_compat.h"
//     into scmRTOS_CONFIG.h
//  2. Rename process functions from Exec() to exec()
//

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
#define SLON_TRUNK      C,5,H


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
tick_count_t tick_count;          // global variable for OS::GetTickCount testing


//------------------------------------------------------------------------------
//
//   Message "body"
//
//
class TSlon
{
public:
    TSlon() { }
    virtual void eat() = 0;      // feed the slon. For non-russians: slon == elephant ;)
};

//------------------------------------------------------------------------------
class TAfricanSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;

        ON(SLON_TRUNK);
        OFF(SLON_TRUNK);
    }
};

//------------------------------------------------------------------------------
class TIndianSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;

        ON(SLON_TRUNK);
        OFF(SLON_TRUNK);
        ON(SLON_TRUNK);
        OFF(SLON_TRUNK);
    }
};

//------------------------------------------------------------------------------

TAfricanSlon African;
TIndianSlon  Indian;

OS::channel<TSlon*, 8> SlonQueue; // OS::channel object for 8 'TSlon*' items

OS::TEventFlag Timer1_Ovf;

//---------------------------------------------------------------------------
int main()
{
    TCCR1B = (1 << WGM12) | (1 << CS10);    // CTC mode, clk/1
    OCR1A   = 10005;
    TIMER1_IE_REG = (1 << OCIE1A); // Timer1 OC interrupt enable

    // Start System Timer
    TIMER0_CS_REG  = (1 << CS01) | (1 << CS00); // clk/64
    TIMER0_IE_REG |= (1 << TOIE0);

    DRIVER(TIMER1_ISR,OUT);
    DRIVER(TIMER_HOOK,OUT);
    DRIVER(IDLE_HOOK,OUT);
    DRIVER(SLON_TRUNK,OUT);

    OS::Run();
}


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc1::exec()
{
    DRIVER(PROC1,OUT);
    DRIVER(TIMER1_TO_PROC1,OUT);
    for(;;)
    {
        OFF(PROC1);
        Timer1_Ovf.Wait();
        ON(PROC1);
        OFF(TIMER1_TO_PROC1);
        SlonQueue.push(&African);
    }
} // TProc1::exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc2::exec()
{
    DRIVER(PROC2,OUT);
    for(;;)
    {
        tick_count = OS::GetTickCount();
        OFF(PROC2);
        Sleep( static_cast<uint16_t>(tick_count) & 0x200  ?  1  :  2  );
        ON(PROC2);
        SlonQueue.push(&Indian);
    }
} // TProc2::exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> void TProc3::exec()
{
    DRIVER(PROC3,OUT);
    for(;;)
    {
        //--------------------------------------------------
        //
        //            Channel test
        //
        //
        //     Get data through channel
        //
        TSlon *p;
        OFF(PROC3);
        SlonQueue.pop(p);     // get pointer from queue
        ON(PROC3);
        p->eat();             // feed the appropriate Slon
    }
} // TProc3::exec()

} // namespace OS


//---------------------------------------------------------------------------
#if scmRTOS_SYSTIMER_HOOK_ENABLE
void OS::SystemTimerUserHook()
{
#if  scmRTOS_SYSTIMER_NEST_INTS_ENABLE  &&  !PORT_TOGGLE_BY_PIN_WRITE
    TCritSect cs;
#endif
    CPL(TIMER_HOOK);
}
#endif // scmRTOS_SYSTIMER_HOOK_ENABLE

//---------------------------------------------------------------------------
#if scmRTOS_IDLE_HOOK_ENABLE
void OS::IdleProcessUserHook()
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

    Timer1_Ovf.SignalISR();

    OFF(TIMER1_ISR);
}

//------    end of file  main.cpp   -------------------------------------------

