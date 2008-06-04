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
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2008

#ifndef scmRTOS_ARM_H
#define scmRTOS_ARM_H

#include <commdefs.h>
#include <inarm.h>

#ifndef __IAR_SYSTEMS_ICC__
#error "This file should only be compiled with IAR C/EC++ Compiler"
#endif // __IAR_SYSTEMS_ICC__

#ifndef __ICCARM__
#error "This file must be compiled for ARM processor only."
#endif

#if __VER__ < 420
#error "This file must be compiled by IAR C/C++ Compiler v4.20 or higher."
#endif

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
#include "scmRTOS_config.h"
#include "scmRTOS_TARGET_CFG.h"
#include <OS_Target_core.h>
#include <scmRTOS_defs.h>


#define OS_PROCESS                          // ordinary function
#define DUMMY_INSTR() __no_operation()

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
    TStatusReg StatusReg;
};

// Atmel Application Note Rev. 1156A–08/98
inline __arm TCritSect::TCritSect() : StatusReg( __get_CPSR() )
{
    TStatusReg Tmp = StatusReg;

    while ((Tmp & (1<<7)) == 0)
    {
        __set_CPSR(Tmp | (1<<7));   // disable IRQ
        Tmp = __get_CPSR();         // re-read cpsr
    }
};

inline __arm TCritSect::~TCritSect()
{
    __set_CPSR(StatusReg);
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

    inline OS::TProcessMap GetPrioTag(const byte pr)
    {
        return static_cast<OS::TProcessMap> (1 << pr);
    }

#if scmRTOS_PROCESS_COUNT < 6
    extern TPriority const PriorityTable[1 << scmRTOS_PROCESS_COUNT + 1];
    // #define used instead of inline function to ensure inlining to both ARM and THUMB functions.
    #define GetHighPriority(pm)     OS::PriorityTable[pm]
#else
    // Thanks to sergeeff, Yuri Tiomkin, Alexey Musin
    inline TPriority GetHighPriority(TProcessMap pm)
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
inline __arm TStatusReg GetInterruptState() { return __get_CPSR(); }
inline __arm void SetInterruptState(TStatusReg sr) { __set_CPSR(sr);}

inline __arm void EnableInterrupts() { __set_CPSR(__get_CPSR() & ~(1<<7)); }
inline __arm void DisableInterrupts()
{
    TStatusReg Tmp = __get_CPSR();
    while ((Tmp & (1<<7)) == 0)
    {
        __set_CPSR(Tmp | (1<<7));   // disable IRQ
        Tmp = __get_CPSR();         // re-read cpsr
    }
}

namespace OS
{
    INLINE inline void EnableContextSwitch()  { EnableInterrupts(); }
    INLINE inline void DisableContextSwitch() { DisableInterrupts(); }
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
        inline TISRW();
        inline ~TISRW();
    private:
    };

    // no software interrupt stack switching provided,
    // TISRW_SS declared to be the same as TISRW for porting compability
    #define TISRW_SS    TISRW

}   //  namespace OS

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
extern "C" __arm void SaveSP(TStackItem** Curr_SP);
extern "C" __arm void Set_New_SP(TStackItem* New_SP);

__arm inline OS::TISRW::TISRW()
{
    if(Kernel.ISR_NestCount++ == 0)
    {
        SaveSP(&Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer);
    }
}
__arm inline OS::TISRW::~TISRW()
{
    if(--Kernel.ISR_NestCount == 0)
    {
        TPriority NextProcPriority = GetHighPriority(Kernel.ReadyProcessMap);
        TStackItem*  Next_SP = Kernel.ProcessTable[NextProcPriority]->StackPointer;
        Kernel.CurProcPriority = NextProcPriority;
        Set_New_SP(Next_SP);
    }
    IRQ_DONE();
}
#else   // scmRTOS_CONTEXT_SWITCH_SCHEME == 1
__arm inline OS::TISRW::TISRW()
{
    Kernel.ISR_NestCount++;
}
__arm inline OS::TISRW::~TISRW()
{
    DisableInterrupts();
    if(--Kernel.ISR_NestCount == 0)
        Kernel.SchedISR();
    IRQ_DONE();
}
#endif  // scmRTOS_CONTEXT_SWITCH_SCHEME

//-----------------------------------------------------------------------------
#endif // scmRTOS_ARM_H
