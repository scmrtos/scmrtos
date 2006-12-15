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

OS::TPrioMaskTable OS::PrioMaskTable;

//------------------------------------------------------------------------------
//
//       OS Process's constructor
//
//       Performs:  
//           * initializing process data;
//           * registering of the process in kernel;
//           * preparing stack frame;
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
    *(--StackPointer) = reinterpret_cast<word>(exec);  // return from interrupt address
    *(--StackPointer) =   0x0008;                      // SR value: GIE set
    StackPointer -= 12;                                // emulate 12 "push rxx"
}
//------------------------------------------------------------------------------
//
//   Idle Process
//
typedef process<prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;

OS_PROCESS void TIdleProcess::Exec()
{
    for(;;)
    {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
        #endif
    }
}
//------------------------------------------------------------------------------
OS_INTERRUPT void OS::SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

    Kernel.SystemTimer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 1
    ENABLE_NESTED_INTERRUPTS();
#endif

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    SystemTimerUserHook();
#endif
}
//--------------------------------------------------------------------------

