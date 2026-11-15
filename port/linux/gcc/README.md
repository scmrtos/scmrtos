scmRTOS Linux port (test port)
==============================

([Русская версия](README_ru.md))

The port runs the scmRTOS kernel as an ordinary Linux program. It is meant for
debugging and testing the kernel, services, extensions and application logic
without target hardware: under a debugger, with sanitizers, in CI.

How it works
------------

The whole RTOS runs in one Linux thread.

| scmRTOS notion | In this port |
| --- | --- |
| Process context | `ucontext_t`, switched with `swapcontext()` |
| Process "stack pointer" | address of its `ucontext_t` |
| Interrupt | POSIX signal |
| System timer | `SIGALRM` (from `setitimer()` or `OS::sim_tick()`) |
| Context switch software interrupt (scheme 1, like PendSV) | `SIGRTMIN+8` |
| User interrupts 0..7 | `SIGRTMIN+0` … `SIGRTMIN+7` |
| Critical section | `sigprocmask()` blocks all port signals |

Interrupt handlers do not nest: all port signals are blocked inside a handler.
When several interrupts are pending, the system timer is taken first, then the
user interrupts in ascending order, and the context switch last. That makes it
behave like PendSV with the lowest priority on Cortex-M: an interrupt that was
pending when the switch was requested runs first and may change the process to
switch to. This order holds exactly because every handler blocks all the port
signals: with an empty `sa_mask` Linux stacks the handler frames and runs them
in the reverse order, from the highest signal number down. Note the difference
from Cortex-M: there the timer interrupt normally runs below the user
interrupts (their NVIC priority is chosen by the application), here it runs
above all of them.

A new process starts with the interrupts disabled and enables them itself:
`swapcontext()` sets the signal mask before it switches the registers, so a
context must not be entered with the mask open.

Configuration
-------------

Set in the project's `scmRTOS_TARGET_CFG.h` or with `-D`.

| Macro | Values | Default |
| --- | --- | --- |
| `scmRTOS_CONTEXT_SWITCH_SCHEME` | 0 - direct switch in the scheduler; 1 - via the software interrupt, the code path of the Cortex-M and Zynq-7000 ports | 0 |
| `scmRTOS_PRIORITY_ORDER` | 0 - ascending, 1 - descending | 0 |
| `scmRTOS_LINUX_TICK_MODE` | 0 - manual ticks with `OS::sim_tick()`, deterministic; 1 - real time, `SIGALRM` | 0 |
| `scmRTOS_LINUX_TICK_PERIOD_US` | system timer period in real-time mode, us | 1000 |
| `scmRTOS_LINUX_PRIO_MASK_TABLE` | 1 - `get_prio_tag()` reads a dynamically initialized table, like the AVR/MSP430/STM8 ports | 0 |
| `scmRTOS_LINUX_MIN_STACK_SIZE` | minimal process stack, bytes; checked when `scmRTOS_DEBUG_ENABLE == 1` | 16384 |

Port API
--------

```cpp
OS::sim_tick();                              // one system timer tick, here and now
OS::host::set_irq_handler(n, handler);       // set handler of user interrupt n (0..7)
OS::host::raise_irq(n);                      // request interrupt n
OS::host::irq_signal(n);                     // signal number of interrupt n, e.g. for timer_create()
get_interrupt_state();                       // 1 - interrupts disabled (critical section, handler)
```

If the macro `scmRTOS_LINUX_CRITSECT_EXIT_HOOK` names a function
`extern "C" void f()`, the port calls it every time an outermost critical
section ends, i.e. at every point where a real MCU would take a pending
interrupt. Regression tests use it to inject interrupts at all such points.

An interrupt requested inside a critical section is taken when the section
ends, as on a real MCU. Handlers are written as in other ports:

```cpp
static void uart_rx_irq()
{
    OS::TISRW isr;               // must come first
    RxFlag.signal_isr();
}
```

Limitations
-----------

- **glibc only.** `makecontext()` must build the frame from the stack top, as
  glibc does. The port is tested on x86-64.
- **Stack overflow is not detected.** With `scmRTOS_DEBUG_ENABLE == 1` the port
  checks the stack size at start-up and `stack_slack()` shows the margin; without
  it the port does not know the stack bottom.
- **Process stacks of 16 KiB or more.** Signal handlers run on the stack of the
  interrupted process; there is no separate interrupt stack.
- **libc is not reentrant.** In real-time mode a process can be preempted inside
  `printf()` or `malloc()`. Call them under a mutex (`OS::TMutexLocker`) or in a
  critical section.
- **Ticks can be lost.** Standard signals do not queue: when Linux deschedules
  the program for longer than a timer period, several `SIGALRM`s merge into one.
  OS time stays consistent but falls behind wall-clock time.
- **`SIGALRM` is taken.** Do not use `alarm()`, libc `sleep()`,
  `setitimer(ITIMER_REAL)` or `SIGRTMIN..SIGRTMIN+8` in the application.
- **One thread.** Do not call OS functions from other Linux threads.
- **Sanitizers.** UndefinedBehaviorSanitizer works as is. AddressSanitizer works
  with `ASAN_OPTIONS=detect_stack_use_after_return=0`: the port unpoisons a
  process stack when the process is (re)started, but has no stack-switch
  annotations (`__sanitizer_start_switch_fiber`).
