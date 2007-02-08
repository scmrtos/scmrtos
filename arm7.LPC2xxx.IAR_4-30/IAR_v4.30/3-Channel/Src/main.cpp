//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: LPC2xxx (NXP)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
//*     Copyright (c) 2005-2006, Sergey A. Borshch
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
dword T;                         // global variable for OS::GetTickCount testing
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

        IO0SET = (1 << 29);
        IO0CLR = (1 << 29);

    }
};
//------------------------------------------------------------------------------
class TIndianSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;

        IO0SET = (1 << 29);
        IO0CLR = (1 << 29);
        IO0SET = (1 << 29);
        IO0CLR = (1 << 29);
    }
};
//------------------------------------------------------------------------------

TAfricanSlon African;
TIndianSlon  Indian;

OS::channel<TSlon*, 8> SlonQueue; // OS::channel object for 8 'TSlon*' items

OS::TEventFlag Timer_Ovf;
//---------------------------------------------------------------------------
int main()
{
    OS::Run();
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc1::Exec()
{
    for(;;)
    {
        Timer_Ovf.Wait();
        SlonQueue.push(&African);
    }
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc2::Exec()
{
    for(;;)
    {
        T += OS::GetTickCount();

        Sleep(1);
        SlonQueue.push(&Indian);
    }
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc3::Exec()
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
void OS::SystemTimerUserHook() { }
//---------------------------------------------------------------------------
void OS::IdleProcessUserHook() { }
//---------------------------------------------------------------------------
OS_INTERRUPT void Timer_ISR()
{
    OS::TISRW ISRW;

    T1IR = T1IR;                    // clear int flag

    Timer_Ovf.SignalISR();

    VICVectAddr = 0;
}
//-----------------------------------------------------------------------------

_C_LIB_DECL
#pragma language=extended
#pragma location="ICODE"

#define RTOS_TICK_RATE  1000        // Hz
#define OSC             11059200UL
#define CCLK            (OSC * 5)
#define PCLK            (CCLK)

#define TEST_TIMER_RATE 3500        // Hz

extern "C" void ContextSwitcher_ISR();
int __low_level_init(void)
{
// ***************************************************************************
// ** PLL
// ***************************************************************************
    PLLCFG = (1<<5) | (CCLK / OSC - 1);     // psel = 1; msel = (CCLK / OSC - 1)
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    PLLCON = (1<<0);                        // PLLE=1, Enable PLL
    PLLFEED = 0xAA;
    PLLFEED = 0x55;
    while(!PLLSTAT_bit.PLOCK) ;             // wait for lock

    PLLCON = (1<<1) | (1<<0);               // PLLC = 1, PLLE = 1, Connect PLL
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    VPBDIV = 1;                             // pclk = cclk

// ***************************************************************************
// ** MAM
// ***************************************************************************
    MAMTIM_bit.CYCLES = 3;                  // 3 cycles per fetch
    MAMCR_bit.MODECTRL = 2;                 // Memory acceleration fully enabled
// ***************************************************************************
// ** GPIO
// ***************************************************************************
    IO0DIR = (1<<29);                       // Test pin -> output

// ***************************************************************************
// ** TIMER0
// ***************************************************************************
//          RTOS system timer
    T0IR = (unsigned)-1;                    // clear int requests
    T0TCR = (1<<0);                         // CE = 1, enable timer
    T0PR = 0;

    T0MR0 = PCLK / RTOS_TICK_RATE;          // int at TICK_RATE
    T0MCR = (1<<1) | (1<<0);                // MR0INT = 1, MR0RES = 1

// ***************************************************************************
// ** TIMER1
// ***************************************************************************
//          EventFlag test timer
    T1IR = (unsigned)-1;                    // clear int requests
    T1TCR = (1<<0);                         // CE = 1, enable timer
    T1PR = 0;

    T1MR0 = PCLK / TEST_TIMER_RATE;         // int at 350Hz
    T1MCR = (1<<1) | (1<<0);                // MR0INT = 1, MR0RES = 1

//***************************************************************************
// ** VIC
//***************************************************************************

    VICVectAddr0 = (dword)Timer_ISR;
    VICVectCntl0 = (1<<5) | VIC_TIMER1;     // Enable vector interrupt for TIMER0

    VICVectAddr15 = (dword)OS::SystemTimer_ISR;
    VICVectCntl15 = (1<<5) | SYSTEM_TIMER_INT;     // Enable vector interrupt for TIMER0

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    VICVectAddr14 = (dword)ContextSwitcher_ISR;
    VICVectCntl14 = (1<<5) | CONTEXT_SWITCH_INT;

    VICIntEnable =  (1UL<<SYSTEM_TIMER_INT) | (1UL<<CONTEXT_SWITCH_INT) | (1UL<<VIC_TIMER1);
#else
    VICIntEnable =  (1UL<<SYSTEM_TIMER_INT) | (1UL<<VIC_TIMER1);
#endif

    VICVectAddr = 0;    // Reset VIC logic

    return 1;
}
#pragma language=default
_END_C_LIB_DECL
