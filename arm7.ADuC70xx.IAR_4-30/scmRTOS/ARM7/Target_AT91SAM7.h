//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AT91SAM7xxx (Atmel)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006

#ifndef	TARGET_AT91_H__
#define	TARGET_AT91_H__

#ifdef __IAR_SYSTEMS_ICC__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
// #define used instead of inline function to ensure inlining to both ARM and THUMB functions.
#define	RaiseContextSwitch()                                \
    do                                                      \
    {                                                       \
        AT91C_BASE_AIC->AIC_ISCR = (1<<CONTEXT_SWITCH_INT); \
        AT91C_BASE_AIC->AIC_IECR = (1<<CONTEXT_SWITCH_INT); \
    }                                                       \
    while (0) // set flag and enable interrupt
#endif

#define	IRQ_DONE() do { AT91C_BASE_AIC->AIC_EOICR = 0; } while(0)       // Reset AIC logic                                                      // implemented in asm-wrapper

#define	SYSTEM_TIMER_HANDLER()                                  \
    do                                                          \
    {                                                           \
        volatile dword Tmp = AT91C_BASE_PITC->PITC_PIVR >> 20;  \
        do {                                                    \
            SystemTimer_Handler();                              \
        } while (--Tmp);                                        \
    }                                                           \
    while(0)

#else   // __IAR_SYSTEMS_ASM__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

IRQ_SWITCH  MACRO
        LDR     R1, =AT91C_AIC_IVR
        MOV     LR, PC
        LDR     PC,[R1]                             ; void (*AT91C_AIC_IVR)()
        ENDM

#else   // scmRTOS_CONTEXT_SWITCH_SCHEME == 1
IRQ_SWITCH  MACRO
        LDR     PC, AT91C_AIC_IVR                   ; void (*AT91C_AIC_IVR)()
        ENDM
IRQ_DONE    MACRO
        LDR     R1, =AT91C_AIC_EOICR
        STR     R0, [R1]                            ; reset AIC
        ENDM
#endif  // scmRTOS_CONTEXT_SWITCH_SCHEME

#endif  // __IAR_SYSTEMS_ASM__

#endif  // TARGET_AT91_H__
