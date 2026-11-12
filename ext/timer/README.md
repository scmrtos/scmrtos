TSoftwareTimer — callback software timers
=========================================

([Русская версия](README_ru.md))

A scmRTOS extension: timer objects that invoke a callback function after a
given number of ticks, once or periodically. A single dispatcher function,
`service()`, services all timers; it is called once per tick regardless of
the number of running timers; the natural tick source is the system timer
hook (`scmRTOS_SYSTIMER_HOOK`).

The callback runs in the context of whoever calls `service()` (with the
standard integration: the system timer interrupt), so it must be short and
non-blocking: only ISR-safe operations inside (see the ISR section of the
main scmRTOS documentation).

Integration
-----------

The extension needs exactly one thing: `service()` must be called once per
tick, from one and only one context. The standard integration is the system
timer hook, two steps:

1. add the `ext/timer` directory to your project's include paths and the
   `timer.cpp` file to the list of compiled sources (the header can be
   included directly where needed, or via `scmRTOS_extensions.h`);

2. set `scmRTOS_SYSTIMER_HOOK_ENABLE = 1` in `scmRTOS_CONFIG.h` and call the
   dispatcher from the user hook:

```cpp
void system_timer_user_hook()
{
    OS::TSoftwareTimer::service();
}
```

Until `service()` is called every tick, timers do not tick. If other
extension code needs the same hook, call every dispatcher from the single
hook function.

Other acceptable tick sources are a hardware timer ISR or a dedicated
servicing process. Both must obey one rule: `service()` is not reentrant —
a second call nesting into the first (while some callback is running) would
double the decrements and interleave the dispatches. A process also occupies
a priority slot, and its `sleep(1)` adds jitter to the ticks — the hook has
neither drawback.

API
---

```cpp
class TSoftwareTimer {
    typedef void (*callback_t)(void* arg);

    TSoftwareTimer(callback_t cb, void* arg, bool periodic);
    ~TSoftwareTimer();                       // unregisters the timer

    bool start(timeout_t ticks);   // start/restart; false if ticks == 0
    bool stop();                   // false if the timer was not running
    bool is_running() const;

    static void service();   // once per tick, from a single context
};
```

- `start()` arms the timer: the callback fires `ticks` ticks later. Calling
  `start()` on a running timer restarts it. `ticks == 0` is not a valid
  period; the function returns `false`.
- On a one-shot timer (`periodic == false`) the callback fires once; a
  periodic timer reloads automatically. The reload is taken from the expiry
  point, so the period does not drift over time.
- All members are non-blocking and callable from processes and ISRs alike
  (the registry is mutated under `TCritSect` only).
- The callback may call any timer member, including restarting or deleting
  the timer it belongs to — the registration state is updated before the
  callback is invoked.

Examples
--------

### Periodic task without a dedicated process

```cpp
void flush_led(void* arg)        // runs in the system timer ISR
{
    gpio_toggle();               // must be short and non-blocking
}

OS::TSoftwareTimer blinker(flush_led, 0, true);
...
blinker.start(500);              // toggle every 500 ms
```

### Waking a process from a timer

```cpp
void on_timeout(void* arg)
{
    static_cast<OS::TEventFlag*>(arg)->signal_isr();
}

OS::TEventFlag watchdog_kick;
OS::TSoftwareTimer wdt(on_timeout, &watchdog_kick, true);

void supervisor() {
    wdt.start(1000);
    for (;;) {
        watchdog_kick.wait(1500);    // the timer wakes us every 1 s
        ...
    }
}
```

Notes
-----

- A `TSoftwareTimer` object takes about 4 pointers, plus whatever the
  callback does.
- A timer absent from the registry (never started, already expired, or
  stopped) costs nothing in `service()`: only running timers are linked.
- Deleting a timer from an ISR that preempts the system tick exactly while
  that timer's own callback is running may still let the callback complete
  one last time (its copy of `(cb, arg)` was taken before the deletion).
  Memory stays safe; only the last call is possible.
- Time base is the tick of whoever calls `service()`; the maximum period is
  the range of `timeout_t`, the timeout type defined in the project
  configuration.
