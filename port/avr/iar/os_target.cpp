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
//*     AVR/IAR port by Harry E. Zhurov, Copyright (c) 2003-2015

#include <scmRTOS.h>

using namespace OS;

OS::TPrioMaskTable OS::PrioMaskTable;

OS::TSavedSP OS::SavedSP;

#define REGS_COUNT 29     //  29 regs : r0:r15 (16 regs), r17:r27 (11 regs), r30:r31

#ifdef __HAS_RAMPZ__
    #define RAMPZ_PLACE 1
#else
    #define RAMPZ_PLACE 0
#endif

#ifdef __HAS_EIND__
    #define EIND_PLACE 1
#else
    #define EIND_PLACE 0
#endif

#define STACK_CORRECTION (REGS_COUNT + RAMPZ_PLACE + EIND_PLACE)

//------------------------------------------------------------------------------
void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , stack_item_t * RStack
                                   , void (*exec)() 
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackPool
                                   , stack_item_t * RStackPool
                                #endif
                                   )
{
    // Can we use __HAS_EIND__ instead of explcit MCU names ?
#if defined(__ATmega2560__)  || \
    defined(__ATmega2561__)
    *(--RStack) = reinterpret_cast<uint32_t>(exec);                // return from interrupt address (low  byte)
    *(--RStack) = reinterpret_cast<uint32_t>(exec) >> 8;           // return from interrupt address (middle byte)
    *(--RStack) = reinterpret_cast<uint32_t>(exec) >> 16;          // return from interrupt address (high byte)
#else
    *(--RStack) = reinterpret_cast<uint16_t>(exec);                // return from interrupt address (low  byte)
    *(--RStack) = reinterpret_cast<uint16_t>(exec) >> 8;           // return from interrupt address (high byte)
#endif

    StackPointer = Stack;
    --StackPointer;                                            // emulate saving r31
    *(--StackPointer) =   0x80;                                // SREG value: I-bit set, enable interrupts
    *(--StackPointer) = reinterpret_cast<uint16_t>(RStack-1) >> 8; // SP (high byte)
    *(--StackPointer) = reinterpret_cast<uint16_t>(RStack-1);      // SP (low  byte)
    StackPointer     -= STACK_CORRECTION;                          // emulate saving regs (except r31) and SFRS

#if scmRTOS_DEBUG_ENABLE == 1
    //-----------------------------------------------------------------------
    //   Fill stack pools with predefined value for stack consumption checking
    //   Do not fill area for GPR and SFR on data stack
    stack_item_t *fill_ptr;
    fill_ptr = RStack;
    while( fill_ptr > RStackPool )
    {
	*--fill_ptr = STACK_DEFAULT_PATTERN;
    }
    fill_ptr = StackPointer;
    while( fill_ptr > StackPool )
    {
	*--fill_ptr = STACK_DEFAULT_PATTERN;
    }
#endif // scmRTOS_DEBUG_ENABLE
}


//------------------------------------------------------------------------------
#pragma vector=SYSTEM_TIMER_VECTOR
OS_INTERRUPT void OS_SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif

    Kernel.system_timer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 1
    ENABLE_NESTED_INTERRUPTS();
#endif

}

