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
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version:   3.00-beta
//*
//*     $Revision: 60 $
//*     $Date: 2006-12-20 16:12:56 +0200 (Ср, 20 дек 2006) $
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

#ifndef	TARGET_LPC2XXX_H__
#define	TARGET_LPC2XXX_H__

#ifdef __IAR_SYSTEMS_ICC__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
// #define used instead of inline function to ensure inlining to both ARM and THUMB functions.
#define	RaiseContextSwitch()                        \
    do                                              \
    {                                               \
        VICSoftInt = (1<<CONTEXT_SWITCH_INT);       \
        VICIntEnable = (1<<CONTEXT_SWITCH_INT);     \
    }                                               \
    while (0) // set flag and enable interrupt
#endif

#define	IRQ_DONE()	do { VICVectAddr = 0; } while(0)    // Reset VIC logic

#define	SYSTEM_TIMER_HANDLER()  \
    do                          \
    {                           \
        T0IR = T0IR;            \
        SystemTimer_Handler();  \
    }                           \
    while(0)

#else   //__IAR_SYSTEMS_ASM__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
IRQ_SWITCH  MACRO                                              ; call interrupt handler
        LDR     R1,=VICVectAddr
        MOV     LR, PC
        LDR     PC,[R1]
        ENDM
#else   // scmRTOS_CONTEXT_SWITCH_SCHEME == 1
IRQ_SWITCH  MACRO                                              ; call interrupt handler
        LDR     PC, VICVectAddr
        ENDM

IRQ_DONE    MACRO                                               ; reset interrupt controller
        LDR     R1, =VICVectAddr
        MOV     R2, #(1 << CONTEXT_SWITCH_INT)
        STR     R2, [R1, #VICSoftIntClear - VICVectAddr]        ; clear soft int request
        STR     R1, [R1]                                        ; reset VIC
        ENDM
#endif  // scmRTOS_CONTEXT_SWITCH_SCHEME

#endif  //__IAR_SYSTEMS_ASM__

#endif  // TARGET_LPC2XXX_H__
