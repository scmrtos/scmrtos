//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-A9
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Target Dependent Low-Level Stuff
//*
//*     Version: v5.2.0
//*
//*
//*     Copyright (c) 2003-2021, scmRTOS Team
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
//*     Cortex-A9 GCC port by Harry E. Zhurov, Copyright (c) 2024-2025

.syntax unified

.global __vector_table
.global os_start

.extern irq_handler
.extern os_context_switch_hook

.org 0
.text

//------------------------------------------------------------------------------
.section .vectors
__vector_table:
    b       __start
    b       undefined
    b       process_switch_exc
    b       prefetch_abort
    b       data_abort
    nop                               // Placeholder for address exception vector
    b       interrupt_request_exc

.section .exhandlers
    // FIQ exception handler, do nothing for now
    nop
    subs    pc, lr, #4                // return from FIQ

//------------------------------------------------------------------------------
undefined:
    stmdb   sp!,{r0-r3,r12,lr}
    ldr     r0, =undefined_exception_addr
    sub     r1, lr, #4
    str     r1, [r0]                  // store address of instruction causing undefined exception

    bl      undefined_exception
    ldmia   sp!,{r0-r3,r12,lr}
    movs    pc, lr
//------------------------------------------------------------------------------
data_abort:
    dsb                               // ARM ERRATA 775420: data cache maintenance operation which aborts, might lead to deadlock

    stmdb   sp!,{r0-r3,r12,lr}
    ldr     r0, =data_abort_addr
    sub     r1, lr, #8
    str     r1, [r0]                  // stores instruction causing data abort

    bl      data_abort_exception

    ldmia   sp!,{r0-r3,r12,lr}

    subs    pc, lr, #8                // LR adjustment for Data Abort: points to the instruction that caused the exception
//------------------------------------------------------------------------------
prefetch_abort:
    dsb                               // ARM ERRATA 775420: data cache maintenance operation which aborts, might lead to deadlock

    stmdb   sp!,{r0-r3,r12,lr}
    ldr     r0, =prefetch_abort_addr
    sub     r1, lr, #4
    str     r1, [r0]                  // stores instruction causing prefetch abort

    bl      prefetch_abort_exception

    ldmia   sp!,{r0-r3,r12,lr}

    subs    pc, lr, #4                // LR adjustment for Prefetch Abort: points to the instruction that caused the exception

//------------------------------------------------------------------------------
//
//    Exception handler stubs
//
.align 4
.weak undefined_exception
.type undefined_exception, %function
undefined_exception:
    bx lr

.align 4
.weak data_abort_exception
.type data_abort_exception, %function
data_abort_exception:
    bx lr

.align 4
.weak prefetch_abort_exception
.type prefetch_abort_exception, %function
prefetch_abort_exception:
    bx lr

.section .bss
undefined_exception_addr: .word
data_abort_addr:          .word
prefetch_abort_addr:      .word
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//    RTOS control flow transfer stuff
//
.set SYS_MODE,  0x1f
.set SVC_MODE,  0x13
.set IRQ_MODE,  0x12

//------------------------------------------------------------------------------
//
//    Macros
//
.macro SAVE_CONTEXT
    srsdb   sp!, #SYS_MODE               // save the lr and spsr onto the system mode stack
    cps     #SYS_MODE                    // switch to system mode
    push    {r0-r12, r14}                // save system mode registers

#if FPU_ENABLE                           // floating point context
    vmrs    r1,  fpscr
    push    {r1, r2}                     // push r2 -- for stack 64-bit alignment
    vpush   {d0-d15}
    vpush   {d16-d31}
#endif
.endm

.macro RESTORE_CONTEXT
#if FPU_ENABLE                           // floating point context
    vpop    {d16-d31}
    vpop    {d0-d15}
    pop     {r1, r2}
    vmsr    fpscr, r1
#endif

    pop     {r0-r12, r14}                // restore system mode registers

.endm

//------------------------------------------------------------------------------
//
//    Macros
//
.text
.align 4

os_start:

    mov     sp, r0
    RESTORE_CONTEXT
    rfeia   sp!                          // return to the process code pointed by lr
                                         // and restoring cpsr
os_start.end:

//------------------------------------------------------------------------------
.align 4
process_switch_exc:

    SAVE_CONTEXT

    // switch process stack pointers
    mov     r0, sp                       // pass sp of current process as argument
    ldr     r1, =os_context_switch_hook
    blx     r1

    mov     sp, r0                       // load sp of new (current for now) process
    RESTORE_CONTEXT
    rfeia   sp!                          // return to the process code pointed by lr
                                         // and restoring cpsr

context_switch_exc.end:

//------------------------------------------------------------------------------
.align 4
interrupt_request_exc:

    sub     lr, lr, #4
    push    {lr}                         // push count: +1 = 1
    mrs     lr, spsr
    push    {lr}                         // push count: +1 = 2

    push    {r0-r4, r12}                 // push count: +6 = 8  (r4 - to maintain even push count for stack 64-bit alignment)

#if FPU_ENABLE                           // save FPU context
    vpush   {d0-d7}
    vpush   {d16-d31}
    vmrs     r1, fpscr
    push    {r1}                         // push count: +1 = 9
    vmrs     r1, fpexc
    push    {r1}                         // push count: +1 = 10: even count!
#endif

    bl      irq_handler

#if FPU_ENABLE                           // restore FPU context
    pop     {r1}
    vmsr    fpexc, r1
    pop     {r1}
    vmsr    fpscr, r1
    vpop    {d16-d31}
    vpop    {d0-d7}
#endif

    cmp     r0, #0
    bne     ctx_sw
    pop     {r0-r4, r12}
    pop     {lr}
    msr     spsr_cxsf, lr
    pop     {lr}
    movs    pc, lr

ctx_sw:
    pop     {r0-r4, r12}
    pop     {lr}
    msr     spsr_cxsf, lr
    pop     {lr}

    SAVE_CONTEXT
    mov     r0, sp                       // pass sp of current process as argument
    ldr     r1, =os_context_switch_hook
    blx     r1
    mov     sp, r0                       // load sp of new (current for now) process
    RESTORE_CONTEXT
    rfeia   sp!

interrupt_request_exc.end:
//------------------------------------------------------------------------------

