//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AT91SAM7xxx (Atmel)
//*
//*     TOOLKIT:   arm-(elf/none-eabi)-gcc (GNU)
//*
//*     PURPOSE:   Startup file.
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2007-2012

#define MODE_USER       0x10
#define MODE_FIQ        0x11
#define MODE_IRQ        0x12
#define MODE_SVC        0x13
#define MODE_ABORT      0x17
#define MODE_UND        0x1B
#define MODE_SYS        0x1F

#define NIRQ            (1<<7)
#define NFIQ            (1<<6)
#define THUMB           (1<<5)

#include <scmRTOS_CONFIG.h>
    .code 32
/****************************************************************************/
/*               Vector table and reset entry                               */
/****************************************************************************/
    .section .vectors,"ax"
    .global _start
_start:
        LDR     PC, reset_addr      /* Reset                 */
        LDR     PC, undef_addr      /* Undefined instruction */
        LDR     PC, swi_addr        /* Software interrupt    */
        LDR     PC, p_abort_addr    /* Prefetch abort        */
        LDR     PC, d_abort_addr    /* Data abort            */
        NOP                         /* Reserved              */
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1 && !defined(GCC_IRQ_PATCH_REQUIRED)
        LDR     PC, [PC, #-0xF20]   /* Read address from AIC */
#else
        LDR     PC, irq_addr        /* IRQ interrupt         */
#endif
        LDR     PC, fiq_addr        /* FIQ interrupt         */
reset_addr:
        .word reset_handler
undef_addr:
        .word undef_handler
swi_addr:
        .word swi_handler
p_abort_addr:
        .word p_abort_handler
d_abort_addr:
        .word d_abort_handler

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0 || defined(GCC_IRQ_PATCH_REQUIRED)
irq_addr:
        .word irq_handler
#endif

fiq_addr:
        .word fiq_handler
    .ltorg

//-----------------------------------------------------------------------------
//
//     Reset handler
//     program starts here
//
    .section .text, "ax"
reset_handler:
//-----------------------------------------------------------------------------
//     Setup stasks
        MSR     CPSR_c, #MODE_FIQ | NIRQ | NFIQ     // Switch to fiq mode, IRQ & FIQ disabled
        LDR     SP, =__stack_fiq
        MSR     CPSR_c, #MODE_SVC | NIRQ | NFIQ     // Switch to supervisor mode, IRQ & FIQ disabled
        LDR     SP, =__stack_svc
        MSR     CPSR_c, #MODE_UND | NIRQ | NFIQ     // Switch to undefined mode, IRQ & FIQ disabled
        LDR     SP, =__stack_und
        MSR     CPSR_c, #MODE_ABORT | NIRQ | NFIQ   // Switch to abort mode, IRQ & FIQ disabled
        LDR     SP, =__stack_abort
        MSR     CPSR_c, #MODE_IRQ | NIRQ | NFIQ     // Switch to irq mode, IRQ & FIQ disabled
        LDR     SP, =__stack_irq
        MSR     CPSR_c, #MODE_SYS | NIRQ | NFIQ     // Switch to system mode, IRQ & FIQ disabled
        LDR     SP, =__stack_sys
//-----------------------------------------------------------------------------
//     Setup hardware
        LDR     R0,=__low_level_init
        MOV     LR,PC
        BX      R0
//-----------------------------------------------------------------------------
//     Clear .bss section
        LDR     R1, =__bss_start
        LDR     R2, =__bss_end
        MOV     R3, #0
bss_clear_loop:
        CMP     R1, R2
        STRLO   R3, [R1], #+4
        BLO     bss_clear_loop
//-----------------------------------------------------------------------------
//     Copy init values to .data section
        LDR     R1,=_data_image                     // data image start
        LDR     R2,=_data                           // destination
        LDR     R3,=_edata                          // end of destination
data_copy_loop:
        CMP     R2,R3
        LDRLO   R0,[R1],#4
        STRLO   R0,[R2],#4
        BLO     data_copy_loop
//-----------------------------------------------------------------------------
//     Call C++ constructors
        LDR     R0, =__ctors_start
        LDR     R1, =__ctors_end
ctor_loop:
        CMP     R0, R1
        BEQ     ctor_end
        LDR     R2, [R0], #4
        STMFD   SP!, {R0,R1}
        MOV     LR, PC
        BX      R2                      // some constructors can be in THUMB mode
        LDMFD   SP!, {R0,R1}
        B       ctor_loop
ctor_end:
//-----------------------------------------------------------------------------
//     Call main() with no arguments
        MOV     R0,#0
        MOV     R1,R0
        LDR     R2,=main
        MOV     LR,PC
        BX      R2
//-----------------------------------------------------------------------------
//     Exit function. Normaly never reach here
    .section .text.weakExitFunction, "ax"
    .global exit_function
    .weak exit_function
exit_function:
        B       exit_function

//-----------------------------------------------------------------------------
//     Default exeptions handlers
    .section .text.weak_fiq_handler, "ax"
    .weak fiq_handler
fiq_handler:
        B       fiq_handler

    .section .text.weak_undef_handler, "ax"
    .weak undef_handler
undef_handler:
        B       undef_handler

    .section .text.weak_swi_handler, "ax"
    .weak swi_handler
swi_handler:
        B       swi_handler

    .section .text.weak_p_abort_handler, "ax"
    .weak p_abort_handler
p_abort_handler:
        B       p_abort_handler

    .section .text.weak_d_abort_handler, "ax"
    .weak d_abort_handler
d_abort_handler:
        B       d_abort_handler

    .ltorg


