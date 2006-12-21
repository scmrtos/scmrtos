//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuC 70xx (Analog Devices)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version:   3.00-beta
//*
//*     $Revision: 68 $
//*     $Date: 2006-12-20 19:47:00 +0200 (Ср, 20 дек 2006) $
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006

#ifndef TARGET_ADUC_H__
#define TARGET_ADUC_H__

#if scmRTOS_CONTEXT_SWITCH_SCHEME != 0
#error "The only Direct Context Switch Scheme supported for ADuC!"
#endif

#ifdef  __IAR_SYSTEMS_ICC__

#define IRQ_DONE()                  // No interrupt controller implemented

#define SYSTEM_TIMER_HANDLER()      \
    do                              \
    {                               \
        T0CLRI = 0;                 \
        SystemTimer_Handler();      \
    }                               \
    while (0)

#else   //__IAR_SYSTEMS_ASM__

IRQ_SWITCH  MACRO
        EXTERN      IRQ_Switch
        LDR         R1, =IRQ_Switch
        MOV         LR, PC
        BX          R1
        ENDM
#endif

#endif	// TARGET_ADUC_H__
