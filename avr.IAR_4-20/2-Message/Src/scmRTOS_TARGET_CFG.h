//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   EWAVR (IAR Systems)
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


#define CONTEXT_SWITCH_ISR_VECTOR ANA_COMP_vect

#include <ioavr.h>

#ifndef __IAR_SYSTEMS_ASM__


//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#ifdef  TIMER0_OVF0_vect
#define TIMER0_OVF_vect TIMER0_OVF0_vect
#endif

#define SYSTEM_TIMER_VECTOR TIMER0_OVF_vect
#define LOCK_SYSTEM_TIMER()    ( TIMSK &= ~(1 << TOIE0) )
#define UNLOCK_SYSTEM_TIMER()  ( TIMSK |=  (1 << TOIE0) )

namespace OS
{
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
    #pragma vector=SYSTEM_TIMER_VECTOR
    OS_INTERRUPT void OS_SystemTimer_ISR();
#else
    #pragma vector=SYSTEM_TIMER_VECTOR
    __interrupt void SystemTimer_ISR();
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
}
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

    INLINE inline void RaiseContextSwitch()
    {
        PORTB |= (1 << 3); PORTB &= ~(1 << 3); // set flag
    }
    INLINE inline void BlockContextSwitch() { ACSR &= ~(1 << ACIE); } // disable interrupt

    class TNestedISRW
    {                              
    public:                        
        INLINE TNestedISRW() : State(ACSR) { BlockContextSwitch(); __enable_interrupt(); } 
        INLINE ~TNestedISRW() 
        { 
            __disable_interrupt(); 
            ACSR = State; 
            if(State & (1 << ACI)) RaiseContextSwitch(); 
        }
                                                                             
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

