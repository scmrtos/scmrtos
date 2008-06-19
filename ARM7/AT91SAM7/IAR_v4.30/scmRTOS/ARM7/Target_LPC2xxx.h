//******************************************************************************
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
//*     Version: 3.05
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2008

#ifndef TARGET_LPC2XXX_H__
#define TARGET_LPC2XXX_H__

#ifdef __IAR_SYSTEMS_ICC__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
    #define OS_INTERRUPT __arm
#else
    #define OS_INTERRUPT __arm __irq
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
// #define used instead of inline function to ensure inlining to both ARM and THUMB functions.
#define RaiseContextSwitch()                        \
    do                                              \
    {                                               \
        VICSoftInt = (1<<CONTEXT_SWITCH_INT);       \
    }                                               \
    while (0) // set flag and enable interrupt
#endif

#define IRQ_DONE()  do { VICVectAddr = 0; } while(0)    // Reset VIC logic

#define SYSTEM_TIMER_HANDLER()  \
    do                          \
    {                           \
        RESET_SYSTIMER_INT();   \
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
