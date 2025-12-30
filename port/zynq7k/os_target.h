//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-A9
//*
//*     TOOLKIT:   ARM GCC
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
//*     Cortex-A9 GCC port by Harry E. Zhurov, Copyright (c) 2024

#ifndef scmRTOS_CORTEXA9_H
#define scmRTOS_CORTEXA9_H

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
//
#ifndef __GNUC__
#error "This file should only be compiled with GNU C++ Compiler"
#endif // __GNUC__

#if (!defined __ARM_ARCH_7A__)
#error "This file must be compiled for ARMv7-A (Cortex-A9) processors only."
#endif

#if (__GNUC__ < 7)
#error "This file must be compiled by GCC C/C++ Compiler v7.0 or higher."
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

#define DUMMY_INSTR() __asm__ __volatile__ ("    nop\n")
#define INLINE_PROCESS_CTOR INLINE

//-----------------------------------------------------------------------------
// Separate return stack not required
#define SEPARATE_RETURN_STACK   0

//-----------------------------------------------------------------------------
//    Software interrupt stack switching not supported in Cortex-A port
//    because processor implements hardware stack switching.
//    So, system timer ISR wrapper can't be chosen at project level
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
//    Cortex-A port supports software interrupt switch method only.
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
//    On Cortex-A9 the descending order is used for performance reason.
//
#define  scmRTOS_PRIORITY_ORDER             1

//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include <z7int.h>
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
#define scmRTOS_STACK_PATTERN 0xDEADC0DE
#endif


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
//     uses z7lib (https://github.com/z7bm/z7lib)


//-----------------------------------------------------------------------------
//
//     The Critical Section Wrapper
//
//     uses z7lib (https://github.com/z7bm/z7lib)
//
using TCritSect = CritSect;

//-----------------------------------------------------------------------------
//
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
INLINE uint_fast8_t    highest_priority(TProcessMap pm)    { return 31 - __builtin_clz(pm); }
INLINE void            enable_context_switch()             {  }
INLINE void            disable_context_switch()            {  }

}

//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//
namespace OS
{
INLINE void raise_context_switch() { asm __volatile__("    svc #0\n" ::: "memory"); }

//#define ENABLE_NESTED_INTERRUPTS()

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
#define DISABLE_NESTED_INTERRUPTS() TCritSect cs
#else
#define DISABLE_NESTED_INTERRUPTS()
#endif

}

#include <os_kernel.h>

namespace OS
{

//--------------------------------------------------------------------------
//
//      NAME       :   OS ISR support
//
//      PURPOSE    :   Provide access to update scheduling priority function
//                     call
//
class TISRW
{
public:
    bool context_switch_pending() { return Kernel.update_sched_prio(); }

};

//------------------------------------------------------------------------------
//
//    No software interrupt stack switching provided,
//    TISRW_SS declared to be the same as TISRW for porting compatibility
//
#define TISRW_SS    TISRW

//------------------------------------------------------------------------------
//
//    System timer
//
//--------------------------------------------------------------------
//
//    Setup and start system timer
//
//    Cortex-A9 CPU private timer is used as RTOS system timer
//
#include <z7ptmr.h>
//--------------------------------------------------------------------
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
//--------------------------------------------------------------------
//
//    f:  private timer clock, CPU_x2 clock (L2 domain clock), MHz
//    t:  system timer interrupt inteval, us
//    pr: system timer interrupt priority, integer value 0..30
//
INLINE void start_system_timer(uint32_t f, uint32_t t, size_t pr)
{
    ps7_register_isr(&OS::system_timer_isr, PS7IRQ_ID_PTMR);
    gic_set_priority(PS7IRQ_ID_PTMR, pr);
    gic_int_enable(PS7IRQ_ID_PTMR);
    PrivateTimer::set_reload_value(f, t); // MHz, us
    PrivateTimer::start();
}

} // namespace OS
//------------------------------------------------------------------------------

#endif // scmRTOS_CORTEXA9_H
//------------------------------------------------------------------------------

