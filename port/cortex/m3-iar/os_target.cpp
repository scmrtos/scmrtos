//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*               
//*     PURPOSE:   Target Dependent Stuff Source
//*               
//*     Version: 5.0.0
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2015


#include <scmRTOS.h>

using namespace OS;

//------------------------------------------------------------------------------
void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                   #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                   #endif
                                   )
{
    // ARM Architecture Procedure Call Standard [AAPCS] requires 8-byte stack alignment:
    StackPointer = (stack_item_t*)((uintptr_t)Stack & 0xFFFFFFF8);
    // Prepare Process Stack Frame.
    *(--StackPointer)  = 0x01000000L;             // xPSR
    *(--StackPointer)  = reinterpret_cast<uint32_t>(exec); // Entry Point
    StackPointer -= 14;                           // emulate "push R14,R12,R3,R2,R1,R0,R11-R4"
    
#if scmRTOS_DEBUG_ENABLE == 1
    for (stack_item_t* pDst = StackBegin; pDst < StackPointer; ++pDst)
        *pDst = STACK_DEFAULT_PATTERN;
#endif // scmRTOS_DEBUG_ENABLE
}

//------------------------------------------------------------------------------
#if USE_SYSTICK_TIMER == 0
OS_INTERRUPT void OS::SystemTimer_Handler()
#else
OS_INTERRUPT void OS::SysTick_Handler()
#endif
{
    scmRTOS_ISRW_TYPE ISR;

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
    DISABLE_NESTED_INTERRUPTS();
#endif

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif

    Kernel.system_timer();
}
//------------------------------------------------------------------------------

