//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00a
//*
//*     $Revision: 196 $
//*     $Date:: 2008-06-19 #$
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2011

#include <scmRTOS.h>

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 400> TProc1;
typedef OS::process<OS::pr1, 400> TProc2;
typedef OS::process<OS::pr2, 400> TProc3;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------
tick_count_t T;                  // global variable for OS::GetTickCount testing
                                 //
OS::TEventFlag ef;               //
OS::TEventFlag Timer_B_Ovf;

void SetSleep(timeout_t x);


//---------------------------------------------------------------------------
//
void main()
{
    OS::run();
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc1::exec()
{
    for(;;)
    {
        ef.wait();
    }     
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc2::exec()
{
    for(;;)
    {
        Timer_B_Ovf.wait();
    }
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc3::exec()
{
    for(;;)
    {
        SetSleep(10);
        ef.signal();
    }
}
//---------------------------------------------------------------------------
void SetSleep(timeout_t x)
{
    OS::sleep(x);
}
//---------------------------------------------------------------------------
void OS::system_timer_user_hook()
{
    static int cnt=0;
    if (++cnt == 25)
    {
        cnt = 0;
        Timer_B_Ovf.signal_isr();
    }
}
//---------------------------------------------------------------------------
void OS::idle_process_user_hook()
{
}

//-----------------------------------------------------------------------------


