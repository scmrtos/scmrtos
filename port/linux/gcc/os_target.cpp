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
//*     PURPOSE:   Target Dependent Stuff Source
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

#include <scmRTOS.h>

#include <ucontext.h>

// AddressSanitizer keeps "poison" marks of old stack frames in a process stack;
// they must be cleared when the stack is reused for a (re)started process.
#if defined(__SANITIZE_ADDRESS__)
#define SCMRTOS_LINUX_ASAN 1
#elif defined(__has_feature)
#if __has_feature(address_sanitizer)
#define SCMRTOS_LINUX_ASAN 1
#endif
#endif
#ifdef SCMRTOS_LINUX_ASAN
extern "C" void __asan_unpoison_memory_region(void const volatile * addr, size_t size);
#define UNPOISON_STACK(addr, size) __asan_unpoison_memory_region((addr), (size))
#endif
#ifndef UNPOISON_STACK
#define UNPOISON_STACK(addr, size)
#endif
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace
{
    ucontext_t             Contexts[OS::MAX_PROCESS_COUNT];   // indexed by priority
    void                (* EntryPoints[OS::MAX_PROCESS_COUNT])(); // process functions, indexed by priority
    ucontext_t * volatile  CurrentContext = 0;                // context of the running process
    volatile sig_atomic_t  TimerLocked    = 0;
    bool                   Started        = false;           // os_start() has been called
    void (* volatile       IrqHandlers[OS::host::IRQ_COUNT])();
    bool                   IrqSetReady    = false;

    void init_irq_set()
    {
        if(IrqSetReady)
            return;
        sigemptyset(&OS::host::IrqSignals);
        sigaddset(&OS::host::IrqSignals, OS::host::SIG_SYSTEM_TIMER);
        sigaddset(&OS::host::IrqSignals, OS::host::context_sw_signal());
        for(int i = 0; i < OS::host::IRQ_COUNT; ++i)
            sigaddset(&OS::host::IrqSignals, OS::host::irq_signal(i));
        IrqSetReady = true;
    }

    //--------------------------------------------------------------------------
    //  First code of every process. A new context starts with the interrupts
    //  disabled and enables them itself, on its own stack: swapcontext() and
    //  setcontext() set the signal mask of the target context before they
    //  switch the registers, so a context that is entered with signals
    //  unblocked can take a pending signal half-way through the switch.
    //  Contexts saved later are always saved with the interrupts disabled
    //  (in a critical section or in an interrupt handler).
    void process_entry(int pr)
    {
        enable_interrupts();
        EntryPoints[pr]();
        abort();                                  // a process function never returns
    }

    void install(int sig, void (*handler)(int))
    {
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = handler;
        sa.sa_mask    = OS::host::IrqSignals;    // no nesting: all "interrupts" are masked in a handler
        sa.sa_flags   = SA_RESTART;
        if(sigaction(sig, &sa, 0) != 0)
        {
            perror("scmRTOS linux port: sigaction");
            abort();
        }
    }

    //--------------------------------------------------------------------------
    //  System timer interrupt
    void system_timer_handler(int)
    {
        if(TimerLocked)
            return;                               // timer "interrupt disabled": tick is lost
        OS::system_timer_isr();
    }

    //--------------------------------------------------------------------------
    //  User interrupts 0..IRQ_COUNT-1
    void irq_handler(int sig)
    {
        int n = sig - OS::host::irq_signal(0);
        if(n >= 0 && n < OS::host::IRQ_COUNT && IrqHandlers[n])
            IrqHandlers[n]();
    }

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    //--------------------------------------------------------------------------
    //  Context switch interrupt (the analogue of Cortex-M PendSV)
    void context_switch_handler(int)
    {
        OS::host::ContextSwitchPended = 0;
        ucontext_t * cur  = CurrentContext;
        ucontext_t * next = reinterpret_cast<ucontext_t*>(os_context_switch_hook(reinterpret_cast<stack_item_t*>(cur)));
        if(next != cur)
        {
            CurrentContext = next;
            swapcontext(cur, next);               // returns when this process is switched back in
        }
    }
#endif
}

sigset_t OS::host::IrqSignals;
volatile sig_atomic_t OS::host::ContextSwitchPended = 0;

#if scmRTOS_LINUX_PRIO_MASK_TABLE == 1
OS::TPrioMaskTable OS::PrioMaskTable;              // dynamic initialization, like AVR/MSP430/STM8
#endif

