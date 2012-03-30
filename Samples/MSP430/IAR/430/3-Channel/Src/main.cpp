//******************************************************************************
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
tick_count_t T;                     // global variable for OS::GetTickCount testing
                                    //

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

        P1OUT |= (1 << 4);
        P1OUT &= ~(1 << 4);
    }
};
//------------------------------------------------------------------------------
class TIndianSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs; 

        P1OUT |= (1 << 4);
        P1OUT &= ~(1 << 4);
        P1OUT |= (1 << 4);
        P1OUT &= ~(1 << 4);
    }
};
//------------------------------------------------------------------------------

TAfricanSlon African;   
TIndianSlon  Indian;    
    
OS::channel<TSlon*, 8> SlonQueue; // OS::channel object for 8 'TSlon*' items

OS::TEventFlag Timer_B_Ovf;

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

    OS::run();
}
//---------------------------------------------------------------------------
template<> void TProc1::exec()
{
    for(;;)
    {
        Timer_B_Ovf.wait();
        SlonQueue.push(&African);
    }     
}
//---------------------------------------------------------------------------
template<> void TProc2::exec()
{
    for(;;)
    {
        T += OS::get_tick_count();
             
        sleep(1);
        SlonQueue.push(&Indian);
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::exec()
{
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
        SlonQueue.pop(p);     // get pointer from queue
        p->eat();             // feed the appropriate Slon
    }
}
//---------------------------------------------------------------------------
void OS::system_timer_user_hook() { }
//---------------------------------------------------------------------------
void OS::idle_process_user_hook() { }
//---------------------------------------------------------------------------
#pragma vector = TIMERB0_VECTOR
OS_INTERRUPT void timer_b_isr()
{
    OS::TISRW ISR;

    ENABLE_NESTED_INTERRUPTS();
    
    Timer_B_Ovf.signal_isr();
}
//-----------------------------------------------------------------------------


