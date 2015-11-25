//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   EWARM (IAR Systems)
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2015

#include "scmRTOS_TARGET_CFG.h"

//-----------------------------------------------------------------------------
//  PUBLIC FUNCTIONS
//
    EXTERN  os_context_switch_hook

    PUBLIC  os_start
    PUBLIC  PendSV_Handler

//-----------------------------------------------------------------------------
//  EQUATES
//
NVIC_SYSPRI14        EQU     0xE000ED22  // System priority register (priority 14).
NVIC_PENDSV_PRI      EQU           0xFF  // PendSV priority value (lowest).
NVIC_SYSPRI15        EQU     0xE000ED23  // System priority register (priority 15).
NVIC_ST_PRI          EQU           0xFF  // SysTick priority value (lowest).

NVIC_ST_CTRL         EQU    0xE000E010   // SysTick Ctrl & Status Reg.
NVIC_ST_RELOAD       EQU    0xE000E014   // SysTick Reload  Value Reg.
NVIC_ST_CTRL_CLK_SRC EQU    0x00000004   // Clock Source.
NVIC_ST_CTRL_INTEN   EQU    0x00000002   // Interrupt enable.
NVIC_ST_CTRL_ENABLE  EQU    0x00000001   // Counter mode.


//-----------------------------------------------------------------------------
//      CODE GENERATION DIRECTIVES
//
        RSEG CODE:CODE(2)
        THUMB

//-----------------------------------------------------------------------------
//      HANDLE PendSV EXCEPTION
//      void PendSV_Handler(void)
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
PendSV_Handler
    CPSID   I                 // Prevent interruption during context switch
    MRS     R0, PSP           // PSP is process stack pointer
    STMDB R0!, {R4-R11}       // Save remaining regs r4-11 on process stack
    
    // At this point, entire context of process has been saved                                                            
    PUSH    {LR}                           // Save LR exc_return value
    
#if USE_NEAR_CALL == 0
    LDR     R1, =os_context_switch_hook    // os_context_switch_hook();
    BLX     R1
#else 
    BL      os_context_switch_hook         // os_context_switch_hook(); 
#endif
    
    // R0 is new process SP;
    LDMIA R0!, {R4-R11}       // Restore r4-11 from new process stack
    MSR     PSP, R0           // Load PSP with new process SP
    CPSIE   I
    POP     {PC}              // Return to saved exc_return. Exception return will restore remaining context
    
//-----------------------------------------------------------------------------
// Perform systick timer initialization.
//
init_system_timer
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
//              a) Setup PendSVexception priority to lowest;
//              b) Setup system timer (exception priority and reload value);
//              c) Enable interrupts (tasks will run with interrupts enabled).
//              d) Jump to exec() function of the highest priority process.
//
os_start
    LDR     R1, =NVIC_SYSPRI14      // Set the PendSV exception priority (lowest)
    LDR     R2, =NVIC_PENDSV_PRI
    STRB    R2, [R1]
    
    LDR     R4, [R0, #(4 * 14)]		// Load process entry point into R3
    ADD     R0, R0, #(4 * 16)       // emulate context restore
    MSR     PSP, R0                 // store process SP to PSP
    MOV     R0, #2                  // Switch thread mode stack to PSP
    MSR     CONTROL, R0
    ISB                             // Insert a barrier

#if USE_SYSTICK_TIMER != 0
    LDR R1, =init_system_timer      // Init and run system timer
    BLX R1
#endif

    CPSIE   I                       // Enable interrupts at processor level

    BX      R4                      // Jump to process exec() function

    END
