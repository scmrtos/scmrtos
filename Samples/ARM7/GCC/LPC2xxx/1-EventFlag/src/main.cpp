//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: LPC2xxx (NXP)
//*
//*     TOOLKIT:   ARM GCC
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2010
//*     lpc2xxx GCC parts by Anton B. Gusev aka AHTOXA, Copyright (c) 2010-2011

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

OS::TEventFlag ef;
OS::TEventFlag TimerEvent;

int main()
{
    OS::run();
}

namespace OS
{
    template <>
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
            ef.wait();          // wait ef event (from Proc3)
            IOSET0 = (1 << 11); // turn off led2
        }
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
        for(;;)
        {
            TimerEvent.wait();  // wait timer event (every 0.5 sec)
            IOSET0 = (1 << 10); // turn off led1
        }
    }

    template <>
    OS_PROCESS void TProc3::exec()
    {
        for (;;)
        {
            sleep(1);               // sleep 1s
            IOCLR0 = (1 << 11);     // turn LED2 on
            ef.signal();            // signal event (bring up Proc1)
        }
    }
}

void OS::system_timer_user_hook() { }

void OS::idle_process_user_hook() { }

OS_INTERRUPT void Timer_ISR()
{
    OS::TISRW ISRW;

    T1IR = T1IR;                    // clear int flag

    IOCLR0 = (1 << 10);
    TimerEvent.signal_isr();

    IRQ_DONE();
}
