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
//*     PURPOSE:   Project Level Configuration
//*
//*     Version: 4.00
//*
//*     $Revision: 196 $
//*     $Date:: 2008-06-19 #$
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

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

//------------------------------------------------------------------------------
// If the macro value is 1 (the default), the port uses SysTick as a system
// timer. It initializes the timer and starts it. The user must make sure that 
// the address of the timer interrupt handler (SysTick_Handler) is in the right
// place at the interrupt vector table.
// If the macro value is 0, then the user has to initialize and start
// the custom timer, which will be used as a system timer.
// In the interrupt handler of the custom timer, the user need to call
// OS::SystemTimer_Handler().
//
#define USE_SYSTICK_TIMER 1

//------------------------------------------------------------------------------
// Define SysTick clock frequency and its interrupt rate in Hz.
// It makes sense if USE_SYSTICK_TIMER = 1.
#define SYSTICKFREQ     8000000
#define SYSTICKINTRATE  500

//------------------------------------------------------------------------------
// PendSVC_Handler optimization:
// 0 - use far call for os_context_switch_hook (slower)
// 1 (default) - use near (+- 1MB) call for os_context_switch_hook (the fastest)
//
#define USE_NEAR_CALL  1


//------------------------------------------------------------------------------
// Definitions for some processor registers in order to not include specific
// header file for various Cortex-M3 processor derivatives.
#define CPU_ICSR            ( ( volatile uint32_t *) 0xE000ED04 )   // Interrupt Control State Register
#define CPU_SYSTICKCSR      ( ( volatile uint32_t *) 0xE000E010 )   // SysTick Control and Status Register
#define CPU_SYSTICKCSR_EINT 0x02                                    // Bit for enable/disable SysTick interrupt

#ifndef __IAR_SYSTEMS_ASM__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
namespace OS
{
OS_INTERRUPT void SysTick_Handler();
OS_INTERRUPT void SystemTimer_Handler();
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
#endif // __IAR_SYSTEMS_ASM__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

