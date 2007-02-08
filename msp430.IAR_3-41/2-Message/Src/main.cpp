//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   EW430 (IAR Systems)
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

#include <scmRTOS.h>
                  
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
#pragma diag_suppress=Pe951      // suppress return type warning 
void main()
{
    P1DIR |= (1 << 4);
    P5DIR |= (1 << 4);
    P5SEL |= (1 << 4);


    TBCTL = MC_1+ID_0+TBSSEL_2+TBCLR;     // Mode Continuous Up to CCR0, Divider/1, Source SMCLK, Reset TA
    TBCCR0  =  10000;
    TBCCTL0 &= ~CCIFG;                    // Clear flag
    TBCCTL0 |=  CCIE;                     // int. enable

    //------------------------------------------------------
    //
    //    Target platform specific actions.
    //
    //    DCO is used as source for MCLK
    //    Set internal DCO clock at max speed (~5 MHz @ 20 Deg C)
    //
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 );     
    DCOCTL  |= ( DCO0  + DCO1  + DCO2  );

    //------------------------------------------------------
    //
    //    System Timer start
    //
    //    WatchDog Timer is used as System Timer.
    //
    //    WatchDog Mode: Interval Timer Mode
    //    Enable Watchdog timer interrupts
    //
    WDTCTL  = ( (0x5a << 8) + WDTTMSEL + WDTCNTCL + WDTIS0); 
    IE1    |= 0x01;

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
            P1OUT &= ~(1 << 4);
        }
        else
        {
            P1OUT &= ~(1 << 4);
            P1OUT |= (1 << 4);
            P1OUT &= ~(1 << 4);
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
        P1OUT |= (1 << 4);
        MamontMsg.send();    // send the message
    }
}
//---------------------------------------------------------------------------
void OS::SystemTimerUserHook() { }
//---------------------------------------------------------------------------
void OS::IdleProcessUserHook() { }
//---------------------------------------------------------------------------
#pragma vector = TIMERB0_VECTOR
OS_INTERRUPT void Timer_B_ISR()
{
    OS::TISRW ISRW;

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
    P1OUT |= (1 << 4);
    MamontMsg.sendISR();    // send the message
}
//-----------------------------------------------------------------------------

