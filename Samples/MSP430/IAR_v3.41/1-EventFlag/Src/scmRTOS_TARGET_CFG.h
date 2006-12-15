//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   EW430 (IAR Systems)
//*
//*     PURPOSE:   Project Level Target Extensions Config
//*
//*     Version:   3.00-beta
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

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#include "device.h"

#define CONTEXT_SWITCH_ISR_VECTOR COMPARATORA_VECTOR

#ifndef __IAR_SYSTEMS_ASM__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#define SYSTEM_TIMER_VECTOR WDT_VECTOR

namespace OS
{
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
    #pragma vector=SYSTEM_TIMER_VECTOR
    OS_INTERRUPT void SystemTimer_ISR();
#else
    #pragma vector=SYSTEM_TIMER_VECTOR
    __interrupt void SystemTimer_ISR();
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
}

#define  LOCK_SYSTEM_TIMER()    ( IE1 &= ~0x01 )
#define  UNLOCK_SYSTEM_TIMER()  ( IE1 |=  0x01 )
//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//
namespace OS
{
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

    INLINE inline void RaiseContextSwitch() { CACTL1 |=  0x03; } // set flag and enable interrupt

    class TNestedISRW              
    {                              
    public:                        
        TNestedISRW() : State(CACTL1) { CACTL1 &= ~0x03; __enable_interrupt(); } 
        ~TNestedISRW() { __disable_interrupt(); CACTL1 = State; }              
                                                                             
    private:                                                                 
        byte State;                                                          
    };

    #define ENABLE_NESTED_INTERRUPTS() OS::TNestedISRW NestedISRW

#else

    #define ENABLE_NESTED_INTERRUPTS() __enable_interrupt()

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

}
//-----------------------------------------------------------------------------
#endif // __IAR_SYSTEMS_ASM__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

