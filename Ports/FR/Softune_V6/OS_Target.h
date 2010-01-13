//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: FR (Fujitsu)
//*
//*     TOOLKIT:   Softune Workbench V6 (Fujitsu)
//*               
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*               
//*     Version: 3.05
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
//********************************************************************************
//*
//*     FR port by Sergey Pinigin, Copyright (c) 2007-2008
//*
//********************************************************************************

#ifndef scmRTOS_FR_H
#define scmRTOS_FR_H

#include <commdefs.h>


#ifndef __COMPILER_FCC911__
#error "This file should only be compiled with SOFTUNE Workbench Compiler"
#endif

#if scmRTOS_PROCESS_COUNT > 30
#error "Process count is too much! Currently up 30 processes is supported."
#endif



//-----------------------------------------------------------------------------
//
///    scmRTOS Context Switch Scheme
///
///    The macro defines a context switch manner. Value 0 sets direct context
///    switch in the scheduler and in the OS ISRs. This is the primary method.
///    Value 1 sets the second way to switch context - by using of software
///    interrupt. See documentation fo details.
///
///    WARNING
///    The only Software Interrupt Context Switch Scheme supported for FR CPU!
//
//
#define scmRTOS_CONTEXT_SWITCH_SCHEME       1
//-----------------------------------------------------------------------------
//
///    scmRTOS Priority Order
///
///    This macro defines the order of the process's priorities. Default,
///    the ascending order is used. Alternatively, the descending priority
///    order can be used. On some platforms the descending order is preferred
///    because of performance.
///
///    WARNING
///    The only alternative (corresponding to descending order) supported for
///    FR CPU! Value of macro is 1.
//
//
#define scmRTOS_PRIORITY_ORDER              1

//-----------------------------------------------------------------------------
//
///    scmRTOS System Timer
//
///    Nested Interrupts Enable macro. Value 1 means that interrupts are
///    globally enabled within System Timer ISR.
//
//
#define scmRTOS_SYSTIMER_NEST_INTS_ENABLE   1



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
#define REGS 
#define OS_PROCESS
#define DUMMY_INSTR()
#define INLINE_PROCESS_CTOR
//__wait_nop()

//--------------------------------------------------
//
//   Uncomment macro value below for SystemTimer() run in critical section
// 
//   This is useful (and necessary) when target processor has hardware 
//   enabled nested interrups. 
// 
#define SYS_TIMER_CRIT_SECT() // TCritSect cs

#define SEPARATE_RETURN_STACK 0

//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_config.h"
#include "scmRTOS_TARGET_CFG.h"
#include <scmRTOS_defs.h>

//-----------------------------------------------------------------------------
//
//
//
extern "C" TStatusReg   _cli();
extern "C" void         _sti(TStatusReg StatusReg);

///     The Critital Section Wrapper
class TCritSect
{
public:
    TCritSect () : StatusReg(_cli()) { }
    ~TCritSect() { _sti(StatusReg); }

private:
    TStatusReg StatusReg;
};
//-----------------------------------------------------------------------------
//
//    Priority stuff
//
//
namespace OS
{
    INLINE inline TProcessMap GetPrioTag(const byte pr) { return 1<<pr; }
    
    inline byte GetHighPriority(TProcessMap pm)
    {
        BSD1 = pm;
        return 31 - BSRR;
    }
}
//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
//INLINE inline TStatusReg GetInterruptState( )             {  }
INLINE inline void SetInterruptState()      { }

INLINE inline void EnableInterrupts()       { }
INLINE inline void DisableInterrupts()      { __set_il(scmRTOS_OS_DI_LEVEL); }

INLINE inline void EnableContextSwitch()    { }
INLINE inline void DisableContextSwitch()   { }

//-----------------------------------------------------------------------------
//
///   OS ISR prototypes

extern "C" void ContextSwitcher_ISR(void);

#define  LOCK_SYSTEM_TIMER()
#define  UNLOCK_SYSTEM_TIMER()
//-----------------------------------------------------------------------------

namespace OS
{
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
#endif

    inline void RaiseContextSwitch()
    {
        DICR = 1;
        //__asm(" int #63 ");
    } ///< raise software interrupt
    void SystemTimer_ISR(void);

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
#include <OS_Kernel.h>
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
    //! OS ISR support

    //! Implements common actions on interrupt enter and exit
    //! under the OS
    class TISRW
    {
    public:
        INLINE  TISRW()  { ISR_Enter(); }
        INLINE  ~TISRW() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE void ISR_Enter()
        {
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
        {
            DisableInterrupts();
            if(--Kernel.ISR_NestCount) return;
            Kernel.SchedISR();
        }
        //-----------------------------------------------------
    };
}
#endif // scmRTOS_FR_H
//-----------------------------------------------------------------------------
