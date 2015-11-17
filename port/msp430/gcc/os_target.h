//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   mspgcc (GNU)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
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
//*     mspgcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2008-2015

#ifndef scmRTOS_MSP430_H
#define scmRTOS_MSP430_H

#include <stdint.h>

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
//
#ifndef __GNUC__
#error "This file should only be compiled with GCC C++ Compiler"
#endif

#ifndef __MSP430__
#error "This file must be compiled for MSP430 processor only."
#endif

#if __GNUC__ < 3
#error GCC_VERSION "This file must be compiled by mspgcc v3.2.3 or higher."
#endif

//------------------------------------------------------------------------------
//
//    Compiler specific attributes
//
//
#ifndef INLINE
#define INLINE      __attribute__((__always_inline__)) inline
#endif

#ifndef NOINLINE
#define NOINLINE    __attribute__((__noinline__))
#endif

#ifndef NORETURN
#define NORETURN    __attribute__((__noreturn__))
#endif


//------------------------------------------------------------------------------
//
//    Target-specific types
//
//
typedef uint16_t stack_item_t;
typedef uint16_t status_reg_t;

//-----------------------------------------------------------------------------
//
//    Configuration macros
//
//
#define OS_PROCESS  NORETURN
#define OS_INTERRUPT
#define DUMMY_INSTR() __asm__ __volatile__ ("nop")
#define INLINE_PROCESS_CTOR INLINE

#define SEPARATE_RETURN_STACK 0

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
#define scmRTOS_STACK_PATTERN 0xABBA
#endif


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE void enable_interrupts()  { __enable_interrupt();  }
INLINE void disable_interrupts() { __disable_interrupt(); }

//-----------------------------------------------------------------------------
//
//     The Critical Section Wrapper
//
//
#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    TCritSect () : StatusReg(get_status_reg()) { disable_interrupts(); }
    ~TCritSect() { set_status_reg(StatusReg); }

private:
    status_reg_t StatusReg;
    INLINE status_reg_t get_status_reg()
    {
        status_reg_t __x;
        __asm__ __volatile__("MOV  R2, %0" : "=r" (__x));
        return __x;
    }
    INLINE void set_status_reg(status_reg_t sr)
    {
        __asm__ __volatile__("MOV  %0, R2" : : "r" (sr) : "memory");
    }
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
        return (TPriority)pr;
    }
#else
    INLINE TPriority highest_priority(TProcessMap pm)
    {
        uint_fast8_t pr = scmRTOS_PROCESS_COUNT;

        while( !(pm & (1 << scmRTOS_PROCESS_COUNT) ) )
        {
            pr--;
            pm <<= 1;
        }
        return (TPriority)pr;
    }
#endif // scmRTOS_PRIORITY_ORDER
}


#ifndef TISRW_SS_STACK_PAD
    #define TISRW_SS_STACK_PAD (4)
#endif

static INLINE stack_item_t* GetInitialStack()
{
    // symbol from gcrt1.S, initial stack value, set to RAMEND by default
    extern uint8_t __stack;
    // Step down a while from ramend. This allows to avoid crashes when compiler
    // reserves some space on stack before TISRW_SS constructor call.
    return (stack_item_t*)((uint16_t)&__stack - TISRW_SS_STACK_PAD);
}

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
        INLINE TISRW()  { ISR_Enter(); }
        INLINE ~TISRW() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE void ISR_Enter()
        {
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
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
        INLINE TISRW_SS()  { ISR_Enter(); }
        INLINE ~TISRW_SS() { ISR_Exit();  }

    private:
        INLINE stack_item_t* get_stack_pointer()
        {
            stack_item_t* __x;
            __asm__ __volatile__("MOV    R1, %0" : "=r" (__x));
            return __x;
        }
        INLINE void set_stack_pointer(stack_item_t* sp)
        {
            __asm__ __volatile__("MOV  %0, R1" : : "r" (sp));
        }

        INLINE void ISR_Enter()
        {
            if(Kernel.ISR_NestCount++ == 0)
            {
                TKernel::ProcessTable[Kernel.CurProcPriority]->StackPointer = get_stack_pointer();
                set_stack_pointer(GetInitialStack());
            }
        }
        INLINE void ISR_Exit()
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

