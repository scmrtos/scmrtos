//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   arm-elf-gcc (GNU)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version:   3.05
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2009, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2009

#ifndef scmRTOS_ARM_H
#define scmRTOS_ARM_H

#include <commdefs.h>

#ifndef __GNUC__
#error "This file should only be compiled with GNU C++ Compiler"
#endif // __GNUC__

#ifndef __ARM_ARCH_4T__
#error "This file must be compiled for ARM7TDMI processor only."
#endif

#if (__GNUC__ < 3)
#error "This file must be compiled by GCC C/C++ Compiler v3.0 or higher."
#endif

#ifdef  __THUMBEL__
#error "This file should be compiled in ARM mode only"
#endif // __thumb__

//-----------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef dword TStackItem;
typedef dword TStatusReg;


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
#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"
#include <OS_Target_core.h>
#include <scmRTOS_defs.h>


#define OS_PROCESS      __attribute__((__noreturn__))
#define DUMMY_INSTR()   __asm__ __volatile__ ("nop" : : )

//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
class TCritSect
{
public:
    INLINE TCritSect ();
    INLINE ~TCritSect();
private:
    TStatusReg StatusReg;
};

INLINE inline TStatusReg __get_CPSR()
{
    TStatusReg cpsr;
    asm volatile 
    (
    " MRS  %0,CPSR    \r\n"
    :"=r"(cpsr)
    :
    );
    return cpsr;
}
INLINE inline void __set_CPSR_c(TStatusReg cpsr)
{
    asm volatile 
    (
    " MSR  CPSR_c, %0    \r\n"
    :
    :"r"(cpsr)
    );
}
// Atmel Application Note Rev. 1156A–08/98
inline TCritSect::TCritSect() : StatusReg( __get_CPSR() )
{
    TStatusReg Tmp = StatusReg;
    while (!(Tmp & (1<<7)))
    {
        __set_CPSR_c(Tmp | (1<<7));   // disable IRQ
        Tmp = __get_CPSR();
    }
};

inline TCritSect::~TCritSect()
{
    __set_CPSR_c(StatusReg);
};

namespace OS
{
//------------------------------------------------------------------------------
//
//       Idle process stuff
//
//
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
#endif

//------------------------------------------------------------------------------
//
//       Declaring system timer handler
//
//
    OS_INTERRUPT void SystemTimer_ISR();

//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//

    INLINE inline OS::TProcessMap GetPrioTag(const byte pr)
    {
        return static_cast<OS::TProcessMap> (1 << pr);
    }

#if scmRTOS_PROCESS_COUNT < 6
    extern TPriority const PriorityTable[1 << (scmRTOS_PROCESS_COUNT + 1)];
    // #define used instead of inline function to ensure inlining to both ARM and THUMB functions.
    #define GetHighPriority(pm)     OS::PriorityTable[pm]
#else
    // Thanks to sergeeff, Yuri Tiomkin, Alexey Musin
    INLINE inline TPriority GetHighPriority(TProcessMap pm)
    {
        extern TPriority const PriorityTable[64];

        // http://www.hackersdelight.org/HDcode/ntz.cc
        dword x = pm;
        x = x & -x;                             // Isolate rightmost 1-bit.

                                                // x = x * 0x450FBAF
        x = (x << 4) | x;                       // x = x*17.
        x = (x << 6) | x;                       // x = x*65.
        x = (x << 16) - x;                      // x = x*65535.

        return PriorityTable[x >> 26];
    }
#endif  // scmRTOS_PROCESS_COUNT < 6
}   //  namespace


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
//inline __arm TStatusReg GetInterruptState() { return __get_CPSR(); }
//inline __arm void SetInterruptState(TStatusReg sr) { __set_CPSR(sr);}

INLINE inline void EnableInterrupts() { __set_CPSR_c(__get_CPSR() & ~(1<<7)); }
INLINE inline void DisableInterrupts()
{
    TStatusReg Tmp = __get_CPSR();
    while (!(Tmp & (1<<7)))
    {
        __set_CPSR_c(Tmp | (1<<7));
        Tmp = __get_CPSR();
    }
}

namespace OS
{
    INLINE inline void EnableContextSwitch()  { EnableInterrupts(); }
    INLINE inline void DisableContextSwitch() { DisableInterrupts(); }
}

