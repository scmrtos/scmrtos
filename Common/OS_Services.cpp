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
//*     Copyright (c) 2003-2006, Harry E. Zhurov
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
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ProcessMap, PrioTag);             // put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map


        TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
        p->Timeout = timeout;
        Kernel.Scheduler();

        ClrPrioTag(ProcessMap, PrioTag);             // remove current process from wait list
        Value = efOff;


        word t = p->Timeout; p->Timeout = 0;

        if(timeout == 0)
            return true;

        if(t)
            return true;
        else
            return false;
    }
}
//------------------------------------------------------------------------------
void OS::TEventFlag::Signal()
{
    TCritSect cs;

    Value = efOn;
    Kernel.ReadyProcessMap |= ProcessMap; // place all waiting processes to ready map

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
    }
    ValueTag = PrioTag;                                     // mutex has been successfully locked
}
//------------------------------------------------------------------------------
void OS::TMutex::Unlock()
{
    TCritSect cs;

    TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
    if(ValueTag != PrioTag) return;                         // the only process that has locked mutex can unlock the mutex
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

    if(Cbuf.get_free_size())
    {
        Cbuf.put(x);
        CheckWaiters(ConsumersProcessMap);
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag  (ProducersProcessMap, PrioTag);  // channel is full, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map
        Kernel.Scheduler();
        Cbuf.put(x);
        CheckWaiters(ConsumersProcessMap);
    }
}
//------------------------------------------------------------------------------
byte OS::TChannel::Pop()
{
    TCritSect cs;
    byte x;

    if(Cbuf.get_count())
    {
        x = Cbuf.get();
        CheckWaiters(ProducersProcessMap);
        return x;
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ConsumersProcessMap, PrioTag);    // channel is empty, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag); // remove current process from ready map
        Kernel.Scheduler();
        x = Cbuf.get();
        CheckWaiters(ProducersProcessMap);
        return x;
    }
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
        Kernel.Scheduler();
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
        Kernel.Scheduler();
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

    if(NonEmpty)
    {
        NonEmpty = false;
        return true;
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ProcessMap, PrioTag);                      // put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);          // remove current process from ready map

        TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
        p->Timeout = timeout;
        Kernel.Scheduler();
        ClrPrioTag(ProcessMap, PrioTag);                      // remove current process from wait list
        NonEmpty = false;

        if(timeout && p->Timeout == 0) return false;          // waked up by timer when timeout expired
        p->Timeout = 0;
        return true;
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

