//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   arm-(elf/none-eabi)-gcc (GNU)
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2007-2021

// to create non-inlined ARM-mode CPSR-related routines
#define scmRTOS_OS_TARGET_CPP

#include <scmRTOS.h>

using namespace OS;

namespace OS
{

#if scmRTOS_DEBUG_ENABLE == 1

struct TDebugSupportInfo
{
    uint8_t PROCESS_COUNT;
    uint8_t TIMEOUT_SIZE;
    uint8_t NAME_OFFSET;
};


__attribute__((used, aligned(2)))
extern const TDebugSupportInfo DebugInfo =
{
    PROCESS_COUNT,
    sizeof(timeout_t),
    sizeof(timeout_t) == 2 ? 20 : 24
};
#endif // scmRTOS_DEBUG_ENABLE

} // namespace OS

void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    // ARM Architecture Procedure Call Standard [AAPCS] requires 8-byte stack alignment:
    StackPointer = (stack_item_t*)((uintptr_t)Stack & 0xFFFFFFF8);
    *(--StackPointer) = (stack_item_t)exec;    // return from interrupt address

    StackPointer -= 14;                        // emulate "push R0-R12", "push LR"

    if((uintptr_t)exec & (1 << 0))             // if exec is THUMB-mode code
        *(--StackPointer) =   0x003F;          // SR value: system mode, FIQ & IRQ enabled, THUMB mode
    else
        *(--StackPointer) =   0x001F;          // SR value: system mode, FIQ & IRQ enabled, ARM mode

#if scmRTOS_DEBUG_ENABLE == 1
    *StackBegin = reinterpret_cast<stack_item_t>(&DebugInfo); // dummy load to keep 'DebugInfo' in output binary
    //-----------------------------------------------------------------------
    //   Fill stack pool with predefined value for stack consumption checking
    //
    for (stack_item_t* pDst = StackBegin; pDst < StackPointer; pDst++)
        *pDst = STACK_DEFAULT_PATTERN;
#endif // scmRTOS_DEBUG_ENABLE
}

//-----------------------------------------------------------------------------
//
//   Idle Process
//
//
typedef OS::process<prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;

//--------------------------------------------------------------------------
OS_INTERRUPT void OS::system_timer_isr()
{
    scmRTOS_ISRW_TYPE ISR;

    SYSTEM_TIMER_HANDLER();

    IRQ_DONE();
}
//------------------------------------------------------------------------------
namespace OS {
    extern TPriority const PriorityTable[] =
    {
        #if scmRTOS_PROCESS_COUNT == 1
            static_cast<TPriority>(0xFF),
            pr0,
            prIDLE, pr0
        #elif scmRTOS_PROCESS_COUNT == 2
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            prIDLE, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 3
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 4
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 5
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #else // scmRTOS_PROCESS_COUNT > 5
            static_cast<TPriority>(32),      static_cast<TPriority>(0),       static_cast<TPriority>(1),       static_cast<TPriority>(12),
            static_cast<TPriority>(2),       static_cast<TPriority>(6),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(13),
            static_cast<TPriority>(3),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(7),       static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(14),
            static_cast<TPriority>(10),      static_cast<TPriority>(4),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(8),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(25),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(21),      static_cast<TPriority>(27),      static_cast<TPriority>(15),
            static_cast<TPriority>(31),      static_cast<TPriority>(11),      static_cast<TPriority>(5),       static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(9),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(24),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(20),      static_cast<TPriority>(26),
            static_cast<TPriority>(30),      static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(23),      static_cast<TPriority>(0xFF),    static_cast<TPriority>(19),
            static_cast<TPriority>(29),      static_cast<TPriority>(0xFF),    static_cast<TPriority>(22),      static_cast<TPriority>(18),
            static_cast<TPriority>(28),      static_cast<TPriority>(17),      static_cast<TPriority>(16),      static_cast<TPriority>(0xFF)
        #endif  // scmRTOS_PROCESS_COUNT
    };
}   //namespace
//--------------------------------------------------------------------------
