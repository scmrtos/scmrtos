
/* This file is part of libgcc.S from mspgcc v3.3.
   Here is original copyright text:
*/

/*   Low-level subroutines for Texas Instruments MSP430 MCU
   Copyright (C) 2001, 2002, 2003 Free Software Foundation, Inc.
   Contributed by Dmitry Diky <diwil@mail.ru>

   This file is part of GCC.
   GCC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
   
   In addition to the permissions in the GNU General Public License, the
   Free Software Foundation gives you unlimited permission to link the
   compiled version of this file into combinations with other programs,
   and to distribute those combinations without any restriction coming
   from the use of this file.  (The General Public License restrictions
   do apply in other respects; for example, they cover modification of
   the file, and distribution when not linked into a combine
   executable.)

   GNU CC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#endif /* GCC_VERSION */

#if (GCC_VERSION > 3002)
#warning "THIS FILE IS NOT NEEDED WITH GCC > 3.2
#endif


/******* CRT support functions *********/

#if defined(L__stop_progExec__)

	.section .fini9, "ax", @progbits
	.global __stop_progExec__
	.func  __stop_progExec__
__stop_progExec__:
	push 	r15

	
	.section .fini0, "ax", @progbits
	
	pop	r15
__stop_progLoop:
	bis	r15, r2
	jmp	__stop_progLoop
	.endfunc
#endif	/* #if defined(L__stop_progExec__) */

#if defined(L_reset_vector__)
/*****************************************************************
 * Initialize data: copy data from _etext to __data_start
 * Can be overwritten.
 *****************************************************************/
	.extern _etext
	.extern __data_start
	.extern _edata
	.extern __bss_start
	.extern __bss_end
	.extern __stack

	.section .init0, "ax", @progbits

	.global	_reset_vector__
.func _reset_vector__
_reset_vector__:
	mov	#23168, &288	

	.section .init2, "ax", @progbits
	.global _copy_data_init__
	.weak   _copy_data_init__

_copy_data_init__:
	mov     #_etext,	r15     ; load r15 with end of .text segment
	mov     #__data_start,  r14     ; load ram start
	mov     #_edata,	r13     ; end of data segment
	cmp     r14,	    r13
	jeq     .Lend_of_data_loop 
.Lcopy_data_loop:  
	/* copy data from @r15 to @r14 */
	mov.b   @r15+,  @r14	    ; move one byte
	inc     r14
	cmp     r13,    r14	     ; check if end of data reached
	jlo     .Lcopy_data_loop
.Lend_of_data_loop:

	.section .init4, "ax", @progbits
	.global _clear_bss_init__
	.weak   _clear_bss_init__
	
_clear_bss_init__:
	mov     #__bss_start,   r15
	mov     #__bss_end,     r13
	cmp     r15,	    r13
	jeq     .Lend_of_bss_loop  
.Lzero_bss_loop:
	clr.b   @r15
	inc     r15 
	cmp     r13,    r15     ; check if r15 < r13
	jlo     .Lzero_bss_loop
.Lend_of_bss_loop:
	
	.section .init9, "ax", @progbits
	.global _end_of_init__
	.weak   _end_of_init__
	
_end_of_init__:
	br      #main	;	jump to main procedure
.endfunc
#endif


#ifdef L_ctors
	.section .init6,"ax",@progbits
	.global __do_global_ctors
	
__do_global_ctors:
	mov	#__stack, r1	; load stack... might be dangerous!!! 
	mov	#__ctors_start,	r11
	mov	#__ctors_end, r10
	cmp	r10, r11
	jeq	.L__ctors_end
.L__ctors_loop:
	call	@r11	; call constructor
	incd	r11
	cmp	r10, r11
	jne	.L__ctors_loop
.L__ctors_end:
#endif

#ifdef L_dtors
	.section .fini6,"ax",@progbits
	.global __do_global_dtors
__do_global_dtors:
	mov	#__dtors_start, r11
	mov	#__dtors_end, r10
	cmp	r10, r11
	jeq	.L__dtors_end
.L__dtors_loop:
	call	@r11
	incd	r11
	cmp	r10, r11
	jne	.L__dtors_loop
.L__dtors_end:
#endif
