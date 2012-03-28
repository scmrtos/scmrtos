//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADSP-BF533 (Analog Devices)
//*
//*     TOOLKIT:   VDSP (Analog Devices)
//*
//*     PURPOSE:   Port Test File
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

//---------------------------------------------------------------------------
#include <scmRTOS.h>
#include "macro.h"
//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 768> TProc1;
typedef OS::process<OS::pr1, 768> TProc2;
typedef OS::process<OS::pr2, 768> TProc3;
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
OS::TEventFlag ef;               //

EX_INTERRUPT_HANDLER(Timer0_ISR);
OS::TEventFlag ef_timer0;

//---------------------------------------------------------------------------
//#pragma noreturn
void main()
{                 
    pll_set_system_vco(8, 0, 0x300);                      
    pll_set_system_clocks(0, 2);
    
    /////////////////////////////////////////////////////////////////////
    //
    //    System resources setup
    // 
    //-------------------------------------------------------------------
    //
    //  System Timer setup and start
    //
    MMR32(TCNTL)   = 1;        // turn on the timer
    MMR32(TSCALE)  = 0;        //
    MMR32(TPERIOD) = 200111;   // 5ns * 200 000 = 1 ms
    MMR32(TCNTL)   = 0x07;     // run timer 
    //-------------------------------------------------------------------
    //
    //    Register System Interrupt Handlers
    //
    //
    register_handler_ex(ik_timer, OS::SystemTimer_ISR, 1);
    register_handler_ex(ik_ivg14, ContextSwitcher_ISR, 1);
    //-------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////


    MMR16(FIO_DIR) |= (1 << 8) + (1 << 9);

    register_handler_ex(ik_ivg11, Timer0_ISR, 1);
    MMR32(SIC_IMASK)     = (1 << 16);             // enable Timer0 interrupt
    MMR16(TIMER0_CONFIG) = PWM_OUT  
                         + IRQ_ENA 
                         + PERIOD_CNT 
                         + OUT_DIS; 

    MMR32(TIMER0_PERIOD) = 10011;
    MMR32(TIMER0_WIDTH)  = 5000;
    MMR16(TIMER_ENABLE)  = TIMEN0;                 // timer0 enable

    OS::Run();
}
//---------------------------------------------------------------------------
template<> void TProc1::Exec()
{
    for(;;)
    {
        ef_timer0.Wait();
        MMR16(FIO_FLAG_C) = (1 << 9);
    }
}
//---------------------------------------------------------------------------
template<> void TProc2::Exec()
{
    for(;;)
    {
        ef.Wait();
        MMR16(FIO_FLAG_C) = (1 << 8);
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::Exec()
{
    for(;;)
    {
        Sleep(3);
        MMR16(FIO_FLAG_S) = (1 << 8);
        ef.Signal();
    }
}
//---------------------------------------------------------------------------
//void OS::SystemTimerUserHook() { }
//---------------------------------------------------------------------------
void OS::IdleProcessUserHook() { }
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(Timer0_ISR)
{
    OS::TISRW ISR;
    MMR16(TIMER_STATUS) = TIMIL0;

    MMR16(FIO_FLAG_S) = (1 << 9);
    ef_timer0.SignalISR();
}
//---------------------------------------------------------------------------

