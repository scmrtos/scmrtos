//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version: 4.00a
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2011, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2011

#include <scmRTOS.h>

//-----------------------------------------------------------------------------
//
//    wrappers to allow ARM mode intrinsics call from THUMB sources
//
#if __CPU_MODE__ != 0   // THUMB

#include    <inarm.h>
__arm status_reg_t get_interrupt_state()
{
    return __get_CPSR();
}

__arm void set_interrupt_state(status_reg_t sr)
{
    __set_CPSR(sr);
}
#endif




using namespace OS;

void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
    *(--Stack) = (stack_item_t)exec;    // return from interrupt address

    Stack -= 14;                        // emulate "push R0-R12", "push LR"

    #if __CPU_MODE__ == 0   // ARM
    *(--Stack) =   0x001F;              // SR value: system mode, FIQ & IRQ enabled, ARM mode
    #else                   // THUMB
    *(--Stack) =   0x003F;              // SR value: system mode, FIQ & IRQ enabled, THUMB mode
    #endif

    StackPointer = Stack;               // pointer to stored context

#if scmRTOS_DEBUG_ENABLE == 1
    //-----------------------------------------------------------------------
    //   Fill stack pool with predefined value for stack consumption checking
    //
    while(--Stack >= StackBegin)
    {
        *Stack = STACK_DEFAULT_PATTERN;
    }
#endif // scmRTOS_DEBUG_ENABLE
}

//-----------------------------------------------------------------------------
//
//   Idle Process
//
//
typedef process<prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;

//------------------------------------------------------------------------------
#if scmRTOS_OBSOLETE_NAMES == 0
OS_INTERRUPT
#endif
                void OS::system_timer_isr()
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
