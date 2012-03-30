//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:  avr-gcc (GNU)
//*
//*     PURPOSE:   Project Level Configuration
//*
//*     Version: 3.10
//*
//*     $Revision$
//*     $Date::             $
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007-2010

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

#ifndef __ASSEMBLER__
typedef uint16_t timeout_t;
typedef uint_fast32_t tick_count_t;
#endif // __ASSEMBLER__

//------------------------------------------------------------------------------
//
//    Specify scmRTOS Process Count. Must be less then 31
//
//
#define  scmRTOS_PROCESS_COUNT              3


//------------------------------------------------------------------------------
//
//    Specify scmRTOS Process Restart capability
//
//
#define scmRTOS_PROCESS_RESTART_ENABLE  0

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer
//
//    Nested Interrupts Enable macro. Value 1 means that interrupts are
//    globally enabled within System Timer ISR.
//
//
#define  scmRTOS_SYSTIMER_NEST_INTS_ENABLE  0

//-----------------------------------------------------------------------------
//
//    ISR Wrapper type used in System Timer ISR
//    There are two types: TISRW and TISRW_SS.
//
//    TISRW : Plain ISR Wrapper, does not switch SP to separate ISR stack.
//            Suitable for processors that have hardware-switched ISR stack,
//            or in such ISRs where stack consumption is acceptable
//
//    TISRW_SS : ISR Wrapper with separate ISR stack software switching
//
#define scmRTOS_ISRW_TYPE   TISRW //_SS

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Tick Counter Enable
//
//
#define  scmRTOS_SYSTEM_TICKS_ENABLE    1


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
#define  scmRTOS_IDLE_HOOK_ENABLE           1


//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Stacks size (in bytes)
//
//
#define scmRTOS_IDLE_PROCESS_STACK_SIZE       90

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
#define  scmRTOS_CONTEXT_SWITCH_SCHEME      1

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch User Hook enable
// 
//    The macro enables/disables user defined hook called from system
//    Context Switch Hook function.
//
//
#define  scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE  1

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
//
#define  scmRTOS_PRIORITY_ORDER             0

//-----------------------------------------------------------------------------
//
//    scmRTOS debug enable
// 
//    The macro enables debug mode which allows debug functionality
//    such as finding process's stack slack and some other.
//
//
#define scmRTOS_DEBUG_ENABLE  0

//-----------------------------------------------------------------------------

#endif // scmRTOS_CONFIG_H
//-----------------------------------------------------------------------------

