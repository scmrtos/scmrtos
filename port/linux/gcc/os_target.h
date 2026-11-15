//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: Linux host (x86-64, AArch64, ...) - simulation/test port
//*
//*     TOOLKIT:   GCC, Clang (glibc)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version: v5.2.0
//*
//*
//*     Copyright (c) 2003-2026, scmRTOS Team
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
//*     Linux test port
//*
//*     The whole RTOS runs in one Linux thread:
//*       - a process context is a ucontext_t, switched with swapcontext();
//*       - "interrupts" are POSIX signals: the system timer is SIGALRM,
//*         the software context-switch interrupt (scheme 1) is SIGRTMIN+8,
//*         user interrupts 0..7 are SIGRTMIN+0..7;
//*       - the critical section blocks all these signals (sigprocmask).
//*     See README.md next to this file.

#ifndef scmRTOS_LINUX_H
#define scmRTOS_LINUX_H

#include <stddef.h>
#include <stdint.h>
#include <signal.h>

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
#if !defined(__GNUC__) || !defined(__linux__)
#error "This port must be compiled by GCC or Clang for Linux"
#endif

//------------------------------------------------------------------------------
//
//    Compiler specific attributes
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
//    A process "stack pointer" holds the address of the process ucontext_t,
//    so stack_item_t must be able to hold a pointer.
//
typedef uintptr_t stack_item_t;
typedef int       status_reg_t;      // 1 - interrupts disabled, 0 - enabled (see get_interrupt_state())

//-----------------------------------------------------------------------------
//
//    Configuration macros
//
#define OS_PROCESS   __attribute__((__noreturn__))
#define OS_INTERRUPT extern "C"
#define DUMMY_INSTR() __asm__ __volatile__ ("" ::: "memory")
#define INLINE_PROCESS_CTOR INLINE

#define SEPARATE_RETURN_STACK   0
#define scmRTOS_ISRW_TYPE       TISRW

//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"

//-----------------------------------------------------------------------------
//
//    Port configuration (may be set in scmRTOS_TARGET_CFG.h or on the command line)
//
//    scmRTOS_CONTEXT_SWITCH_SCHEME  0 - direct switch in the scheduler (default)
//                                   1 - switch by software interrupt (SIGRTMIN+8),
//                                       the same code path as Cortex-M and Zynq-7000
//    scmRTOS_PRIORITY_ORDER         0 - ascending (default), 1 - descending
//
//    scmRTOS_LINUX_TICK_MODE        0 - manual: the system timer ticks only when the
//                                       application calls OS::sim_tick(); deterministic,
//                                       for tests (default)
//                                   1 - real time: SIGALRM from setitimer()
//    scmRTOS_LINUX_TICK_PERIOD_US   system timer period in real-time mode, us (default 1000)
//
//    scmRTOS_LINUX_PRIO_MASK_TABLE  0 - get_prio_tag() is a shift (default)
//                                   1 - get_prio_tag() reads a dynamically initialized
//                                       table, like the AVR/MSP430/STM8 ports do
//
//    scmRTOS_LINUX_MIN_STACK_SIZE   minimal process stack, bytes; a smaller process
//                                   stack is reported at start-up (default 16384)
//
#ifndef scmRTOS_CONTEXT_SWITCH_SCHEME
#define scmRTOS_CONTEXT_SWITCH_SCHEME 0
#endif

#ifndef scmRTOS_PRIORITY_ORDER
#define scmRTOS_PRIORITY_ORDER        0
#endif

#ifndef scmRTOS_LINUX_TICK_MODE
#define scmRTOS_LINUX_TICK_MODE       0
#endif

#ifndef scmRTOS_LINUX_TICK_PERIOD_US
#define scmRTOS_LINUX_TICK_PERIOD_US  1000
#endif

#ifndef scmRTOS_LINUX_PRIO_MASK_TABLE
#define scmRTOS_LINUX_PRIO_MASK_TABLE 0
#endif

#ifndef scmRTOS_LINUX_MIN_STACK_SIZE
#define scmRTOS_LINUX_MIN_STACK_SIZE  16384
#endif

