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
         * Process of priority pr with Stk-byte stack and body supplied
         * at run time (the body is passed to the kernel as the exec pointer).
         */
        template<TPriority pr, size_t Stk>
        class func_process : public TBaseProcess
        {
        public:
            INLINE func_process(const char*
                           #if scmRTOS_DEBUG_ENABLE == 1
                               name_str
                           #endif
                               , void (*body)())
                 : TBaseProcess(&Stack[round_up(Stk, sizeof(stack_item_t)) / sizeof(stack_item_t)]
                               , pr
                               , body
                           #if scmRTOS_DEBUG_ENABLE == 1
                               , Stack
                               , name_str
                           #endif
                               )
            {
            }

        private:
            // Stk bytes, rounded up to a whole number of stack_item_t
            stack_item_t Stack[round_up(Stk, sizeof(stack_item_t)) / sizeof(stack_item_t)];
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
            return max_alignof<alignof(func_process<launch_priority(Is), Desc::stack_size>)...>();
        }

        /**
         * Byte offset of the I-th process in the OS::launch() storage buffer.
         *
         * Every process size is rounded up to the maximum alignment of the set,
         * so each process is placed at an address properly aligned for its type
         * (sizeof() is a multiple of alignof() of the same type, but not necessarily
         * of the alignof() of the following one).
         */
        template<size_t I, class... Desc, size_t... Is>
        constexpr size_t launch_offset(std::index_sequence<Is...>)
        {
            constexpr size_t align = launch_align<Desc...>(std::index_sequence_for<Desc...>{});
            constexpr size_t sizes[] = { round_up(sizeof(func_process<launch_priority(Is), Desc::stack_size>), align)... };
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
         * Construct one OS::launch() process at the given address.
         */
        template<size_t I, class D>
        void launch_create_one(uint8_t* addr, const D& d)
        {
            new (addr) func_process<launch_priority(I), D::stack_size>(d.name, d.body);
        }

        /**
         * Construct all OS::launch() processes in the storage buffer (left to right).
         */
        template<class... Desc, size_t... Is>
        void launch_create_all(uint8_t* storage, std::index_sequence<Is...>, const Desc&... desc)
        {
            (launch_create_one<Is, Desc>(storage + launch_offset<Is, Desc...>(std::index_sequence_for<Desc...>{}), desc), ...);
        }

    #if scmRTOS_DEBUG_ENABLE == 1
        /**
         * Check that no process was created outside OS::launch(): every user
         * priority slot must be empty before the launch creates its processes
         * (a non-empty slot means a global/static/heap process object).
         *
         * Stops in an endless loop at the offending priority - inspectable
         * with a debugger (the 'pr' local variable, ProcessTable[]).
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
     * Process description for OS::launch(): stack size in bytes (compile time),
     * name (used when scmRTOS_DEBUG_ENABLE == 1) and body.
     *
     * Use OS::proc<StackBytes>(name, body) to make one.
     */
    template<size_t Stk>
    struct proc_desc
    {
        static constexpr size_t stack_size = Stk;

        const char* name;
        void (*body)();     // plain function or captureless lambda; must never return
    };

    /**
     * Make a process description for OS::launch().
     */
    template<size_t Stk>
    INLINE constexpr proc_desc<Stk> proc(const char* name, void (*body)())
    {
        return proc_desc<Stk>{ name, body };
    }

    /**
     * launch: Create processes from the descriptions and run the kernel.
     *
     * Processes are defined by descriptions rather than by types: each
     * OS::proc<StackBytes>(name, body) becomes a process with the body called
     * as the process entry point, so no process type declarations and no
     * exec() specializations are needed.
     *
     * Priorities are assigned automatically - the first description gets the
     * highest priority, the following ones get priorities in descending order;
     * the descriptions count must be exactly scmRTOS_PROCESS_COUNT, so the
     * process set is complete and duplicate/omission-free by construction
     * (checked at compile time).
     *
     * The process bodies must never return (infinite loops) and must be
     * captureless lambdas or plain functions.
     *
     * The required RAM is computed at compile time (sum of the process object
     * sizes, each rounded up to the maximum alignment of the set) and allocated
     * as a static buffer (visible in the linker size report).
     *
     * Warning: launch must be the only process creation facility - do not mix
     * it with global process objects. When scmRTOS_DEBUG_ENABLE == 1 launch
     * checks at run time that all priority slots are empty before creating its
     * processes, so such a mix stops in a debugger instead of silently making
     * the outside process orphaned.
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

        detail::launch_create_all(storage, std::index_sequence_for<Desc...>{}, desc...);
        run();
    }

}   // namespace OS
