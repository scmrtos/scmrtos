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
//*     Version: 5.0.0
//*
//*
//*     Copyright (c) 2003-2015, scmRTOS Team
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
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*     mspgcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2008-2015

.nolist

#include "scmRTOS_CONFIG.h"

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
     .p2align 1,0

;-------------------------------------------------------------------------------
     .global	os_start

os_start:
     mov.w  r15,r1				; put arg into SP

     restore_regs
     reti

;-------------------------------------------------------------------------------
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

	.global	os_context_switcher
; void os_context_switcher(stack_item_t** Curr_SP, stack_item_t* Next_SP)
os_context_switcher:
     push r2
     save_regs

     mov.w   r1,0(r15)	; save SP to *Curr_SP
     mov.w   r14,r1		; SP = Next_SP

     restore_regs
     reti

#endif
;-------------------------------------------------------------------------------

     .end
;*******************************************************************************
