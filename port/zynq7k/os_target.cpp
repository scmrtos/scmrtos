//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-A9
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version: v5.2.0
//*
//*
//*     Copyright (c) 2003-2021, scmRTOS Team
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
//*     Cortex-A9 GCC port by Harry E. Zhurov, Copyright (c) 2024

#include <scmRTOS.h>

//------------------------------------------------------------------------------
namespace OS
{
void OS::TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    // ARM Architecture Procedure Call Standard [AAPCS] requires 8-byte stack alignment:
    StackPointer =  reinterpret_cast<stack_item_t*>(reinterpret_cast<uintptr_t>(Stack) & 0xfffffff8ul);

    *(--StackPointer) = reinterpret_cast<uintptr_t>(exec) & 0x01 ?
                                                            0x3f : // System Mode, ARM mode, IRQ en, FIQ en, T(humb) flag on
                                                            0x1f;  // System Mode, ARM mode, IRQ en, FIQ en


    *(--StackPointer) = reinterpret_cast<stack_item_t>(exec);      // process root function start address
    *(--StackPointer) = reinterpret_cast<stack_item_t>(exec);      // lr in stack frame


    for(size_t i = 12; i; --i)
    {
        *(--StackPointer) = (i << 24) | (i << 16) | (i << 8) | i;
    }
    *(--StackPointer) = 0x12345678;                                // r0

#if FPU_ENABLE
    *(--StackPointer) = 0;                                         // fpcsr initial value
    const size_t FPU_CONTEXT_SIZE = 32*2 + 1;                      // 32 64-bit registers + 1 dummy pop for SP alignment
    StackPointer -= FPU_CONTEXT_SIZE ;                             // 1 32-bit FPU status register (fpcsr)
#endif

#if scmRTOS_DEBUG_ENABLE == 1
    for (stack_item_t *p = StackBegin; p < StackPointer; ++p)
    {
        *p = STACK_DEFAULT_PATTERN;
    }
#endif
}

} // namespace OS
//------------------------------------------------------------------------------
extern "C"
{

bool irq_handler()
{
    const uint32_t INT_ID = rpa(GIC_ICCIAR);
    if (INT_ID < PS7_MAX_IRQ_ID)
    {
        (*ps7_handlers[INT_ID])();

    }
    wpa(GIC_ICCEOIR, INT_ID);

    OS::TISRW isr;
    return isr.context_switch_pending();
}

}  // extern "C"
//------------------------------------------------------------------------------

