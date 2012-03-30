//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   EWARM (IAR Systems)
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

#ifndef scmRTOS_ARM_H
#define scmRTOS_ARM_H

#ifndef __IAR_SYSTEMS_ICC__
#error "This file should only be compiled with IAR C/EC++ Compiler"
#endif // __IAR_SYSTEMS_ICC__

#ifndef __ICCARM__
#error "This file must be compiled for ARM processor only."
#endif

#if __VER__ < 420
#error "This file must be compiled by IAR C/C++ Compiler v4.20 or higher."
#endif

//------------------------------------------------------------------------------
//
//    Compiler specific attributes
//
//
#ifndef INLINE
#define INLINE  _Pragma("inline=forced") inline
#endif

//-----------------------------------------------------------------------------
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

//--------------------------------------------------
//
//   Uncomment macro value below for SystemTimer() run in critical section
//
//   This is useful (and necessary) when target processor has hardware
//   enabled nested interrups. ARM7 does not have such interrupts.
//
#define SYS_TIMER_CRIT_SECT() // TCritSect cs

//--------------------------------------------------
// Separate return stack not required
#define SEPARATE_RETURN_STACK   0

//--------------------------------------------------
// software interrupt stack switching not supported in ARM port
// because ARM architecture implements hardware stack switching.
// So, system timer irq wrapper can't be choosen at project level
#define scmRTOS_ISRW_TYPE       TISRW

//-----------------------------------------------------------------------------
//
//    scmRTOS Priority Order
//
//    This macro defines the order of the process's priorities.
//    The ascending order is used, because of a little bit better performance.
//    Descending order is not implemented in ARM7 port
//
#define  scmRTOS_PRIORITY_ORDER 0

//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_config.h"
#include "scmRTOS_TARGET_CFG.h"
#include <OS_Target_core.h>
#include <scmRTOS_defs.h>


#define OS_PROCESS                          // ordinary function

#include <inarm.h>
#define DUMMY_INSTR() __no_operation()

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0x87654321U
#endif
//-----------------------------------------------------------------------------
//
//    wrappers to allow ARM mode intrinsics call from THUMB sources
//
#if __CPU_MODE__ == 2   // ARM
INLINE status_reg_t get_interrupt_state() { return __get_CPSR(); }
INLINE void set_interrupt_state(status_reg_t sr) { __set_CPSR_c(sr);}
#else                   // THUMB
extern __arm status_reg_t get_interrupt_state();
extern __arm void set_interrupt_state(status_reg_t sr);
#endif


//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
class TCritSect
{
public:
    TCritSect ();
    ~TCritSect();
private:
    status_reg_t StatusReg;
};

// Atmel Application Note Rev. 1156A–08/98
INLINE TCritSect::TCritSect() : StatusReg( get_interrupt_state() )
{
    status_reg_t Tmp = StatusReg;

    while ((Tmp & (1<<7)) == 0)
    {
        set_interrupt_state(Tmp | (1<<7));  // disable IRQ
        Tmp = get_interrupt_state();        // re-read cpsr
    }
};

INLINE TCritSect::~TCritSect()
{
    set_interrupt_state(StatusReg);
};

namespace OS
{
//------------------------------------------------------------------------------
//
//       Idle process stuff
//
//
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void idle_process_user_hook();
#endif

//------------------------------------------------------------------------------
//
//       Declaring system timer handler
//
//
    #if scmRTOS_OBSOLETE_NAMES == 0
    OS_INTERRUPT
    #endif
                    void system_timer_isr();

//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//
    INLINE TProcessMap get_prio_tag(const uint_fast8_t pr)
    {
        return static_cast<TProcessMap> (1 << pr);
    }

    INLINE TPriority highest_priority(TProcessMap pm)
    {
        extern TPriority const PriorityTable[];

        #if scmRTOS_PROCESS_COUNT < 6
            return PriorityTable[pm];
        #else
            // Thanks to sergeeff, Yuri Tiomkin, Alexey Musin

            // http://www.hackersdelight.org/HDcode/ntz.cc
            uint32_t x = pm;
            x = x & -x;                             // Isolate rightmost 1-bit.

                                                // x = x * 0x450FBAF
            x = (x << 4) | x;                       // x = x*17.
            x = (x << 6) | x;                       // x = x*65.
            x = (x << 16) - x;                      // x = x*65535.

            return PriorityTable[x >> 26];
        #endif  // scmRTOS_PROCESS_COUNT < 6
    }
}   //  namespace


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE void enable_interrupts() { set_interrupt_state(get_interrupt_state() & ~(1<<7)); }
INLINE void disable_interrupts()
{
    status_reg_t Tmp = get_interrupt_state();
    do
    {
        set_interrupt_state(Tmp | (1<<7));
        Tmp = get_interrupt_state();
    }
    while (!(Tmp & (1<<7)));
}

#if scmRTOS_OBSOLETE_NAMES == 1

INLINE status_reg_t GetInterruptState( )             { return get_interrupt_state(); }
INLINE void       SetInterruptState(status_reg_t sr) { set_interrupt_state(sr);      }

INLINE void EnableInterrupts()  { enable_interrupts();  }
INLINE void DisableInterrupts() { disable_interrupts(); }

#endif // scmRTOS_OBSOLETE_NAMES

namespace OS
{
    INLINE void enable_context_switch()  { enable_interrupts(); }
    INLINE void disable_context_switch() { disable_interrupts(); }
}

#include <OS_Kernel.h>

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
        INLINE TISRW();
        INLINE ~TISRW();
    private:
    };

    // no software interrupt stack switching provided,
    // TISRW_SS declared to be the same as TISRW for porting compability
    #define TISRW_SS    TISRW
    //--------------------------------------------------------------------------
    //
    //      OS system timer handler
    //
    INLINE void system_timer_handler()
    {
        Kernel.system_timer();
    #if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
        system_timer_user_hook();
    #endif
    }

    #if scmRTOS_OBSOLETE_NAMES == 1

    INLINE OS_INTERRUPT void SystemTimer_ISR() { system_timer_isr(); }

    #endif // scmRTOS_OBSOLETE_NAMES

}   //  namespace OS

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
extern "C" __arm void save_sp(stack_item_t** Curr_SP);
extern "C" __arm void load_sp(stack_item_t* New_SP);


OS::TISRW::TISRW()
{
    if(Kernel.ISR_NestCount++ == 0)
    {
        save_sp(&TKernel::ProcessTable[Kernel.CurProcPriority]->StackPointer);
    }
}

OS::TISRW::~TISRW()
{
    if(--Kernel.ISR_NestCount) return;

    TPriority NextProcPriority = highest_priority(Kernel.ReadyProcessMap);
    stack_item_t*  Next_SP = TKernel::ProcessTable[NextProcPriority]->StackPointer;
    Kernel.CurProcPriority = NextProcPriority;
    load_sp(Next_SP);
    IRQ_DONE();
}

#else   // scmRTOS_CONTEXT_SWITCH_SCHEME == 1
OS::TISRW::TISRW()
{
    Kernel.ISR_NestCount++;
}

OS::TISRW::~TISRW()
{
    disable_interrupts();
    if(--Kernel.ISR_NestCount == 0)
        Kernel.sched_isr();
    IRQ_DONE();
}

#if scmRTOS_OBSOLETE_NAMES == 1
#define ContextSwitcher_ISR         context_switcher_isr
#endif // scmRTOS_OBSOLETE_NAMES

#endif  // scmRTOS_CONTEXT_SWITCH_SCHEME

//-----------------------------------------------------------------------------
#endif // scmRTOS_ARM_H