//------------------------------------------------------------------------------
//
//    Process context
//
//    glibc makecontext() builds the initial frame at uc_stack.ss_sp + ss_size and
//    does not use the lower bound, so the stack top is enough; in debug builds the
//    whole stack is known and is filled with the pattern and size-checked.
//
stack_item_t* OS::host::init_context(uint_fast8_t pr, stack_item_t* stack_begin, stack_item_t* stack_end, void (*exec)())
{
    init_irq_set();

    ucontext_t * ctx = &Contexts[pr];
    if(getcontext(ctx) != 0)
    {
        perror("scmRTOS linux port: getcontext");
        abort();
    }

    const size_t size = stack_begin ? (stack_end - stack_begin) * sizeof(stack_item_t) : scmRTOS_LINUX_MIN_STACK_SIZE;
    if(size < scmRTOS_LINUX_MIN_STACK_SIZE)
    {
        fprintf(stderr, "scmRTOS linux port: stack of process with priority %u is %zu bytes, "
                        "at least %u needed (signal handlers run on process stacks)\n",
                (unsigned)pr, size, (unsigned)scmRTOS_LINUX_MIN_STACK_SIZE);
        abort();
    }

    UNPOISON_STACK(reinterpret_cast<char*>(stack_end) - size, size);
    ctx->uc_stack.ss_sp   = reinterpret_cast<char*>(stack_end) - size;
    ctx->uc_stack.ss_size = size;
    ctx->uc_link          = 0;
    for(int s = 1; s < NSIG; ++s)                  // entered with the interrupts disabled,
        if(sigismember(&IrqSignals, s) == 1)       // see process_entry()
            sigaddset(&ctx->uc_sigmask, s);
    EntryPoints[pr] = exec;
    makecontext(ctx, reinterpret_cast<void (*)()>(process_entry), 1, static_cast<int>(pr));

    return reinterpret_cast<stack_item_t*>(ctx);
}

void OS::TBaseProcess::init_stack_frame( stack_item_t * Stack
                                       , void (*exec)()
                                    #if scmRTOS_DEBUG_ENABLE == 1
                                       , stack_item_t * StackBegin
                                    #endif
                                       )
{
    // A process that is restarted while the OS runs (process::terminate()) gets a
    // new context; an interrupt in the middle of that could switch to it.
    if(Started && !get_interrupt_state())
    {
        fprintf(stderr, "scmRTOS linux port: process with priority %u is re-initialized outside a critical section\n", (unsigned)Priority);
        abort();
    }
#if scmRTOS_DEBUG_ENABLE == 1
    UNPOISON_STACK(StackBegin, (Stack - StackBegin) * sizeof(stack_item_t));
    for(stack_item_t * p = StackBegin; p < Stack; ++p)
        *p = STACK_DEFAULT_PATTERN;
    StackPointer = host::init_context(Priority, StackBegin, Stack, exec);
#else
    StackPointer = host::init_context(Priority, 0, Stack, exec);
#endif
}

//------------------------------------------------------------------------------
//
//    User interrupts
//
void OS::host::set_irq_handler(int n, void (*handler)())
{
    if(n < 0 || n >= IRQ_COUNT)
        return;
    init_irq_set();
    IrqHandlers[n] = handler;
    install(irq_signal(n), irq_handler);
}

void OS::host::raise_irq(int n)
{
    if(n >= 0 && n < IRQ_COUNT)
        raise(irq_signal(n));
}

//------------------------------------------------------------------------------
//
//    System timer lock
//
void LOCK_SYSTEM_TIMER()   { TimerLocked = 1; }
void UNLOCK_SYSTEM_TIMER() { TimerLocked = 0; }

//------------------------------------------------------------------------------
//
//    Context switch, scheme 0
//
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
extern "C" void os_context_switcher(stack_item_t** Curr_SP, stack_item_t* Next_SP)
{
    ucontext_t * cur  = reinterpret_cast<ucontext_t*>(*Curr_SP);
    ucontext_t * next = reinterpret_cast<ucontext_t*>(Next_SP);
    CurrentContext = next;
    swapcontext(cur, next);                        // returns when this process is switched back in
}
#endif

//------------------------------------------------------------------------------
//
//    Idle: sleep until the next signal in real-time mode
//
#if scmRTOS_TARGET_IDLE_HOOK_ENABLE == 1
void OS::idle_process_target_hook()
{
#if scmRTOS_LINUX_TICK_MODE == 1
    sigset_t m;
    sigprocmask(SIG_BLOCK, 0, &m);
    for(int s = 1; s < NSIG; ++s)
        if(sigismember(&host::IrqSignals, s) == 1)
            sigdelset(&m, s);
    sigsuspend(&m);
#endif
}
#endif

//------------------------------------------------------------------------------
//
//    START MULTITASKING
//
extern "C" NORETURN void os_start(stack_item_t* sp)
{
    init_irq_set();
    sigprocmask(SIG_BLOCK, &OS::host::IrqSignals, 0);   // no interrupts until the first process runs

    install(OS::host::SIG_SYSTEM_TIMER, system_timer_handler);
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    install(OS::host::context_sw_signal(), context_switch_handler);
#endif

#if scmRTOS_LINUX_TICK_MODE == 1
    struct itimerval t;
    t.it_interval.tv_sec  = scmRTOS_LINUX_TICK_PERIOD_US / 1000000;
    t.it_interval.tv_usec = scmRTOS_LINUX_TICK_PERIOD_US % 1000000;
    t.it_value            = t.it_interval;
    if(setitimer(ITIMER_REAL, &t, 0) != 0)
    {
        perror("scmRTOS linux port: setitimer");
        abort();
    }
#endif

    Started = true;
    CurrentContext = reinterpret_cast<ucontext_t*>(sp);
    setcontext(CurrentContext);                    // the process enables the interrupts itself

    perror("scmRTOS linux port: setcontext");
    abort();
}
//------------------------------------------------------------------------------
