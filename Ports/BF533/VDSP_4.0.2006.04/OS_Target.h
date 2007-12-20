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
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
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
//******************************************************************************

#ifndef scmRTOS_BLACKFIN_H
#define scmRTOS_BLACKFIN_H

#include <commdefs.h>


#ifndef __ADSPBLACKFIN__
#error "This file should only be compiled with VDSP Blackfin Compiler!"
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME != 1
#error "The only Software Interrupt Context Switch Scheme supported for Blackfin!"
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
typedef word  TStatusReg;

//-----------------------------------------------------------------------------
//
//    Configuration macros
//
//
#define INLINE
#define REGS "r0-r7 p0-p5 ASTAT i0-i3 b0-b3 l0-l3 m0-m3 lt0 lt1 lb0 lb1 lc0 lc1 a0 a1 cc"
#define OS_PROCESS _Pragma("regs_clobbered REGS")
#define DUMMY_INSTR() asm(" nop;")

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
//     The Critital Section Wrapper
//
//
class TCritSect
{
public:
    TCritSect () : StatusReg(cli()) { }
    ~TCritSect() { sti(StatusReg); }

private:
    TStatusReg StatusReg;
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
        byte pr;
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
INLINE inline TStatusReg GetInterruptState( )             { return cli(); }
INLINE inline void       SetInterruptState(TStatusReg sr) { sti(sr); }

INLINE inline void EnableInterrupts()  { sti( 0xffe0 );  }
INLINE inline void DisableInterrupts() { }

INLINE inline void EnableContextSwitch()  { sti( 0xc000 );  }
INLINE inline void DisableContextSwitch() { cli( ); }

//-----------------------------------------------------------------------------
//
//    ISR prototypes
//
extern "C" void ContextSwitcher_ISR(int, int, int);

#define  LOCK_SYSTEM_TIMER()
#define  UNLOCK_SYSTEM_TIMER()
//-----------------------------------------------------------------------------

namespace OS
{
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
#endif

    inline void RaiseContextSwitch() { asm(" raise 14;"); } // raise software interrupt
    void SystemTimer_ISR(int, int, int);

}
//-----------------------------------------------------------------------------
/*
#pragma segment="CSTACK"

INLINE inline TStackItem* GetStackPointer()    { return (TStackItem*) __get_SP_register(); }
INLINE inline void        SetISRStackPointer() { __set_SP_register( (word) __segment_end("CSTACK") ); }
INLINE inline void        SetStackPointer(TStackItem* sp) { __set_SP_register( (word)sp ); }
*/
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
  /*
    class TISRW_SS
    {
    public:
        INLINE  TISRW_SS()  { ISR_Enter(); }
        INLINE  ~TISRW_SS() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE void ISR_Enter()
        {
            if(Kernel.ISR_NestCount++ == 0)
            {
                Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer = GetStackPointer();
                SetISRStackPointer();
            }
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
        {
            DisableInterrupts();
            if(--Kernel.ISR_NestCount) return;
            SetStackPointer(Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer);
            Kernel.SchedISR();
        }
        //-----------------------------------------------------
    };
    */
}
#endif // scmRTOS_BLACKFIN_H
//-----------------------------------------------------------------------------

