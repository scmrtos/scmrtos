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

#ifndef RECURSIVE_MUTEX_H
#define RECURSIVE_MUTEX_H

#include <scmRTOS.h>


namespace OS
{

//------------------------------------------------------------------------------
//
// Recursive mutex.
//
// Recursive mutex is similar to TMutex.
// But it can be locked several times by the same thread.
// To fully unlock the mutex, the thread has to unlock the mutex the same times
// it has locked it.
//
class TRecursiveMutex : protected TService
{
public:
    TRecursiveMutex(): ProcessMap(0), ValueTag(0), NestCount(0) { }

    void lock();
    void unlock();
    void unlock_isr();
    bool try_lock();
    bool try_lock(timeout_t timeout);
    bool is_locked() const { TCritSect cs; return (ValueTag != 0); }
    // Unlock the mutex despite of how many times it has been locked.
    void force_unlock();
    void force_unlock_isr();

protected:
    volatile TProcessMap ProcessMap;
    volatile TProcessMap ValueTag;
    volatile size_t NestCount;
}; 

//------------------------------------------------------------------------------
//
inline void TRecursiveMutex::unlock_isr()
{
    TCritSect cs;

    if ( NestCount && --NestCount == 0 )
    {
        ValueTag = 0;
        resume_next_ready_isr(ProcessMap);
    }
}

//------------------------------------------------------------------------------
//
inline void TRecursiveMutex::force_unlock_isr()
{
    TCritSect cs;

    if ( 0 == NestCount )
        return;
    NestCount = 0;
    ValueTag = 0;
    resume_next_ready_isr(ProcessMap);
}



} // ns OS

#endif /* RECURSIVE_MUTEX_H */

