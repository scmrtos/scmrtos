//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   EW430 (IAR Systems)
//*               
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
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
//*     IAR/MSP430 port by Harry E. Zhurov, Copyright (c) 2003-2021


#ifndef scmRTOS_MSP430_H
#define scmRTOS_MSP430_H

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
//
#ifndef __IAR_SYSTEMS_ICC__
#error "This file should only be compiled with IAR C++ Compiler"
#endif 

#if (((__TID__ >> 8) & 0x7F) != 43)
#error "This file must be compiled for MSP430 processor only."
#endif 

#if __VER__ < 420
#error "This file must be compiled by IAR C/C++ Compiler v4.20 or higher."
#endif 

//------------------------------------------------------------------------------
//
//    Compiler specific attributes
//
//
#ifndef INLINE
#define INLINE _Pragma("inline=forced") inline
#endif

//------------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef uint16_t stack_item_t;
typedef uint16_t status_reg_t;

//-----------------------------------------------------------------------------
//
//    Target specific macros
//
//
#define OS_PROCESS   __task
#define OS_INTERRUPT __interrupt
#define DUMMY_INSTR() __no_operation()
#define INLINE_PROCESS_CTOR

//-----------------------------------------------------------------------------
// Separate return stack not required
#define SEPARATE_RETURN_STACK 0

//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_config.h"
#include "scmRTOS_TARGET_CFG.h"
#include <scmRTOS_defs.h>

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0x55aaU
#endif


//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    INLINE TCritSect () : StatusReg(__get_interrupt_state()) { __disable_interrupt(); }
    INLINE ~TCritSect() { __set_interrupt_state(StatusReg); }

private:
    status_reg_t StatusReg;
};
#endif // scmRTOS_USER_DEFINED_CRITSECT_ENABLE

//   Uncomment macro value below for system_timer() and
//   context_switch_hook() run in critical section.
// 
//   This is useful (and necessary) when target processor has hardware 
//   enabled nested interrups.
//   User can define own macros using user-defined TCritSect capabilities.
//
//   MSP430 does not have nested interrupts.
//
#ifndef SYS_TIMER_CRIT_SECT
#define SYS_TIMER_CRIT_SECT() // TCritSect cs
#endif
#ifndef CONTEXT_SWITCH_HOOK_CRIT_SECT
#define CONTEXT_SWITCH_HOOK_CRIT_SECT() // TCritSect cs
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
        for(uint_fast8_t i = 0; i < sizeof(Table)/sizeof(Table[0]); i++)
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
    INLINE uint_fast8_t highest_priority(TProcessMap pm)
    {
        uint_fast8_t pr = 0;

        while( !(pm & 0x0001) )
        {
            pr++;
            pm >>= 1;
        }
        return pr;
    }
#else
    INLINE uint_fast8_t highest_priority(TProcessMap pm)
    {
        uint_fast8_t pr = scmRTOS_PROCESS_COUNT;

        while( !(pm & (1 << scmRTOS_PROCESS_COUNT) ) )
        {
            pr--;
            pm <<= 1;
        }
        return pr;
    }
#endif // scmRTOS_PRIORITY_ORDER
}


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE status_reg_t get_interrupt_state( )             { return __get_interrupt_state(); }
INLINE void       set_interrupt_state(status_reg_t sr) { __set_interrupt_state(sr);      }

INLINE void enable_interrupts()  { __enable_interrupt();  }
INLINE void disable_interrupts() { __disable_interrupt(); }

#pragma segment="CSTACK"

INLINE stack_item_t* get_stack_pointer()    { return reinterpret_cast<stack_item_t*>(__get_SP_register()); }

#pragma diag_suppress=Ta20
INLINE void        set_isr_stack_pointer() { __set_SP_register( reinterpret_cast<uint16_t>(__segment_end("CSTACK")) ); }
#pragma diag_default=Ta20

#pragma diag_suppress=Ta20
INLINE void        set_stack_pointer(stack_item_t* sp) { __set_SP_register( reinterpret_cast<uint16_t>(sp) ); }
#pragma diag_default=Ta20

namespace OS
{
    INLINE void enable_context_switch()  { enable_interrupts(); }
    INLINE void disable_context_switch() { disable_interrupts(); }
}

#include <os_kernel.h>

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
        INLINE  TISRW()  { isr_enter(); }
        INLINE  ~TISRW() { isr_exit();  }

    private:
        //-----------------------------------------------------
        INLINE void isr_enter()
        {
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE void isr_exit()
        {
            disable_interrupts();
            if(--Kernel.ISR_NestCount) return;
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };

    class TISRW_SS
    {
    public:
        INLINE  TISRW_SS()  { isr_enter(); }
        INLINE  ~TISRW_SS() { isr_exit();  }

    private:
        //-----------------------------------------------------
        INLINE void isr_enter()
        {
            if(Kernel.ISR_NestCount++ == 0)
            {
                TKernel::ProcessTable[Kernel.CurProcPriority]->StackPointer = get_stack_pointer();
                set_isr_stack_pointer();
            }
        }
        //-----------------------------------------------------
        INLINE void isr_exit()
        {
            disable_interrupts();
            if(--Kernel.ISR_NestCount) return;
            set_stack_pointer(TKernel::ProcessTable[Kernel.CurProcPriority]->StackPointer);
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };

}
//-----------------------------------------------------------------------------

#endif // scmRTOS_MSP430_H
//-----------------------------------------------------------------------------

