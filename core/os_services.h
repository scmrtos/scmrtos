//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Services Header. Declarations And Definitions
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

#ifndef OS_SERVICES_H
#define OS_SERVICES_H

namespace OS
{
    //==========================================================================
    //
    //   TService
    // 
    //   Base type for creation of RTOS services
    //   
    //
    //       DESCRIPTION:
    //
    //
    class TService : protected TKernelAgent
    {
    protected:
        TService() : TKernelAgent() { }

        INLINE static TProcessMap  cur_proc_prio_tag()  { return get_prio_tag(cur_proc_priority()); }
        INLINE static TProcessMap  highest_prio_tag(TProcessMap map)
        {
        #if scmRTOS_PRIORITY_ORDER == 0
            return map & (~static_cast<unsigned>(map) + 1);                              // Isolate rightmost 1-bit.
        #else   // scmRTOS_PRIORITY_ORDER == 1
            return get_prio_tag(highest_priority(map));
        #endif
        }

        //----------------------------------------------------------------------
        //
        //   Base API
        //

        // add prio_tag proc to waiters map, reschedule
        INLINE void suspend(TProcessMap volatile & waiters_map);

        // returns false if waked-up by timeout or TBaseProcess::wake_up() | force_wake_up()
        INLINE static bool is_timeouted(TProcessMap volatile & waiters_map);

        // wake-up all processes from waiters map
        // return false if no one process was waked-up
               static bool resume_all     (TProcessMap volatile & waiters_map);
        INLINE static bool resume_all_isr (TProcessMap volatile & waiters_map);

        // wake-up next ready (most priority) process from waiters map if any
        // return false if no one process was waked-up
               static bool resume_next_ready     (TProcessMap volatile & waiters_map);
        INLINE static bool resume_next_ready_isr (TProcessMap volatile & waiters_map);
    };
    //--------------------------------------------------------------------------
    //
    //
    //    TService API implementation
    //

    void OS::TService::suspend(TProcessMap volatile & waiters_map)
    {
        TProcessMap PrioTag = cur_proc_prio_tag();
    
        set_prio_tag(waiters_map, PrioTag);                   // put current process to wait map
        clr_prio_tag(ready_process_map(), PrioTag);           // remove current process from ready map
    
    #if scmRTOS_DEBUG_ENABLE == 1
        cur_proc_waiting_for() = this;                        // catch current service address to process debug data
    #endif

    #if scmRTOS_PROCESS_RESTART_ENABLE == 1
        cur_proc_waiting_map() = &waiters_map;
    #endif
        
        reschedule();
        
    #if scmRTOS_DEBUG_ENABLE == 1
        cur_proc_waiting_for() = 0;                           // remove current service address from process debug data
    #endif
        
    #if scmRTOS_PROCESS_RESTART_ENABLE == 1
        cur_proc_waiting_map() = 0;
    #endif
        
    }
    //--------------------------------------------------------------------------
    bool OS::TService::is_timeouted(TProcessMap volatile & waiters_map)
    {
        TProcessMap PrioTag = cur_proc_prio_tag();

        TProcessMap CachedMap = waiters_map;                // cache volatile, code runs in critical section
        if( CachedMap & PrioTag )                           // if waked up by timeout or by
                                                            // OS::TBaseProcess::wake_up() | force_wake_up()
        {
            clr_prio_tag(CachedMap, PrioTag);               // remove process from the wait map
            waiters_map = CachedMap;
            return true;
        }
        return false;
    }
    //--------------------------------------------------------------------------
    bool OS::TService::resume_all_isr (TProcessMap volatile & waiters_map)
    {
        TProcessMap Timeouted = ready_process_map();                      // Process has its tag set in ReadyProcessMap if timeout expired,
                                                                          // or it was waked up by OS::ForceWakeUpProcess()
                                                                          
        TProcessMap CachedMap = waiters_map;                              // cache volatile
        if( CachedMap & ~static_cast<unsigned>(Timeouted) )                                      // if any process has to be waked up
        {                                                                 
            set_prio_tag(ready_process_map(), CachedMap);                 // place all waiting processes to the ready map
            clr_prio_tag(CachedMap, ~static_cast<unsigned>(Timeouted) );  // remove all non-timeouted processes from the waiting map.
            waiters_map = CachedMap;
            return true;
        }
        return false;
    }
    //--------------------------------------------------------------------------
    bool OS::TService::resume_next_ready_isr (TProcessMap volatile & waiters_map)
    {
        TProcessMap Active = ready_process_map();                         // Cache volatile
        TProcessMap Waiters = waiters_map;                                // Cache volatile
                                                                          
        TProcessMap Timeouted = Active;                                   // Process has its tag set in ReadyProcessMap if timeout expired,
                                                                          // or it was waked up by OS::ForceWakeUpProcess()
    
        TProcessMap Ready = Waiters & ~static_cast<unsigned>(Timeouted);
        if( Ready )                                                       // if any process has to be waked up
        {                                                                 
            TProcessMap PrioTag = highest_prio_tag(Ready);                // get next ready process tag
            set_prio_tag(Active, PrioTag);                                // place next ready process to the ready map
            clr_prio_tag(Waiters, PrioTag);                               // remove process from the waiting map.
    
            ready_process_map() = Active;
            waiters_map = Waiters;
    
            return true;
        }
        return false;
    }
    //--------------------------------------------------------------------------
    //==========================================================================


