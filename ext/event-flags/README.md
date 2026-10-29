TEventFlags — 32-bit event flags
================================

([Русская версия](README_ru.md))

A scmRTOS extension: a group of 32 flag bits with blocking wait for a
combination of events. The kernel has no equivalent: `OS::TEventFlag` is a
single bit that does not latch its value when nobody is waiting and cannot
be used to wait for a combination of events.

Flag values are latched: `set()` sets the bits and they stay set until
cleared explicitly or consumed by a wait without `efNoClear`. A process
woken up by `set()` may find its condition (`efWaitAll`) still unfulfilled
and go back to waiting for the missing bits.

Integration
-----------

The standard scmRTOS mechanism: add

```cpp
#include "event_flags.h"
```

to the project configuration file `scmRTOS_extensions.h` — this makes the
extension available in every translation unit that includes `scmRTOS.h`.
This does not remove the need to add the `ext/event-flags` directory to
your project's include paths.

API
---

```cpp
enum TEventFlagsOptions : uint32_t {
    efWaitAny  = 0,   // wake when ANY of the requested bits is set
    efWaitAll  = 1,   // wake when ALL the requested bits are set
    efNoClear  = 2    // do not clear the requested bits on success
};

class TEventFlags {
    bool     wait     (uint32_t Bits, uint32_t Options, timeout_t timeout, uint32_t* Result = 0);
    bool     try_wait (uint32_t Bits, uint32_t Options, uint32_t* Result = 0);
    uint32_t set      (uint32_t Bits);   // returns the value after setting
    uint32_t set_isr  (uint32_t Bits);   // ISR version
    uint32_t clear    (uint32_t Bits);   // returns the value before clearing
    uint32_t get      () const;          // current value, no clearing
    bool     has_waiters () const;       // whether any process is waiting in wait()
};
```

- `wait()` blocks the process until the condition is met; returns `false`
  on `timeout` expiration. `timeout == 0` means "wait forever" (scmRTOS
  convention). The timeout is absolute: intermediate wake-ups inside
  `wait()` do not restart it.
- `wait()`/`try_wait()` store the whole flag value **before** the requested
  bits are cleared into `Result`.
- `Bits == 0` is a parameter error: `wait()`/`try_wait()` return `false`.
- Blocking `wait()` may only be called from processes; from an ISR only
  `set_isr()` is available, inside an `OS::TISRW` wrapper.

Examples
--------

### Wait for multiple events set from an ISR

```cpp
OS::TEventFlags flags;

const uint32_t EF_RX  = 1 << 0;
const uint32_t EF_TX  = 1 << 1;
const uint32_t EF_ERR = 1 << 2;

// In the UART ISR (the TISRW wrapper is required):
OS::TISRW isr;
flags.set_isr(EF_RX);

// In a process: wait for both reception and transmission
void proc() {
    for (;;) {
        uint32_t state;
        if (flags.wait(EF_RX | EF_TX, OS::efWaitAll, 1000, &state)) {
            // state is a snapshot of the flags at the moment of success
            ...
        } // otherwise — 1 s timeout
    }
}
```

### Non-blocking poll

```cpp
if (flags.try_wait(EF_ERR, OS::efWaitAny)) {
    // EF_ERR was set; it has been cleared
}
```

### Peek only, no clearing

```cpp
uint32_t now = flags.get();
if (flags.try_wait(EF_RX | EF_TX, OS::efWaitAll | OS::efNoClear)) {
    // both bits are set and remain set for other waiters
}
```

### Multiple waiters

`set()` wakes ALL waiters (`resume_all`), not just one; each woken process
re-checks its own condition — its own `Bits` and `Options`. Then:

- **Waiting for different (non-overlapping) bits** — each process gets its
  own event: only the requested bits are cleared, other bits are not
  consumed. Waiters do not interfere with each other.
- **Waiting for the same bit without `efNoClear`** — the event goes to one
  process only: after `set()` the highest-priority woken process runs
  first and consumes (clears) its bits. The others wake up, find their
  condition no longer satisfied, and go back to sleep with the remaining
  timeout (the absolute deadline is not restarted) — until the next
  `set()` or the timeout.
- **The same with `efNoClear`** — all waiters succeed in observing the bits
  (nobody clears them); clearing is done explicitly with `clear()`.

A wake-up without success is a normal iteration of the loop inside
`wait()`, not an error: `wait()` returns `true` only when the condition is
actually satisfied for the `Bits` requested by that particular call.

Notes
-----

- A `TEventFlags` object takes `sizeof(TProcessMap) + sizeof(uint32_t)`
  (TProcessMap is 8/16/32 bits depending on `scmRTOS_PROCESS_COUNT`).
- `has_waiters()` is useful for the object owner before destroying it.
- Waiting with `efWaitAll` does not consume bits outside `Bits`: only the
  requested bits are cleared (and not at all with `efNoClear`).
