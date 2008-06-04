//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   avr-gcc (GNU)
//*
//*     PURPOSE:   Project Level Target Extensions Config
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date::             $
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#include <avr/io.h>
#include <avr/interrupt.h>


#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

#  if defined(SPMCSR)
#    define SPM_CONTROL_REG SPMCSR
#  elif defined(SPMCR)
#    define SPM_CONTROL_REG SPMCR
#  else
#    error "SPM control register not defined"
#  endif

#  if defined(SPM_READY_vect)
#    define CONTEXT_SWITCH_ISR_VECTOR  SPM_READY_vect
#  elif defined(SPM_RDY_vect)
#    define CONTEXT_SWITCH_ISR_VECTOR  SPM_RDY_vect
#  else
#    error "SPM ready interrupt vector not defined"
#  endif

#endif

#ifndef __ASSEMBLER__

//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#if defined(TIMER0_OVF0_vect)
#  define SYSTEM_TIMER_VECTOR TIMER0_OVF0_vect
#elif defined(TIMER0_OVF_vect)
#  define SYSTEM_TIMER_VECTOR TIMER0_OVF_vect
#else
#  error "Timer0 overflow vector not defined"
#endif

#if defined(TIMSK0)
#  define TIMSK0_REG TIMSK0
#elif defined(TIMSK)
#  define TIMSK0_REG TIMSK
#else
#  error "Timer0 interrupt mask register not defined"
#endif

#define LOCK_SYSTEM_TIMER()    ( TIMSK0_REG &= ~(1 << TOIE0) )
#define UNLOCK_SYSTEM_TIMER()  ( TIMSK0_REG |=  (1 << TOIE0) )


//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//   SPM_READY interrupt is the lowest possible priority interrupt. Moreover, it is rarely
// or even never used in application section. So, this interrupt is ideal solution for
// software interrupt emulation.
//   By default SPM_READY interrupt perform the context switching, enabling the interrupt
//  will force context switching.
//  But SPM_READY interrupt must be disabled manually when switching ends, so
//  we provide CONTEXT_SWITCH_END macro (see below).
//  CONTEXT_SWITCH_END used inside CONTEXT_SWITCH_ISR_VECTOR handler (see OS_Target_asm.S)
//  You can change or delete the macro if you are use another vector for context switching.
//
namespace OS
{
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

    INLINE inline void RaiseContextSwitch() { SPM_CONTROL_REG |= (1 << SPMIE);  } // enable SPM interrupt

    INLINE inline void BlockContextSwitch() { SPM_CONTROL_REG &= ~(1 << SPMIE); } // disable SPM interrupt

    class TNestedISRW
    {
    public:
        INLINE TNestedISRW() : State(SPM_CONTROL_REG) { BlockContextSwitch(); sei(); }
        INLINE ~TNestedISRW()
        {
            cli();
            SPM_CONTROL_REG = State;
        }
    private:
        byte State;
    };

    #define ENABLE_NESTED_INTERRUPTS() OS::TNestedISRW NestedISRW

#else

    #define ENABLE_NESTED_INTERRUPTS() sei()

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
}

//-----------------------------------------------------------------------------

#else // __ASSEMBLER__


#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

#  if _SFR_IO_REG_P(SPM_CONTROL_REG)
#    define CONTEXT_SWITCH_END \
	in r16, _SFR_IO_ADDR(SPM_CONTROL_REG) $\
	andi r16, lo8(~(1 << SPMIE)) $\
	out _SFR_IO_ADDR(SPM_CONTROL_REG), r16
#  else
#    define CONTEXT_SWITCH_END \
	lds r16, _SFR_MEM_ADDR(SPM_CONTROL_REG) $\
	andi r16, lo8(~(1 << SPMIE)) $\
	sts _SFR_MEM_ADDR(SPM_CONTROL_REG), r16
#  endif

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

#endif // __ASSEMBLER__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------
