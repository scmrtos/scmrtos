//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Kernel Source
//*
//*     Version: 3.05
//*
//*     $Revision: 195 $
//*     $Date:: 2008-06-19 #$
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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

#include "scmRTOS.h"

using namespace OS;
//------------------------------------------------------------------------------
OS::TKernel OS::Kernel;

//------------------------------------------------------------------------------
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
void TKernel::Sched()
{
    byte NextPrty = GetHighPriority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
        TStackItem*  Next_SP = ProcessTable[NextPrty]->StackPointer;
        TStackItem** Curr_SP_addr = &(ProcessTable[CurProcPriority]->StackPointer);
        CurProcPriority = NextPrty;
        OS_ContextSwitcher(Curr_SP_addr, Next_SP);
    }
}
#else
//------------------------------------------------------------------------------
void TKernel::Sched()
{
    byte NextPrty = GetHighPriority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
        SchedProcPriority = NextPrty;
    
        RaiseContextSwitch();
        do
        {
            EnableContextSwitch();
            DUMMY_INSTR();
            DisableContextSwitch();
        } 
        while(!IsContextSwitchDone());
    }
}
//------------------------------------------------------------------------------
TStackItem* OS_ContextSwitchHook(TStackItem* sp) { return OS::Kernel.ContextSwitchHook(sp); }
//------------------------------------------------------------------------------
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
//------------------------------------------------------------------------------
void TBaseProcess::Sleep(TTimeout timeout)
{
    TCritSect cs;

    Kernel.ProcessTable[Kernel.CurProcPriority]->Timeout = timeout;
    Kernel.SetProcessUnready(Kernel.CurProcPriority);
    Kernel.Scheduler();
}
//------------------------------------------------------------------------------
void OS::WakeUpProcess(TBaseProcess& p)
{
    TCritSect cs;

    if(p.Timeout)
    {
        p.Timeout = 0;
        Kernel.SetProcessReady(p.Priority);
        Kernel.Scheduler();
    }
}
//------------------------------------------------------------------------------
void OS::ForceWakeUpProcess(TBaseProcess& p)
{
    TCritSect cs;

    p.Timeout = 0;
    Kernel.SetProcessReady(p.Priority);
    Kernel.Scheduler();
}
//------------------------------------------------------------------------------

