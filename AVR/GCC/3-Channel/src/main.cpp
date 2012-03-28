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
//*     Version: 3.11
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

#include <pin_macros.h>

#include <scmRTOS.h>


//---------------------------------------------------------------------------
//	"Hello, scope!" pins (ATmega168)
#define TIMER1_ISR D,5,H	// pin 11 @ DIP
#define TIMER1_TO_PROC1 B,0,H	// pin 14 @ DIP
#define PROC1 B,1,H	// pin 15 @ DIP
#define PROC2 B,2,H	// pin 16 @ DIP
#define PROC3 B,3,H	// pin 17 @ DIP
#define TIMER_HOOK B,4,H	// pin 18 @ DIP
#define IDLE_HOOK B,5,H	// pin 19 @ DIP
#define SLON_TRUNK C,5,H	// pin 28 @ DIP


//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 120> TProc1;
typedef OS::process<OS::pr1, 160> TProc2;
typedef OS::process<OS::pr2, 120> TProc3;

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

//---------------------------------------------------------------------------
dword tick_count;                // global variable for OS::GetTickCount testing


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
    TCCR1B = (1 << WGM12) | (1 << CS10);	// CTC mode, clk/1
    OCR1A   = 10005;
    TIMSK1  |= (1 << OCIE1A);  // Timer1 OC interrupt enable

    // Start System Timer
    TCCR0B = (1 << CS01) | (1 << CS00);	// clk/64
    TIMSK0 |=  (1 << TOIE0);

    DRIVER(TIMER1_ISR,OUT);
    DRIVER(TIMER_HOOK,OUT);
    DRIVER(IDLE_HOOK,OUT);
    DRIVER(SLON_TRUNK,OUT);

    OS::Run();
}


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc1::Exec()
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
} // TProc1::Exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc2::Exec()
{
    DRIVER(PROC2,OUT);
    for(;;)
    {
        tick_count = OS::GetTickCount();
        OFF(PROC2);
        Sleep( static_cast<word>(tick_count) & 0x200  ?  1  :  2  );
        ON(PROC2);
        SlonQueue.push(&Indian);
    }
} // TProc2::Exec()

} // namespace OS


//---------------------------------------------------------------------------
namespace OS {

template<> OS_PROCESS void TProc3::Exec()
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
