//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: any
//*
//*     TOOLKIT:   any
//*
//*     PURPOSE:   Ring Buffer Extension Definitions
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
//*     Watchdog extension by Yury A. Yakimov, Copyright (c) 2015-2021


#ifndef RINGBUFFEREXT_H
#define RINGBUFFEREXT_H
#include <scmRTOS.h>

namespace OS {
    template<typename T, uint32_t Size, typename S = uint32_t>
    class RingBuffer : protected TService {
    public:
        INLINE RingBuffer()
            : m_head(0)
            , m_tail(0)
            , m_count(0)
            , m_waitingCount(0)
            , m_producersProcessMap(0)
            , m_consumersProcessMap(0) {}

        bool write( const T * data, const S cnt, S * const wr = nullptr, timeout_t tm = 0 );
        bool write_isr( const T * data, const S cnt, S * const wr = nullptr );

        bool read( T * data, const S cnt, S * const rd = nullptr, timeout_t tm = 0 );
        bool read_isr( const T * const data, const S cnt, S * const rd = nullptr );

        bool push( const T &item, timeout_t timeout = 0 );
        bool push_front( const T &item, timeout_t timeout = 0 );
        INLINE  bool push_isr( const T &item );
        bool push_front_isr( const T &item );

        bool pop( T &item, timeout_t timeout = 0 );
        bool pop_back( T &item, timeout_t timeout = 0 );
        bool pop_isr( T &item );
        bool pop_back_isr( T &item );

        S get_count() const;
        S get_free_size() const;

        void flush();
    protected:
        T pop_item();

        T m_buff[Size];
        S m_head; // always points to the first empty element
        S m_tail; // always points to the first unread element
        S m_count;
        S m_waitingCount;
        volatile TProcessMap m_producersProcessMap;
        volatile TProcessMap m_consumersProcessMap;
    };

    template<typename T, uint32_t Size, typename S>
    bool OS::RingBuffer<T, Size, S>::push_isr( const T &item ) {
        TCritSect cs;
        if (m_count == Size)
            return false;
        m_buff[m_head] = item;
        if (++m_head == Size)
            m_head = 0;
        if (++m_count >= m_waitingCount && m_waitingCount) {
            resume_all_isr(m_consumersProcessMap);
            m_waitingCount = 0;
        }
        return true;
    }

    template<typename T, uint32_t Size, typename S>
    bool OS::RingBuffer<T, Size, S>::read( T * data, const S cnt, S * const rd, timeout_t tm ) {
        S count;
        {
            TCritSect cs;
            count = m_count;
        }
        auto result = true;
        if (count < cnt) {
            {
                TCritSect cs;
                m_waitingCount = cnt;
            }
            cur_proc_timeout() = tm;
            suspend(m_consumersProcessMap);
            result = !is_timeouted(m_consumersProcessMap);
            cur_proc_timeout() = 0;
        }
        if (result) {
            TCritSect cs;
            count = m_count;
        }
        count = ( count > cnt ) ? cnt : count;
        if (rd)
            *rd = count;
        while (count--)
            *data++ = pop_item();
        return result;
    }

    template<typename T, uint32_t Size, typename S>
    T OS::RingBuffer<T, Size, S>::pop_item() {
        auto result = m_buff[m_tail];
        m_count--;
        if (++m_tail == Size)
            m_tail = 0;
        return result;
    }

    template<typename T, uint32_t Size, typename S>
    void OS::RingBuffer<T, Size, S>::flush() {
        TCritSect cs;
        m_count = m_head = m_tail = m_waitingCount = 0;
        resume_all(m_producersProcessMap);
    }
};


#endif
