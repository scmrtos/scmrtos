//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Project Level Configuration
//*
//*     Version:   3.00-beta
//*
//*     $Revision: 39 $
//*     $Date: 2006-12-17 17:46:00 +0200 (Вс, 17 дек 2006) $
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
//*     Copyright (c) 2005-2006, Sergey A. Borshch
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

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

#ifndef __IAR_SYSTEMS_ASM__
#include <commdefs.h>
typedef word TTimeout;
#endif // __IAR_SYSTEMS_ASM__

#include "device.h"
//------------------------------------------------------------------------------
//
//    Specify scmRTOS Process Count. Must be less then 31
//
//
#define  scmRTOS_PROCESS_COUNT                  3

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer
//
//    Nested Interrupts Enable macro. Value 1 means that interrupts are
//    globally enabled within System Timer ISR.
//
//
#define  scmRTOS_SYSTIMER_NEST_INTS_ENABLE  1

//-----------------------------------------------------------------------------
//
//    ISR Wrapper type used in System Timer ISR
//    There are two types: TISRW and TISRW_SS.
//
//    TISRW : Plain ISR Wrapper, does not switch SP to separate ISR stack.
//            Suitable for processors that have hardware-switched ISR stack,
//            or in such ISRs where stack consumption is acceptable
//
//    TISRW_SS : ISR Wrapper with separate ISR stack software switching
//

#define scmRTOS_ISRW_TYPE TISRW_SS

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Tick Counter Enable
//
//
#define  scmRTOS_SYSTEM_TICKS_ENABLE        1


//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Hook
//
//
#define  scmRTOS_SYSTIMER_HOOK_ENABLE       1

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Hook
//
//
#define  scmRTOS_IDLE_HOOK_ENABLE           1

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Stack size (in bytes)
//
//
#define scmRTOS_IDLE_PROCESS_STACK_SIZE       0

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch Scheme
//
//    The macro defines a context switch manner. Value 0 sets direct context
//    switch in the scheduler and in the OS ISRs. This is the primary method.
//    Value 1 sets the second way to switch context - by using of software
//    interrupt. See documentation fo details.
//
//
#define  scmRTOS_CONTEXT_SWITCH_SCHEME 1
//-----------------------------------------------------------------------------
//
//    scmRTOS Priority Order
//
//    This macro defines the order of the process's priorities. Default,
//    the ascending order is used. Alternatively, the descending priority
//    order can be used. On some platforms the descending order is preferred
//    because of performance.
//
//    Default (corresponding to ascending order) value of macro is 0.
//    Alternative (corresponding to descending order) value of macro is 1.
//
//
#define  scmRTOS_PRIORITY_ORDER 0

//-----------------------------------------------------------------------------

#endif // scmRTOS_CONFIG_H
//-----------------------------------------------------------------------------

