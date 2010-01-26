//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   arm-elf-gcc (GNU)
//*
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version: 3.10
//*
//*     $Revision$
//*     $Date::             $
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2007-2010

#include <scmRTOS.h>

using namespace OS;

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
    , Timeout(0)
    , Priority(pr)
{
    Kernel.RegisterProcess(this);

    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
    *(--StackPointer) = (dword)exec;        // return from interrupt address

    StackPointer -= 14;                     // emulate "push R0-R12", "push LR"
    *(--StackPointer) =   0x001F;           // SR value: system mode, FIQ & IRQ enabled, ARM
}
//-----------------------------------------------------------------------------
//
//   Idle Process
//
//
typedef OS::process<prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;
namespace OS
{
    template<>
    OS_PROCESS void TIdleProcess::Exec()
    {
        for(;;)
        {
            #if scmRTOS_IDLE_HOOK_ENABLE == 1
            IdleProcessUserHook();
            #endif
        }
    }
}
//------------------------------------------------------------------------------
namespace OS
{
    INLINE inline void SystemTimer_Handler();
}

void OS::SystemTimer_Handler()
{
    Kernel.SystemTimer();
#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    SystemTimerUserHook();
#endif
}

OS_INTERRUPT void OS::SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

    SYSTEM_TIMER_HANDLER();

    IRQ_DONE();
}
//--------------------------------------------------------------------------
namespace OS {
    #if scmRTOS_PROCESS_COUNT == 1
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            prIDLE, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 2
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            prIDLE, pr0, pr1, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 3
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 4
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 5
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        };
    #else // scmRTOS_PROCESS_COUNT > 5
        extern TPriority const PriorityTable[64] =
        {
            (TPriority)32,      (TPriority)0,       (TPriority)1,       (TPriority)12,
            (TPriority)2,       (TPriority)6,       (TPriority)0xFF,    (TPriority)13,
            (TPriority)3,       (TPriority)0xFF,    (TPriority)7,       (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)14,
            (TPriority)10,      (TPriority)4,       (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)8,       (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)25,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)21,      (TPriority)27,      (TPriority)15,
            (TPriority)31,      (TPriority)11,      (TPriority)5,       (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)9,       (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)24,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)20,      (TPriority)26,
            (TPriority)30,      (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)23,      (TPriority)0xFF,    (TPriority)19,
            (TPriority)29,      (TPriority)0xFF,    (TPriority)22,      (TPriority)18,
            (TPriority)28,      (TPriority)17,      (TPriority)16,      (TPriority)0xFF
        };
    #endif  // scmRTOS_PROCESS_COUNT
}   //namespace
//--------------------------------------------------------------------------
