//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  32-bit event flags extension.
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
//*     Event flags extension by Anton B. Gusev, Copyright (c) 2026

#pragma once

#include <scmRTOS.h>

namespace OS
{
    //--------------------------------------------------------------------------
    //
    //   TEventFlags
    //
    //   32-bit event flags (TEventFlag is single-bit and does not latch the
    //   value when somebody is waiting - that is not enough for the
    //   "wait for a combination of events" pattern).
    //
    //   Value is ALWAYS latched by set(): a waiter woken by set() may find its
    //   condition unfulfilled (wait_all) and go back to sleep, so the bits must
    //   stay for it and for the processes that will call wait() later.
    //
    //   wait() returns the whole value BEFORE the waited bits are cleared.
    //
    enum TEventFlagsOptions : uint32_t
    {
        efWaitAny  = 0,   // wake when any of the requested bits is set
        efWaitAll  = 1,   // wake when all the requested bits are set
        efNoClear  = 2    // do not clear the requested bits on success
    };

    class TEventFlags : protected TService
    {
    public:
        TEventFlags() : ProcessMap(0), Value(0) { }

        // timeout == 0 means "wait forever" (scmRTOS convention).
        bool wait     (uint32_t Bits, uint32_t Options, timeout_t timeout, uint32_t* Result = 0);
        bool try_wait (uint32_t Bits, uint32_t Options, uint32_t* Result = 0);

        uint32_t set     (uint32_t Bits);         // value after setting
        uint32_t set_isr (uint32_t Bits);
        uint32_t clear   (uint32_t Bits);         // value before clearing
        uint32_t get     () const { TCritSect cs; return Value; }

    protected:
        static bool is_satisfied(uint32_t Value, uint32_t Bits, uint32_t Options)
        {
            return Options & efWaitAll ? (Value & Bits) == Bits
                                       : (Value & Bits) != 0;
        }

        volatile TProcessMap ProcessMap;
        volatile uint32_t    Value;
    };
}
