//********************************************************************************
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
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
//*
//*     =================================================================
//*     scmRTOS is free software; you can redistribute it and/or
//*     modify it under the terms of the GNU General Public License
//*     as published by the Free Software Foundation; either version 2
//*     of the License, or (at your option) any later version.
//*
//*     This program is distributed in the hope that it will be useful,
//*     but WITHOUT ANY WARRANTY; without even the implied warranty of
//*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//*     GNU General Public License for more details.
//*
//*     You should have received a copy of the GNU General Public License
//*     along with this program; if not, write to the Free Software
//*     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//*     MA  02110-1301, USA.
//*     =================================================================
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//********************************************************************************

//---------------------------------------------------------------------------
#include <scmRTOS.h>
//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 120, 32> TProc1;
typedef OS::process<OS::pr1, 160, 32> TProc2;
typedef OS::process<OS::pr2, 120, 32> TProc3;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------
dword T;                         // global variable for OS::GetTickCount testing
                                 //

struct TMamont                   //  data type for sanding by message
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

    ACSR |= (1 << ACBG) | (1 << ACIE); /* Ref ON, IE ON */  
    DDRB |= (1 << 3);                  /* AIN1*/


    OS::Run();
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc1::Exec()
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
OS_PROCESS void TProc2::Exec()
{
    for(;;)
    {
        Sleep(20);
    }
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc3::Exec()
{
    for(;;)
    {
        Sleep(1);
        TMamont m;           // create message content

        m.src  = TMamont::PROC_SRC;
        m.data = 5;
        MamontMsg = m;       // put the content to the OS::message object
        PORTB |= (1 << 4);
        MamontMsg.send();    // send the message
    }
}
//---------------------------------------------------------------------------
void OS::SystemTimerUserHook() { }
//---------------------------------------------------------------------------
void OS::IdleProcessUserHook() { }
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
    MamontMsg.sendISR();    // send the message
}
//---------------------------------------------------------------------------


