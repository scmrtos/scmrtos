safe_run — run() with compile-time process set check
====================================================

([Русская версия](README_ru.md))

A scmRTOS extension: `OS::safe_run()` — a drop-in replacement for `OS::run()`
that additionally verifies **at compile time** that the process list is
complete and consistent.

The scmRTOS invariant: every priority `pr0..pr(PROCESS_COUNT-1)` must be
occupied by exactly one process. A missing or duplicated priority is not
detected by the plain `OS::run()`: the kernel hits a `nullptr` in
`ProcessTable[]` at runtime, typically deep inside `system_timer()`.
`safe_run()` turns this into a compiler error instead.

Integration
-----------

The standard scmRTOS mechanism: add

```cpp
#include "safe_run.h"
```

to the project configuration file `scmRTOS_extensions.h` — this makes the
extension available in every translation unit that includes `scmRTOS.h`.
This does not remove the need to add the `ext/safe-run` directory to your
project's include paths. The extension is header-only, no .cpp file is
compiled.

API
---

```cpp
namespace OS {
    // Start the kernel; the check happens at compile time.
    template<class... Procs>
    NORETURN void safe_run(Procs&... procs);

    // The checker itself, usable in your own static_assert:
    template<class... Procs>
    class ProcListCheck {
        static constexpr bool check();
    };
}
```

`safe_run(proc_a, proc_b, ...)` takes references to all process objects and
checks that their priorities form exactly the set `pr0..pr(PROCESS_COUNT-1)`:

- **missing priority** — a process of some priority is not in the list;
- **duplicate priority** — two processes of the same priority are passed;
- **out of range** — `prIDLE` or a priority beyond `PROCESS_COUNT-1`.

Any violation fails a `static_assert` with the message
"each priority pr0..pr(PROCESS_COUNT-1) must be occupied by exactly one
process". The order of arguments does not matter — the check is by the set
of priorities, not by position.

If the check passes, `safe_run()` simply calls `OS::run()`.

Example
-------

```cpp
// Process types — plain OS::process, not derived classes:
typedef OS::process<OS::pr0, 512> TProcBlink;
typedef OS::process<OS::pr1, 256> TProcSensor;

TProcBlink  proc_blink;     // registration happens at construction
TProcSensor proc_sensor;

// Process bodies — explicit specialization of exec():
template<> void TProcBlink::exec()  { for (;;) { ... } }
template<> void TProcSensor::exec() { for (;;) { ... } }

int main() {
    ...
    OS::safe_run(proc_blink, proc_sensor);   // pr0 + pr1 — ok
}
```

Now remove `proc_sensor` from the config (`scmRTOS_PROCESS_COUNT` stays 2)
or pass it twice — the build stops with the `static_assert` message instead
of crashing at runtime.

Notes
-----

- Process types **derived** from `OS::process` are not recognized — the
  extension matches the exact `OS::process<pr, stk...>` template, a derived
  class is a compile error. Use a `typedef`/alias of `OS::process` instead
  of inheritance.
- `safe_run()` does not create processes — they register themselves in the
  kernel as usual (in the constructor of the object). The extension only
  checks the list and starts the kernel.
- The check only covers the arguments you pass. A process that is created
  but not passed to `safe_run()` does not participate in the check — pass
  ALL process objects, otherwise the check loses its meaning.
- Do not mix with `OS::launch()`: in a given build processes are created by
  something one — either `launch` (which has its own static_assert) or
  process objects with `safe_run`.
