launch — create processes from a list of descriptions and run
=============================================================

([Русская версия](README_ru.md))

A scmRTOS extension: `OS::launch()` creates all processes from a list of
inline descriptions and starts the kernel. No process class declarations,
no `exec()` specializations — a process body is any callable object
(a function or a lambda, captures allowed).

The process priority is determined by its position in the list: the first
description gets the highest priority (`pr0`), the next ones go down.

The list must contain exactly `scmRTOS_PROCESS_COUNT` descriptions,
otherwise the compilation fails (static_assert).

Integration
-----------

The standard scmRTOS mechanism: add

```cpp
#include "launch.h"
```

to the project configuration file `scmRTOS_extensions.h` — this makes the
extension available in every translation unit that includes `scmRTOS.h`.
This does not remove the need to add the `ext/launch` directory to your
project's include paths. The extension is header-only, no .cpp file is
compiled.

API
---

```cpp
namespace OS {
    // Process description: stack size in bytes, start state, name, body.
    template<size_t Stk, TProcessStartState Pss = pssRunning, class F>
    proc_desc<...> proc(const char* name, F&& body);

    // Create the processes and run the kernel; never returns.
    template<class... Desc>
    NORETURN void launch(Desc... desc);

    // Access to the already created processes (once the OS is running):
    TBaseProcess& proc_by_prio(TPriority pr);
    TBaseProcess& proc_by_idx(size_t i);   // index in the launch() list
}
```

- **Body** — the main function of the process (the `body` argument of
  `OS::proc()`), the code that runs inside the process. It can be any
  object callable with no arguments: a plain function, a function pointer,
  or a lambda (captures allowed). Execution starts when the process starts,
  and the body **must never return** (an infinite loop is expected;
  a return leads to a hang in an endless loop). A lambda's closure is
  stored inside the process object, so a reference capture must outlive
  the process.
- **Name** is used only when `scmRTOS_DEBUG_ENABLE == 1`.
- **Start state**: `OS::proc<stk, OS::pssSuspended>("name", body)` creates
  a suspended process (requires `scmRTOS_SUSPENDED_PROCESS_ENABLE == 1`,
  otherwise a static_assert). Start it later via `proc_by_prio()` /
  `proc_by_idx()`.
- **Memory**: process objects are placed by placement new into one static
  buffer of a size computed at compile time (sum of the object sizes, each
  rounded up to the maximum alignment of the set) — the RAM usage is
  visible in the linker `size` report.

Example
-------

```cpp
int main() {
    InitHw();

    OS::launch(
        // pr0 — highest priority: blink the LED
        OS::proc<1200>("blink", [] {
            for (;;) {
                led.toggle();
                OS::sleep(100);
            }
        }),
        // pr1 (a regular function defined somewhere in the project)
        OS::proc<256>("sensor", sensorTask),
        // pr2
        OS::proc<128>("idle_loop", [] {
            for (;;)
                OS::sleep(1000);
        })
    );
}
```

A suspended process, started from another one:

```cpp
OS::launch(
    OS::proc<256>("master", [] {
        for (;;) {
            ...
            OS::proc_by_prio(OS::pr1).start();   // wake the worker up
            ...
        }
    }),
    OS::proc<256, OS::pssSuspended>("worker", [] {
        for (;;) { ... }
    })
);
```

Notes
-----

- `launch()` must be the **only** process creation facility in a build:
  do not mix it with global process objects or other process creators. With
  `scmRTOS_DEBUG_ENABLE == 1` a slot of `ProcessTable[]` occupied before
  `launch()` stops in an endless loop (inspect `pr` and `ProcessTable[]`
  in the debugger); in a release build there is no such check.
- Do not call `proc_by_prio()` / `proc_by_idx()` before the OS is running.
- `proc_by_idx()` indices shift silently when the launch list is edited —
  prefer `proc_by_prio()` for cross-references to a specific process.
- Not supported with `SEPARATE_RETURN_STACK != 0` (an `#error` at compile
  time).
