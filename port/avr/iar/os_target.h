//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   EWAVR (IAR Systems)
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
//*     AVR/IAR port by Harry E. Zhurov, Copyright (c) 2003-2015

#ifndef scmRTOS_AVR_H
#define scmRTOS_AVR_H

#include <inavr.h>

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
//
#ifndef __IAR_SYSTEMS_ICC__
#error "This file should only be compiled with IAR C++ Compiler"
#endif // __IAR_SYSTEMS_ICC__

#if (((__TID__ >> 8) & 0x7F) != 90)
#error "This file must be compiled for AVR processor only."
#endif

#if __VER__ < 412
#error "This file must be compiled by IAR C/C++ Compiler v4.12 or higher."
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
typedef uint8_t stack_item_t;
typedef uint8_t status_reg_t;

//-----------------------------------------------------------------------------
//
//      Target specific macros
//
//
#define OS_PROCESS    __task
#define OS_INTERRUPT  __interrupt
#define DUMMY_INSTR() __no_operation()
#define INLINE_PROCESS_CTOR INLINE

//-----------------------------------------------------------------------------
// Separate return stack required for IAR/AVR compiler
#define SEPARATE_RETURN_STACK  1


//-----------------------------------------------------------------------------
//
//     Include project-level configurations
//    !!! The order of includes is important !!!
//
#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"
#include <scmRTOS_defs.h>

//-----------------------------------------------------------------------------
//
//    Target-specific configuration macros
//
#ifdef scmRTOS_USER_DEFINED_STACK_PATTERN
#define scmRTOS_STACK_PATTERN scmRTOS_USER_DEFINED_STACK_PATTERN
#else
#define scmRTOS_STACK_PATTERN 0x5AU
#endif

#define scmRTOS_TARGET_IDLE_HOOK_ENABLE 0

//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
#if scmRTOS_USER_DEFINED_CRITSECT_ENABLE == 0
class TCritSect
{
public:
    TCritSect () : StatusReg(__save_interrupt()) { __disable_interrupt(); }
    ~TCritSect() { __restore_interrupt(StatusReg); }

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
//   AVR does not have nested interrupts.
//
#ifndef SYS_TIMER_CRIT_SECT
#define SYS_TIMER_CRIT_SECT() // TCritSect cs
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
struct TPrioMaskTable
{
    TPrioMaskTable()
    {
        TProcessMap pm = 0x01;
        for(uint8_t i = 0; i < sizeof(Table)/sizeof(Table[0]); i++)
        {
            Table[i] = pm;
            pm <<= 1;
        }
    }

    TProcessMap Table[scmRTOS_PROCESS_COUNT+1];
};
extern TPrioMaskTable PrioMaskTable;

INLINE OS::TProcessMap get_prio_tag(const uint_fast8_t pr) { return PrioMaskTable.Table[pr]; }

#if scmRTOS_PRIORITY_ORDER == 0
    INLINE uint8_t highest_priority(TProcessMap pm)
    {
        uint8_t pr = 0;

        while( !(pm & 0x0001) )
        {
            pr++;
            pm >>= 1;
        }
        return (TPriority)pr;
    }
#else
    INLINE TPriority highest_priority(TProcessMap pm)
    {
        uint8_t pr = scmRTOS_PROCESS_COUNT;

        while( !(pm & (1 << scmRTOS_PROCESS_COUNT) ) )
        {
            pr--;
            pm <<= 1;
        }
        return (TPriority)pr;
    }
#endif // scmRTOS_PRIORITY_ORDER
}


//-----------------------------------------------------------------------------
//
//     Interrupt and Interrupt Service Routines support
//
INLINE status_reg_t get_interrupt_state( )               { return __save_interrupt(); }
INLINE void         set_interrupt_state(status_reg_t sr) { __set_interrupt_state(sr); }

INLINE void enable_interrupts()  { __enable_interrupt();  }
INLINE void disable_interrupts() { __disable_interrupt(); }

#pragma segment="CSTACK"
#pragma segment="RSTACK"

#define  ABS_WORD(x)  (*((volatile uint16_t*)x))

INLINE stack_item_t* get_data_sp()   { return reinterpret_cast<stack_item_t*>(ABS_WORD(28)); }
INLINE stack_item_t* get_return_sp() { return reinterpret_cast<stack_item_t*>(SP); }

INLINE void set_isr_stack_pointers() 
{ 
    ABS_WORD(28) = reinterpret_cast<uint16_t>(__segment_end("CSTACK"));
    SP = reinterpret_cast<uint16_t>(__segment_end("RSTACK")) - 1;
}

INLINE void set_data_sp(stack_item_t* sp)   { ABS_WORD(28) = reinterpret_cast<uint16_t>(sp); }
INLINE void set_return_sp(stack_item_t* sp) { SP = reinterpret_cast<uint16_t>(sp); }

namespace OS
{
    INLINE void enable_context_switch()  { enable_interrupts();  }
    INLINE void disable_context_switch() { disable_interrupts(); }
}

#if scmRTOS_OBSOLETE_NAMES == 1

INLINE status_reg_t GetInterruptState( )               { return get_interrupt_state(); }
INLINE void         SetInterruptState(status_reg_t sr) { set_interrupt_state(sr);      }

INLINE void EnableInterrupts()  { enable_interrupts();  }
INLINE void DisableInterrupts() { disable_interrupts(); }

INLINE stack_item_t* GetDataSP()                   { return get_data_sp();     }
INLINE stack_item_t* GetReturnSP()                 { return get_return_sp();   }
INLINE void          SetDataSP(stack_item_t* sp)   { set_data_sp(sp);          }
INLINE void          SetReturnSP(stack_item_t* sp) { set_return_sp(sp);        }
INLINE void          SetISRStackPointers()         { set_isr_stack_pointers(); }

namespace OS
{
    INLINE void EnableContextSwitch()  { enable_context_switch();  }
    INLINE void DisableContextSwitch() { disable_context_switch(); }
}

#endif // scmRTOS_OBSOLETE_NAMES



//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
#include <os_kernel.h>
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
namespace OS
{
    struct TSavedSP
    {
        stack_item_t *DataSP;
        stack_item_t *ReturnSP;
    };

    extern TSavedSP SavedSP;
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
        INLINE void ISR_Enter() // volatile
        {
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
        {
            disable_interrupts();
            if(--Kernel.ISR_NestCount) return;
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };

    class TISRW_SS
    {
    public:
        INLINE  TISRW_SS()  { ISR_Enter(); }
        INLINE  ~TISRW_SS() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE void ISR_Enter() // volatile
        {
            if(Kernel.ISR_NestCount++ == 0)
            {
                 SavedSP.DataSP   = get_data_sp();
                 SavedSP.ReturnSP = get_return_sp();
                 set_isr_stack_pointers();
            }
        }
        //-----------------------------------------------------
        INLINE void ISR_Exit()
        {
            disable_interrupts();
            if(--Kernel.ISR_NestCount) return;
            set_return_sp(SavedSP.ReturnSP);
            set_data_sp  (SavedSP.DataSP);
            Kernel.sched_isr();
        }
        //-----------------------------------------------------
    };
}
//-----------------------------------------------------------------------------

#endif // scmRTOS_AVR_H
