//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   mspgcc (GNU)
//*
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version: v5.0.1
//*
//*
//*     Copyright (c) 2003-2015, scmRTOS Team
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
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*     mspgcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2008-2015

#include <scmRTOS.h>

using namespace OS;

OS::TPrioMaskTable OS::PrioMaskTable;

void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    StackPointer = Stack;
    *(--StackPointer) = reinterpret_cast<uint16_t>(exec);  // return from interrupt address
    *(--StackPointer) =   0x0008;                      // SR value: GIE set
    StackPointer -= 12;                                // emulate 12 "push rxx"

#if scmRTOS_DEBUG_ENABLE == 1
    for (stack_item_t* pDst = StackBegin; pDst < StackPointer; pDst++)
        *pDst = STACK_DEFAULT_PATTERN;
#endif // scmRTOS_DEBUG_ENABLE
}

//------------------------------------------------------------------------------
interrupt(SYSTEM_TIMER_VECTOR) OS::SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

    Kernel.system_timer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 1
    ENABLE_NESTED_INTERRUPTS();
#endif

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif
}


//------------------------------------------------------------------------------
__attribute__ (( naked ))
interrupt (CONTEXT_SWITCH_ISR_VECTOR) context_switcher_isr()
{
    __asm__ __volatile__(
        " PUSH     R4    \r\n"
        " PUSH     R5    \r\n"
        " PUSH     R6    \r\n"
        " PUSH     R7    \r\n"
        " PUSH     R8    \r\n"
        " PUSH     R9    \r\n"
        " PUSH     R10   \r\n"
        " PUSH     R11   \r\n"
        " PUSH     R12   \r\n"
        " PUSH     R13   \r\n"
        " PUSH     R14   \r\n"
        " PUSH     R15   \r\n"

        " MOV      R1, R15   \r\n"
        " CALL     #os_context_switch_hook   \r\n"
        " MOV      R15, R1   \r\n"

        " POP      R15   \r\n"
        " POP      R14   \r\n"
        " POP      R13   \r\n"
        " POP      R12   \r\n"
        " POP      R11   \r\n"
        " POP      R10   \r\n"
        " POP      R9    \r\n"
        " POP      R8    \r\n"
        " POP      R7    \r\n"
        " POP      R6    \r\n"
        " POP      R5    \r\n"
        " POP      R4    \r\n"
        " RETI           \r\n"
    :
    :
    );
}

//******************************************************************************
