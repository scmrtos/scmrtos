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
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
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
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//******************************************************************************
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2015

#ifndef scmRTOS_CORTEXM3_H
#define scmRTOS_CORTEXM3_H

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
//
#ifndef __IAR_SYSTEMS_ICC__
#error "This file should only be compiled with IAR C/EC++ Compiler"
#endif // __IAR_SYSTEMS_ICC__

#ifndef __ICCARM__
#error "This file must be compiled for ARM processor only."
#endif

#if __VER__ < 520
#error "This file must be compiled by IAR C/C++ Compiler v5.20 or higher."
#endif

//------------------------------------------------------------------------------
//
//    Compiler specific attributes
//
//
#ifndef INLINE
#define INLINE _Pragma("inline=forced") inline
#endif

#ifndef NORETURN
#define NORETURN __noreturn
#endif

//------------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef uint32_t stack_item_t;
typedef uint32_t status_reg_t;

//-----------------------------------------------------------------------------
//
//    Configuration macros
//
//
#define OS_PROCESS   
#define OS_INTERRUPT extern "C"
#define DUMMY_INSTR() __no_operation()
#define INLINE_PROCESS_CTOR 

//-----------------------------------------------------------------------------
// Separate return stack not required
#define SEPARATE_RETURN_STACK   0

//-----------------------------------------------------------------------------
// Software interrupt stack switching not supported in Cortex-M3 port
// because processor implements hardware stack switching.
// So, system timer isr wrapper can't be choosen at project level
//
#define scmRTOS_ISRW_TYPE       TISRW

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch Scheme
//
//    The macro defines a context switch manner. Value 0 sets direct context
//    switch in the scheduler and in the OS ISRs. This is the primary method.
//    Value 1 sets the second way to switch context - by using of software 
//    interrupt. See documentation fo details.
//    Cortex-M3 port supports software interrupt switch method only.
//
#define  scmRTOS_CONTEXT_SWITCH_SCHEME 1

//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_config.h"
#include "scmRTOS_TARGET_CFG.h"
#include <scmRTOS_defs.h>
#include <intrinsics.h>

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0xABBA55AA
#endif


//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    TCritSect () : StatusReg(__get_interrupt_state()) { __disable_interrupt(); }
    ~TCritSect() { __set_interrupt_state(StatusReg); }

private:
    status_reg_t StatusReg;
};
#endif // scmRTOS_USER_DEFINED_CRITSECT_ENABLE

//   Uncomment macro value below for system_timer() and
//   context_switch_hook() run in critical section.
// 
//   This is useful (and necessary) when target processor has hardware 
//   enabled nested interrups.
//   User can define own macros using user-defined TCritSect capabilities.
//
//   Cortex-M3 have nested interrupts but interrupts are disabled
//   during context switch ISR. So, critical section is needed
//   for system timer routine and not needed for context switcher.
// 
#ifndef SYS_TIMER_CRIT_SECT
#define SYS_TIMER_CRIT_SECT() TCritSect cs
#endif
#ifndef CONTEXT_SWITCH_HOOK_CRIT_SECT
#define CONTEXT_SWITCH_HOOK_CRIT_SECT() // TCritSect cs
#endif

//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//
namespace OS
{
INLINE OS::TProcessMap get_prio_tag(const uint_fast8_t pr) { return static_cast<OS::TProcessMap> (1 << pr); }

#if scmRTOS_PRIORITY_ORDER == 0
    INLINE uint_fast8_t highest_priority(TProcessMap pm)
    {
        uint_fast8_t pr = 0;

        while( !(pm & 0x0001) )
        {
            pr++;
            pm >>= 1;
        }
        return pr;
    }
#else
    INLINE uint_fast8_t highest_priority(TProcessMap pm) { return (31 - __CLZ(pm)); }
#endif // scmRTOS_PRIORITY_ORDER
}

//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE status_reg_t get_interrupt_state( )               { return __get_interrupt_state(); }
INLINE void         set_interrupt_state(status_reg_t sr) { __set_interrupt_state(sr); }

INLINE void enable_interrupts()  { __enable_interrupt();  }
INLINE void disable_interrupts() { __disable_interrupt(); }

namespace OS
{
    INLINE void enable_context_switch()  { enable_interrupts(); }
    INLINE void disable_context_switch() { disable_interrupts(); }
}

#include <os_kernel.h>

namespace OS
{
    //--------------------------------------------------------------------------
    //
    //      NAME       :   OS ISR support 
    //
    //      PURPOSE    :   Implements common actions on interrupt enter and exit 
    //                     under the OS
    //
    //      DESCRIPTION:
    //
    //
    class TISRW
    {
    public:
        INLINE  TISRW()  { ISR_Enter(); }
        INLINE  ~TISRW() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE void ISR_Enter()
        {
            TCritSect cs;
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
        {
            TCritSect cs;
            if(--Kernel.ISR_NestCount) return;
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };

    // No software interrupt stack switching provided,
    // TISRW_SS declared to be the same as TISRW for porting compatibility
    #define TISRW_SS    TISRW
    
} // ns OS
//-----------------------------------------------------------------------------

#endif // scmRTOS_CORTEXM3_H
//-----------------------------------------------------------------------------

