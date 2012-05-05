//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   ARM GCC
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2012
//*     Ported to GCC Ivan A-R <ivan@tuxotronic.org> (l) 2008
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2012

#include "scmRTOS_TARGET_CFG.h"

//-----------------------------------------------------------------------------
//      CODE GENERATION DIRECTIVES
//
//        RSEG CODE:CODE(2)
    .cpu cortex-m3
    .fpu softvfp   
    .syntax unified
    .thumb
    .text	
    .align 4


//-----------------------------------------------------------------------------
//  EQUATES
//
    .equ    NVIC_SYSPRI14        ,     0xE000ED22  // System priority register (priority 14).
    .equ    NVIC_PENDSV_PRI      ,           0xFF  // PendSV priority value (lowest).
    .equ    NVIC_SYSPRI15        ,     0xE000ED23  // System priority register (priority 15).
    .equ    NVIC_ST_PRI          ,           0xFF  // SysTick priority value (lowest).

    .equ    NVIC_ST_CTRL         ,    0xE000E010   // SysTick Ctrl & Status Reg.
    .equ    NVIC_ST_RELOAD       ,    0xE000E014   // SysTick Reload  Value Reg.
    .equ    NVIC_ST_CTRL_CLK_SRC ,    0x00000004   // Clock Source.
    .equ    NVIC_ST_CTRL_INTEN   ,    0x00000002   // Interrupt enable.
    .equ    NVIC_ST_CTRL_ENABLE  ,    0x00000001   // Counter mode.


//-----------------------------------------------------------------------------
//  PUBLIC FUNCTIONS
//
    .section    .text,"ax"
    .code 16

    .extern os_context_switch_hook

    .global PendSVC_ISR
    .global os_start

//-----------------------------------------------------------------------------
//      HANDLE PendSV EXCEPTION
//      void PendSVC_ISR(void)
//
// Note(s) : 1) PendSV is used to cause a context switch.  This is a recommended method for performing
//              context switches with Cortex-M3.  This is because the Cortex-M3 auto-saves half of the
//              processor context on any exception, and restores same on return from exception.  So only
//              saving of R4-R11 is required and fixing up the stack pointers.  Using the PendSV exception
//              this way means that context saving and restoring is identical whether it is initiated from
//              a thread or occurs due to an interrupt or exception.
//
//           2) Pseudo-code is:
//              a) Get the process SP
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
//           4) Since PendSV is set to lowest priority in the system (by os_start() below), we
//              know that it will only be run when no other exception or interrupt is active, and
//              therefore safe to assume that context being switched out was using the process stack (PSP).
//

.thumb_func
PendSVC_ISR:
    CPSID   I                 // Prevent interruption during context switch
    MRS     R0, PSP           // PSP is process stack pointer
    STMDB   R0!, {R4-R11}     // Save remaining regs r4-11 on process stack
    // At this point, entire context of process has been saved                                                            

    PUSH    {LR}              // Save LR exc_return value
    BL      os_context_switch_hook    // call os_context_switch_hook();
    
    // R0 is new process SP;
    LDMIA   R0!, {R4-R11}     // Restore r4-11 from new process stack
    MSR     PSP, R0           // Load PSP with new process SP
    CPSIE   I
    POP     {PC}              // Return to saved exc_return. Exception return will restore remaining context

    .align 2

//-----------------------------------------------------------------------------
//      Initialize system timer.
//      void init_system_timer()
// Perform systick timer initialization.
//
    .weak  __init_system_timer
__init_system_timer:

    LDR     R1, =NVIC_SYSPRI15      // Set the SysTick exception priority (lowest)
    LDR     R2, =NVIC_ST_PRI
    STRB    R2, [R1]

    LDR     R1, =NVIC_ST_RELOAD     // Setup SysTick
    LDR     R2, =(SYSTICKFREQ/SYSTICKINTRATE-1)
    STR     R2, [R1]
    LDR     R1, =NVIC_ST_CTRL       // Enable and run SysTick
    LDR     R2, =(NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE)
    STR     R2, [R1]
    BX      LR

//-----------------------------------------------------------------------------
//      START MULTITASKING
//      void os_start(stack_item_t* sp)
//
// Note(s) : 1) os_start() MUST:
//              a) Setup PendSV and SysTick exception priority to lowest;
//              b) Setup SysTick (reload value);
//              c) Enable interrupts (tasks will run with interrupts enabled).
//              d) Jump to exec() function of the highest priority process.
//
.thumb_func
os_start:
    LDR     R1, =NVIC_SYSPRI14      // Set the PendSV exception priority (lowest)
    LDR     R2, =NVIC_PENDSV_PRI
    STRB    R2, [R1]

    LDR     R4, [R0, #(4 * 14)]		// Load process entry point into R4
    ADD     R0, #(4 * 16)           // emulate context restore
    MSR     PSP, R0                 // store process SP to PSP
    MOV     R0, #2                  // Switch thread mode stack to PSP
    MSR     CONTROL, R0
    ISB                             // Insert a barrier

    BL      __init_system_timer      // run system timer

    CPSIE   I                       // Enable interrupts at processor level

    BX      R4                      // Jump to process exec() function

    .end

