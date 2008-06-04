//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   mspgcc (GNU)
//*
//*     PURPOSE:   Target Dependent Low-Level Stuff
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
//*     mspgcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2008

.nolist

#include <io.h>

#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"

.list


;-------------------------------------------------------------------------------
.macro	save_regs

     push     r4
     push     r5
     push     r6
     push     r7
     push     r8
     push     r9
     push     r10
     push     r11
     push     r12
     push     r13
     push     r14
     push     r15

.endm

;-------------------------------------------------------------------------------
.macro	restore_regs

     pop      r15
     pop      r14
     pop      r13
     pop      r12
     pop      r11
     pop      r10
     pop      r9
     pop      r8
     pop      r7
     pop      r6
     pop      r5
     pop      r4

.endm
;-------------------------------------------------------------------------------

     .text


;-------------------------------------------------------------------------------
     .global	OS_Start

OS_Start:
     mov.w  r15,r1				; put arg into SP
     jmp    L_RestoreContext

;-------------------------------------------------------------------------------
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

	.global	OS_ContextSwitcher
OS_ContextSwitcher:		; void OS_ContextSwitcher(TStackItem** Curr_SP, TStackItem* Next_SP)
     push r2
     save_regs

     mov.w   r1,0(r15)	; save SP to *Curr_SP
     mov.w   r14,r1		; SP = Next_SP

L_RestoreContext:
     restore_regs
     reti

;-------------------------------------------------------------------------------
#else

    .extern OS_ContextSwitchHook
    .global	ContextSwitcher_ISR

interrupt (CONTEXT_SWITCH_ISR_VECTOR)
ContextSwitcher_ISR:
    save_regs
    mov   r1,r15
    call  #OS_ContextSwitchHook
    mov   r15,r1
L_RestoreContext:
    restore_regs
    reti

#endif
;-------------------------------------------------------------------------------

     .end
;*******************************************************************************
