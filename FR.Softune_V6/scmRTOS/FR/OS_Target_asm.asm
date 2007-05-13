//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: FR (Fujitsu)
//*
//*     TOOLKIT:   Softune Workbench V6 (Fujitsu)
//*
//*     PURPOSE:   Target Dependent Low-Level Stuff
//*
//*     Version:   3.00-beta
//*
//*     $Revision: 1 $
//*     $Date: 2006-12-15 12:51:04 +0500 (Пт, 15 дек 2006) $
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
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
//********************************************************************************
//*
//*     FR port by Sergey Pinigin, Copyright (c) 2007
//*
//********************************************************************************


    #include    "scmRTOS_TARGET_CFG.h"

    .PROGRAM    OS_TARGET_ASM

    .GLOBAL     _OS_Start
    .GLOBAL     _ContextSwitcher_ISR

    .GLOBAL     _OS_ContextSwitchHook

    .EXPORT     __cli
    .EXPORT     __sti
 
    .section    CODE, code, align=4

;//------------------------------------------------------------------------------

__cli:
        MOV         PS, R4                   ; Save state of PS
        STILM       #scmRTOS_OS_DI_LEVEL     ; Disable interrupts with OS services
;        ANDCCR      #0xEF                   ; Disable interrupts
        RET

__sti:
        MOV         R4, PS                   ; Restore state of PS
        RET


;//------------------------------------------------------------------------------
_OS_Start:

    MOV     R4,     USP

    ; Switch to USP 'S'= 1
    ORCCR   #0x20

    ; Jump to restore context of registers
    BRA     _jctx
;//------------------------------------------------------------------------------


;//------------------------------------------------------------------------------
_ContextSwitcher_ISR:

    ;//--------------------------------------------------------------------------
    ;//
    ;//   Save context
    ;//
    ORCCR   #0x20         ; Switch to USP ('S'= 1)

    STM0    (R0, R1, R2, R3, R4, R5, R6, R7)
    STM1    (R8, R9, R10, R11, R12, R13, R14)

    ST      MDL,    @-SP
    ST      MDH,    @-SP
    ST      RP,     @-SP

    MOV     SSP,    R14     ; FP = SSP

    ; Load PS and PC from SystemStack
    LD      @(R14,0),   R0
    LD      @(R14,+4),  R1

    ; Store PS and PC in TaskStack and down UserStack
    ST      R1,     @-SP
    ST      R0,     @-SP
    
    ; DICR = 0
    LDI:8   #0,     R13
    DMOVB   R13,    @_dicr

    ;//--------------------------------------------------------------------------
    ;//
    ;//   Switch stack pointers
    ;//
    MOV     USP,    R4

    LDI:20  #_OS_ContextSwitchHook, R0
    CALL    @R0

    MOV     R4,     USP

    ;//--------------------------------------------------------------------------
    ;//
    ;//   Restore context
    ;//
_jctx:

    MOV     SSP,    R14     ; FP = SSP

    ; Load PS and PC from TaskStack and up UserStack
    LD      @SP+,   R0
    LD      @SP+,   R1

    ; Store PS and PC in SystemStack
    ST      R0,     @(R14,0)
    ST      R1,     @(R14,+4)

    ; Load registers from TaskStack
    LD      @SP+,   RP
    LD      @SP+,   MDH
    LD      @SP+,   MDL

    LDM1    (R8, R9, R10, R11, R12, R13, R14)
    LDM0    (R0, R1, R2, R3, R4, R5, R6, R7)

    ANDCCR  #0x1f        ;switch to SSP ('S'= 0)

    RETI
;//------------------------------------------------------------------------------
    .END
