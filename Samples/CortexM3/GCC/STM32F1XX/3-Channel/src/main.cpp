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
tick_count_t tick_count;         // global variable for OS::GetTickCount testing

//---------------------------------------------------------------------------
//
//      IO Pins
//
Pin<'B', 0> PB0;
Pin<'B', 1> PB1;
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

class TAfricanSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;
        PB0.On();
        PB0.Off();
        PB0.On();
        PB0.Off();
    }
};

class TIndianSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;
        PB0.On();
        PB0.Off();
    }
};

TAfricanSlon African;   
TIndianSlon  Indian;    
    
OS::channel<TSlon*, 8> SlonQueue; // OS::channel object for 8 'TSlon*' items

OS::TEventFlag TimerEvent;


int main()
{
    // configure IO pins
    PB0.Direct(OUTPUT);
    PB0.Off();
    PB1.Direct(OUTPUT);
    PB1.Off();

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
            TimerEvent.wait();
            SlonQueue.push(&African);
        }
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
        for(;;)
        {
            tick_count += OS::get_tick_count();
             
            sleep(1);
            SlonQueue.push(&Indian);
        }
    }

    template <>
    OS_PROCESS void TProc3::exec()
    {
        for (;;)
        {
            //--------------------------------------------------
            //
            //            Channel test
            //
            //
            //     Get data through channel
            //
            TSlon *p;
            SlonQueue.pop(p);     // get pointer from queue
            p->eat();             // feed the appropriate Slon
        }
    }
}

void OS::system_timer_user_hook()
{
    PB1.Cpl();
    TimerEvent.signal_isr();
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
