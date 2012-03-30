//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M0
//*
//*     TOOLKIT:   ARM GCC
//*               
//*     PURPOSE:   Target Dependent Low-Level Stuff
//*               
//*     Version: 4.00a
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2011, Harry E. Zhurov
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
//*     Cortex-M0 port by Sergey A. Borshch, Copyright (c) 2011
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2010
//*     Ported to GCC Ivan A-R <ivan@tuxotronic.org> (l) 2008

#include "scmRTOS_TARGET_CFG.h"

//-----------------------------------------------------------------------------
//      CODE GENERATION DIRECTIVES
//
//        RSEG CODE:CODE(2)
    .cpu cortex-m0
    .fpu softvfp   
    .syntax unified
    .thumb
    .text	
    .align 2

//-----------------------------------------------------------------------------
//  PUBLIC FUNCTIONS
//
    .section    .text,"ax"
    .code 16

    .extern os_context_switch_hook

    .global PendSVC_ISR
//-----------------------------------------------------------------------------
//      HANDLE PendSV EXCEPTION
//      void PendSVC_ISR(void)
//
// Note(s) : 1) PendSV is used to cause a context switch.  This is a recommended method for performing
//              context switches with Cortex-M0.  This is because the Cortex-M0 auto-saves half of the
//              processor context on any exception, and restores same on return from exception.  So only
//              saving of R4-R11 is required and fixing up the stack pointers.  Using the PendSV exception
//              this way means that context saving and restoring is identical whether it is initiated from
//              a thread or occurs due to an interrupt or exception.
//
//           2) Pseudo-code is:
//              a) Get the process SP;
//              b) Save remaining regs r4-r11 on process stack;
//              c) Call os_context_switch_hook for save current task SP and get new task SP;
//              d) Restore R4-R11 from new process stack;
//              e) Perform exception return which will restore remaining context.
//
//           3) On entry into PendSV handler:
//              a) The following have been saved on the process stack (by processor):
//                 xPSR, PC, LR, R12, R0-R3
//              b) Processor mode is switched to Handler mode (from Thread mode)
//              c) Stack is Main stack (switched from Process stack)
//
//           4) Since PendSV is set to lowest priority in the system (by os_start()), we
//              know that it will only be run when no other exception or interrupt is active, and
//              therefore safe to assume that context being switched out was using the process stack (PSP).
//

.thumb_func
PendSVC_ISR:
    CPSID   I                 // Prevent interruption during context switch
    MRS     R0, PSP           // PSP is process stack pointer
    SUBS    R0, #32           // Adjust R0 to point to top of saved context (No STMDB instruction available in Cortex-M0)
    MOV     R1, R0            // R1 - temp. reg for STM
    ADDS    R1, #16           // ADDS with imm: Rd and Rn must specify the same register, so ADDS R1, R0, #16 is illegal
    STM     R1!, {R4-R7}      // Save lo portion of remaining regs (r4-7) on process stack
    SUBS    R1, #32
    MOV     R4, R8            // Move hi portion of remaining regs (r8-11) to lo regs
    MOV     R5, R9
    MOV     R6, R10
    MOV     R7, R11
    STM     R1!, {R4-R7}      // Save hi portion of remaining regs (r8-11) on process stack
    // At this point, entire context of process has been saved                                                            

    PUSH    {LR}              // Save LR exc_return value
    LDR     R1, =os_context_switch_hook    // os_context_switch_hook();
    BLX     R1
    
ContextRestore:
    // R0 is new process SP;
    LDM     R0!, {R4-R7}      // Restore r8-11 values from new process stack
    MOV     R8, R4            // Move restored values to hi regs (r8-11)
    MOV     R9, R5
    MOV     R10, R6
    MOV     R11, R7
    LDM     R0!, {R4-R7}      // Restore r4-7 from new process stack
    MSR     PSP, R0           // Load PSP with new process SP

    CPSIE   I                 // re-enable interrupts
    POP     {PC}              // pop pushed exc_return value causes Exception return and restore of remaining context

    .end

