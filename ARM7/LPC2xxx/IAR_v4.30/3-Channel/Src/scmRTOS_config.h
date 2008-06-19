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
//*     PURPOSE:   Project Level Configuration
//*
//*     Version: 3.05
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2008

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

#ifndef __IAR_SYSTEMS_ASM__
#include <commdefs.h>
typedef word TTimeout;
#endif // __IAR_SYSTEMS_ASM__

#include "device.h"
//------------------------------------------------------------------------------
//
//    Specify scmRTOS Process Count. Must be less then 32
//
//
#define  scmRTOS_PROCESS_COUNT                  3

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer
//
//    Nested Interrupts Enable macro. Value 1 means that interrupts are
//    globally enabled within System Timer ISR.
//
//    Nested interrupts not supported in ARM port yet, this option has no effect
//
#define  scmRTOS_SYSTIMER_NEST_INTS_ENABLE      0

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Tick Counter Enable
//
//
#define  scmRTOS_SYSTEM_TICKS_ENABLE            1


//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Hook
//
//
#define  scmRTOS_SYSTIMER_HOOK_ENABLE           1

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Hook
//
//
#define  scmRTOS_IDLE_HOOK_ENABLE               1

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Stack size (in bytes)
//
//
#define scmRTOS_IDLE_PROCESS_STACK_SIZE         17 * sizeof(TStackItem)

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch Scheme
//
//    The macro defines a context switch manner. Value 0 sets direct context
//    switch in the scheduler and in the OS ISRs. This is the primary method.
//    Value 1 sets the second way to switch context - by using of software
//    interrupt. See documentation fo details.
//
//
#define  scmRTOS_CONTEXT_SWITCH_SCHEME          1

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

#endif // scmRTOS_CONFIG_H
//-----------------------------------------------------------------------------

