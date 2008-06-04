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
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2007, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2007

#ifndef TARGET_STR7XX_H__
#define TARGET_STR7XX_H__

#ifdef __IAR_SYSTEMS_ICC__

#undef  OS_INTERRUPT    // STR7xx has very funny interrupt controller
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
    #define OS_INTERRUPT                        \
        _Pragma("segment=\"INT_HANDLERS\"")     \
        _Pragma("location=\"INT_HANDLERS\"")    \
        __arm
#else
    #define OS_INTERRUPT                        \
        _Pragma("segment=\"INT_HANDLERS\"")     \
        _Pragma("location=\"INT_HANDLERS\"")    \
        __arm __irq
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
// #define used instead of inline function to ensure inlining to both ARM and THUMB functions.
#define RaiseContextSwitch()                                \
    do                                                      \
    {                                                       \
        EIC->IER |= (1<<CONTEXT_SWITCH_INT);                \
    }                                                       \
    while (0) // enable interrupt. flag always set normally
#endif

#define IRQ_DONE() do { EIC->IPR = (1 << EIC->CICR); } while(0)     // Reset AIC logic

#define	SYSTEM_TIMER_HANDLER()                  \
    do                                          \
    {                                           \
        RESET_SYSTIMER_INT();                   \
        SystemTimer_Handler();                  \
    }                                           \
    while(0)

#else   // __IAR_SYSTEMS_ASM__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

IRQ_SWITCH  MACRO
        LDR     R1, =STR71X_EIC_IVR
        MOV     LR, PC
        LDR     PC,[R1]                             ; void (*EIC_IVR)()
        ENDM

#else   // scmRTOS_CONTEXT_SWITCH_SCHEME == 1
IRQ_SWITCH  MACRO
        LDR     PC, STR71X_EIC_IVR                  ; void (*EIC_IVR)()
        ENDM
IRQ_DONE    MACRO                                   ; do not corrupt R0 contens!!!
        LDR     R1, =STR71X_EIC_IPR
        MOV     R2, #1
        MOV     R2, R2, LSL #CONTEXT_SWITCH_INT             ; (1 << CONTEXT_SWITCH_INT)
        LDR     R3, [R1, #STR71X_EIC_IER - STR71X_EIC_IPR]
        BIC     R3, R3, R2
        STR     R3, [R1, #STR71X_EIC_IER - STR71X_EIC_IPR]  ; EIC->IER &= ~(1 << CONTEXT_SWITCH_INT)

        STR     R2, [R1]                                    ; EIC->IPR = (1 << CONTEXT_SWITCH_INT)
        ENDM
#endif  // scmRTOS_CONTEXT_SWITCH_SCHEME

#endif  // __IAR_SYSTEMS_ASM__

#endif  // TARGET_STR7XX_H__
