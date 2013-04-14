//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Extensions includes
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//*****************************************************************************

#ifndef  scmRTOS_EXTENSIONS_H
#define  scmRTOS_EXTENSIONS_H

#include <profiler.h>

//------------------------------------------------------------------------------
//  Context switch takes about 240-250 MCU cycles depend on context switch
// scheme. Prescaler clk/256 is too coarse for profiler timebase.
// With prescaler clk/64 T1 overflow frequency is F_CPU/64/65536
//  ~1.76 Hz for 7.3728 MHz and ~3.52 Hz for 14.7456 MHz crystal.
// Without TCNT1 extension by variable function TProfiler::time_interval() must
// be called more frequently. Force context switch every 200ms by setup profler
// process sleep time to 200 ticks.
// UART printing is done every 5th wake-up, 1 second interval.

typedef TProfiler<0> TProfilerBase;

class TProfilerDemo : public TProfilerBase
{
public:
    INLINE TProfilerDemo()
    {
        TCCR1A = 0;
        TCCR1B = (1 << CS01) | (1 << CS10);    // Free running, clk/64
        TIMSK1 = 0;
    }
};

template<> INLINE 
uint32_t TProfilerBase::time_interval()
{
    static uint16_t  prev_ticks;

    uint16_t  ticks = TCNT1;
    uint16_t  diff = ticks - prev_ticks;
    prev_ticks = ticks;
    return diff;
}

extern TProfilerDemo profiler;

#if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE != 1
#  error Profiler requires scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
#endif

#if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE
INLINE void OS::context_switch_user_hook()
{
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    block_context_switch();
#endif
// #if USE_PROFILER == 1
    profiler.advance_counters();
// #endif
}
#endif

#endif // scmRTOS_EXTENSIONS_H
//-----------------------------------------------------------------------------