    //--------------------------------------------------------------------------
    //
    //   Event Flag
    // 
    //   Intended for processes synchronization and
    //   event notification one (or more) process by another
    //
    //       DESCRIPTION:
    //
    //
    class TEventFlag : protected TService
    {
    public:
        enum TValue { efOn = 1, efOff= 0 };     // prefix 'ef' means: "Event Flag"

    public:
        INLINE TEventFlag(TValue init_val = efOff) : ProcessMap(0), Value(init_val) { }

               bool wait(timeout_t timeout = 0);
        INLINE void signal();
        INLINE void clear()       { TCritSect cs; Value = efOff; }
        INLINE void signal_isr();
        INLINE bool is_signaled() { TCritSect cs; return Value == efOn; }

    protected:
        volatile TProcessMap ProcessMap;
        volatile TValue      Value;
    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //  Mutex
    //
    //  Binary semaphore for support of mutual exclusion
    //
    //       DESCRIPTION:
    //
    //
    class TMutex : protected TService
    {
    public:
        INLINE TMutex() : ProcessMap(0), ValueTag(0) { }
               void lock();
               void unlock();
        INLINE void unlock_isr();

        INLINE bool try_lock()       { TCritSect cs; if(ValueTag) return false; else lock(); return true; }
               bool try_lock(timeout_t timeout);
        INLINE bool is_locked() const { TCritSect cs; return ValueTag != 0; }

    protected:
        volatile TProcessMap ProcessMap;
        volatile TProcessMap ValueTag;

    };
    //--------------------------------------------------------------------------
    template <typename Mutex>
    class TScopedLock
    {
    public:
        TScopedLock(Mutex& m): mx(m) { mx.lock(); }
        ~TScopedLock() { mx.unlock(); }
    private:
        Mutex & mx;
    };

    typedef TScopedLock<OS::TMutex> TMutexLocker;
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //   TChannel
    // 
    //   Byte-wide data channel for transferring "raw" data
    //
    //       DESCRIPTION:
    //
    //
    class TChannel : protected TService
    {
    public:
        INLINE TChannel(uint8_t* buf, uint8_t size) 
            : ProducersProcessMap(0)
            , ConsumersProcessMap(0)
            , Cbuf(buf, size)
        { 
        }

        void    push(uint8_t x);
        uint8_t pop();

        void write(const uint8_t* data, const uint8_t count);
        void read(uint8_t* const data, const uint8_t count);

        INLINE uint8_t get_count() const { TCritSect cs; return Cbuf.get_count(); }

    protected:
        volatile TProcessMap ProducersProcessMap;
        volatile TProcessMap ConsumersProcessMap;
        usr::TCbuf Cbuf;
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
    template<typename T, uint16_t Size, typename S = uint8_t>
    class channel : protected TService
    {
    public:
        INLINE channel() : ProducersProcessMap(0)
                         , ConsumersProcessMap(0)
                         , pool()
        {
        }

        //----------------------------------------------------------------
        //
        //    Data transfer functions
        //
        void write     (const T* data, const S cnt);
        S    write_isr (const T* data, const S cnt);

        bool read      (T* const data, const S cnt, timeout_t timeout = 0);
        S    read_isr  (T* const data, const S max_size);

        void push      (const T& item);
        void push_front(const T& item);

        bool pop     (T& item, timeout_t timeout = 0);
        bool pop_back(T& item, timeout_t timeout = 0);


        //----------------------------------------------------------------
        //
        //    Service functions
        //
        INLINE S    get_count()     const { TCritSect cs; return pool.get_count();     }
        INLINE S    get_free_size() const { TCritSect cs; return pool.get_free_size(); }
               void flush();

    protected:
        volatile TProcessMap ProducersProcessMap;
        volatile TProcessMap ConsumersProcessMap;
        usr::ring_buffer<T, Size, S> pool;
    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //  message
    // 
    //  Template for messages
    //
    //       DESCRIPTION:
    //
    //
    class TBaseMessage : protected TService
    {
    public:
        INLINE TBaseMessage() : ProcessMap(0), NonEmpty(false) { }

               bool wait  (timeout_t timeout = 0);
        INLINE void send();
        INLINE void send_isr();
        INLINE bool is_non_empty() const { TCritSect cs; return NonEmpty;  }
        INLINE void reset       ()       { TCritSect cs; NonEmpty = false; }

