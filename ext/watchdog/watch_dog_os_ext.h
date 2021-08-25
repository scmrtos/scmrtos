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
        WatchdogExtension() {
            wdg_init_user_hook();
            for ( auto &it : m_table )
                it.p = nullptr;
        }

        // use this method to register task that is under watchdog
        void register_process( const OS::TBaseProcess &proc, const timeout_t timeout );
        // call asleep() ONLY before your task sleeps for unknow time
        // CALL alive() just as your task is awakend. If you call asleep() in such case (twice)
        // the system will be rebooted
        // if you call it for unregistered task an immediate reset will occur
        INLINE void asleep();
        // call this method within the allowed timeout of your task
        // if you call it for unregistered task an immediate reset will occur
        INLINE void alive();
        // call this method every system timer tick
        INLINE void run();

    private:
        struct TItem {
            const OS::TBaseProcess *    p;
            timeout_t                   initialTimeout;
            timeout_t                   timeout;
        };

        TItem &get_proc_item( const TPriority pr );
        TItem &get_current_proc_item();

        TItem   m_table[scmRTOS_PROCESS_COUNT+1];
    };

    void WatchdogExtension::register_process( const OS::TBaseProcess &proc, const timeout_t timeout ) {
        TItem &item = get_proc_item(proc.priority());
        item.p                = &proc;
        item.initialTimeout   = timeout;
        item.timeout          = timeout;
    }

    void WatchdogExtension::asleep() {
        TCritSect cs;
        TItem &item = get_current_proc_item();
        if (item.p == nullptr || item.timeout == 0) { // if call asleep() twice
            wdg_force_reboot_user_hook(item.p->priority());
            while (1);
        }
        item.timeout = 0;
    }

    void WatchdogExtension::alive() {
        TCritSect cs;
        TItem &item = get_current_proc_item();
        if (item.p == nullptr) {
            wdg_force_reboot_user_hook(item.p->priority());
            while (1);
        }
        if (item.timeout == 0) { // if call after asleep() after some event has been received
            item.timeout = item.initialTimeout;
            return;
        }
        item.timeout = item.initialTimeout;
    }

    void WatchdogExtension::run() {
        for ( auto &it : m_table ) {
            if (it.p == nullptr)
                continue;
            if (it.timeout == 0)
                continue;
            if (--it.timeout == 0) {
                TCritSect cs;
                wdg_force_reboot_user_hook(it.p->priority());
                while (1);
            }
        }
        wdg_feed_user_hook();
    }

    WatchdogExtension::TItem &WatchdogExtension::get_current_proc_item() {
        return get_proc_item(static_cast<TPriority>(cur_proc_priority()));
    }

    WatchdogExtension::TItem &WatchdogExtension::get_proc_item( const TPriority pr ) {
        return m_table[pr];
    }
};


#endif
