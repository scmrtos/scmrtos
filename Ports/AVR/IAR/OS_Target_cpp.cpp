//******************************************************************************
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
//*     $Date::             $
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
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

