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
//*     PURPOSE:   Target Dependent Stuff Source
//*               
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
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

typedef OS::process<OS::prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProc;

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

