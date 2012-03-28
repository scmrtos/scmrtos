//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STR71x (ST)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Project Level Target Extensions Config
//*
//*     Version: 3.11
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2012

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#include "device.h"
//------------------------------------------------------------------------------
//
//       Context switching interrupt choosing
//
//
// TIM0 OCMPA interrupt used for context switching.
// This int flag set because timer used as system timer and runs in PWM mode
// This flag never to be cleared, enable bit in EIC->IER cleared instead
// to make this channel always ready to assert int
//     Software interrupts in XTI not used because:
// 1) context switching int handler must be so fast as possible
// 2) it's difficult to share one handler between OS core and user application
//    if required.
#define CONTEXT_SWITCH_INT      STR71X_IRQ_T0_OCMPA

#ifdef __IAR_SYSTEMS_ICC__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//      TIM0 in PWM mode used as system timer
//
#define SYSTEM_TIMER_INT        STR71X_IRQ_T0_OCMPB

#define RESET_SYSTIMER_INT()    do { TIM0->SR = ~(1<<STR71X_TIM_OCFB); } while(0)
#define LOCK_SYSTEM_TIMER()     do { TIM0->CR2 &= ~(1 << STR71X_TIM_OCBIE); } while(0)
#define UNLOCK_SYSTEM_TIMER()   do { TIM0->CR2 |=  (1 << STR71X_TIM_OCBIE); } while(0)

//-----------------------------------------------------------------------------
#endif // __IAR_SYSTEMS_ICC__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