//-----------------------------------------------------------------------------
//
//     Kernel-related inline functions
//
//
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
extern "C" INLINE inline void OS_ContextSwitcher(TStackItem** Curr_SP, TStackItem* Next_SP)
{
//  commented lines below makes compiled code shorter
//    register TStackItem* arg asm("r1");
//    arg = Next_SP;
    asm volatile(
        //  - store -
        "STMFD  SP!, {R0-R12,LR}        \r\n"   // store R0_R12, LR to reserve space in context
        "MRS    r2, CPSR                \r\n"   // move CPSR of process to register
        "STMFD  SP!, {r2,LR}            \r\n"   // store CPSR, LR on top of context and adjust SP
        "ADR    LR, 1f                  \r\n"   // load context switcher exit address,
                                                // to branch to if context stored in OS_ContextSwitcher
        "STR    LR, [SP, #4*15]         \r\n"   // store return address in reserved space (instead of first saved LR)
        "STR    SP, [%0]                \r\n"
        //  - restore -
        "LDMFD   %1!, {r2, LR}          \r\n"   // restoring LR_user, saved CPSR_user
        "ADD     SP, %1, #4*14          \r\n"   // set process SP

        "MSR     CPSR_c, %2             \r\n"   // switch to IRQ mode to get access to SPSR_irq
        "MSR     SPSR_cxsf, r2          \r\n"   // store process CPSR to SPSR_irq to restore at return from irq

        "LDMFD   %1, {R0-R12,PC}^       \r\n"   // restoring remaining context, CPSR and reti
"1:"

        :
        :"r"(Curr_SP), "r"(Next_SP), "n"(NIRQ | MODE_IRQ)
        :"r2"
    );
}
#endif
extern "C" __attribute__((__noreturn__)) void ContextRestore(TStackItem* sp);
extern "C" __attribute__((__noreturn__)) 
INLINE inline void OS_Start(TStackItem* sp)
{
    ContextRestore(sp);
}
//-----------------------------------------------------------------------------
//
//   GCC requires functions and clsses be declared before declaring as friends
//
namespace OS
{
    void Run();
    class TBaseProcess;
}

#include <OS_Kernel.h>

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
        INLINE TISRW();
        INLINE ~TISRW();
    private:
    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
        INLINE void SaveSP(TStackItem** Curr_SP);
        INLINE void LoadSP(TStackItem* New_SP);
    #endif
    };

    // no software interrupt stack switching provided,
    // TISRW_SS declared to be the same as TISRW for porting compability
    #define TISRW_SS    TISRW

}   //  namespace OS

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
inline void OS::TISRW::SaveSP(TStackItem** Curr_SP)
{
    asm volatile (
        "MSR     CPSR_c, %1     \r\n" // switching to System mode, to get access to sp_user
        "STR     SP, [%0]       \r\n"
        "MSR     CPSR_c, %2     \r\n" // switching back to IRQ mode
        :
        :"r"(Curr_SP),"n"(NIRQ | MODE_SYS), "n"(NIRQ | MODE_IRQ)
    );
}
inline void OS::TISRW::LoadSP(TStackItem* New_SP)
{
    asm volatile (
        "MSR     CPSR_c, %1     \r\n" // switching to System mode, to get access to sp_user
        "MOV     SP, %0         \r\n"
        "MSR     CPSR_c, %2     \r\n" // switching back to IRQ mode
        :
        :"r"(New_SP),"n"(NIRQ | MODE_SYS), "n"(NIRQ | MODE_IRQ)
    );
}
inline OS::TISRW::TISRW()
{
    if(Kernel.ISR_NestCount++ == 0)
    {
        SaveSP(&Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer);
    }
}
inline OS::TISRW::~TISRW()
{
    if(--Kernel.ISR_NestCount) return;

    TPriority NextProcPriority = GetHighPriority(Kernel.ReadyProcessMap);
    TStackItem*  Next_SP = Kernel.ProcessTable[NextProcPriority]->StackPointer;
    Kernel.CurProcPriority = NextProcPriority;
    LoadSP(Next_SP);
}
#else
inline OS::TISRW::TISRW()
{
    Kernel.ISR_NestCount++;
}
INLINE inline OS::TISRW::~TISRW()
{
    DisableInterrupts();
    if(--Kernel.ISR_NestCount) return;
    Kernel.SchedISR();
}
#endif

#endif // scmRTOS_ARM_H
