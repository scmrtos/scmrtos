//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: LPC2xxx (NXP)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Startup file.
//*
//*     Version: 4.00a
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2010, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2010
//*     lpc2xxx GCC parts by Anton B. Gusev aka AHTOXA, Copyright (c) 2010-2011

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

#include <OS_Target_core.h>
#include <scmRTOS_CONFIG.h>
    .code 32
/****************************************************************************/
/*               Vector table and reset entry                               */
/****************************************************************************/
    .section .vectors,"ax"
    .global _start
_start:
        LDR     PC, ResetAddr       /* Reset                 */
        LDR     PC, UndefAddr       /* Undefined instruction */
        LDR     PC, SWIAddr         /* Software interrupt    */
        LDR     PC, PAbortAddr      /* Prefetch abort        */
        LDR     PC, DAbortAddr      /* Data abort            */
        .word   0xB9205F88          /* Reserved              */
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1 && !defined(GCC_IRQ_PATCH_REQUIRED)
        LDR     PC, [PC, #-0xFF0]   /* Read address from AIC */
#else
        LDR     PC, IRQAddr         /* IRQ interrupt         */
#endif
        LDR     PC, FIQAddr         /* FIQ interrupt         */
ResetAddr:
        .word ResetHandler
UndefAddr:
        .word UndefHandler
SWIAddr:
        .word SWIHandler
PAbortAddr:
        .word PAbortHandler
DAbortAddr:
        .word DAbortHandler

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0 || defined(GCC_IRQ_PATCH_REQUIRED)
IRQAddr:
        .word IRQHandler
#endif

FIQAddr:
        .word FIQHandler
    .ltorg

//-----------------------------------------------------------------------------
//
//     Reset handler
//     program starts here
//
    .section .text, "ax"
ResetHandler:
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
        LDR     R1,=_data_image           // data image start
        LDR     R2,=_data                 // destination
        LDR     R3,=_edata                // end of destination
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
//     Exit function. Should never get here
    .section .text.weakExitFunction, "ax"
    .global ExitFunction
    .weak ExitFunction
ExitFunction:
        B       ExitFunction

//-----------------------------------------------------------------------------
//     Default __low_level_init implementation. Does nothing.
    .section .text.__low_level_init, "ax"
    .weak __low_level_init
__low_level_init:
        BX       LR


//-----------------------------------------------------------------------------
//     Default exeptions handlers
    .section .text.weakFIQHandler, "ax"
    .weak FIQHandler
FIQHandler:
        B       FIQHandler

    .section .text.weakUndefHandler, "ax"
    .weak UndefHandler
UndefHandler:
        B       UndefHandler

    .section .text.weakSWIHandler, "ax"
    .weak SWIHandler
SWIHandler:
        B       SWIHandler

    .section .text.weakPAbortHandler, "ax"
    .weak PAbortHandler
PAbortHandler:
        B       PAbortHandler

    .section .text.weakDAbortHandler, "ax"
    .weak DAbortHandler
DAbortHandler:
        B       DAbortHandler

    .ltorg


