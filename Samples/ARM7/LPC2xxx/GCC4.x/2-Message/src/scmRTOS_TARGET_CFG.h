//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: LPC2xxx (NXP)
//*
//*     TOOLKIT:   GCC
//*
//*     PURPOSE:   Project Level Target Extensions Config
//*
//*     Version: 3.10
//*
//*     $Revision: 256 $
//*     $Date:: 2010-01-22 #$
//*
//*     Copyright (c) 2003-2010, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2010
//*     lpc2xxx GCC parts by Anton B. Gusev aka AHTOXA, Copyright (c) 2010

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#include "device.h"

//------------------------------------------------------------------------------
//
//       Context switching interrupt choosing
//
//
#define VIC_SW                  1
#define CONTEXT_SWITCH_INT      VIC_SW

#ifndef __ASSEMBLER__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//  TIMER0 used as System timer
//
#define VIC_TIMER0              4
#define SYSTEM_TIMER_INT        VIC_TIMER0

#define T0MCR_MR0I              0x00000001UL

#define RESET_SYSTIMER_INT()    do { T0IR = T0IR; } while(0)
#define LOCK_SYSTEM_TIMER()     do { T0MCR &= ~T0MCR_MR0I; } while(0)
#define UNLOCK_SYSTEM_TIMER()   do { T0MCR |= T0MCR_MR0I; } while(0)

//-----------------------------------------------------------------------------
#endif // __ASSEMBLER__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

