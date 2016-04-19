//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   avr-gcc (GNU)
//*
//*     PURPOSE:   Target Dependent Low-Level Stuff
//*
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007-2016

.nolist

#include <avr/io.h>

#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"
#include "os_target.h"  // SAVE_EIND & Co

.list

;-------------------------------------------------------------------------------
;
#if FLASHEND > 0x1FFF
  #define XJMP jmp
  #define XCALL call
#else
  #define XJMP rjmp
  #define XCALL rcall
#endif


;-------------------------------------------------------------------------------
;  r1 is used as __zero_reg__ so the register is saved first (and is used for SFR saving) 
;  for easier stack image initialisation in TBaseProcess constructor.
;
.macro push_sfr addr
	in	r1, \addr
	push	r1
.endm

.macro pop_sfr addr
	pop	r1
	out	\addr, r1
.endm

.macro	save_context

        push	r1			; save r1 value
        push_sfr _SFR_IO_ADDR(SREG)	;

    #ifdef SAVE_RAMPZ
	push_sfr _SFR_IO_ADDR(RAMPZ)
    #endif
    #ifdef SAVE_EIND
	push_sfr _SFR_IO_ADDR(EIND)
    #endif

        push	r0
        ; r1 is saved before SREG
        push	r2
        push	r3
        push	r4
        push	r5
        push	r6
        push	r7
        push	r8
        push	r9
        push	r10
        push	r11
        push	r12
        push	r13
        push	r14
        push	r15
        push	r16
        push	r17
        push	r18
        push	r19
        push	r20
        push	r21
        push	r22
        push	r23
        push	r24
        push	r25
        push	r26
        push	r27
        push	r28
        push	r29
        push	r30
        push	r31

     .endm

;-------------------------------------------------------------------------------
.macro	restore_context

        pop	r31
        pop	r30
        pop	r29
        pop	r28
        pop	r27
        pop	r26
        pop	r25
        pop	r24
        pop	r23
        pop	r22
        pop	r21
        pop	r20
        pop	r19
        pop	r18
        pop	r17
        pop	r16
        pop	r15
        pop	r14
        pop	r13
        pop	r12
        pop	r11
        pop	r10
        pop	r9
        pop	r8
        pop	r7
        pop	r6
        pop	r5
        pop	r4
        pop	r3
        pop	r2
        ; r1 will be restored after SREG
        pop	r0

    #ifdef SAVE_EIND
	pop_sfr	_SFR_IO_ADDR(EIND)
    #endif
    #ifdef SAVE_RAMPZ
	pop_sfr	_SFR_IO_ADDR(RAMPZ)
    #endif

        pop_sfr	_SFR_IO_ADDR(SREG)
        pop	r1			; restore r1 value

     .endm

;-------------------------------------------------------------------------------
     .text


;-------------------------------------------------------------------------------
     .global	os_start

os_start:
	out	_SFR_IO_ADDR(SPH), r25	; set next process Stack Pointer
	out	_SFR_IO_ADDR(SPL), r24
	rjmp L_RestoreContext

;-------------------------------------------------------------------------------
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

	.global	os_context_switcher
os_context_switcher:
	save_context

    #ifdef __AVR_ENHANCED__
	movw	r30,r24		        ; Curr_SP_addr
    #else
	mov	r30,r24
	mov	r31,r25
    #endif

	in	r24,_SFR_IO_ADDR(SPL)   ; load current stack pointer
	in	r25,_SFR_IO_ADDR(SPH)
	std	Z+0,r24		        ; save current process's Stack Pointer
	std	Z+1,r25		        ;
	out	_SFR_IO_ADDR(SPH), r23	; set new process's Stack Pointer
	out	_SFR_IO_ADDR(SPL), r22

L_RestoreContext:
	restore_context
	ret

;-------------------------------------------------------------------------------
#else

	.extern	os_context_switch_hook
	.global CONTEXT_SWITCH_ISR_VECTOR

CONTEXT_SWITCH_ISR_VECTOR:
	save_context

	in	r24,_SFR_IO_ADDR(SPL)	; load current stack pointer
	in	r25,_SFR_IO_ADDR(SPH)	; as argument
	XCALL os_context_switch_hook
	out	_SFR_IO_ADDR(SPH), r25	; set next stack pointer
	out	_SFR_IO_ADDR(SPL), r24	; from return value

L_RestoreContext:
	restore_context
	reti

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
;-------------------------------------------------------------------------------

      .end
;*******************************************************************************
