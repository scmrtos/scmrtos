//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  Software timer extension (callback timers driven by the system timer hook)
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
//*     Software timer extension by Anton B. Gusev, Copyright (c) 2026

#pragma once

#include <scmRTOS.h>

namespace OS
{
    //--------------------------------------------------------------------------
    //
    //   TSoftwareTimer
    //
    //   Callback-driven software timer, one-shot or periodic.
    //
    //   The application must call TSoftwareTimer::service() once per tick,
    //   from one and only one context (not reentrant). The natural tick
    //   source is the system timer hook: enable scmRTOS_SYSTIMER_HOOK_ENABLE
    //   and call service() from system_timer_user_hook(); until service()
    //   runs every tick, timers do not tick.
    //
    //   The callback runs in the context of whoever calls service() (with
    //   the hook integration: the system timer ISR), so it must be short and
    //   non-blocking (only ISR-safe API). It may call any TSoftwareTimer
    //   member, including restarting or deleting the timer it belongs to -
    //   registration state is updated before the callback is invoked.
    //
    //   All members are non-blocking and callable from processes and ISRs
    //   alike (registry mutations happen under TCritSect).
    //
    class TSoftwareTimer
    {
    public:
        typedef void (*callback_t)(void* arg);

        INLINE TSoftwareTimer(const callback_t cb, void* const arg, const bool periodic)
          : m_cb(cb)
          , m_arg(arg)
          , m_periodic(periodic)
        {
        }

        // Unregisters the timer; safe whether it is running or not.
        ~TSoftwareTimer();

        // Start or restart: the next expiry comes `ticks` ticks later
        // (ticks == 0 is not a valid period - returns false).
        bool start(const timeout_t ticks);

        // Returns false if the timer was not running.
        bool stop();

        INLINE bool is_running() const { return m_running; }

        // Advance every registered timer by one tick and dispatch the
        // expired callbacks. Call exactly once per tick and from a single
        // context only: a nested second call would double-decrement and
        // interleave dispatches. The system timer hook is the recommended
        // source (see README).
        static void service();

    private:
        // m_next links the registered timers; every field below is mutated
        // under TCritSect only (except reads of plain flags, which are
        // volatile). Invariant: m_running == (timer is in the registry).
        TSoftwareTimer*     m_next = nullptr;
        volatile timeout_t  m_remain = 0;   // ticks left until expiry
        volatile timeout_t  m_period = 0;   // reload value (periodic timers)

        const callback_t    m_cb;
        void* const         m_arg;
        const bool          m_periodic;
        volatile bool       m_running = false;

        inline static TSoftwareTimer* Registry = nullptr;
    };

}   // namespace OS
