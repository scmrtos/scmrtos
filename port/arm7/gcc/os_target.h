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
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2012

#ifndef scmRTOS_ARM_H
#define scmRTOS_ARM_H

#ifndef __GNUC__
#error "This file should only be compiled with GNU C++ Compiler"
#endif // __GNUC__

#ifndef __ARM_ARCH_4T__
#error "This file must be compiled for ARM7TDMI processor only."
#endif

#if (__GNUC__ < 3)
#error "This file must be compiled by GCC C/C++ Compiler v3.0 or higher."
#endif

#ifdef  __THUMBEL__
//#error "This file should be compiled in ARM mode only"
#endif // __thumb__

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

#ifndef INLINE_PROCESS_CTOR
#define INLINE_PROCESS_CTOR
#endif


//-----------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef uint32_t stack_item_t;
typedef uint32_t status_reg_t;


//-----------------------------------------------------------------------------
//
//    Configuration macros
//
//

//--------------------------------------------------
// Separate return stack not required
#define SEPARATE_RETURN_STACK   0

//--------------------------------------------------
// software interrupt stack switching not supported in ARM port
// because ARM architecture implements hardware stack switching.
// So, system timer irq wrapper can't be choosen at project level
#define scmRTOS_ISRW_TYPE       TISRW

//-----------------------------------------------------------------------------
//
//    scmRTOS Priority Order
//
//    This macro defines the order of the process's priorities.
//    The ascending order is used, because of a little bit better performance.
//    Descending order is not implemented in ARM7 port
//
#define  scmRTOS_PRIORITY_ORDER 0

//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"
#include <os_target_core.h>
#include <scmRTOS_defs.h>


#define OS_PROCESS      __attribute__((__noreturn__))
#define DUMMY_INSTR()   __asm__ __volatile__ ("nop" : : )

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0x87654321U
#endif

//-----------------------------------------------------------------------------
//
//     CPSR access functions
//
//

#ifndef __THUMBEL__
// inline into ARM-mode code
INLINE status_reg_t __get_CPSR_inline()
{
    status_reg_t cpsr;
    asm volatile
    (
    " MRS  %0,CPSR    \r\n"
    :"=r"(cpsr)
    :
    );
    return cpsr;
}
INLINE void __set_CPSR_c_inline(status_reg_t cpsr)
{
    asm volatile
    (
    " MSR  CPSR_c, %0    \r\n"
    :
    :"r"(cpsr)
    );
}

#ifndef scmRTOS_OS_TARGET_CPP
// non-inlined ARM-mode code should present for call from thumb-code
    #define scmRTOS_ARM7_INLINE  INLINE
#else
    #define scmRTOS_ARM7_INLINE
#endif

scmRTOS_ARM7_INLINE status_reg_t __get_CPSR() { return __get_CPSR_inline(); }
scmRTOS_ARM7_INLINE void __set_CPSR_c(status_reg_t cpsr) { __set_CPSR_c_inline(cpsr); }

#else   //__THUMBEL__
extern status_reg_t __get_CPSR();
extern void __set_CPSR_c(status_reg_t cpsr);
#endif  //__THUMBEL__


//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//

#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    TCritSect ();
    ~TCritSect();
private:
    status_reg_t StatusReg;
};

#ifndef __THUMBEL__
// Atmel Application Note Rev. 1156A 08/98
scmRTOS_ARM7_INLINE TCritSect::TCritSect() : StatusReg( __get_CPSR_inline() )
{
    status_reg_t Tmp = StatusReg;
    do
    {
        __set_CPSR_c(Tmp | (1<<7));   // disable IRQ
        Tmp = __get_CPSR_inline();
    }
    while (!(Tmp & (1<<7)));
}

scmRTOS_ARM7_INLINE TCritSect::~TCritSect()
{
    __set_CPSR_c_inline(StatusReg);
}
#endif  //__THUMBEL__

//   Uncomment macro value below for system_timer() and
//   context_switch_hook() run in critical section.
// 
//   This is useful (and necessary) when target processor has hardware 
//   enabled nested interrups.
//   User can define own macros using user-defined TCritSect capabilities.
//
//   ARM7 does not have nested interrupts.
//
#ifndef SYS_TIMER_CRIT_SECT
#define SYS_TIMER_CRIT_SECT() // TCritSect cs
#endif
#ifndef CONTEXT_SWITCH_HOOK_CRIT_SECT
#define CONTEXT_SWITCH_HOOK_CRIT_SECT() // TCritSect cs
#endif

#endif // scmRTOS_USER_DEFINED_CRITSECT_ENABLE


namespace OS
{
//------------------------------------------------------------------------------
//
//       Declaring system timer handler
//
//
    OS_INTERRUPT void system_timer_isr();

//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//

    INLINE TProcessMap get_prio_tag(const uint_fast8_t pr)
    {
        return static_cast<TProcessMap> (1 << pr);
    }

    INLINE TPriority highest_priority(TProcessMap pm)
    {
        extern TPriority const PriorityTable[];

        #if scmRTOS_PROCESS_COUNT < 6
            return PriorityTable[pm];
        #else
            // Thanks to sergeeff, Yuri Tiomkin, Alexey Musin

            // http://www.hackersdelight.org/HDcode/ntz.cc
            uint32_t x = pm;
            x = x & -x;                             // Isolate rightmost 1-bit.

                                                // x = x * 0x450FBAF
            x = (x << 4) | x;                       // x = x*17.
            x = (x << 6) | x;                       // x = x*65.
            x = (x << 16) - x;                      // x = x*65535.

            return PriorityTable[x >> 26];
        #endif  // scmRTOS_PROCESS_COUNT < 6
    }
}   //  namespace


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE status_reg_t get_interrupt_state() { return __get_CPSR(); }
INLINE void set_interrupt_state(status_reg_t sr) { __set_CPSR_c(sr);}

