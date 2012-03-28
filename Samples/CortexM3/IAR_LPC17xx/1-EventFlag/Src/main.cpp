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
//*     Version: 3.11
//*
//*     $Revision: 196 $
//*     $Date:: 2008-06-19 #$
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2012

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
dword T;                         // global variable for OS::GetTickCount testing
                                 //
OS::TEventFlag ef;               //
OS::TEventFlag Timer_B_Ovf;

void SetSleep(TTimeout x);


//---------------------------------------------------------------------------
//
void main()
{
    OS::Run();
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc1::Exec()
{
    for(;;)
    {
        ef.Wait();
    }     
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc2::Exec()
{
    for(;;)
    {
        Timer_B_Ovf.Wait();
    }
}
//---------------------------------------------------------------------------
template<> OS_PROCESS void TProc3::Exec()
{
    for(;;)
    {
        SetSleep(10);
        ef.Signal();
    }
}
//---------------------------------------------------------------------------
void SetSleep(TTimeout x)
{
    OS::Sleep(x);
}
//---------------------------------------------------------------------------
void OS::SystemTimerUserHook()
{
    static int cnt=0;
    if (++cnt == 25)
    {
        cnt = 0;
        Timer_B_Ovf.SignalISR();
    }
}
//---------------------------------------------------------------------------
void OS::IdleProcessUserHook() { }
//-----------------------------------------------------------------------------