#if (scmRTOS_LINUX_TICK_MODE < 0) || (scmRTOS_LINUX_TICK_MODE > 1)
#error "Error: scmRTOS_LINUX_TICK_MODE must have values 0 or 1 only!"
#endif

// In real-time mode the idle process sleeps until the next signal.
#if (scmRTOS_LINUX_TICK_MODE == 1) && !defined(scmRTOS_TARGET_IDLE_HOOK_ENABLE)
#define scmRTOS_TARGET_IDLE_HOOK_ENABLE 1
#endif

#include <scmRTOS_defs.h>

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0xABBAABBA
#endif

//-----------------------------------------------------------------------------
//
//     "Interrupts": signals used by the port
//
namespace OS
{
namespace host
{
    const int IRQ_COUNT        = 8;                     // user interrupts 0..7
    const int SIG_SYSTEM_TIMER = SIGALRM;

    // The context switch interrupt must be the last one taken when several are
    // pending, like PendSV with the lowest priority on Cortex-M: an interrupt
    // that is pending when the scheduler asks for a switch runs first and may
    // change the process to switch to. Linux delivers the lowest-numbered pending
    // signal first, so the context switch uses a number above all the others.
    INLINE int context_sw_signal() { return SIGRTMIN + IRQ_COUNT; }

    // "Pended" bit of the context switch interrupt: real-time signals queue,
    // a pended interrupt does not.
    extern volatile sig_atomic_t ContextSwitchPended;
    INLINE int irq_signal(int n) { return SIGRTMIN + n; }

    // the set of all signals that the port treats as interrupts
    extern sigset_t IrqSignals;

    // Install 'handler' for user interrupt n (0..IRQ_COUNT-1). The handler is an
    // ordinary function; as in other ports it must declare OS::TISRW first.
    void set_irq_handler(int n, void (*handler)());

    // Request user interrupt n. Delivered at once, or when the critical section ends.
    void raise_irq(int n);

    // Prepare a process context; used by TBaseProcess::init_stack_frame().
    stack_item_t* init_context(uint_fast8_t pr, stack_item_t* stack_begin, stack_item_t* stack_end, void (*exec)());
}
}

//-----------------------------------------------------------------------------
//
//     The Critical Section Wrapper
//
//     scmRTOS_LINUX_CRITSECT_EXIT_HOOK (optional) names a function `void f()`
//     that is called every time an outermost critical section ends, i.e. at
//     every point where a pending interrupt would be taken on a real MCU.
//     Tests use it to inject interrupts at all such points (see test/unit).
//
#ifdef scmRTOS_LINUX_CRITSECT_EXIT_HOOK
extern "C" void scmRTOS_LINUX_CRITSECT_EXIT_HOOK();
#endif

INLINE void enable_interrupts()  { sigprocmask(SIG_UNBLOCK, &OS::host::IrqSignals, 0); }
// 1 if the interrupts are disabled now (inside a critical section or an interrupt handler)
INLINE status_reg_t get_interrupt_state()
{
    sigset_t m;
    sigprocmask(SIG_BLOCK, 0, &m);
    return sigismember(&m, OS::host::SIG_SYSTEM_TIMER) == 1;
}
INLINE void disable_interrupts() { sigprocmask(SIG_BLOCK,   &OS::host::IrqSignals, 0); }

#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    INLINE TCritSect () { sigprocmask(SIG_BLOCK, &OS::host::IrqSignals, &Saved); __asm__ __volatile__ ("" ::: "memory"); }
    INLINE ~TCritSect()
    {
        __asm__ __volatile__ ("" ::: "memory");
        sigprocmask(SIG_SETMASK, &Saved, 0);
    #ifdef scmRTOS_LINUX_CRITSECT_EXIT_HOOK
        if(sigismember(&Saved, OS::host::SIG_SYSTEM_TIMER) == 0)    // interrupts are enabled again
            scmRTOS_LINUX_CRITSECT_EXIT_HOOK();
    #endif
    }

private:
    sigset_t Saved;
};
#endif // scmRTOS_USER_DEFINED_CRITSECT_ENABLE

// Interrupt handlers run with all port signals blocked: no nesting.
#define SYS_TIMER_CRIT_SECT()
#define CONTEXT_SWITCH_HOOK_CRIT_SECT()

