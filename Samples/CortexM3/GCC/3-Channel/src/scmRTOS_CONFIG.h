//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3
//*
//*     TOOLKIT:   GCC
//*
//*     PURPOSE:   Project Level Configuration
//*
//*     Version: 3.10
//*
//*     $Revision: 196 $
//*     $Date:: 2008-06-19 #$
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2010

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

#ifndef __ASSEMBLER__
#include <commdefs.h>

typedef word TTimeout;

#endif // __ASSEMBLER__

#include "device.h"
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
#define scmRTOS_SYSTIMER_NEST_INTS_ENABLE 1

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
//    (20 * sizeof(TStackItem)) - it's a minimum allowed value.
//
#define scmRTOS_IDLE_PROCESS_STACK_SIZE       (100 * sizeof(TStackItem))

//-----------------------------------------------------------------------------
//
//    scmRTOS Priority Order
//
//    This macro defines the order of the process's priorities. Default,
//    the ascending order is used. Alternatively, the descending priority
//    order can be used. On some platforms the descending order is preferred
//    because of performance.
//
//    Default (corresponding to ascending order) value of macro is 0.
//    Alternative (corresponding to descending order) value of macro is 1.
//
//    On Cortex-M3 the descending order is preferred for performance reason.
//
#define  scmRTOS_PRIORITY_ORDER 1

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch User Hook enable
//
//    The macro enables/disables user defined hook called from system
//    Context Switch Hook function.
//
//
#define  scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE  0


#endif // scmRTOS_CONFIG_H
//-----------------------------------------------------------------------------

