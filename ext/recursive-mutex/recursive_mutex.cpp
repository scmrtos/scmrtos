//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
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
//*     Recursive mutex extension by Andrey Chuykin, Copyright (c) 2015-2016

#include "recursive_mutex.h"

namespace OS
{

//------------------------------------------------------------------------------
//
void TRecursiveMutex::lock()
{
    TCritSect cs;
    TProcessMap curr_tag = cur_proc_prio_tag();

    if ( 0 == ValueTag )
    {
        ValueTag = curr_tag;
        NestCount = 1;
    }
    else if ( ValueTag == curr_tag )
    {
        ++NestCount;
    }
    else
    {
        while ( ValueTag )
            suspend(ProcessMap);
        ValueTag = cur_proc_prio_tag();
        NestCount = 1;
    }
}


//------------------------------------------------------------------------------
//
void TRecursiveMutex::unlock()
{
    TCritSect cs;

    if ( ValueTag != cur_proc_prio_tag() || 0 == NestCount )
        return;
    if ( --NestCount == 0 )
    {
        ValueTag = 0;
        resume_next_ready(ProcessMap);
    }
}


//------------------------------------------------------------------------------
//
void TRecursiveMutex::force_unlock()
{
    TCritSect cs;

    if ( ValueTag != cur_proc_prio_tag() || 0 == NestCount )
        return;
    NestCount = 0;
    ValueTag = 0;
    resume_next_ready(ProcessMap);
}


//------------------------------------------------------------------------------
//
bool TRecursiveMutex::try_lock()
{
    TCritSect cs;

    if ( ValueTag && ValueTag != cur_proc_prio_tag() ) 
        return false;
    else
        lock();
    return true; 
}


//------------------------------------------------------------------------------
//
bool TRecursiveMutex::try_lock(timeout_t timeout)
{
    TCritSect cs;

    if ( ValueTag && ValueTag != cur_proc_prio_tag() ) 
    {
        // mutex already locked by another process, suspend current process
        while ( ValueTag ) 
        {
            cur_proc_timeout() = timeout;
            suspend(ProcessMap);
            if ( is_timeouted(ProcessMap) )
                return false;             // waked up by timeout or by externals
            cur_proc_timeout() = 0;
        }
    }
    lock();
    return true;
}

} // ns OS