//-----------------------------------------------------------------------------
//
//     Lock/unlock system timer: ticks that arrive while locked are dropped,
//     like a timer with its interrupt disabled.
//
void LOCK_SYSTEM_TIMER();
void UNLOCK_SYSTEM_TIMER();

//-----------------------------------------------------------------------------
//
//     Priority stuff
//
namespace OS
{
#if scmRTOS_LINUX_PRIO_MASK_TABLE == 1
    struct TPrioMaskTable
    {
        TPrioMaskTable()
        {
            TProcessMap pm = 0x01;
            for(uint8_t i = 0; i < sizeof(Table)/sizeof(Table[0]); i++) { Table[i] = pm; pm <<= 1; }
        }
        TProcessMap Table[scmRTOS_PROCESS_COUNT+1];
    };
    extern TPrioMaskTable PrioMaskTable;
    INLINE TProcessMap get_prio_tag(const uint_fast8_t pr) { return PrioMaskTable.Table[pr]; }
#else
    INLINE TProcessMap get_prio_tag(const uint_fast8_t pr) { return static_cast<TProcessMap>(static_cast<TProcessMap>(1) << pr); }
#endif

#if scmRTOS_PRIORITY_ORDER == 0
    INLINE uint_fast8_t highest_priority(TProcessMap pm) { return static_cast<uint_fast8_t>(__builtin_ctzll(pm)); }
#else
    INLINE uint_fast8_t highest_priority(TProcessMap pm) { return static_cast<uint_fast8_t>(63 - __builtin_clzll(pm)); }
#endif
}

//------------------------------------------------------------------------------
//
//       Context Switch stuff
//
namespace OS
{
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    // Pend the context switch interrupt (like PendSV): it is taken when the
    // signals are unblocked, after every other interrupt pending at that moment.
    INLINE void raise_context_switch()
    {
        if(!host::ContextSwitchPended)          // always called with the interrupts disabled
        {
            host::ContextSwitchPended = 1;
            raise(host::context_sw_signal());
        }
    }
    INLINE void enable_context_switch()  { enable_interrupts();  }
    INLINE void disable_context_switch() { disable_interrupts(); }
#else
    INLINE void enable_context_switch()  { }
    INLINE void disable_context_switch() { }
#endif

#define ENABLE_NESTED_INTERRUPTS()
#define DISABLE_NESTED_INTERRUPTS()
}

#include <os_kernel.h>

namespace OS
{
    //--------------------------------------------------------------------------
    //
    //      NAME       :   OS ISR support
    //
    //      PURPOSE    :   Implements common actions on interrupt enter and exit
    //                     under the OS. Declare it first in every interrupt handler.
    //
    class TISRW
    {
    public:
        INLINE  TISRW()  { ISR_Enter(); }
        INLINE  ~TISRW() { ISR_Exit();  }

    private:
        INLINE void ISR_Enter()
        {
            TCritSect cs;
            Kernel.ISR_NestCount = Kernel.ISR_NestCount + 1;
        }
        INLINE void ISR_Exit()
        {
            TCritSect cs;
            uint_fast8_t cnt = Kernel.ISR_NestCount - 1;
            Kernel.ISR_NestCount = cnt;
            if(cnt) return;
            Kernel.sched_isr();
        }
    };

    // No interrupt stack switching: handlers run on the stack of the interrupted process.
    #define TISRW_SS    TISRW

    //--------------------------------------------------------------------------
    //
    //    System timer interrupt handler (SIGALRM)
    //
    INLINE void system_timer_isr()
    {
        OS::TISRW ISR;

    #if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
        system_timer_user_hook();
    #endif

        Kernel.system_timer();
    }

    //--------------------------------------------------------------------------
    //
    //    One system timer tick, as if the timer interrupt fired here.
    //    Taken at once, or at the end of the critical section if called inside one.
    //    Usable in both tick modes; in manual mode it is the only tick source.
    //
    INLINE void sim_tick() { raise(host::SIG_SYSTEM_TIMER); }

} // namespace OS
//-----------------------------------------------------------------------------

#endif // scmRTOS_LINUX_H
//-----------------------------------------------------------------------------
