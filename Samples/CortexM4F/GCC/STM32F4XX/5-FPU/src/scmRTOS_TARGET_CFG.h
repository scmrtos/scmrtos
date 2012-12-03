//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M4F
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Project Level Configuration
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
//*     GCC port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2012

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

// Define SysTick clock frequency and its interrupt rate in Hz.
#define SYSTICKFREQ     168000000
#define SYSTICKINTRATE  1000

//------------------------------------------------------------------------------
// Definitions for some processor registers in order to not include specific
// header file for various Cortex-M3 processor derivatives.
#define CPU_ICSR            ( ( volatile uint32_t *) 0xE000ED04 )   // Interrupt Control State Register
#define CPU_SYSTICKCSR      ( ( volatile uint32_t *) 0xE000E010 )   // SysTick Control and Status Register
#define CPU_SYSTICKCSR_EINT 0x02                                    // Bit for enable/disable SysTick interrupt

#ifndef __ASSEMBLER__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
namespace OS
{
OS_INTERRUPT void SystemTimer_ISR();
}

#define  LOCK_SYSTEM_TIMER()    ( *CPU_SYSTICKCSR &= ~CPU_SYSTICKCSR_EINT )
#define  UNLOCK_SYSTEM_TIMER()  ( *CPU_SYSTICKCSR |=  CPU_SYSTICKCSR_EINT )

//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//
namespace OS
{
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void idle_process_user_hook();
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

    INLINE void raise_context_switch() { *CPU_ICSR |= 0x10000000; }

    #define ENABLE_NESTED_INTERRUPTS()

    #if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
        #define DISABLE_NESTED_INTERRUPTS() TCritSect cs
    #else
        #define DISABLE_NESTED_INTERRUPTS()
    #endif

#else
    #error "Cortex-M3 port supports software interrupt switch method only!"

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

}
//-----------------------------------------------------------------------------
#endif // __ASSEMBLER__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

