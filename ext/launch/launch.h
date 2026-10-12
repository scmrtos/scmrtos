//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  Launch extension (create processes from descriptions and run).
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
//*     Launch extension by Anton B. Gusev, Copyright (c) 2026

#pragma once

#include <new>
#include <type_traits>
#include <utility>

#include <scmRTOS.h>

namespace OS
{
#if SEPARATE_RETURN_STACK != 0
#error "scmRTOS launch extension: OS::launch() is not implemented for SEPARATE_RETURN_STACK"
#endif

    namespace detail
    {
        /**
         * Maximum alignment of the process types.
         */
        template<size_t... A>
        constexpr size_t max_alignof()
        {
            size_t m = 0;
            ((m = (A > m ? A : m)), ...);
            return m;
        }

        /**
         * Round n up to a multiple of align (align must be a power of two).
         */
        constexpr size_t round_up(size_t n, size_t align)
        {
            return (n + align - 1) / align * align;
        }

        /**
         * Process of priority pr, Stk-byte stack, start state Pss and a
         * callable body stored in the object (captures allowed).
         *
         * The static exec() finds its object through ProcessTable[pr]: pr is
         * a compile-time constant, and launch() guarantees the object type.
         */
        template<TPriority pr, size_t Stk, TProcessStartState Pss, class F>
        class func_process : public TBaseProcess
        {
            // Stk bytes as a whole number of stack_item_t
            static constexpr size_t stk_items = round_up(Stk, sizeof(stack_item_t)) / sizeof(stack_item_t);

        public:
            INLINE func_process(const char*
                           #if scmRTOS_DEBUG_ENABLE == 1
                               name_str
                           #endif
                               , F&& body_)
                 : TBaseProcess(&Stack[stk_items]
                               , pr
                               , &exec
                           #if scmRTOS_DEBUG_ENABLE == 1
                               , Stack
                               , name_str
                           #endif
                               )
                 , body(std::forward<F>(body_))
            {
                #if scmRTOS_SUSPENDED_PROCESS_ENABLE != 0
                    if ( Pss == pssSuspended )
                        clr_prio_tag(SuspendedProcessMap, get_prio_tag(pr));
                #endif
            }

        private:
            OS_PROCESS static void exec()
            {
                static_cast<func_process*>(const_cast<TBaseProcess*>(get_proc(pr)))->body();
                for (;;);   // the body must never return
            }

            F            body;
            stack_item_t Stack[stk_items];
        };

        /**
         * Priority of the I-th OS::launch() description: the first one is the highest.
         */
        constexpr TPriority launch_priority(const size_t i)
        {
            return scmRTOS_PRIORITY_ORDER
                 ? static_cast<TPriority>(PROCESS_COUNT - 1 - i)
                 : static_cast<TPriority>(i);
        }

        /**
         * Maximum alignment of the OS::launch() process types.
         */
        template<class... Desc, size_t... Is>
        constexpr size_t launch_align(std::index_sequence<Is...>)
        {
            return max_alignof<alignof(func_process<launch_priority(Is), Desc::stack_size, Desc::start_state, typename Desc::body_type>)...>();
        }

        /**
         * Byte offset of the I-th process in the storage buffer; each size is
         * rounded up to the maximum alignment of the set, so every process is
         * properly aligned for its own type.
         */
        template<size_t I, class... Desc, size_t... Is>
        constexpr size_t launch_offset(std::index_sequence<Is...>)
        {
            constexpr size_t align = launch_align<Desc...>(std::index_sequence_for<Desc...>{});
            constexpr size_t sizes[] = { round_up(sizeof(func_process<launch_priority(Is), Desc::stack_size, Desc::start_state, typename Desc::body_type>), align)... };
            size_t off = 0;
            for (size_t i = 0; i < I; ++i)
                off += sizes[i];
            return off;
        }

        /**
         * Total size of the OS::launch() process storage buffer.
         */
        template<class... Desc>
        constexpr size_t launch_storage_size()
        {
            return launch_offset<sizeof...(Desc), Desc...>(std::index_sequence_for<Desc...>{});
        }

        /**
         * Construct the I-th process at addr, moving the body out of the description.
         */
        template<size_t I, class D>
        void launch_create_one(uint8_t* addr, D&& d)
        {
            new (addr) func_process<launch_priority(I), D::stack_size, D::start_state, typename D::body_type>(
                d.name, std::forward<D>(d).body);
        }

        /**
         * Construct all OS::launch() processes in the storage buffer (left to right).
         */
        template<class... Desc, size_t... Is>
        void launch_create_all(uint8_t* storage, std::index_sequence<Is...>, Desc&&... desc)
        {
            (launch_create_one<Is, Desc>(storage + launch_offset<Is, Desc...>(std::index_sequence_for<Desc...>{}), std::forward<Desc>(desc)), ...);
        }

