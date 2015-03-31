//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M0+
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Project Level Configuration
//*
//*     Version: 4.00
//*
//*     $Revision: 559 $
//*     $Date:: 2012-12-03 #$
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     GCC STM32L0XX Samples by Anton B. Gusev aka AHTOXA, Copyright (c) 2015

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

#ifndef __ASSEMBLER__

#include <stdint.h>

typedef uint16_t      timeout_t;
typedef uint_fast32_t tick_count_t;

#endif // __ASSEMBLER__

//------------------------------------------------------------------------------
//
//    Specify scmRTOS Process Count. Must be less than 31
//
//
#define  scmRTOS_PROCESS_COUNT                  3

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer
//
//    Nested Interrupts enable macro. Value 1 means that interrupts are
//    globally enabled within System Timer ISR (this is default for Cortex-M3).
//
//
#define scmRTOS_SYSTIMER_NEST_INTS_ENABLE   1

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Tick Counter Enable
//
//
#define  scmRTOS_SYSTEM_TICKS_ENABLE        1


//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Hook
//
//
#define  scmRTOS_SYSTIMER_HOOK_ENABLE       1

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Hook
//
//
#define  scmRTOS_IDLE_HOOK_ENABLE           0

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Stack size (in bytes)
//    (20 * sizeof(stack_item_t)) - it's a minimum allowed value.
//
#define scmRTOS_IDLE_PROCESS_STACK_SIZE     (100 * sizeof(stack_item_t))

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch User Hook enable
//
//    The macro enables/disables user defined hook called from system
//    Context Switch Hook function.
//
//
#define  scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE  0

//-----------------------------------------------------------------------------
//
//    scmRTOS Debug enable
//
//    The macro enables/disables acquisition of some debug info:
//    stack usage information and information about the object that process is waiting for.
//
//
#define scmRTOS_DEBUG_ENABLE                0

//-----------------------------------------------------------------------------
//
//    scmRTOS Process Restart enable
//
//    The macro enables/disables process restarting facility.
//
//
#define scmRTOS_PROCESS_RESTART_ENABLE      0

//-----------------------------------------------------------------------------
//
//     PendSVC_ISR optimization:
//    0 - use near (+- 1Mb) call for os_context_switch_hook
//    1 - use far call
//
#define scmRTOS_CONTEXT_SWITCH_HOOK_IS_FAR     0

#endif // scmRTOS_CONFIG_H
//-----------------------------------------------------------------------------

