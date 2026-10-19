//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  Counting semaphore extension.
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
//*     Semaphore extension by Anton B. Gusev, Copyright (c) 2026

#pragma once

#include <scmRTOS.h>

namespace OS
{
    //--------------------------------------------------------------------------
    //
    //   TSemaphore
    //
    //   Counting semaphore.
    //
    //   Unlike TMutex, a semaphore has no owner and no priority inheritance,
    //   and any process may release it. release() returns false when the count
    //   is already at the maximum, so releasing "too many" times is visible to
    //   the caller.
    //
    //   Waiting is not FIFO: resume_next_ready() wakes the highest priority
    //   waiter, which is the scmRTOS convention everywhere.
    //
    class TSemaphore : protected TService
    {
    public:
        TSemaphore(size_t max_count, size_t initial_count)
          : ProcessMap(0)
          , Count(initial_count)
          , MaxCount(max_count)
        {
        }

        // timeout == 0 means "wait forever" (scmRTOS convention).
        bool acquire(timeout_t timeout = 0);
        // Non-blocking attempt: never suspends the process.
        bool try_acquire();

        // false if the semaphore is already at MaxCount (nothing was released).
        bool release();
        bool release_isr();

        size_t get_count()     const { TCritSect cs; return Count;    }
        size_t get_max_count() const { return MaxCount; }

    protected:
        volatile TProcessMap ProcessMap;
        volatile size_t      Count;
        const size_t         MaxCount;
    };
}
