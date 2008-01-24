//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Services Source
//*
//*     Version:  3.00-beta
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2007, Harry E. Zhurov
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
//******************************************************************************

#include "scmRTOS.h"

using namespace OS;

//------------------------------------------------------------------------------
//
//
//      TEventFlag
//
//
bool OS::TEventFlag::Wait(TTimeout timeout)
{
    TCritSect cs;

    if(Value == efOn)
    {
        Value = efOff;
        return true;
    }
    else
    {
        TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
        p->Timeout = timeout;
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        do
        {

            SetPrioTag(ProcessMap, PrioTag);             // put current process to wait map
            ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map

            Kernel.Scheduler();

            ClrPrioTag(ProcessMap, PrioTag);             // remove current process from wait list

            if( Value == efOn)                           // if waked-up by signal() or signal_ISR()
            {
                p->Timeout = 0;
                Value = efOff;
                return true;
            }
                                                         // otherwice waked-up by timeout or
                                                         // by signal() or signal_ISR(), but flag was
                                                         // read and cleared by hihger-priority process
        }
        while(p->Timeout != 0);

        return false;
    }
}
//------------------------------------------------------------------------------
void OS::TEventFlag::Signal()
{
    TCritSect cs;

    Value = efOn;
    Kernel.ReadyProcessMap |= ProcessMap;            // place all waiting processes to ready map

    Kernel.Scheduler();
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//
//      TMutex
//
//
void OS::TMutex::Lock()
{
    TCritSect cs;

    TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
    while(ValueTag)
    {
        SetPrioTag(ProcessMap, PrioTag);             // mutex already locked by another process, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map

        Kernel.Scheduler();
        // ValueTag at this point means that process with higher priority
        // has alredy had to Lock() this mutex
    }
    ValueTag = PrioTag;                              // mutex has been successfully locked
}
//------------------------------------------------------------------------------
void OS::TMutex::Unlock()
{
    TCritSect cs;

    TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
    if(ValueTag != PrioTag) return;                  // the only process that has locked mutex can unlock the mutex
    ValueTag = 0;
    if(ProcessMap)
    {
        byte pr = GetHighPriority(ProcessMap);
        TProcessMap PrioTag = GetPrioTag(pr);
        ClrPrioTag(ProcessMap, PrioTag);             // remove next ready process from wait map
        SetPrioTag(Kernel.ReadyProcessMap, PrioTag); // place next process to ready map
        Kernel.Scheduler();
    }
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//
//      TChannel
//
//
void OS::TChannel::CheckWaiters(TProcessMap& pm)
{
    if(pm)
    {
        byte pr = GetHighPriority(pm);
        TProcessMap PrioTag = GetPrioTag(pr);
        ClrPrioTag(pm, PrioTag);                     // remove next ready process from wait map
        SetPrioTag(Kernel.ReadyProcessMap, PrioTag); // place next process to ready map
        Kernel.Scheduler();
    }
}
//------------------------------------------------------------------------------
void OS::TChannel::Push(byte x)
{
    TCritSect cs;

    while (!Cbuf.get_free_size())
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag  (ProducersProcessMap, PrioTag);  // channel is full, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map
        Kernel.Scheduler();                          // wait until waked-up by Pop() or Read()
        // Cbuf.get_free_size() == 0 at this point means that
        // process with higher priority has alredy had to Push() or Write() new data
    }

    Cbuf.put(x);
    CheckWaiters(ConsumersProcessMap);
}
//------------------------------------------------------------------------------
byte OS::TChannel::Pop()
{
    TCritSect cs;
    byte x;

    while(!Cbuf.get_count())
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ConsumersProcessMap, PrioTag);    // channel is empty, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map
        Kernel.Scheduler();                          // wait until waked-up by Push() or Write()
        // Cbuf.get_count() == 0 at this point means that
        // process with higher priority has alredy had to Pop() or Read() new data
    }
    x = Cbuf.get();
    CheckWaiters(ProducersProcessMap);
    return x;
}
//------------------------------------------------------------------------------
void OS::TChannel::Write(const byte* data, const byte count)
{
    TCritSect cs;

    while(Cbuf.get_free_size() < count)
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ProducersProcessMap, PrioTag);    // channel has not enough space, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map
        Kernel.Scheduler();                          // wait until waked-up by Read() or Pop()
        // Cbuf.get_free_size() < count at this point means that
        // not enough data removed by Read() or Pop()
        // or process with higher priority has alredy had to Write() or Push() new data
    }

    Cbuf.write(data, count);
    CheckWaiters(ConsumersProcessMap);
}
//------------------------------------------------------------------------------
void OS::TChannel::Read(byte* const data, const byte count)
{
    TCritSect cs;

    while(Cbuf.get_count() < count)
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ConsumersProcessMap, PrioTag);    // channel doesn't contain enough data, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map
        Kernel.Scheduler();                          // wait until waked-up by Write() or Push()
        // Cbuf.get_count() < count at this point means that
        // not enough data placed by Write() or Push()
        // or process with higher priority has alredy had to Read() or Pop() new data
    }

    Cbuf.read(data, count);
    CheckWaiters(ProducersProcessMap);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//              OS::message template
//
//          Function-members implementation
//
//
//------------------------------------------------------------------------------
bool OS::TBaseMessage::wait(TTimeout timeout)
{
    TCritSect cs;

    if(NonEmpty)                                                  // message alredy send
    {
        NonEmpty = false;
        return true;
    }
    else
    {
        TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
        p->Timeout = timeout;
        for(;;)
        {
            TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
            SetPrioTag(ProcessMap, PrioTag);                      // put current process to wait map
            ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);          // remove current process from ready map

            Kernel.Scheduler();                                   // wait until waked-up
            ClrPrioTag(ProcessMap, PrioTag);                      // remove current process from wait list

            if( NonEmpty == true )                                // if waked-up by send()
            {
                p->Timeout = 0;
                return true;
            }

            if(timeout && p->Timeout == 0)                        // waked up by timer when timeout expired
                return false;
            // otherwice this message was removed by higher priority process,
            // wait for next message
        }
    }
}
//------------------------------------------------------------------------------
void OS::TBaseMessage::send()
{
    TCritSect cs;

    NonEmpty = true;
    OS::Kernel.ReadyProcessMap |= ProcessMap; // place all waiting processes to ready map

    Kernel.Scheduler();
}
//------------------------------------------------------------------------------

