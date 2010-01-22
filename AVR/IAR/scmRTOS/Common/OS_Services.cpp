//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Services Source
//*
//*     Version: 3.10
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2010, Harry E. Zhurov
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

    if(Value)                                           // if flag already signaled
    {
        Value = efOff;                                  // clear flag
        return true;
    }
    else
    {
        TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
        p->Timeout = timeout;
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);

        SetPrioTag(ProcessMap, PrioTag);                // put current process to the wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);    // remove current process from the ready map

        Kernel.Scheduler();

        p->Timeout = 0;

        if( !(ProcessMap & PrioTag) )                   // if waked up by signal() or signal_ISR()
            return true;

        ClrPrioTag(ProcessMap, PrioTag);                // otherwise waked up by timeout or by
        return false;                                   // OS::ForceWakeUpProcess(), remove process from the wait map
    }
}
//------------------------------------------------------------------------------
void OS::TEventFlag::Signal()
{
    TCritSect cs;
    if(ProcessMap)                                          // if any process waits for event
    {
        TProcessMap Timeouted = Kernel.ReadyProcessMap;     // Process has its tag set in ReadyProcessMap if timeout expired
                                                            // or it was waked up by OS::ForceWakeUpProcess()

        if( ProcessMap & ~Timeouted )                       // if any process has to be waked up
        {
            SetPrioTag(Kernel.ReadyProcessMap, ProcessMap); // place all waiting processes to the ready map
            ClrPrioTag(ProcessMap, ~Timeouted);             // remove all non-timeouted processes from the waiting map.
                                                            // Used to check that process waked up by signal() or signalISR()
                                                            // and not by timeout or OS::ForceWakeUpProcess()
            Kernel.Scheduler();
            return;
        }
    }
    Value = efOn;
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
        SetPrioTag(ProcessMap, PrioTag);             // mutex already locked by another process, put current process to the wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from the ready map

        Kernel.Scheduler();
    }
    ValueTag = PrioTag;                              // mutex has been successfully locked
}
//------------------------------------------------------------------------------
void OS::TMutex::Unlock()
{
    TCritSect cs;

    TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
    if(ValueTag != PrioTag) return;                  // the only process that had locked mutex can unlock the mutex
    ValueTag = 0;
    if(ProcessMap)
    {
        byte pr = GetHighPriority(ProcessMap);
        PrioTag = GetPrioTag(pr);
        ClrPrioTag(ProcessMap, PrioTag);             // remove next ready process from the wait map
        SetPrioTag(Kernel.ReadyProcessMap, PrioTag); // place next process to the ready map
        Kernel.Scheduler();
    }
}
//------------------------------------------------------------------------------
void OS::TMutex::UnlockISR()
{
    TCritSect cs;

    ValueTag = 0;
    if(ProcessMap)
    {
        byte pr = GetHighPriority(ProcessMap);
        TProcessMap PrioTag = GetPrioTag(pr);
        ClrPrioTag(ProcessMap, PrioTag);             // remove next ready process from the wait map
        SetPrioTag(Kernel.ReadyProcessMap, PrioTag); // place next process to the ready map
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
        ClrPrioTag(pm, PrioTag);                     // remove next ready process from the wait map
        SetPrioTag(Kernel.ReadyProcessMap, PrioTag); // place next process to the ready map
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
        SetPrioTag  (ProducersProcessMap, PrioTag);  // channel is full, put current process to the wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from the ready map
        Kernel.Scheduler();                          // wait until waked-up by Pop() or Read()
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
        SetPrioTag(ConsumersProcessMap, PrioTag);    // channel is empty, put current process to the wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from the ready map
        Kernel.Scheduler();                          // wait until waked up by Push() or Write()
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
        SetPrioTag(ProducersProcessMap, PrioTag);    // channel has not enough space, put current process to the wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from the ready map
        Kernel.Scheduler();                          // wait until waked up by Read() or Pop()
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
        SetPrioTag(ConsumersProcessMap, PrioTag);    // channel doesn't contain enough data, put current process to the wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from the ready map
        Kernel.Scheduler();                          // wait until waked up by Write() or Push()
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
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);

        SetPrioTag(ProcessMap, PrioTag);                          // put current process to the wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);              // remove current process from the ready map
        Kernel.Scheduler();                                       // wait until wake up

        p->Timeout = 0;
        if( !(ProcessMap & PrioTag) )                             // if waked up by send() or sendISR()
            return true;

        ClrPrioTag(ProcessMap, PrioTag);                          // otherwise waked up by timeout or by
            return false;                                         // OS::ForceWakeUpProcess(), remove process from wait map
    }
}
//------------------------------------------------------------------------------
void OS::TBaseMessage::send()
{
    TCritSect cs;

    if(ProcessMap)
    {
        TProcessMap Timeouted = Kernel.ReadyProcessMap;         // Process has its tag set in ReadyProcessMap if timeout expired,
                                                                // or it was waked up by OS::ForceWakeUpProcess()
        if( ProcessMap & ~Timeouted )                           // if any process has to be waked up
        {
            SetPrioTag(Kernel.ReadyProcessMap, ProcessMap);     // place all waiting processes to the ready map
            ClrPrioTag(ProcessMap, ~Timeouted);                 // remove all non-timeouted processes from the waiting map.
            Kernel.Scheduler();
            return;
        }
    }

    NonEmpty = true;
}
//------------------------------------------------------------------------------

