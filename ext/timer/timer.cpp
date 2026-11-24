//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  Software timer extension implementation
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

#include <timer.h>

namespace OS
{
    //--------------------------------------------------------------------------
    // Insert a registered timer expiring `delta` ticks from now (delta >= 1),
    // keeping the delta list sorted. Timers that expire at the same moment
    // keep FIFO order: the scan stops at the first strictly larger delta.
    void TSoftwareTimer::insert_sorted(TSoftwareTimer* const t, timeout_t delta)
    {
        for (TSoftwareTimer** pp = &Registry; ; pp = &(*pp)->m_next)
        {
            TSoftwareTimer* const n = *pp;

            if (n == nullptr || n->m_remain > delta)
            {
                t->m_remain = delta;
                if (n != nullptr)
                    n->m_remain -= delta;
                t->m_next = n;
                *pp = t;
                return;
            }

            delta -= n->m_remain;
        }
    }

    //--------------------------------------------------------------------------
    // Unlink a registered timer. Its delta must be passed on to the
    // successor, otherwise every later timer would start firing early.
    void TSoftwareTimer::unlink(TSoftwareTimer* const t)
    {
        for (TSoftwareTimer** pp = &Registry; ; pp = &(*pp)->m_next)
        {
            if (*pp == t)
            {
                if (t->m_next != nullptr)
                    t->m_next->m_remain += t->m_remain;
                *pp = t->m_next;
                t->m_next = nullptr;
                return;
            }
        }
    }

    //--------------------------------------------------------------------------
    TSoftwareTimer::~TSoftwareTimer()
    {
        TCritSect cs;

        // By the invariant, a timer that never ran is simply absent from
        // the registry; nothing to unlink there.
        if (m_running)
            unlink(this);
        m_running = false;
    }

    //--------------------------------------------------------------------------
    bool TSoftwareTimer::start(const timeout_t ticks)
    {
        if (ticks == 0 || m_cb == nullptr)
            return false;

        TCritSect cs;

        if (m_running)
            unlink(this);
        else
            m_running = true;

        m_period = ticks;
        insert_sorted(this, ticks);
        return true;
    }

    //--------------------------------------------------------------------------
    bool TSoftwareTimer::stop()
    {
        TCritSect cs;

        if (!m_running)
            return false;

        m_running = false;
        unlink(this);
        return true;
    }

    //--------------------------------------------------------------------------
    void TSoftwareTimer::service()
    {
        {
            TCritSect cs;

            // Only the head has to tick: every later timer expires no
            // earlier than the head plus its own delta, so a non-zero head
            // means nothing expires on this tick.
            if (Registry != nullptr && Registry->m_remain != 0)
                --Registry->m_remain;
        }

        // Dispatch one expired timer per iteration, outside the critical
        // section: its callback may start/stop/delete any timer, including
        // this one. Registration is updated before the call, and a callback
        // can only insert timers that expire at least one tick later, so
        // every iteration retires one expired head and the loop terminates.
        for (;;)
        {
            callback_t cb;
            void*      arg;

            {
                TCritSect cs;

                TSoftwareTimer* const t = Registry;
                if (t == nullptr || t->m_remain != 0)
                    return;

                // The successor's delta counts from this expiry, so a plain
                // pop keeps the list consistent; the successor may well be
                // expired on this same tick.
                Registry = t->m_next;

                if (t->m_periodic)
                    insert_sorted(t, t->m_period);  // period from the expiry
                                                    // point, no drift
                else
                {
                    t->m_running = false;
                    t->m_next    = nullptr;
                }

                cb  = t->m_cb;
                arg = t->m_arg;
            }

            cb(arg);
        }
    }

}   // namespace OS
