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


#include "event_flags.h"

bool OS::TEventFlags::wait(uint32_t Bits, uint32_t Options, timeout_t timeout, uint32_t* Result)
{
    TCritSect cs;

    if(!Bits)
        return false;                             // parameter error: nothing to wait for

    cur_proc_timeout() = timeout;

    for(;;)
    {
        if(is_satisfied(Value, Bits, Options))
        {
            if(Result)
                *Result = Value;                  // the value BEFORE clearing
            if(!(Options & efNoClear))
                Value = Value & ~Bits;

            cur_proc_timeout() = 0;
            return true;
        }

        // condition not met yet, suspend until set() or timeout
        suspend(ProcessMap);

        if(is_waked_up(ProcessMap))
        {
            cur_proc_timeout() = 0;
            return false;                         // waked up by timeout or by wake_up()
        }
        // waked up by set(): loop and re-check, e.g. wait_all may still miss bits.
        // Timeout is NOT restarted here: the remaining Timeout keeps counting,
        // so the timeout is an absolute deadline.
    }
}
//------------------------------------------------------------------------------
bool OS::TEventFlags::try_wait(uint32_t Bits, uint32_t Options, uint32_t* Result)
{
    TCritSect cs;

    if(!Bits || !is_satisfied(Value, Bits, Options))
        return false;

    if(Result)
        *Result = Value;
    if(!(Options & efNoClear))
        Value = Value & ~Bits;

    return true;
}
//------------------------------------------------------------------------------
uint32_t OS::TEventFlags::set(uint32_t Bits)
{
    TCritSect cs;

    Value = Value | Bits;                 // latched, even if a woken waiter stays asleep
    resume_all(ProcessMap);               // every waiter re-checks its own condition
    return Value;
}
//------------------------------------------------------------------------------
uint32_t OS::TEventFlags::set_isr(uint32_t Bits)
{
    TCritSect cs;

    Value = Value | Bits;
    resume_all_isr(ProcessMap);
    return Value;
}
//------------------------------------------------------------------------------
uint32_t OS::TEventFlags::clear(uint32_t Bits)
{
    TCritSect cs;

    uint32_t Prev = Value;
    Value = Value & ~Bits;
    return Prev;
}
