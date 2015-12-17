//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADSP-BF533 (Analog Devices)
//*
//*     TOOLKIT:   VDSP (Analog Devices)
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
//*     Blackfin/CrossCore Embedded Studio port by Evgeny Nesterov, Copyright (c) 2012-2015

#ifndef scmRTOS_BLACKFIN_H
#define scmRTOS_BLACKFIN_H

#ifndef __ADSPBLACKFIN__
#error "This file should only be compiled with VDSP Blackfin Compiler!"
#endif

//------------------------------------------------------------------------------
//
//    Compiler specific attributes
//
//
#ifndef INLINE
#define INLINE _Pragma("always_inline") inline
#endif

//-----------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef uint32_t stack_item_t;
typedef uint16_t status_reg_t;

//-----------------------------------------------------------------------------
//
//    Configuration macros
//
//
#define REGS "r0-r7 p0-p5 ASTAT i0-i3 b0-b3 l0-l3 m0-m3 lt0 lt1 lb0 lb1 lc0 lc1 a0 a1 cc"
#define OS_PROCESS _Pragma("regs_clobbered REGS")
#define DUMMY_INSTR()  asm(" nop;")
#define INLINE_PROCESS_CTOR

//--------------------------------------------------
//
//   Uncomment macro value below for SystemTimer() run in critical section
// 
//   This is useful (and necessary) when target processor has hardware 
//   enabled nested interrups. 
// 
#define SYS_TIMER_CRIT_SECT()           // TCritSect cs
#define CONTEXT_SWITCH_HOOK_CRIT_SECT()    TCritSect cs

#define  SEPARATE_RETURN_STACK              0
#define  scmRTOS_CONTEXT_SWITCH_SCHEME      1
#define  scmRTOS_SYSTIMER_NEST_INTS_ENABLE  0
#define  scmRTOS_ISRW_TYPE                  TISRW // separate ISR stack is not supported

#ifndef  scmRTOS_PRIORITY_ORDER
#define  scmRTOS_PRIORITY_ORDER  1                // default descending order of priorites
#endif


//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_config.h"
#include <scmRTOS_TARGET_CFG.h>
#include <scmRTOS_defs.h>

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0x55aa963bUL
#endif


//-----------------------------------------------------------------------------
//
//    Target-specific checks
//
#if scmRTOS_PROCESS_COUNT > 30 
#error "Process count is too much! Currently up 30 processes is supported."
#endif


//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
class TCritSect
{
public:
     TCritSect () : StatusReg(cli()) { }
     ~TCritSect() { sti(StatusReg); }

private:
    status_reg_t StatusReg;
};
//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//
namespace OS
{
    INLINE TProcessMap get_prio_tag(const uint_fast8_t pr) { return 1<<pr; }
    
    #if scmRTOS_PRIORITY_ORDER == 0
    inline uint8_t highest_priority(TProcessMap pm)
    {
        uint8_t pr = 0;

        while( !(pm & 0x0001) )
        {
            pr++;
            pm >>= 1;
        }
        return pr;
    }
    #else
    inline uint8_t highest_priority(TProcessMap pm)
    {
        uint8_t pr;
        asm
        (
            " %0.l = signbits %1; " :
            "=d" (pr) :
            "d" (pm)
        );
        return 30 - pr;
    }
    #endif // scmRTOS_PRIORITY_ORDER
}
//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE status_reg_t get_interrupt_state( )               { return cli(); }
INLINE void         set_interrupt_state(status_reg_t sr) { sti(sr); }

INLINE void enable_interrupts()  { sti( 0xffe0 );  }
INLINE void disable_interrupts() { }

INLINE void enable_context_switch()  { sti( 0xc000 );  }
INLINE void disable_context_switch() { cli( ); }

//-----------------------------------------------------------------------------
//
//    ISR prototypes
//
extern "C" void context_switcher_isr(unsigned int,int,void*);
//extern "C" void context_switcher_isr();



#define  LOCK_SYSTEM_TIMER()
#define  UNLOCK_SYSTEM_TIMER()
//-----------------------------------------------------------------------------

namespace OS
{
    void system_timer_isr(unsigned int a,int b,void* c);
    //void system_timer_isr();
    inline void raise_context_switch() { raise_intr(14); } // raise software interrupt
}
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
#include <os_kernel.h>
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
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
        INLINE  TISRW()  { isr_enter(); }
        INLINE  ~TISRW() { isr_exit();  }

    private:
        //-----------------------------------------------------
        INLINE void isr_enter()
        {
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE void isr_exit()
        {
            TCritSect cs;
            
            if(--Kernel.ISR_NestCount) return;
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };
}
#endif // scmRTOS_BLACKFIN_H
//-----------------------------------------------------------------------------

