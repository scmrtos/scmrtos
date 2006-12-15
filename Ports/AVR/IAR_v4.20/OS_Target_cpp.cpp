//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   EWAVR (IAR Systems)
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

OS::TSavedSP OS::SavedSP;

#ifndef __HAS_RAMPZ__
    #define REGS_COUNT 29     //  29 regs : r0:r15 (16 regs), r17:r27 (11 regs), r30:r31
#else
    #define REGS_COUNT 30     //  29 regs + RAMPZ
#endif

//------------------------------------------------------------------------------
//
//
//
//
//
OS::TBaseProcess::TBaseProcess(TStackItem* Stack, TStackItem* RStack, TPriority pr, void (*exec)())
    : StackPointer(Stack)
    , Priority(pr)
    , Timeout(0)
{
    Kernel.RegisterProcess(this);

    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
    *(--RStack) = reinterpret_cast<word>(exec);                // return from interrupt address (low  byte)
    *(--RStack) = reinterpret_cast<word>(exec) >> 8;           // return from interrupt address (high byte)

    --StackPointer;                                            // emulate saving r31
    *(--StackPointer) =   0x80;                                // SREG value: I-bit set, enable interrupts
    *(--StackPointer) = reinterpret_cast<word>(RStack-1) >> 8; // SP (high byte)
    *(--StackPointer) = reinterpret_cast<word>(RStack-1);      // SP (low  byte)
    StackPointer     -= REGS_COUNT;                            // emulate saving regs (except r31)
}
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//
//    Idle Process
//
//
process<prIDLE, 
        scmRTOS_IDLE_PROCESS_DATA_STACK_SIZE, 
        scmRTOS_IDLE_PROCESS_RETURN_STACK_SIZE> IdleProcess;

OS_PROCESS void process<prIDLE, 70, 10>::Exec()
{

    for(;;)
    {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
        #endif
    }
}

//------------------------------------------------------------------------------
#pragma vector=SYSTEM_TIMER_VECTOR
OS_INTERRUPT void OS_SystemTimer_ISR()
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
//------------------------------------------------------------------------------

