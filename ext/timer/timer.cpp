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
    TSoftwareTimer::~TSoftwareTimer()
    {
        TCritSect cs;

        // The guard against the end of the list is required here (and only
        // here): the destructor must also accept a timer that was never
        // started and is therefore absent from the registry.
        for (TSoftwareTimer** pp = &Registry; *pp != nullptr; pp = &(*pp)->m_next)
        {
            if (*pp == this)
            {
                *pp = m_next;
                break;
            }
        }
        m_running = false;
    }

    //--------------------------------------------------------------------------
    bool TSoftwareTimer::start(const timeout_t ticks)
    {
        if (ticks == 0)
            return false;

        TCritSect cs;

        if (!m_running)
        {
            m_running = true;
            m_next    = Registry;
            Registry  = this;
        }

        m_period = ticks;
        m_remain = ticks;
        return true;
    }

    //--------------------------------------------------------------------------
    bool TSoftwareTimer::stop()
    {
        TCritSect cs;

        if (!m_running)
            return false;

        m_running = false;

        // m_running was true, so by the invariant the timer is linked in -
        // the scan cannot run past the end of the list.
        for (TSoftwareTimer** pp = &Registry; ; pp = &(*pp)->m_next)
        {
            if (*pp == this)
            {
                *pp = m_next;
                break;
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------
    void TSoftwareTimer::service()
    {
        {
            TCritSect cs;

            for (TSoftwareTimer* t = Registry; t != nullptr; t = t->m_next)
                if (t->m_remain != 0)
                    --t->m_remain;
        }

        // Dispatch one expired timer per iteration, outside the critical
        // section: its callback may start/stop/delete any timer, including
        // this one. Registration is updated before the call, and a callback
        // can only (re)start timers with m_remain >= 1, so every iteration
        // retires one expired entry and the loop terminates.
        for (;;)
        {
            callback_t cb;
            void*      arg;

            {
                TCritSect cs;

                TSoftwareTimer* t = Registry;
                while (t != nullptr && t->m_remain != 0)
                    t = t->m_next;
                if (t == nullptr)
                    return;

                cb  = t->m_cb;
                arg = t->m_arg;

                if (t->m_periodic)
                    t->m_remain = t->m_period;      // period from the expiry
                                                    // point, no drift
                else
                {
                    t->m_running = false;

                    for (TSoftwareTimer** pp = &Registry; ; pp = &(*pp)->m_next)
                    {
                        if (*pp == t)
                        {
                            *pp = t->m_next;
                            break;
                        }
                    }
                }
            }

            cb(arg);
        }
    }

}   // namespace OS
