//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADSP-BF533 (Analog Devices)
//*
//*     TOOLKIT:   VDSP (Analog Devices)
//*
//*     PURPOSE:   Round-Robin extension definitions
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
//*     Round-Robin extension by Harry E. Zhurov, Copyright (c) 2015-2016

#ifndef  ROUND_ROBIN_H
#define  ROUND_ROBIN_H

#include <scmRTOS.h>

namespace os = OS;

//------------------------------------------------------------------------------
//
//      
// 
//
template <uint_fast8_t proc_count>
class round_robin_mgr : public OS::TKernelAgent
{
public:
    round_robin_mgr() : cur_idx(0), reg_idx(0) 
    { 
        for(int i = 0; i < proc_count; ++i)
        {
            put_off[i]  = true;
        }
    }

    void register_process(const OS::TBaseProcess &proc, timeout_t tslot = 1)
    {
        table[reg_idx].p = &proc;
        table[reg_idx].t = tslot;
        timers[reg_idx]  = tslot;
        if(reg_idx++)
        {
            set_process_unready( proc.priority() );
        }
    }

    INLINE void run();

private:
    struct TItem
    {
        const OS::TBaseProcess *p;
        timeout_t               t;
    };

    INLINE void next();

private:                
    uint_fast8_t cur_idx;
    uint_fast8_t reg_idx;
    TItem        table[proc_count];
    timeout_t    timers[proc_count];
    bool         put_off[proc_count];      // set the flag when process is suspended by round-robin manager

};
//------------------------------------------------------------------------------
template <uint_fast8_t proc_count>
void round_robin_mgr<proc_count>::next()
{
    for(int i = 0; i < reg_idx; ++i)
    {
        if( ++cur_idx == reg_idx )
        {
            cur_idx = 0;
        }

        if( put_off[cur_idx] )
        {
            put_off[cur_idx]  = false;
            timers[cur_idx]   = table[cur_idx].t;
            set_process_ready( table[cur_idx].p->priority() );
            return;
        }
    }
}
//------------------------------------------------------------------------------
template <uint_fast8_t proc_count>
void round_robin_mgr<proc_count>::run()
{
    //-----------------------------------------------
    //
    //   Check if active process is suspended 
    //   by external source (sleep, wait, etc),
    //   then get next process
    // 
    if( table[cur_idx].p->is_suspended() )
    {
        next();
        return;
    }

    //-----------------------------------------------
    //
    //   Check if any inactive process is waked up by
    //   external source (timeout expired, signaled, etc)
    // 
    for(int i = 0; i < reg_idx; ++i)
    {
        if( cur_idx != i && !table[i].p->is_suspended() )
        {
            put_off[i]  = true;
            set_process_unready( table[i].p->priority() );
        }
    }

    //-----------------------------------------------
    //
    //   Check active process timer and advance the sequence 
    // 
    if( --timers[cur_idx] == 0  )
    {
        put_off[cur_idx] = true;
        set_process_unready( table[cur_idx].p->priority() );
        next();
    }
}
//------------------------------------------------------------------------------

#endif // ROUND_ROBIN_H
