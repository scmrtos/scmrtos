//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuC70xx (Analog Devices)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2012
//*     ADuC70xx port maintenance: Anton B. Gusev aka AHTOXA, Copyright (c) 2011-2012

#include <scmRTOS.h>
#include "pin.h"

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 200> TProc1;
typedef OS::process<OS::pr1, 200> TProc2;
typedef OS::process<OS::pr2, 200> TProc3;
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
Pin<0, 3> LED0;
Pin<0, 4> LED1;

struct TMamont                   //  data type for sending by message
{                                //
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

int main()
{
    // configure IO pins
	LED0.Direct(OUTPUT);
	LED0.Off();
	LED1.Direct(OUTPUT);
	LED1.Off();

    // run OS
    OS::run();
}

namespace OS
{
    template<>
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
            //--------------------------------------------------
            //
            //            Message test
            //
            //
            //     Receive data as message
            //
            MamontMsg.wait();                                     // wait for message
            Mamont = MamontMsg;                                   // read message content to global test object
            if(Mamont.src == TMamont::PROC_SRC)
            {
                LED0.Off();
            }
            else
            {
                LED0.Off();
                LED0.On();
                LED0.Off();
            }
        }
    }
    //---------------------------------------------------------------------------
    template<>
    OS_PROCESS void TProc2::exec()
    {
        for(;;)
        {
            sleep(20);
        }
    }
    //---------------------------------------------------------------------------
    template<>
    OS_PROCESS void TProc3::exec()
    {
        for(;;)
        {
            sleep(1);
            TMamont m;           // create message content

            m.src  = TMamont::PROC_SRC;
            m.data = 5;
            MamontMsg = m;       // put the content to the OS::message object
            LED0.On();
            MamontMsg.send();    // send the message
        }
    }
}

void OS::system_timer_user_hook()
{
	static int timer_event_counter = 5;
	if (!--timer_event_counter)
	{
		timer_event_counter = 5;
	    //--------------------------------------------------
	    //
	    //            Message test
	    //
	    //     Send data as message
	    //
	    TMamont m;           // create message content

	    m.src  = TMamont::ISR_SRC;
	    m.data = 10;
	    MamontMsg = m;       // put the content to the OS::message object
        LED0.On();
	    MamontMsg.send_isr();    // send the message
	}
}

void OS::idle_process_user_hook() { }

extern "C" void IRQ_Switch()
{
    uint32_t irq = IRQSTA;
    if(irq & SYSTEM_TIMER_INT)
    {
        OS::system_timer_isr();
    }
}
