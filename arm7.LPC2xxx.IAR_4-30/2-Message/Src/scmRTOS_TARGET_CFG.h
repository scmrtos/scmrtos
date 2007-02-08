//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: LPC2xxx (NXP)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Project Level Target Extensions Config
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
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

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#include "device.h"

#define	CONTEXT_SWITCH_INT      VIC_SW

#ifndef __IAR_SYSTEMS_ASM__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#define SYSTEM_TIMER_INT        VIC_TIMER0

namespace OS
{
    OS_INTERRUPT void SystemTimer_ISR();
}

//  TIMER0 used as System timer
#define LOCK_SYSTEM_TIMER()     do { T0MCR_bit.MR0INT = 0; } while(0)
#define UNLOCK_SYSTEM_TIMER()   do { T0MCR_bit.MR0INT = 1; } while(0)

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

#define ENABLE_NESTED_INTERRUPTS()
}
//-----------------------------------------------------------------------------
#endif // __IAR_SYSTEMS_ASM__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

