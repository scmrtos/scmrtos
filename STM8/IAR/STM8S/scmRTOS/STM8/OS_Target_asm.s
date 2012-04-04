//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STM8 (STMicroelectronics)
//*
//*     TOOLKIT:   EWSTM8 (IAR Systems)
//*               
//*     PURPOSE:   Target Dependent Low-Level Stuff
//*               
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011-2012

#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"

#include <vregs.inc>

;-------------------------------------------------------------------------------
	module  scmRTOS_Asm

;-------------------------------------------------------------------------------
;	Save/restore MCU registers
;   Not in order of interrupt entry / exit process:
;      save CC first and restore last -- just before RET(F)

save_regs	macro
	push	CC
	// FIXME: Disable interrupts till end of context switch?
	pushw	Y
	pushw	X
	push	A
    endm

restore_regs	macro
	pop	A
	popw	X
	popw	Y
	pop	CC
    endm

;-------------------------------------------------------------------------------
save_virt_regs   macro
	push	?b0
	push	?b1
	push	?b2
	push	?b3
	push	?b4
	push	?b5
	push	?b6
	push	?b7
	push	?b8
	push	?b9
	push	?b10
	push	?b11
	;
	push	?b12
	push	?b13
	push	?b14
	push	?b15
	;
    endm

;-------------------------------------------------------------------------------
restore_virt_regs  macro
	;
	pop	?b15
	pop	?b14
	pop	?b13
	pop	?b12
	;
	pop	?b11
	pop	?b10
	pop	?b9
	pop	?b8
	pop	?b7
	pop	?b6
	pop	?b5
	pop	?b4
	pop	?b3
	pop	?b2
	pop	?b1
	pop	?b0
    endm

;-------------------------------------------------------------------------------
	public  os_start
	public  os_context_switcher

#if __CODE_MODEL__ == __SMALL_CODE_MODEL__
	section `.near_func.text`:CODE:NOROOT(0)
#else
	section `.far_func.text`:CODE:NOROOT(0)
#endif

;-------------------------------------------------------------------------------
; extern "C" void os_context_switcher(stack_item_t** Curr_SP, stack_item_t* Next_SP);


os_context_switcher:
        save_regs
        save_virt_regs

        ldw     Y, SP       ; Next_SP from Y was pushed in 'save_regs' above
        ldw     (X), Y      ; Save Curr_SP
        ldw     X, (20,SP)  ; Get Next_SP
os_start:
        ldw     SP, X

L_RestoreContext:
        restore_virt_regs
        restore_regs
        
#if __CODE_MODEL__ == __SMALL_CODE_MODEL__
	ret
#else
	retf
#endif

;-------------------------------------------------------------------------------

      end
;*******************************************************************************

