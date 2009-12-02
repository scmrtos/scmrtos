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
//*     Version: 3.05
//*
//*     $Revision: 195 $
//*     $Date:: 2008-06-19 #$
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008

#include "scmRTOS_TARGET_CFG.h"

//-----------------------------------------------------------------------------
//  PUBLIC FUNCTIONS
//
    EXTERN  OS_ContextSwitchHook

    PUBLIC  OS_Start
    PUBLIC  PendSV_Handler

//-----------------------------------------------------------------------------
//  EQUATES
//
NVIC_INT_CTRL        EQU     0xE000ED04  // Interrupt control state register.
NVIC_PENDSVSET       EQU     0x10000000  // Value to trigger PendSV exception.

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
//              a) Get the process SP, if 0 then skip (goto f) the saving part (first context switch);
//              b) Save remaining regs r4-r11 on process stack;
//              c) Call OS_ContextSwitchHook for save current task SP and get new task SP;
//              d) Restore R4-R11 from new process stack;
//              e) Perform exception return which will restore remaining context.
//              f) Get SP for the first context switch (R2 hold it);
//                 run SysTick; goto d);
//
//           3) On entry into PendSV handler:
//              a) The following have been saved on the process stack (by processor):
//                 xPSR, PC, LR, R12, R0-R3
//              b) Processor mode is switched to Handler mode (from Thread mode)
//              c) Stack is Main stack (switched from Process stack)
//
//           4) Since PendSV is set to lowest priority in the system (by OS_Start() below), we
//              know that it will only be run when no other exception or interrupt is active, and
//              therefore safe to assume that context being switched out was using the process stack (PSP).
//
PendSV_Handler
    CPSID   I                 // Prevent interruption during context switch
    MRS     R0, PSP           // PSP is process stack pointer
    CBZ     R0, nosave        // Skip register save the first time    

    STMDB R0!, {R4-R11}       // Save remaining regs r4-11 on process stack
    // At this point, entire context of process has been saved                                                            

    PUSH    {R14}                        // Save LR exc_return value
    LDR     R1, =OS_ContextSwitchHook    // OS_ContextSwitchHook();
    BLX     R1
    POP     {R14}
    
ContextRestore
    // R0 is new process SP;
    LDMIA R0!, {R4-R11}         // Restore r4-11 from new process stack
    MSR     PSP, R0           // Load PSP with new process SP
    ORR     LR, LR, #0x04     // Ensure exception return uses process stack
    CPSIE   I
    BX      LR                // Exception return will restore remaining context
nosave
    MOV R0, R2                // R2 hold the first task SP
    
    LDR     R1, =NVIC_ST_CTRL // Enable and run SysTick
    LDR     R2, =(NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE)
    STR     R2, [R1]
    
    B   ContextRestore

   
//-----------------------------------------------------------------------------
//      START MULTITASKING
//      void OS_Start(TStackItem* sp)
//
// Note(s) : 1) OS_Start() MUST:
//              a) Setup PendSV and SysTick exception priority to lowest;
//              b) Setup SysTick (reload value);
//              c) Enable interrupts (tasks will run with interrupts enabled).
//
OS_Start
    LDR     R1, =NVIC_SYSPRI14      // Set the PendSV exception priority (lowest)
    LDR     R2, =NVIC_PENDSV_PRI
    STRB    R2, [R1]
    LDR     R1, =NVIC_SYSPRI15      // Set the SysTick exception priority (lowest)
    LDR     R2, =NVIC_ST_PRI
    STRB    R2, [R1]
    
    LDR     R1, =NVIC_ST_RELOAD     // Setup SysTick
    LDR     R2, =(SYSTICKFREQ/SYSTICKINTRATE-1)  
    STR     R2, [R1]

    MOV     R2, R0                  // Save the first task stack
    MOVS    R0, #0                  // Set the PSP to 0 for initial context switch call
    MSR     PSP, R0

    LDR     R0, =NVIC_INT_CTRL      // Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]

    CPSIE   I                       // Enable interrupts at processor level
loop
    B       loop                    // Should never get here


    END
