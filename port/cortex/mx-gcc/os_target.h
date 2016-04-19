//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M0(+), Cortex-M1, Cortex-M3, Cortex-M4(F)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
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
//*     Cortex-M3/M4(F) GCC port by Anton B. Gusev aka AHTOXA, Copyright (c) 2012-2016
//*     Cortex-M0 port by Sergey A. Borshch, Copyright (c) 2011-2016

#ifndef scmRTOS_CORTEXMX_H
#define scmRTOS_CORTEXMX_H

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
//
#ifndef __GNUC__
#error "This file should only be compiled with GNU C++ Compiler"
#endif // __GNUC__

#if (!defined __ARM_ARCH_7M__) && (!defined __ARM_ARCH_7EM__) && (!defined __ARM_ARCH_6M__)
#error "This file must be compiled for ARMv6-M (Cortex-M0(+)), ARMv7-M (Cortex-M3) and ARMv7E-M (Cortex-M4(F)) processors only."
#endif

#if (__GNUC__ < 3)
#error "This file must be compiled by GCC C/C++ Compiler v3.0 or higher."
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
#define OS_PROCESS __attribute__((__noreturn__))
#define OS_INTERRUPT extern "C"

#define DUMMY_INSTR() __asm__ __volatile__ ("nop")
#define INLINE_PROCESS_CTOR INLINE

//-----------------------------------------------------------------------------
// Separate return stack not required
#define SEPARATE_RETURN_STACK   0

//-----------------------------------------------------------------------------
// Software interrupt stack switching not supported in Cortex-M port
// because processor implements hardware stack switching.
// So, system timer ISR wrapper can't be chosen at project level
//
#define scmRTOS_ISRW_TYPE       TISRW

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch Scheme
//
//    The macro defines a context switch manner. Value 0 sets direct context
//    switch in the scheduler and in the OS ISRs. This is the primary method.
//    Value 1 sets the second way to switch context - by using of software
//    interrupt. See documentation for details.
//    Cortex-M port supports software interrupt switch method only.
//
#define  scmRTOS_CONTEXT_SWITCH_SCHEME 1

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
//    On Cortex-M3/M4 the descending order is used for performance reason.
//    Cortex-M0 lacks CLZ instruction, so only ascending order is implemented for it.
//
#if (defined __ARM_ARCH_6M__)
#define  scmRTOS_PRIORITY_ORDER             0
#else
#define  scmRTOS_PRIORITY_ORDER             1
#endif

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
#define enable_interrupts() __asm__ __volatile__ ("cpsie i")
#define disable_interrupts() __asm__ __volatile__ ("cpsid i")

INLINE void set_interrupt_state(status_reg_t status)
{
    __asm__ __volatile__ (
        "MSR PRIMASK, %0\n"
        : : "r"(status)
        :"memory"
    );
}

INLINE status_reg_t get_interrupt_state()
{
    status_reg_t sr;
    __asm__ __volatile__ ("MRS %0, PRIMASK" : "=r"(sr) );
    return sr;
}

//-----------------------------------------------------------------------------
//
//     The Critical Section Wrapper
//
//
#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    TCritSect () : StatusReg(get_interrupt_state()) { disable_interrupts(); }
    ~TCritSect() { set_interrupt_state(StatusReg); }

private:
    status_reg_t StatusReg;
};
#endif // scmRTOS_USER_DEFINED_CRITSECT_ENABLE

//   Uncomment macro value below for system_timer() and
//   context_switch_hook() run in critical section.
//
//   This is useful (and necessary) when target processor has hardware
//   enabled nested interrupts.
//   User can define own macros using user-defined TCritSect capabilities.
//
//   Cortex-M have nested interrupts but interrupts are disabled
//   during context switch ISR. So, critical section is needed
//   for system timer routine and not needed for context switcher.
//
#define SYS_TIMER_CRIT_SECT() TCritSect cs
#define CONTEXT_SWITCH_HOOK_CRIT_SECT()


//-----------------------------------------------------------------------------
//
//     Lock/unlock system timer.
//
//
void LOCK_SYSTEM_TIMER();
void UNLOCK_SYSTEM_TIMER();


//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//
namespace OS
{
INLINE OS::TProcessMap get_prio_tag(const uint_fast8_t pr) { return static_cast<OS::TProcessMap> (1 << pr); }

#if scmRTOS_PRIORITY_ORDER == 0
    INLINE uint_fast8_t highest_priority(TProcessMap pm)
    {
        extern TPriority const PriorityTable[];

        #if scmRTOS_PROCESS_COUNT < 6
            return PriorityTable[pm];
        #else
            uint32_t x = pm;
            x = x & -x;                             // Isolate rightmost 1-bit.

                                                // x = x * 0x450FBAF
            x = (x << 4) | x;                       // x = x*17.
            x = (x << 6) | x;                       // x = x*65.
            x = (x << 16) - x;                      // x = x*65535.

            return PriorityTable[x >> 26];
        #endif  // scmRTOS_PROCESS_COUNT < 6
    }
#else
    INLINE uint_fast8_t highest_priority(TProcessMap pm)
    {
        return 31 - __builtin_clz(pm);
    }
#endif // scmRTOS_PRIORITY_ORDER
}

namespace OS
{
    INLINE void enable_context_switch()  { enable_interrupts(); }
    INLINE void disable_context_switch() { disable_interrupts(); }
}

//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//
namespace OS
{
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

// 0xE000ED04 - Interrupt Control State Register
INLINE void raise_context_switch() { *((volatile uint32_t*)0xE000ED04) |= 0x10000000; }

#define ENABLE_NESTED_INTERRUPTS()

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
#define DISABLE_NESTED_INTERRUPTS() TCritSect cs
#else
#define DISABLE_NESTED_INTERRUPTS()
#endif

#else
#error "Cortex-M3 port supports software interrupt switch method only!"

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

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
    INLINE  TISRW()  { ISR_Enter(); }
    INLINE  ~TISRW() { ISR_Exit();  }

private:
    //-----------------------------------------------------
    INLINE void ISR_Enter()
    {
        TCritSect cs;
        Kernel.ISR_NestCount++;
    }
    //-----------------------------------------------------
    INLINE void ISR_Exit()
    {
        TCritSect cs;
        if(--Kernel.ISR_NestCount) return;
        Kernel.sched_isr();
    }
    //-----------------------------------------------------
};

// No software interrupt stack switching provided,
// TISRW_SS declared to be the same as TISRW for porting compatibility
#define TISRW_SS    TISRW

/*
 * System timer interrupt handler.
 */
INLINE void system_timer_isr()
{
	OS::TISRW ISR;

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
    DISABLE_NESTED_INTERRUPTS();
#endif

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif

    Kernel.system_timer();
}

} // namespace OS
//-----------------------------------------------------------------------------

#endif // scmRTOS_CORTEXMX_H
//-----------------------------------------------------------------------------

