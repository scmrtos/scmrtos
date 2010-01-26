//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuC 70xx (Analog Devices)
//*
//*     TOOLKIT:   arm-elf-gcc (GNU)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version: 3.10
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

#ifndef TARGET_ADUC_H__
#define TARGET_ADUC_H__

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch Scheme
//
//    The macro defines a context switch manner. Value 0 sets direct context
//    switch in the scheduler and in the OS ISRs. This is the primary method.
//    Value 1 sets the second way to switch context - by using of software
//    interrupt. See documentation fo details.
//
//    The only Direct Context Switch Scheme supported for ADuC!
//
#define  scmRTOS_CONTEXT_SWITCH_SCHEME      0

#ifndef __ASSEMBLER__

#define OS_INTERRUPT

#define IRQ_DONE()                  // No interrupt controller implemented

#define SYSTEM_TIMER_HANDLER()      \
    do                              \
    {                               \
        T0CLRI = 0;                 \
        SystemTimer_Handler();      \
    }                               \
    while (0)

#else   //__ASSEMBLER__

        .macro      IRQ_SWITCH
        .extern     IRQ_Switch
        LDR         R1, =IRQ_Switch
        MOV         LR, PC
        BX          R1
        .endm
#endif  // __ASSEMBLER__

#endif  // TARGET_ADUC_H__