    #if scmRTOS_DEBUG_ENABLE == 1
        /**
         * Debug: all user priority slots must be empty before launch - a
         * non-empty one means a process created outside launch(); stops in an
         * endless loop at the offending priority (inspect 'pr', ProcessTable[]).
         */
        inline void launch_precheck()
        {
            for (int pr = 0; pr < static_cast<int>(PROCESS_COUNT); ++pr)
            {
                if (pr == static_cast<int>(prIDLE))
                    continue;
                if (get_proc(static_cast<uint_fast8_t>(pr)))
                    for (;;);   // process created in a bypass of launch()
            }
        }
    #endif

    }   // namespace detail

    /**
     * Process description for OS::launch() - made by OS::proc(), see below.
     */
    template<size_t Stk, TProcessStartState Pss, class F>
    struct proc_desc
    {
        static constexpr size_t stack_size = Stk;
        static constexpr TProcessStartState start_state = Pss;
        using body_type = F;

        const char* name;
        F body;     // function or lambda (captures allowed); must never return
    };

    /**
     * Process description: stack size in bytes, start state (pssSuspended
     * requires scmRTOS_SUSPENDED_PROCESS_ENABLE == 1), name (used when
     * scmRTOS_DEBUG_ENABLE == 1) and body.
     *
     * The body closure is stored inside the process object, so a reference
     * capture must outlive the process.
     */
    template<size_t Stk, TProcessStartState Pss = pssRunning, class F>
    INLINE proc_desc<Stk, Pss, typename std::decay<F>::type> proc(const char* name, F&& body)
    {
        static_assert(Pss == pssRunning || scmRTOS_SUSPENDED_PROCESS_ENABLE != 0,
            "scmRTOS: OS::proc<..., pssSuspended> requires scmRTOS_SUSPENDED_PROCESS_ENABLE == 1 in scmRTOS_CONFIG.h");
        static_assert(std::is_invocable<typename std::decay<F>::type>::value,
            "scmRTOS: OS::proc() body must be callable with no arguments");
        return proc_desc<Stk, Pss, typename std::decay<F>::type>{ name, std::forward<F>(body) };
    }

    /**
     * Create processes from the descriptions and run the kernel.
     *
     * - Priorities are assigned by position: the first description gets the
     *   highest one; their count must be exactly scmRTOS_PROCESS_COUNT
     *   (static_assert), so the set is complete and duplicate-free.
     * - Body: any callable invocable with no arguments (function, lambda,
     *   captures allowed); it runs as the process entry, must never return.
     * - OS::proc<Stk, pssSuspended>(...) starts suspended; start it later via
     *   OS::proc_by_prio() / OS::proc_by_idx().
     * - Process RAM is computed at compile time and allocated as a static
     *   buffer (visible in the linker size report).
     *
     * Warning: launch must be the only process creation facility - do not mix
     * it with global process objects (with scmRTOS_DEBUG_ENABLE == 1 such a
     * mix stops in a debugger instead of silently orphaning the process).
     */
    template<class... Desc>
    INLINE NORETURN void launch(Desc... desc)
    {
        static_assert(sizeof...(Desc) == PROCESS_COUNT - 1,
            "scmRTOS: OS::launch() requires exactly one process description per priority pr0..pr(PROCESS_COUNT-1)");

    #if scmRTOS_DEBUG_ENABLE == 1
        detail::launch_precheck();
    #endif

        constexpr size_t RAM = detail::launch_storage_size<Desc...>();

        alignas(detail::launch_align<Desc...>(std::index_sequence_for<Desc...>{}))
            static uint8_t storage[RAM ? RAM : 1];

        detail::launch_create_all(storage, std::index_sequence_for<Desc...>{}, std::move(desc)...);
        run();
    }

    /**
     * Handle of the process by priority: start() a pssSuspended one, wake_up(),
     * is_sleeping()/is_suspended(), name()/stack_slack() (debug builds).
     *
     * Call after the OS is launched (from a process or an ISR); in a debug
     * build an unregistered priority stops in an endless loop instead of a
     * null dereference.
     */
    INLINE TBaseProcess& proc_by_prio(const TPriority pr)
    {
        const TBaseProcess* p = get_proc(static_cast<uint_fast8_t>(pr));
    #if scmRTOS_DEBUG_ENABLE == 1
        if (!p)
            for (;;);   // no process registered at this priority
    #endif
        return const_cast<TBaseProcess&>(*p);
    }

    /**
     * Handle of the I-th process of the launch() list (index 0 = highest
     * priority). Warning: indices shift silently when the list is edited -
     * prefer proc_by_prio() to refer to a specific process.
     */
    INLINE TBaseProcess& proc_by_idx(const size_t i)
    {
        return proc_by_prio(detail::launch_priority(i));
    }

}   // namespace OS
