//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*               
//*     PURPOSE:  OS Services Header. Declarations And Definitions
//*               
//*     Version:  3.00-beta
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
//*
//*     =================================================================
//*     scmRTOS is free software; you can redistribute it and/or
//*     modify it under the terms of the GNU General Public License
//*     as published by the Free Software Foundation; either version 2
//*     of the License, or (at your option) any later version.
//*
//*     This program is distributed in the hope that it will be useful,
//*     but WITHOUT ANY WARRANTY; without even the implied warranty of
//*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//*     GNU General Public License for more details.
//*
//*     You should have received a copy of the GNU General Public License
//*     along with this program; if not, write to the Free Software
//*     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//*     MA  02110-1301, USA.
//*     =================================================================
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//********************************************************************************

#ifndef SERVICES_H
#define SERVICES_H

namespace OS
{
    //--------------------------------------------------------------------------
    //
    //       NAME       :   Mutex
    //
    //       PURPOSE    :   Binary semaphore for support of mutual exclusion
    //
    //       DESCRIPTION:
    //
    //
    class TMutex
    {
    public:
        TMutex() : ProcessMap(0), ValueTag(0) { }
        void Lock();
        void Unlock();

        INLINE bool LockSoftly()     { TCritSect cs; if(ValueTag) return false; else Lock(); return true; }
        INLINE bool IsLocked() const { TCritSect cs; if(ValueTag) return true; else return false; }

    private:
        TProcessMap ProcessMap;
        TProcessMap ValueTag;

    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //       NAME       : Event Flag
    //
    //       PURPOSE    : Intended for processes synchronization and
    //                    event notification one (or more) process by another
    //
    //       DESCRIPTION:
    //
    //
    class TEventFlag
    {
        enum TValue { efOn = 1, efOff= 0 }; // prefix 'ef' means: "Event Flag"

    public:
        TEventFlag(TValue init_val = efOff) : ProcessMap(0), Value(init_val) { }

        bool Wait(TTimeout timeout = 0);
        void Signal();
        INLINE void Clear() { TCritSect cs; Value = efOff; }
        INLINE inline void SignalISR();
        INLINE bool IsSignaled() { TCritSect cs; if(Value == efOn) return true; else return false; }

    private:
        TProcessMap ProcessMap;
        TValue Value;
    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //       NAME       :  TChannel
    //
    //       PURPOSE    :  Byte-wide data channel for transferring "raw" data
    //
    //       DESCRIPTION:
    //
    //
    class TChannel
    {
    public:
        TChannel(byte* buf, byte size) : Cbuf(buf, size) { }
        void Push(byte x);
        byte Pop();
        void Write(const byte* data, const byte count);
        void Read(byte* const data, const byte count);

        INLINE byte GetCount() const { TCritSect cs; return Cbuf.get_count(); }

    private:
        TProcessMap ProducersProcessMap;
        TProcessMap ConsumersProcessMap;
        usr::TCbuf Cbuf;

    private:
        void CheckWaiters(TProcessMap& pm);
    };
    //--------------------------------------------------------------------------


    //--------------------------------------------------------------------------
    //
    //       NAME       :  channel
    //
    //       PURPOSE    :  Data channel for transferring data
    //                     objects of arbitrary type
    //
    //       DESCRIPTION:
    //
    //
    template<typename T, word size, class S = byte>
    class channel
    {
    public:
        channel() : pool() { }

        //----------------------------------------------------------------
        //
        //    Data transfer functions
        //
        void write(const T* data, const S cnt);
        bool read (T* const data, const S cnt, TTimeout timeout = 0);

        void push      (const T& item);
        void push_front(const T& item);

        bool pop     (T& item, TTimeout timeout = 0);
        bool pop_back(T& item, TTimeout timeout = 0);


        //----------------------------------------------------------------
        //
        //    Service functions
        //
        S get_count()     const { TCritSect cs; return pool.get_count();     }
        S get_free_size() const { TCritSect cs; return pool.get_free_size(); }
        void flush();
        //const T& operator[](const S index) { TCritSect cs; return pool[index]; }


    private:
        TProcessMap ProducersProcessMap;
        TProcessMap ConsumersProcessMap;
        usr::ring_buffer<T, size, S> pool;

    private:
        void CheckWaiters(TProcessMap& pm);
        bool PopItem(T& item, T (usr::ring_buffer<T, size, S>::*pf)());
    };

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //       NAME       :  message
    //
    //       PURPOSE    :  Template for messages
    //
    //       DESCRIPTION:
    //
    //
    class TBaseMessage
    {
    public:
        TBaseMessage() : ProcessMap(0), NonEmpty(false) { }

        bool wait  (TTimeout timeout = 0);
        void send();
        INLINE inline void sendISR();
        INLINE bool is_non_empty() const { TCritSect cs; return NonEmpty;  }
        INLINE void reset       ()       { TCritSect cs; NonEmpty = false; }

    private:
        TProcessMap ProcessMap;
        bool NonEmpty;
    };
    //--------------------------------------------------------------------------
    template<typename T>
    class message : public TBaseMessage
    {
    public:
        message() : TBaseMessage()   { }
        void operator=(const T& msg) { TCritSect cs; Msg = msg;  }
        operator     T() const       { TCritSect cs; return Msg; }

