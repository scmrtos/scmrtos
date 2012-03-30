//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M0
//*
//*     TOOLKIT:   ARM GCC
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2010
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2010
//*     Cortex-M0 port by Sergey A. Borshch, Copyright (c) 2011


#include <scmRTOS.h>

using namespace OS;

void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    // ARM Architecture Procedure Call Standard [AAPCS] requires 8-byte stack alignment:
    StackPointer = (stack_item_t*)((uintptr_t)Stack & 0xFFFFFFF8);
    *(--StackPointer)  = 0x01000000L;             // xPSR
    *(--StackPointer)  = reinterpret_cast<uint32_t>(exec); // Entry Point
    StackPointer -= 14;                           // emulate "push R14,R12,R3,R2,R1,R0,R11-R4"

#if scmRTOS_DEBUG_ENABLE == 1
    for (stack_item_t* pDst = StackBegin; pDst < StackPointer; pDst++)
        *pDst = STACK_DEFAULT_PATTERN;
#endif // scmRTOS_DEBUG_ENABLE
}

//------------------------------------------------------------------------------
OS_INTERRUPT void OS::SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

    Kernel.system_timer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
    DISABLE_NESTED_INTERRUPTS();
#endif

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif
}
//------------------------------------------------------------------------------

extern "C" void os_start(stack_item_t *sp)
{
    // Set System Timer and Context switch interrupts priorities
    struct scb_t
    {
        uint32_t const  CPUID;
        uint32_t        ICSR;
        uint32_t        VTOR;
        uint32_t        AIRCR;
        uint32_t        SCR;
        uint32_t const  CCR;
        uint32_t        RESERVED_1;
        uint32_t        SHPR2;
        uint32_t        SHPR3;
        uint32_t        SHCSR;
        uint32_t        RESERVED_2[2];
        uint32_t        DFSR;
    };
    scb_t volatile * const SCB = (scb_t volatile * const)0xE000ED00;

    SCB->SHPR3 = 0
            | (3 << 22)     // PendSV priority = 3, lowest
            | (2 << 30)     // SysTick priority = 2, little higher
            ;

    //
    register stack_item_t * Context_ptr asm("r0");
    Context_ptr = sp;
    register void (*EntryPoint)()       asm("r1");
    asm volatile (
               "LDR   %1, [%0, #4 * 14] \n" // Load process entry point
            "   ADD   %0, #4 * 16       \n" // emulate context restore
            "   MSR   PSP, %0           \n" // store process SP to PSP
            "   MOV   %0, #2            \n" // Switch thread mode stack to PSP
            "   MSR   CONTROL, %0       \n"
            "   ISB                     \n" // Ensure CONTROL written before next instruction
            "   CPSIE I                 \n"
            "   BX    %1                \n"
            : "+r"(Context_ptr)
            : "r"(EntryPoint)
            );
    __builtin_unreachable();                // never got here, suppress compiler warning "'noreturn' func does return"
}
//------------------------------------------------------------------------------
namespace OS
{
    extern TPriority const PriorityTable[] =
    {
        #if scmRTOS_PROCESS_COUNT == 1
            (TPriority)0xFF,
            pr0,
            prIDLE, pr0
        #elif scmRTOS_PROCESS_COUNT == 2
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            prIDLE, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 3
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 4
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 5
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #else // scmRTOS_PROCESS_COUNT > 5
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
        #endif  // scmRTOS_PROCESS_COUNT
    };
}   //namespace
//------------------------------------------------------------------------------

