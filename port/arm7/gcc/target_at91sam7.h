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
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version: v5.0.1
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2015

#ifndef TARGET_AT91SAM7_H__
#define TARGET_AT91SAM7_H__

#ifndef __ASSEMBLER__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1 && !defined(GCC_IRQ_PATCH_REQUIRED)
#define OS_INTERRUPT   __attribute__((interrupt("IRQ")))
#else
#define OS_INTERRUPT
#endif
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
namespace OS
{
    INLINE void raise_context_switch()
    {
        AT91C_BASE_AIC->AIC_ISCR = (1<<CONTEXT_SWITCH_INT);
    }
}   // namespace OS
#endif

INLINE void IRQ_DONE()
{
    AT91C_BASE_AIC->AIC_EOICR = 0;  // indicate end of IRQ servicing 
}

// SYSTEM_TIMER_HANDLER(): while() used instead of do-while()
// to allow other interrupt sources on AT91C_ID_SYS.
// Write your own handler instead of OS::system_timer_isr() to handle other SYS sources
#define SYSTEM_TIMER_HANDLER()                                  \
    do                                                          \
    {                                                           \
        volatile uint32_t Tmp = AT91C_BASE_PITC->PITC_PIVR >> 20;  \
        while (Tmp)                                             \
        {                                                       \
            --Tmp;                                              \
            OS::system_timer_handler();                         \
        }                                                       \
    }                                                           \
    while(0)

#else   // __ASSEMBLER__

        .macro  IRQ_SWITCH
        LDR     R1, =AT91C_AIC_IVR
        MOV     LR, PC
        LDR     PC,[R1]                             // void (*AT91C_AIC_IVR)()
        .endm

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        .macro  IRQ_DONE
        LDR     R1, =AT91C_AIC_EOICR
        STR     R0, [R1]                            // indicate end of IRQ servicing
        .endm
    #endif  // scmRTOS_CONTEXT_SWITCH_SCHEME

#endif  // __ASSEMBLER__

#endif  // TARGET_AT91SAM7_H__
