//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   EWAVR (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 3.10
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

//---------------------------------------------------------------------------
//      Sample target
//  The sample is intended for atmega32 (atmega32A) AVR microcontroller.
//  Some changes in register names may be needed for other AVRs.

//---------------------------------------------------------------------------
#include <scmRTOS.h>
//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 120, 32> TProc1;
typedef OS::process<OS::pr1, 160, 32> TProc2;
typedef OS::process<OS::pr2, 120, 32> TProc3;

template<> void TProc1::exec();
template<> void TProc2::exec();
template<> void TProc3::exec();

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------
tick_count_t T;                  // global variable for OS::get_tick_count testing
                                 //

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

//---------------------------------------------------------------------------
int main()
{
    DDRB |= (1 << 4); 

    TCCR1B |= (1 << WGM12);   // CTC mode
    OCR1A   = 10005;          // 
    TCCR1B |= (1 << CS10);    // Timer1 run with prescaling 1
    TIMSK  |= (1 << OCIE1A);  // Timer1 OC interrupt enable

    TCCR0 = 0x03;             // Start System Timer
    TIMSK |=  (1 << TOIE0);   //

    OS::run();
}
//---------------------------------------------------------------------------
template<> void TProc1::exec()
{
    for(;;)
    {
        //--------------------------------------------------
        //            Message test
        //
        //     Receive data as message
        //
        MamontMsg.wait();             // wait for message
        MamontMsg.out(Mamont);        // read message content to global test object 
        if(Mamont.src == TMamont::PROC_SRC)
        {
            PORTB &= ~(1 << 4);
        }
        else
        {
            PORTB &= ~(1 << 4);
            PORTB |= (1 << 4);
            PORTB &= ~(1 << 4);
        }
    }
}
//---------------------------------------------------------------------------
template<> void TProc2::exec()
{
    for(;;)
    {
        sleep(20);
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::exec()
{
    for(;;)
    {
        sleep(1);
        TMamont m;           // create message content

        m.src  = TMamont::PROC_SRC;
        m.data = 5;
        MamontMsg = m;       // put the content to the OS::message object
        PORTB |= (1 << 4);
        MamontMsg.send();    // send the message
    }
}

//---------------------------------------------------------------------------
#if  scmRTOS_SYSTIMER_HOOK_ENABLE
void OS::system_timer_user_hook() { }
#endif

//---------------------------------------------------------------------------
#if  scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook() { }
#endif

//---------------------------------------------------------------------------
#pragma vector=TIMER1_COMPA_vect
OS_INTERRUPT void Timer1_period_ISR()
{
    OS::TISRW_SS ISRW;

    ENABLE_NESTED_INTERRUPTS();

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
    PORTB |= (1 << 4);
    MamontMsg.send_isr();    // send the message
}
//---------------------------------------------------------------------------

