//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STM8 (STMicroelectronics)
//*
//*     TOOLKIT:   EWSTM8 (IAR Systems)
//*               
//*     PURPOSE:   Target Dependent Stuff Source
//*               
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
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
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011-2016

#include <scmRTOS.h>

using namespace OS;

OS::TPrioMaskTable OS::PrioMaskTable;

// FIXME: Context save/restore routine in os_target_asm.s does not depend on .vregs size
//  But for IAR 1.20 and 1.30 .vregs size does not depend of IDE virtual regs number setting.
//  Is .vregs section size fixed by IAR to 16 bytes and 12 bytes is compiler-limitation
//  but 16 bytes of RAM reserved for both options?
// #pragma section =".vregs"
// Stack -= 5 + __section_size(".vregs") + 1;
#warning "This scmRTOS port assumes that .vregs section occupies 16-byte area"

/* SP в STM8 показує на першу вільну комірку пам’яті, PUSH це *sp-- = data;
 * Так само, як у AVR.
 * В scmRTOS параметер Stack показує на першу комірку за масивом, тобто логіка інша.
 * FIXME: Переписати уважно, в тому числі може бути вигідно відразу мінуснути Stack,
 * а потім зі зміщенням заносити. У STM8 нема команд з автомодифікацією вказівника.
 * Хоча по розміру коду
 *   LD   (X),A
 *   DECW X
 * таке ж саме, як
 *   LD   (5,X), A
 * Другий варіант наче швидший, але на етапі старту це не так важливо.
 */

//  For scmRTOS_CONTEXT_SWITCH_SCHEME == 0 MCU registers are saved/restored in os_target_asm.s
//  not in order of interrupt entry/exit process.
#if 0
enum {
    BASE_START = 0,
    A_OFFSET,
    XH_OFFSET, XL_OFFSET,
    YH_OFFSET, YL_OFFSET,
    CC_OFFSET,
#if __CODE_MODEL__ != __SMALL_CODE_MODEL__
    PCE_OFFSET,
#endif
    PCH_OFFSET, PCL_OFSFET,
    BASE_CONTEXT_SIZE = PCL_OFFSET - BASE_START
};
#endif

//------------------------------------------------------------------------------
void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)() 
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackPool
                                #endif
                                   )
{
    // scmRTOS passes address of next_to_last position in stack array.
#if __CODE_MODEL__ == __SMALL_CODE_MODEL__
    Stack -= 2;
    *(uint16_t*)Stack = reinterpret_cast<uint16_t>(exec); // return address
#else // __CODE_MODEL__ != __SMALL_CODE_MODEL__
    Stack -= 2;
    *(uint16_t*)Stack = reinterpret_cast<uint32_t>(exec); // return address
    *--Stack = reinterpret_cast<uint32_t>(exec) >> 16; // return address (high byte)
#endif // __CODE_MODEL__

    *--Stack = 0x20; // CC -- all interrupts enabled (I1 = 1, I0 = 0)

    // Reserve space for Y, X, A and 16-byte area of virtual registers.
    // +1 for pointing to free memory cell
    Stack -= 5 + 16 + 1;

    StackPointer = Stack;

#if scmRTOS_DEBUG_ENABLE == 1
    //-----------------------------------------------------------------------
    //   Fill stack pool with predefined value for stack consumption checking
    //   Do not fill area for MCU registers and virtual registers.
    //   *Stack position is filled - the position is free because of SP behavior
    stack_item_t *fill_ptr = StackPool;
    while( fill_ptr <= Stack )
    {
    *fill_ptr++ = STACK_DEFAULT_PATTERN;
    }
#endif // scmRTOS_DEBUG_ENABLE
}


//------------------------------------------------------------------------------
#ifndef SYSTEM_TIMER_FLAG_CLEAR
#error "SYSTEM_TIMER_FLAG_CLEAR() macro must be defined"
#endif

INTERRUPT_HANDLER(OS_SystemTimer_ISR, SYSTEM_TIMER_VECTOR)
{
#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
    // Disable all priority levels (including higher than this handler)
    DISABLE_NESTED_INTERRUPTS();
#endif

    SYSTEM_TIMER_FLAG_CLEAR();
    scmRTOS_ISRW_TYPE ISR;

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif

    Kernel.system_timer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 1
    // Enable all priority levels (including lower and equal than this handler)
    ENABLE_NESTED_INTERRUPTS();
#endif

}

