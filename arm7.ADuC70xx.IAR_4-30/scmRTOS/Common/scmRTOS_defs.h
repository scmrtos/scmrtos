//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*               
//*     PURPOSE:  Macros And Common Definitions
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

#ifndef scmRTOS_DEFS_H
#define scmRTOS_DEFS_H

#include <commdefs.h>
#include "scmRTOS_config.h"

//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//
//   Macro for Channel Type definition
//
//
#define DefineChannel(Name, Capacity)                                            \
class Name : public OS::TChannel                                                 \
{                                                                                \
public:                                                                          \
    Name() : OS::TChannel(buf, sizeof(buf)) { }                                  \
                                                                                 \
private:                                                                         \
    byte buf[Capacity];                                                          \
                                                                                 \
}
//-----------------------------------------------------------------------------
//
//    Check CONFIG Macro Definitions
//
//

//----------------- scmRTOS_SYSTIMER_NEST_INTS_ENABLE -------------------------
#ifndef scmRTOS_SYSTIMER_NEST_INTS_ENABLE
#error "Error: Config macro scmRTOS_SYSTIMER_NEST_INTS_ENABLE must be defined!"
#endif

#if (scmRTOS_SYSTIMER_NEST_INTS_ENABLE < 0) || (scmRTOS_SYSTIMER_NEST_INTS_ENABLE > 1)
#error "Error: scmRTOS_SYSTIMER_NEST_INTS_ENABLE must have values 0 or 1 only!"
#endif

//----------------- scmRTOS_SYSTEM_TICKS_ENABLE -------------------------------
#ifndef scmRTOS_SYSTEM_TICKS_ENABLE
#error "Error: Config macro scmRTOS_SYSTEM_TICKS_ENABLE must be defined!"
#endif

#if (scmRTOS_SYSTEM_TICKS_ENABLE < 0) || (scmRTOS_SYSTEM_TICKS_ENABLE > 1)
#error "Error: scmRTOS_SYSTEM_TICKS_ENABLE must have values 0 or 1 only!"
#endif


//----------------- scmRTOS_SYSTIMER_HOOK_ENABLE ------------------------------
#ifndef scmRTOS_SYSTIMER_HOOK_ENABLE
#error "Error: Config macro scmRTOS_SYSTIMER_HOOK_ENABLE must be defined!"
#endif

#if (scmRTOS_SYSTIMER_HOOK_ENABLE < 0) || (scmRTOS_SYSTIMER_HOOK_ENABLE > 1)
#error "Error: scmRTOS_SYSTIMER_HOOK_ENABLE must have values 0 or 1 only!"
#endif

//----------------- scmRTOS_IDLE_HOOK_ENABLE ----------------------------------
#ifndef scmRTOS_IDLE_HOOK_ENABLE
#error "Error: Config macro scmRTOS_IDLE_HOOK_ENABLE must be defined!"
#endif

#if (scmRTOS_IDLE_HOOK_ENABLE < 0) || (scmRTOS_IDLE_HOOK_ENABLE > 1)
#error "Error: scmRTOS_IDLE_HOOK_ENABLE must have values 0 or 1 only!"
#endif

//----------------- scmRTOS_CONTEXT_SWITCH_SCHEME -----------------------------
#ifndef scmRTOS_CONTEXT_SWITCH_SCHEME
#error "Error: Config macro scmRTOS_CONTEXT_SWITCH_SCHEME must be defined!"
#endif

#if (scmRTOS_CONTEXT_SWITCH_SCHEME < 0) || (scmRTOS_CONTEXT_SWITCH_SCHEME > 1)
#error "Error: scmRTOS_CONTEXT_SWITCH_SCHEME must have values 0 or 1 only!"
#endif


//----------------- scmRTOS_PRIORITY_ORDER ------------------------------------
#ifndef scmRTOS_PRIORITY_ORDER
#error "Error: Config macro scmRTOS_PRIORITY_ORDER must be defined!"
#endif

#if (scmRTOS_PRIORITY_ORDER < 0) || (scmRTOS_PRIORITY_ORDER > 1)
#error "Error: scmRTOS_PRIORITY_ORDER must have values 0 or 1 only!"
#endif


//-----------------------------------------------------------------------------
//
//    Priority and process map type definitions
//
//
namespace OS
{
    #if scmRTOS_PROCESS_COUNT < 8
        typedef byte TProcessMap;
    #elif scmRTOS_PROCESS_COUNT < 16
        typedef word TProcessMap;
    #else
        typedef dword TProcessMap;
    #endif
    //------------------------------------------------------
#if scmRTOS_PRIORITY_ORDER == 0
    enum TPriority {
        #if scmRTOS_PROCESS_COUNT   > 0
            pr0,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 1
            pr1,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 2
            pr2,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 3
            pr3,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 4
            pr4,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 5
            pr5,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 6
            pr6,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 7
            pr7,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 8
            pr8,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 9
            pr9,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 10
            pr10,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 11
            pr11,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 12
            pr12,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 13
            pr13,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 14
            pr14,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 15
            pr15,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 16
            pr16,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 17
            pr17,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 18
            pr18,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 19
            pr19,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 20
            pr20,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 21
            pr21,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 22
            pr22,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 23
            pr23,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 24
            pr24,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 25
            pr25,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 26
            pr26,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 27
            pr27,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 28
            pr28,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 29
            pr29,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 30
            pr30,
        #endif
        #if (scmRTOS_PROCESS_COUNT   > 31) || (scmRTOS_PROCESS_COUNT   < 1)
            #error "Invalid Process Count specification! Must be from 1 to 31."
        #endif
            prIDLE
    };
#else   // scmRTOS_PRIORITY_ORDER == 1
    enum TPriority {
            prIDLE,
        #if scmRTOS_PROCESS_COUNT   > 30
            pr30,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 29
            pr29,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 28
            pr28,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 27
            pr27,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 26
            pr26,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 25
            pr25,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 24
            pr24,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 23
            pr23,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 22
            pr22,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 21
            pr21,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 20
            pr20,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 19
            pr19,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 18
            pr18,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 17
            pr17,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 16
            pr16,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 15
            pr15,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 14
            pr14,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 13
            pr13,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 12
            pr12,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 11
            pr11,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 10
            pr10,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 9
            pr9,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 8
            pr8,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 7
            pr7,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 6
            pr6,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 5
            pr5,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 4
            pr4,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 3
            pr3,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 2
            pr2,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 1
            pr1,
        #endif
        #if scmRTOS_PROCESS_COUNT   > 0
            pr0
        #endif
        #if (scmRTOS_PROCESS_COUNT   > 31) || (scmRTOS_PROCESS_COUNT   < 1)
            #error "Invalid Process Count specification! Must be from 1 to 31."
        #endif
    };
#endif //scmRTOS_PRIORITY_ORDER
}
//-----------------------------------------------------------------------------

#endif // scmRTOS_DEFS_H
