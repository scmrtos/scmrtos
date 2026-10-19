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


#include "semaphore.h"

bool OS::TSemaphore::acquire(timeout_t timeout)
{
    TCritSect cs;

    for(;;)
    {
        if(Count)
        {
            --Count;                              // take a token
            return true;
        }

        cur_proc_timeout() = timeout;

        // no tokens, suspend until release() or timeout
        suspend(ProcessMap);

        if(is_timeouted(ProcessMap))
        {
            cur_proc_timeout() = 0;
            return false;                         // waked up by timeout or by wake_up()
        }
        // otherwise waked up by release(): loop and re-check the token count,
        // a higher priority process may have taken the token first.
    }
}
//------------------------------------------------------------------------------
bool OS::TSemaphore::try_acquire()
{
    TCritSect cs;

    if(!Count)
        return false;

    --Count;
    return true;
}
//------------------------------------------------------------------------------
bool OS::TSemaphore::release()
{
    TCritSect cs;

    if(Count >= MaxCount)
        return false;                             // already full, nothing to release

    ++Count;
    resume_next_ready(ProcessMap);
    return true;
}
//------------------------------------------------------------------------------
bool OS::TSemaphore::release_isr()
{
    TCritSect cs;

    if(Count >= MaxCount)
        return false;

    ++Count;
    resume_next_ready_isr(ProcessMap);
    return true;
}
