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
//*     PURPOSE:   Watchdog Extension Definitions
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


#ifndef WATHDOGOSEXT_H
#define WATHDOGOSEXT_H
#include <scmRTOS.h>

namespace OS {
    // Declare these hook in your code
    void wdg_init_user_hook();          // this hook setup needed hardware, internal watchdog, for example
    void wdg_force_reboot_user_hook( const TPriority  pr );  // this hook forces to reboot the system immideately
    void wdg_feed_user_hook();          // this hook feeds the watchdog

    class WatchdogExtension : public TKernelAgent {
    public:
        WatchdogExtension()
            : m_asleep(0) {
            wdg_init_user_hook();
            for ( auto &it : m_table )
                it.p = nullptr;
        }

        // use this method to register task that is under watchdog
        INLINE void register_process( const OS::TBaseProcess &proc, const timeout_t timeout ) {
            TItem &item = get_proc_item(proc.priority());
            item.p                = &proc;
            item.initialTimeout   = timeout;
            item.timeout          = timeout;
        }

        // call asleep() ONLY before your task sleeps for unknow time
        // CALL alive() just as your task is awakend. If you call asleep() in such case (twice)
        // the system will be rebooted
        // if you call it for unregistered task an immediate reset will occur
        INLINE void asleep() {
            TCritSect cs;
            TItem &item = get_current_proc_item();
            const TProcessMap tag = get_prio_tag(cur_proc_priority());
            if (item.p == nullptr || m_asleep & tag) { // if call asleep() twice
                wdg_force_reboot_user_hook(item.p->priority());
                while (1);
            }
            m_asleep |= tag;
        }

        // call alive() within the allowed timeout of your task
        // if you call it for unregistered task an immediate reset will occur
        // if you call it just after asleep() it only clear 'alseep' state and timeout decrementing
        // resumes, you must call it second time within allowed timeout
        INLINE void alive() {
            TCritSect cs;
            TItem &item = get_current_proc_item();
            if (item.p == nullptr) {
                wdg_force_reboot_user_hook(item.p->priority());
                while (1);
            }
            const TProcessMap tag = get_prio_tag(cur_proc_priority());
            if (m_asleep & tag) { // if call after asleep()
                m_asleep &= ~tag;
                return;
            }
            item.timeout = item.initialTimeout;
        }

        // call this method every system timer tick, period of systick interrupt must be
        // lower than hardware watchdog period
        INLINE void tick() {
            for ( auto &it : m_table ) {
                if (it.p == nullptr) // no task is registerd, skip it
                    continue;
                if (it.timeout == 0 || // may be some process corrupt this variable?
                    it.initialTimeout == 0 || // or this variable has been affected
                    ( it.timeout > it.initialTimeout )) { // timeout can't be grater than its initial value
                    TCritSect cs;
                    wdg_force_reboot_user_hook(it.p->priority());
                    while (1);
                }
                const TProcessMap tag = get_prio_tag(it.p->priority());
                if (m_asleep & tag) // task is in asleep mode, it can be there forever((
                    continue;
                if (--it.timeout == 0) {
                    TCritSect cs;
                    wdg_force_reboot_user_hook(it.p->priority());
                    while (1);
                }
            }
            wdg_feed_user_hook();
        }

    private:
        struct TItem {
            const OS::TBaseProcess *    p;
            timeout_t                   initialTimeout;
            timeout_t                   timeout;
        };

        TItem &get_current_proc_item() {
            return get_proc_item(static_cast<TPriority>(cur_proc_priority()));
        }

        TItem &get_proc_item( const TPriority pr ) {
            return m_table[pr];
        }

        TItem       m_table[scmRTOS_PROCESS_COUNT+1]; // +1 means slot for IDLE task
        TProcessMap m_asleep;
    };
};


#endif