    protected:
        volatile TProcessMap ProcessMap;
        volatile bool NonEmpty;
    };
    //--------------------------------------------------------------------------
    template<typename T>
    class message : public TBaseMessage
    {
    public:
        INLINE message() : TBaseMessage()   { }
        INLINE const T& operator= (const T& msg) { TCritSect cs; *(const_cast<T*>(&Msg)) = msg; return const_cast<const T&>(Msg); }
        INLINE          operator T() const       { TCritSect cs; return const_cast<const T&>(Msg); }
        INLINE void            out(T& msg)       { TCritSect cs; msg = const_cast<T&>(Msg); }

    protected:
        volatile T Msg;
    };
    //--------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
//
//          Function-members implementation
//
//------------------------------------------------------------------------------
void OS::TEventFlag::signal()
{
    TCritSect cs;
    if(!resume_all(ProcessMap))                         // if no one process was waiting for flag
        Value = efOn;
}
//------------------------------------------------------------------------------
void OS::TEventFlag::signal_isr()
{
    TCritSect cs;
    if(!resume_all_isr(ProcessMap))                         // if no one process was waiting for flag
        Value = efOn;
}
//------------------------------------------------------------------------------
void OS::TMutex::unlock_isr()
{
    TCritSect cs;

    ValueTag = 0;
    resume_next_ready_isr(ProcessMap);
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
void OS::channel<T, Size, S>::push(const T& item)
{
    TCritSect cs;

    while(!pool.get_free_size())
    {
        // channel is full, suspend current process until data removed
        suspend(ProducersProcessMap);
    }

    pool.push_back(item);
    resume_all(ConsumersProcessMap);
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
void OS::channel<T, Size, S>::push_front(const T& item)
{
    TCritSect cs;

    while(!pool.get_free_size())
    {
        // channel is full, suspend current process until data removed
        suspend(ProducersProcessMap);
    }

    pool.push_front(item);
    resume_all(ConsumersProcessMap);

}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
bool OS::channel<T, Size, S>::pop(T& item, timeout_t timeout)
{
    TCritSect cs;

    if(pool.get_count())
    {
        item = pool.pop();
        resume_all(ProducersProcessMap);
        return true;
    }
    else
    {
        cur_proc_timeout() = timeout;

        for(;;)
        {
            // channel is empty, suspend current process until data received or timeout
            suspend(ConsumersProcessMap);
            if(is_timeouted(ConsumersProcessMap))
                return false;

            if(pool.get_count())
            {
                cur_proc_timeout() = 0;
                item = pool.pop();
                resume_all(ProducersProcessMap);
                return true;
            }
            // otherwise another process caught data
        }
    }
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
bool OS::channel<T, Size, S>::pop_back(T& item, timeout_t timeout)
{
    TCritSect cs;

    if(pool.get_count())
    {
        item = pool.pop_back();
        resume_all(ProducersProcessMap);
        return true;
    }
    else
    {
        cur_proc_timeout() = timeout;

        for(;;)
        {
            // channel is empty, suspend current process until data received or timeout
            suspend(ConsumersProcessMap);
            if(is_timeouted(ConsumersProcessMap))
                return false;

            if(pool.get_count())
            {
                cur_proc_timeout() = 0;
                item = pool.pop_back();
                resume_all(ProducersProcessMap);
                return true;
            }
            // otherwise another process caught data
        }
    }
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
void OS::channel<T, Size, S>::flush()
{
    TCritSect cs;
    pool.flush();
    resume_all(ProducersProcessMap);
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
void OS::channel<T, Size, S>::write(const T* data, const S count)
{
    TCritSect cs;

    while(pool.get_free_size() < count)
    {
        // channel does not have enough space, suspend current process until data removed
        suspend(ProducersProcessMap);
    }

    pool.write(data, count);
    resume_all(ConsumersProcessMap);

}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
S OS::channel<T, Size, S>::write_isr(const T* data, const S count)
{
    TCritSect cs;

    const S free = pool.get_free_size();
    S qty = free < count ? free : count;
    pool.write(data, qty);
    resume_all_isr(ConsumersProcessMap);
    return qty;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
bool OS::channel<T, Size, S>::read(T* const data, const S count, timeout_t timeout)
{
    TCritSect cs;

    cur_proc_timeout() = timeout;

    while(pool.get_count() < count)
    {
        // channel doesn't contain enough data, suspend current process until data received or timeout
        suspend(ConsumersProcessMap);
        if(is_timeouted(ConsumersProcessMap))
            return false;
    }

    cur_proc_timeout() = 0;
    pool.read(data, count);
    resume_all(ProducersProcessMap);

    return true;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
S OS::channel<T, Size, S>::read_isr(T* const data, const S max_size)
{
    TCritSect cs;

    const S avail = pool.get_count();
    S count = avail < max_size ? avail : max_size;
    pool.read(data, count);
    resume_all_isr(ProducersProcessMap);
    return count;
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
void OS::TBaseMessage::send()
{
    TCritSect cs;
    if(!resume_all(ProcessMap))
        NonEmpty = true;
}
//------------------------------------------------------------------------------
void OS::TBaseMessage::send_isr()
{
    TCritSect cs;

    if(!resume_all_isr(ProcessMap))
        NonEmpty = true;
}
//------------------------------------------------------------------------------
#endif // OS_SERVICES_H
