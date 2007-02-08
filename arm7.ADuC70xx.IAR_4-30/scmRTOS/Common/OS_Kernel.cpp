//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Kernel Source
//*
//*     Version:  3.00-beta
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

#include "scmRTOS.h"

using namespace OS;
//------------------------------------------------------------------------------
OS::TKernel OS::Kernel;

//-----------------------------------------------------------------------------
void OS::Run()
{
    TStackItem* sp = Kernel.ProcessTable[pr0]->StackPointer;
    OS_Start(sp);
}
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

