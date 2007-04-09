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
//*     Version:   3.00-beta
//*
//*     $Revision: 1 $
//*     $Date: 2006-12-15 12:51:04 +0500 (Пт, 15 дек 2006) $
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
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
//*     FR port by Sergey Pinigin, Copyright (c) 2007
//*
//********************************************************************************

#ifndef scmRTOS_FR_H
#define scmRTOS_FR_H

#include <commdefs.h>


#ifndef __COMPILER_FCC911__
#error "This file should only be compiled with SOFTUNE Workbench Compiler"
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME != 1
#warning "The only Software Interrupt Context Switch Scheme supported for FR CPU!"
#define scmRTOS_CONTEXT_SWITCH_SCHEME 1
#endif

#if scmRTOS_PROCESS_COUNT > 30
#error "Process count is too much! Currently up 30 processes is supported."
#endif


//-----------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef dword TStackItem;
//typedef word  TStatusReg;

//-----------------------------------------------------------------------------
//
//    Configuration macros
//
//
#define INLINE
#define REGS 
#define OS_PROCESS
#define DUMMY_INSTR()
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

#include "scmRTOS_TARGET_CFG.h"

//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
class TCritSect
{
public:
    TCritSect () { __DI(); }
    ~TCritSect() { __EI(); }

//private:
//    TStatusReg StatusReg;
};
//-----------------------------------------------------------------------------
//
//     Priority stuff
//
//
namespace OS
{
    INLINE inline TProcessMap GetPrioTag(const byte pr) { return 1<<pr; }
    
#if scmRTOS_PRIORITY_ORDER == 0
    inline byte GetHighPriority(TProcessMap pm)
    {
        byte pr = 0;

        while( !(pm & 0x0001) )
        {
            pr++;
            pm >>= 1;
        }
        return pr;
    }
#else
    inline byte GetHighPriority(TProcessMap pm)
    {
        BSD1 = pm;
        return 31 - BSRR;
    }
#endif // scmRTOS_PRIORITY_ORDER
}
//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
//INLINE inline TStatusReg GetInterruptState( )             {  }
INLINE inline void SetInterruptState()      { }

INLINE inline void EnableInterrupts()       { }
INLINE inline void DisableInterrupts()      { __DI(); }

INLINE inline void EnableContextSwitch()    { }
INLINE inline void DisableContextSwitch()   { }

//-----------------------------------------------------------------------------
//
//    ISR prototypes
//
extern "C" void ContextSwitcher_ISR(void);

#define  LOCK_SYSTEM_TIMER()
#define  UNLOCK_SYSTEM_TIMER()
//-----------------------------------------------------------------------------

namespace OS
{
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
#endif

    inline void RaiseContextSwitch() { asm(" int #63 "); } // raise software interrupt
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
#endif // scmRTOS_BLACKFIN_H
//-----------------------------------------------------------------------------