    private:
        T Msg;
    };
    //--------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
//
//          Function-members implementation
//
//------------------------------------------------------------------------------
void OS::TEventFlag::SignalISR()
{
    TCritSect cs;

    Value = efOn;
    OS::Kernel.ReadyProcessMap |= ProcessMap;         // place all waiting processes to ready map
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void OS::channel<T, size, S>::CheckWaiters(TProcessMap& pm)
{
    if(pm)
    {
        byte pr = GetHighPriority(pm);
        TProcessMap PrioTag = GetPrioTag(pr);
        ClrPrioTag(pm, PrioTag);                      // remove next ready process from wait map
        SetPrioTag(Kernel.ReadyProcessMap, PrioTag);  // place next process to ready map
        Kernel.Scheduler();
    }
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void OS::channel<T, size, S>::push(const T& item)
{
    TCritSect cs;

    if(pool.get_free_size())
    {
        pool.push_back(item);
        CheckWaiters(ConsumersProcessMap);
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ProducersProcessMap, PrioTag);     // channel is full, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);  // remove current process from ready map
        Kernel.Scheduler();
        pool.push_back(item);
        CheckWaiters(ConsumersProcessMap);
    }
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void OS::channel<T, size, S>::push_front(const T& item)
{
    TCritSect cs;

    if(pool.get_free_size())
    {
        pool.push_front(item);
        CheckWaiters(ConsumersProcessMap);
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ProducersProcessMap, PrioTag);     // channel is full, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);  // remove current process from ready map
        Kernel.Scheduler();
        pool.push_front(item);
        CheckWaiters(ConsumersProcessMap);
    }
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
bool OS::channel<T, size, S>::pop(T& item, TTimeout timeout)
{
    //return PopItem(item, &ring_buffer<T, size, S>::pop);
    TCritSect cs;

    if(pool.get_count())
    {
        item = pool.pop();
        CheckWaiters(ProducersProcessMap);
        return true;
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ConsumersProcessMap, PrioTag);     // channel is empty, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);  // remove current process from ready map

        TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
        p->Timeout = timeout;

        Kernel.Scheduler();

        if(timeout && p->Timeout == 0)                       // waked up by timer when timeout expired
        {                                                                     
            ClrPrioTag(ConsumersProcessMap, PrioTag); // timeout expired, remove current process from wait map
            return false;                                                     
        }

        p->Timeout = 0;
        item = pool.pop();
        CheckWaiters(ProducersProcessMap);
        return true;
    }
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
bool OS::channel<T, size, S>::pop_back(T& item, TTimeout timeout)
{
    //return PopItem(item, &ring_buffer<T, size, S>::pop);
    TCritSect cs;

    if(pool.get_count())
    {
        item = pool.pop_back();
        CheckWaiters(ProducersProcessMap);
        return true;
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ConsumersProcessMap, PrioTag);     // channel is empty, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);  // remove current process from ready map

        TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
        p->Timeout = timeout;

        Kernel.Scheduler();

        if(timeout && p->Timeout == 0)                       // waked up by timer when timeout expired
        {                                                                     
            ClrPrioTag(ConsumersProcessMap, PrioTag); // timeout expired, remove current process from wait map
            return false;                                                     
        }

        p->Timeout = 0;
        item = pool.pop_back();
        CheckWaiters(ProducersProcessMap);
        return true;
    }
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void OS::channel<T, size, S>::flush()
{
    TCritSect cs;
    pool.flush();
    CheckWaiters(ProducersProcessMap);
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
bool OS::channel<T, size, S>::PopItem(T& item, T (usr::ring_buffer<T, size, S>::*pf)())
{
    TCritSect cs;

    if(pool.get_count())
    {
        item = (pool.*pf)();
        CheckWaiters(ProducersProcessMap);
        return true;
    }
    else
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ConsumersProcessMap, PrioTag);     // channel is empty, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);  // remove current process from ready map
        Kernel.Scheduler();
        item = (pool.*pf)();
        CheckWaiters(ProducersProcessMap);
        return false;
    }
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void OS::channel<T, size, S>::write(const T* data, const S count)
{
    TCritSect cs;

    while(pool.get_free_size() < count)
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ProducersProcessMap, PrioTag);     // channel has not enough space, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);  // remove current process from ready map
        Kernel.Scheduler();
    }

    pool.write(data, count);
    CheckWaiters(ConsumersProcessMap);
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
bool OS::channel<T, size, S>::read(T* const data, const S count, TTimeout timeout)
{
    TCritSect cs;

    TBaseProcess* p = Kernel.ProcessTable[Kernel.CurProcPriority];
    p->Timeout = timeout;

    while(pool.get_count() < count)
    {
        TProcessMap PrioTag = GetPrioTag(Kernel.CurProcPriority);
        SetPrioTag(ConsumersProcessMap, PrioTag);     // channel doesn't contain enough data, put current process to wait map
        ClrPrioTag(Kernel.ReadyProcessMap, PrioTag);  // remove current process from ready map
        Kernel.Scheduler();

        if(timeout && p->Timeout == 0)                       // waked up by timer when timeout expired
        {                                                                     
            ClrPrioTag(ConsumersProcessMap, PrioTag); // timeout expired, remove current process from wait map
            return false;                                                     
        }
    }

    p->Timeout = 0;
    pool.read(data, count);
    CheckWaiters(ProducersProcessMap);

    return true;
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
void OS::TBaseMessage::sendISR()
{
    TCritSect cs;

    NonEmpty = true;
    OS::Kernel.ReadyProcessMap |= ProcessMap; // place all waiting processes to ready map
}
//------------------------------------------------------------------------------


#endif // SERVICES_H
