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
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
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
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011-2015

#ifndef scmRTOS_STM8_H
#define scmRTOS_STM8_H


//------------------------------------------------------------------------------
//
//      Compiler and Target checks
//
//
#ifndef __IAR_SYSTEMS_ICC__
#error "This file should only be compiled with IAR C++ Compiler"
#endif // __IAR_SYSTEMS_ICC__

#if (((__TID__ >> 8) & 0x7F) != 0x38)
#error This file should only be compiled by STM8 IAR compiler and assembler
#endif

// LARGE data model is very inefficient (especially for C++ ?)
// and seems will not be supported.
// It is recommended to declare large constant arrays as __far explicitly.
#if __DATA_MODEL__ == __LARGE_DATA_MODEL__
#error LARGE data model is not supported by this scmRTOS port
#endif

//------------------------------------------------------------------------------
//
//      IAR Systems include file[s]
//
#include <intrinsics.h> // interrupt state handling


//------------------------------------------------------------------------------
//    Some configuration macro are commented out in scmRTOS_CONFIG.h and
//  placed here because of port limitation.
#define  scmRTOS_CONTEXT_SWITCH_SCHEME      0


//------------------------------------------------------------------------------
//
//    Compiler specific attributes
//
//
#ifndef INLINE
#define INLINE _Pragma("inline=forced") inline
#endif

#ifndef NORETURN
#define NORETURN __noreturn
#endif

//------------------------------------------------------------------------------
//
//    Target specific types
//
//
// TODO: typedef __near uint8_t stack_item_t; for large+ data models? (stack_item_t* must be 16 bit)
typedef uint8_t stack_item_t;
typedef __istate_t status_reg_t;

//-----------------------------------------------------------------------------
//
//      Target specific macros
//
//
#define OS_PROCESS    __task
#define OS_INTERRUPT  __interrupt
#define DUMMY_INSTR() __no_operation()
#define INLINE_PROCESS_CTOR INLINE

//-----------------------------------------------------------------------------
// Separate return stack not required
#define SEPARATE_RETURN_STACK  0


//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"
#include <scmRTOS_defs.h>

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0x5AU
#endif

#define scmRTOS_TARGET_IDLE_HOOK_ENABLE 0

//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    TCritSect () : InterruptState(__get_interrupt_state()) { __disable_interrupt(); }
    ~TCritSect() { __set_interrupt_state(InterruptState); }

private:
    status_reg_t InterruptState;
};
#endif // scmRTOS_USER_DEFINED_CRITSECT_ENABLE

//   Uncomment macro value below for system_timer() and
//   context_switch_hook() run in critical section
// 
//   This is useful (and necessary) when target processor has hardware 
//   enabled nested interrups.
//   User can define own macros using user-defined TCritSect capabilities.
// 
//   STM8 has multi-level interrupt system so system timer and context switcher
//   interrupts can be interrupted.
//
#ifndef SYS_TIMER_CRIT_SECT
#define SYS_TIMER_CRIT_SECT()           TCritSect cs
#endif
// CONTEXT_SWITCH_HOOK_CRIT_SECT() is used only for scmRTOS_CONTEXT_SWITCH_SCHEME == 1
// TODO: add SIM at context switching start just after push CC ?
// Or context switch hook is better?
#ifndef CONTEXT_SWITCH_HOOK_CRIT_SECT
#define CONTEXT_SWITCH_HOOK_CRIT_SECT() TCritSect cs
#endif

//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//
namespace OS
{

struct TPrioMaskTable
{
    TPrioMaskTable()
    {
        TProcessMap pm = 0x01;
        for(uint8_t i = 0; i < sizeof(Table)/sizeof(Table[0]); i++)
        {
            Table[i] = pm;
            pm <<= 1;
        }
    }

    TProcessMap Table[scmRTOS_PROCESS_COUNT+1];
};

extern TPrioMaskTable PrioMaskTable;

INLINE OS::TProcessMap get_prio_tag(const uint_fast8_t pr) { return PrioMaskTable.Table[pr]; }

#if scmRTOS_PRIORITY_ORDER == 0
    INLINE uint8_t highest_priority(TProcessMap pm)
    {
        uint8_t pr = 0;

        while( !(pm & 0x0001) )
        {
            pr++;
            pm >>= 1;
        }
        return pr;
    }
#else
    INLINE uint8_t highest_priority(TProcessMap pm)
    {
        uint8_t pr = scmRTOS_PROCESS_COUNT;

        while( !(pm & (1 << scmRTOS_PROCESS_COUNT) ) )
        {
            pr--;
            pm <<= 1;
        }
        return pr;
    }
#endif // scmRTOS_PRIORITY_ORDER

} // namespace OS


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE status_reg_t get_interrupt_state( )               { return __get_interrupt_state(); }
INLINE void         set_interrupt_state(status_reg_t sr) { __set_interrupt_state(sr); }

INLINE void enable_interrupts()  { __enable_interrupt();  }
INLINE void disable_interrupts() { __disable_interrupt(); }

#if 0

// TODO: Separate stack for interrupts
INLINE stack_item_t* get_stack_pointer() { return reinterpret_cast<stack_item_t*>(SP); }
INLINE void  set_stack_pointer(stack_item_t* sp) { SP = reinterpret_cast<uint16_t>(sp); }

INLINE void set_isr_stack_pointer()
{
    // OS::run() never returns and main stack can be used as ISR stack 
    // symbol from initial stack value, set to RAMEND by default
    extern uint8_t __stack;
    SP = reinterpret_cast<uint16_t>(&__stack);
}

#endif

namespace OS
{
    INLINE void enable_context_switch()  { enable_interrupts();  }
    INLINE void disable_context_switch() { disable_interrupts(); }
}

//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
#include <os_kernel.h>
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
namespace OS
{
    //--------------------------------------------------------------------------
    //
    //      NAME       :   OS ISR support 
    //
    //      PURPOSE    :   Implements common actions on interrupt enter and exit 
    //                     under the OS
    //
    //      DESCRIPTION:
    //
    //
    class TISRW
    {
    public:
        INLINE  TISRW()  { ISR_Enter(); }
        INLINE  ~TISRW() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE void ISR_Enter()
        {
            // STM8 can (atomically) increment byte in memory, but IAR 1.20 and 1.30 - can't :-(
            TCritSect cs;
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
        {
            TCritSect cs; // FIXME: disable_interrupts() is enough ?
            if(--Kernel.ISR_NestCount) return;
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };

#if 1
    // Separate Stack for interrupts is not supported now
    // Define for compatibility:
    #define TISRW_SS TISRW
#else
    class TISRW_SS
    {
    public:
        INLINE  TISRW_SS()  { ISR_Enter(); }
        INLINE  ~TISRW_SS() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE void ISR_Enter() // volatile
        {
            TCritSect cs;
            if(Kernel.ISR_NestCount++ == 0)
            {
                Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer = get_stack_pointer();
                set_isr_stack_pointer();
            }
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
        {
            TCritSect cs; // FIXME: disable_interrupts() is enough ?
            if(--Kernel.ISR_NestCount) return;
            set_stack_pointer(Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer);
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };
#endif
}
//-----------------------------------------------------------------------------

#endif // scmRTOS_STM8_H

