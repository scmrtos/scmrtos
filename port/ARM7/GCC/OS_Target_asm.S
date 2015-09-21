//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   arm-(elf/none-eabi)-gcc (GNU)
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2007-2012


#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"
#include "OS_Target_core.h"

//  Context structure:
//        lo address
//  CPSR
//  R14 (LR)
//  R0
//  R1
//  R2
//  R3
//  R4
//  R5
//  R6
//  R7
//  R8
//  R9
//  R10
//  R11
//  R12
//  Process interrupt point (return address)
//        hi address

//-------------------------------------------------------------------------------

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
        .section .text,"ax"
        .code 32

        .global irq_handler
        .global context_restore

#if scmRTOS_OBSOLETE_NAMES == 1
        .global IRQHandler
IRQHandler:
#endif // scmRTOS_OBSOLETE_NAMES
irq_handler:
        MSR     CPSR_c, #(NIRQ | MODE_SYS)  // switching to System mode, because context has to be saved
                                            // on top of user mode stack, enable FIQ
        STMFD   SP!, {R0-R12,LR}            // store R0_R12, dummy store LR to reserve space in context
        STMFD   SP!, {R1,LR}                // reserve space for CPSR, store LR_user on top of context

        MOV     R0, SP                      // store context pointer in non-banked register
        MSR     CPSR_c, #(NIRQ | MODE_IRQ)  // switching back to IRQ mode
        SUB     LR, LR, #4                  // adjusting return address
        STR     LR, [R0, #4*15]             // store return address in reserved space (instead of saved LR_user)
        MRS     R1, SPSR                    // move stored CPSR of process to non-banked register
        STR     R1, [R0]                    // store SPSR in reserved space (instead of saved R1)

        IRQ_SWITCH                          // call IRQ handler

        MSR     CPSR_c, #(NIRQ | MODE_SYS)  // switching to System mode, because context has to be restored
                                            // from user mode stack, enable FIQ
        MOV     R0, SP
context_restore:     // os_start() passes New_SP in R0
        LDMFD   R0!, {R1, LR}               // restoring LR_user, saved CPSR_user
        ADD     SP, R0, #4*14               // set process SP

        MSR     CPSR_c, #(NIRQ | MODE_IRQ)  // switch to IRQ mode to get access to SPSR_irq
        MSR     SPSR_cxsf, R1               // store process CPSR to SPSR_irq to restore at return from irq

        LDMFD   R0, {R0-R12,PC}^            // restoring remaining context, CPSR and reti

#elif scmRTOS_CONTEXT_SWITCH_SCHEME == 1
//-------------------------------------------------------------------------------
        // TStackItem* os_context_switch_hook(TStackItem* sp)//
        .extern os_context_switch_hook
        .global context_switcher_isr
        .global context_restore
context_switcher_isr:
        MSR     CPSR_c, #(NIRQ | MODE_SYS)  // switching to System mode, because context has to be saved
                                            // on top of user mode stack, enable FIQ
        STMFD   SP!, {R0-R12,LR}            // store R0_R12, dummy store LR to reserve space in context

        MOV     R0, SP                      // store context pointer in non-banked register
        MOV     R2, LR                      // store LR in non-banked register
        MSR     CPSR_c, #(NIRQ | MODE_IRQ)  // switching back to IRQ mode
        SUB     LR, LR, #4                  // adjusting return address
        STR     LR, [R0, #4*13]             // store return address in reserved space (instead of saved LR_user)
        MRS     R1, SPSR                    // move stored CPSR of process to non-banked register
        STMFD   R0!, {R1,R2}                // store CPSR, LR_user on top of context

        LDR     R1, =os_context_switch_hook // call possibly Thumb mode routine
        MOV     LR, PC
        BX      R1
        IRQ_DONE                            // reset interrupt controller
        MSR     CPSR_c, #(NIRQ | MODE_SYS)  // switching back to System mode
context_restore:
        LDMFD   R0!, {R1, LR}               // restoring LR_user, saved CPSR_user
        ADD     SP, R0, #4*14               // set process SP

        MSR     CPSR_c, #(NIRQ | MODE_IRQ)  // switch to IRQ mode to get access to SPSR_irq
        MSR     SPSR_cxsf, R1               // store process CPSR to SPSR_irq to restore at return from irq

        LDMFD   R0, {R0-R12,PC}^            // restoring remining context, CPSR and reti
#else
#error "scmRTOS_CONTEXT_SWITCH_SCHEME not defined"
#endif
//-------------------------------------------------------------------------------
        .ltorg
