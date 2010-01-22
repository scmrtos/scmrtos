#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#include "device.h"

// Define SysTick clock frequency and its interrupt rate in Hz.
#define SYSTICKFREQ     72000000
#define SYSTICKINTRATE  1000

#ifndef __ASSEMBLER__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
namespace OS
{
extern "C" void SystemTimer_ISR();
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
    void IdleProcessUserHook();
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

    INLINE inline void RaiseContextSwitch() { *CPU_ICSR |= 0x10000000; }

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

