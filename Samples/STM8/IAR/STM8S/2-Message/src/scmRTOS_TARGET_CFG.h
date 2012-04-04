//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STM8 (STMicroelectronics)
//*
//*     TOOLKIT:   EWSTM8 (IAR Systems)
//*
//*     PURPOSE:   STM8/IAR Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011-2012

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#ifndef __IAR_SYSTEMS_ASM__

#include "stm8_target.h"

//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#define SYSTEM_TIMER_VECTOR        ITC_IRQ_TIM4_OVF
#define SYSTEM_TIMER_FLAG_CLEAR() (TIM4->SR1 &= ~TIM4_SR1_UIF)
#define LOCK_SYSTEM_TIMER()       (TIM4->IER &= ~TIM4_IER_UIE)
#define UNLOCK_SYSTEM_TIMER()     (TIM4->IER |= TIM4_IER_UIE)

namespace OS
{
    // FIXME: Is forward declaration needed here at all?
    INTERRUPT_HANDLER( OS_SystemTimer_ISR, SYSTEM_TIMER_VECTOR);
}

//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//
namespace OS
{

// The only option supported
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

    #define ENABLE_NESTED_INTERRUPTS()  enable_interrupts()
    #define DISABLE_NESTED_INTERRUPTS() disable_interrupts()

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
}
//-----------------------------------------------------------------------------
#else  // __IAR_SYSTEMS_ASM__


#endif // __IAR_SYSTEMS_ASM__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------
