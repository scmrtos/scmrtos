TSemaphore — counting semaphore
===============================

([Русская версия](README_ru.md))

A scmRTOS extension: a classical counting semaphore.
It has no owner: any process may release it (`release()`), not only the one
that acquired it; it can also be released from an ISR — `release_isr()`;
any process may read the current token count.

Waiting is not FIFO: `release()` does not wake the first in line but the
*highest priority* waiter (`resume_next_ready()`) — the usual practice in
scmRTOS.

Integration
-----------

The standard scmRTOS mechanism: add

```cpp
#include "semaphore.h"
```

to the project configuration file `scmRTOS_extensions.h` — this makes the
extension available in every translation unit that includes `scmRTOS.h`.
This does not remove the need to add the `ext/semaphore` directory to your
project's include paths, and the `semaphore.cpp` file to the list of
compiled sources.

API
---

```cpp
class TSemaphore {
    TSemaphore(size_t max_count, size_t initial_count);

    bool   acquire     (timeout_t timeout = 0);  // false on timeout
    bool   try_acquire ();                       // never suspends the process
    bool   release     ();   // false if the count is already at MaxCount
    bool   release_isr ();   // ISR version
    size_t get_count     () const;               // current token count
    size_t get_max_count () const;
    bool   has_waiters   () const;               // whether any process is waiting in acquire()
};
```

- `acquire()` takes one free token if there is one, otherwise blocks the
  process until a token becomes free (someone calls `release()`) or
  `timeout` expires; returns `false` on timeout. `timeout == 0` means
  "wait forever" (scmRTOS convention).
- `release()` returns one token to the pool and wakes the highest priority
  waiter. Returns `false` if the token count is already at its maximum
  (`max_count`).
- Blocking `acquire()` — from processes only; from an ISR — `release_isr()`
  inside an `OS::TISRW` wrapper.

Examples
--------

### Limit concurrent access to a resource pool

```cpp
OS::TSemaphore buffers(4, 4);    // 4 buffers, all initially free

void worker() {
    for (;;) {
        if (buffers.acquire()) {         // wait for a free buffer
            ...                          // use it
            buffers.release();           // return it
        }
    }
}
```

Several `worker()` processes at different priorities can run concurrently;
no more than four of them are inside the pool at any moment, and when a
buffer is returned the highest priority waiter gets the token.

### Non-blocking attempt

```cpp
if (buffers.try_acquire()) {
    // token acquired; otherwise the pool is empty — do something else
    ...
    buffers.release();
}
```

### Wait for a signal from an ISR (a sort of TEventFlag analog)

```cpp
OS::TSemaphore rx_ready(1, 0);   // binary semaphore, initially empty

// In the UART ISR (the TISRW wrapper is required):
OS::TISRW isr;
rx_ready.release_isr();

// In a process:
void proc() {
    for (;;) {
        if (rx_ready.acquire(1000)) {
            // a byte has arrived
            ...
        } // otherwise — 1 s timeout
    }
}
```

Notes
-----

- A `TSemaphore` object takes `sizeof(TProcessMap) + 2 * sizeof(size_t)`
  (TProcessMap is 8/16/32 bits depending on `scmRTOS_PROCESS_COUNT`).
- `has_waiters()` is useful for the object owner before destroying it.
- There is no priority inheritance (there is no owner to inherit from).
  If you need a lock with an owner, use `OS::TMutex`.
