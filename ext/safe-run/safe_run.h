//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  Safe run extension (run with compile-time process set check).
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
//*     Safe run extension by by Anton B. Gusev, Copyright (c) 2026

#pragma once

#include <scmRTOS.h>

namespace OS
{
    namespace detail
    {
        /**
         * Extract process priority from process type at compile time.
         *
         * Warning: Process types derived from OS::process are not matched,
         * do not use this extension in a such case.
         */
        template<class P> struct extract_process_priority;

    #if SEPARATE_RETURN_STACK == 0
        template<TPriority pr, size_t stk_size, TProcessStartState pss>
        struct extract_process_priority<OS::process<pr, stk_size, pss>>
        {
            static constexpr TPriority value = pr;
        };
    #else   // SEPARATE_RETURN_STACK
        template<TPriority pr, size_t stk_size, size_t rstk_size, TProcessStartState pss>
        struct extract_process_priority<OS::process<pr, stk_size, rstk_size, pss>>
        {
            static constexpr TPriority value = pr;
        };
    #endif  // SEPARATE_RETURN_STACK

    }   // namespace detail

    /**
     * Compile-time checker of process set completeness.
     *
     * Every priority pr0..pr(PROCESS_COUNT-1) must be occupied by exactly one process.
     */
    template<class... Procs>
    class ProcListCheck
    {
    public:
        static constexpr bool check()
        {
            // make array of process priorities (the trailing element keeps the array non-empty when Procs... is empty).
            constexpr int prs[] = { static_cast<int>(detail::extract_process_priority<Procs>::value)..., -1 };

            TProcessMap listed = 0;
            for (int i = 0; i < static_cast<int>(sizeof...(Procs)); ++i)
            {
                if (!valid_prio(prs[i]))   // prIDLE / out of range?
                    return false;
                if (listed & get_tag(prs[i])) // duplicated priority?
                    return false;
                listed |= get_tag(prs[i]);
            }

            TProcessMap expected = 0;         //  all priorities but prIDLE
            for (int pr = 0; pr < static_cast<int>(PROCESS_COUNT); ++pr)
                if (pr != static_cast<int>(prIDLE))
                    expected |= get_tag(pr);

            return listed == expected;
        }

    private:
        static constexpr TProcessMap get_tag(const int pr)
        {
            return static_cast<TProcessMap>(1u << pr);
        }

        static constexpr bool valid_prio(const int pr)
        {
            return pr >= 0
                && pr < static_cast<int>(PROCESS_COUNT)
                && pr != static_cast<int>(prIDLE);
        }

    };

    /**
     * safe_run: Start kernel with compile-time check of process list passed.
     *
     * Checks that the process list contains exactly one process of each priority pr0..pr(PROCESS_COUNT-1).
     */
    template<class... Procs>
    INLINE NORETURN void safe_run(Procs&...)
    {
        static_assert(ProcListCheck<Procs...>::check(),
            "scmRTOS: each priority pr0..pr(PROCESS_COUNT-1) must be occupied by exactly one process");
        run();
    }

}   // namespace OS