INLINE void enable_interrupts() { __set_CPSR_c(__get_CPSR() & ~(1<<7)); }
INLINE void disable_interrupts()
{
    status_reg_t Tmp = __get_CPSR();
    do
    {
        __set_CPSR_c(Tmp | (1<<7));
        Tmp = __get_CPSR();
    }
    while (!(Tmp & (1<<7)));
}

#if scmRTOS_OBSOLETE_NAMES == 1

INLINE status_reg_t GetInterruptState( )             { return get_interrupt_state(); }
INLINE void       SetInterruptState(status_reg_t sr) { set_interrupt_state(sr);      }

INLINE void EnableInterrupts()  { enable_interrupts();  }
INLINE void DisableInterrupts() { disable_interrupts(); }

#endif // scmRTOS_OBSOLETE_NAMES

namespace OS
{
    INLINE void enable_context_switch()  { enable_interrupts(); }
    INLINE void disable_context_switch() { disable_interrupts(); }
}


//-----------------------------------------------------------------------------
//
//     Kernel-related inline functions
//
//
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
extern "C" INLINE void os_context_switcher(stack_item_t** Curr_SP, stack_item_t* Next_SP)
{
//  commented lines below makes compiled code shorter
//    register stack_item_t* arg asm("r1");
//    arg = Next_SP;
    asm volatile(
        //  - store -
        "STMFD  SP!, {R0-R12,LR}        \r\n"   // store R0_R12, LR to reserve space in context
        "MRS    r2, CPSR                \r\n"   // move CPSR of process to register
        "STMFD  SP!, {r2,LR}            \r\n"   // store CPSR, LR on top of context and adjust SP
        "ADR    LR, 1f                  \r\n"   // load context switcher exit address,
                                                // to branch to if context stored in OS_ContextSwitcher
        "STR    LR, [SP, #4*15]         \r\n"   // store return address in reserved space (instead of first saved LR)
        "STR    SP, [%0]                \r\n"
        //  - restore -
        "LDMFD   %1!, {r2, LR}          \r\n"   // restoring LR_user, saved CPSR_user
        "ADD     SP, %1, #4*14          \r\n"   // set process SP

        "MSR     CPSR_c, %2             \r\n"   // switch to IRQ mode to get access to SPSR_irq
        "MSR     SPSR_cxsf, r2          \r\n"   // store process CPSR to SPSR_irq to restore at return from irq

        "LDMFD   %1, {R0-R12,PC}^       \r\n"   // restoring remaining context, CPSR and reti
"1:"

        :
        :"r"(Curr_SP), "r"(Next_SP), "n"(NIRQ | MODE_IRQ)
        :"r2"
    );
}
#endif
extern "C" __attribute__((__noreturn__)) void context_restore(stack_item_t* sp);
extern "C" __attribute__((__noreturn__))
INLINE void os_start(stack_item_t* sp)
{
    context_restore(sp);
}

#include <os_kernel.h>

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
        INLINE TISRW();
        INLINE ~TISRW();
    private:
    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
        INLINE void save_sp(stack_item_t** Curr_SP);
        INLINE void load_sp(stack_item_t* New_SP);
    #endif
    };

    // no software interrupt stack switching provided,
    // TISRW_SS declared to be the same as TISRW for porting compability
    #define TISRW_SS    TISRW

    //--------------------------------------------------------------------------
    //
    //      OS system timer handler
    //
    INLINE void system_timer_handler()
    {
        Kernel.system_timer();
    #if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
        system_timer_user_hook();
    #endif
    }

    #if scmRTOS_OBSOLETE_NAMES == 1

    INLINE void SystemTimer_ISR() { system_timer_isr(); }

    #endif // scmRTOS_OBSOLETE_NAMES

}   //  namespace OS

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
inline void OS::TISRW::save_sp(stack_item_t** Curr_SP)
{
    asm volatile (
        "MSR     CPSR_c, %1     \r\n" // switching to System mode, to get access to sp_user
        "STR     SP, [%0]       \r\n"
        "MSR     CPSR_c, %2     \r\n" // switching back to IRQ mode
        :
        :"r"(Curr_SP),"n"(NIRQ | MODE_SYS), "n"(NIRQ | MODE_IRQ)
    );
}
inline void OS::TISRW::load_sp(stack_item_t* New_SP)
{
    asm volatile (
        "MSR     CPSR_c, %1     \r\n" // switching to System mode, to get access to sp_user
        "MOV     SP, %0         \r\n"
        "MSR     CPSR_c, %2     \r\n" // switching back to IRQ mode
        :
        :"r"(New_SP),"n"(NIRQ | MODE_SYS), "n"(NIRQ | MODE_IRQ)
    );
}
inline OS::TISRW::TISRW()
{
    if(Kernel.ISR_NestCount++ == 0)
    {
        save_sp(&TKernel::ProcessTable[Kernel.CurProcPriority]->StackPointer);
    }
}
inline OS::TISRW::~TISRW()
{
    if(--Kernel.ISR_NestCount) return;

    TPriority NextProcPriority = highest_priority(Kernel.ReadyProcessMap);
    stack_item_t*  Next_SP = TKernel::ProcessTable[NextProcPriority]->StackPointer;
    Kernel.CurProcPriority = NextProcPriority;
    load_sp(Next_SP);
}
#else
inline OS::TISRW::TISRW()
{
    Kernel.ISR_NestCount++;
}
INLINE OS::TISRW::~TISRW()
{
    disable_interrupts();
    if(--Kernel.ISR_NestCount) return;
    Kernel.sched_isr();
}
#endif

#endif // scmRTOS_ARM_H
