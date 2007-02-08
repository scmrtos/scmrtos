//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADSP-BF533 (Analog Devices)
//*
//*     TOOLKIT:   VDSP (Analog Devices)
//*               
//*     PURPOSE:   Target Dependent Stuff Source
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

using namespace OS;

//------------------------------------------------------------------------------
//
//
//
//
//
TBaseProcess::TBaseProcess(TStackItem* Stack, TPriority pr, void (*exec)())
    : StackPointer(Stack)
    , Priority(pr)
    , Timeout(0)
{
    Kernel.RegisterProcess(this);

    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
    *(--StackPointer) = (dword)exec;       // process main function address
    StackPointer -= 43;                    // emulate 43 "push rxx"
    *(--StackPointer) =   0xffe0;          // enable interrupts
}
//------------------------------------------------------------------------------
/*
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
TBaseProcess::TBaseProcess(TStackItem*** Stack, TPriority pr)
    : Priority(pr)
    , Timeout(0)
{
    Kernel.RegisterProcess(this);
    *Stack = &StackPointer;
}
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
*/
//-----------------------------------------------------------------------------
//
//
//   Idle Process
//
//
//
// extern "C" void IdleProcessExec();
// extern "C" TStackItem** IdleProcStackPointer;
// TStackItem** IdleProcStackPointer;

// TBaseProcess IdleProcess(&IdleProcStackPointer, prIDLE);
//
// extern "C" void IdleProcessExec()
// {
//     for(;;)
//     {
//         #if scmRTOS_IDLE_HOOK_ENABLE == 1
//         IdleProcessUserHook();
//         #endif
//     }
// }

typedef OS::process<OS::prIDLE, 768> TIdleProc;

TIdleProc IdleProc;

OS_PROCESS void TIdleProc::Exec()
{
    for(;;)
    {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
        #endif
    }
}
//------------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(OS::SystemTimer_ISR)
{
    TISRW ISR;
    Kernel.SystemTimer();

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    SystemTimerUserHook();
#endif
}
//------------------------------------------------------------------------------

