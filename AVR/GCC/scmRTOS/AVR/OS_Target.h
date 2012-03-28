//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   avr-gcc (GNU)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Declarations And Definitions
//*
//*     Version: 3.11
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007-2012

#ifndef scmRTOS_AVR_H
#define scmRTOS_AVR_H

#include <commdefs.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//------------------------------------------------------------------------------
//
//    Compiler and Target checks
//
//
#ifndef __GNUC__
#error "This file should only be compiled with GCC C++ Compiler"
#endif // __GNUC__

#ifndef __AVR_ARCH__
#error "This file must be compiled for AVR processor only."
#endif

#ifdef __AVR_3_BYTE_PC__
#error "AVRs with 3-byte program counter not suported by this scmRTOS port"
#endif

#ifndef SPH
#error "AVRs with 1-byte stack pointer (no more than 160 bytes of RAM) not suported by this scmRTOS port"
#endif

//
#if (__GNUC__ < 3)
#error "This file must be compiled by AVR-GCC C/C++ Compiler v3.0 or higher."
#endif

//------------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef byte TStackItem;
typedef byte TStatusReg;

//-----------------------------------------------------------------------------
//
//      Target specific macros
//

#define	OS_PROCESS	NORETURN

#ifdef __INTR_ATTRS	/* default ISR attributes from avr/interrupt.h */
# define	OS_INTERRUPT	extern "C" __attribute__((__signal__,__INTR_ATTRS))
#else
# define	OS_INTERRUPT	extern "C" __attribute__((__signal__))
#endif

#define	DUMMY_INSTR()	__asm__ __volatile__ ("nop" : : )

#define	INLINE_PROCESS_CTOR INLINE inline

//--------------------------------------------------
//
//   Uncomment macro value below for SystemTimer() run in critical section
//
//   This is useful (and necessary) when target processor has hardware
//   enabled nested interrups. AVR does not have such interrupts.
//
#define SYS_TIMER_CRIT_SECT() // TCritSect cs

#define SEPARATE_RETURN_STACK  0


//-----------------------------------------------------------------------------
//
//

#include "scmRTOS_CONFIG.h"
#include "scmRTOS_TARGET_CFG.h"
#include <scmRTOS_defs.h>

//-----------------------------------------------------------------------------
//      allow some optimization
extern "C" NORETURN void OS_Start(TStackItem* sp);


//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
class TCritSect
{
public:
    TCritSect () : StatusReg( SREG ) { cli(); }
    ~TCritSect() { SREG = StatusReg; }
    //~TCritSect() { if( StatusReg & (1 << SREG_I)) sei(); }

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
struct TPrioMaskTable
{
    TPrioMaskTable()
    {
        TProcessMap pm = 0x01;
        for(byte i = 0; i < sizeof(Table)/sizeof(Table[0]); i++)
        {
            Table[i] = pm;
            pm <<= 1;
        }
    }

    TProcessMap Table[scmRTOS_PROCESS_COUNT+1];
};
extern TPrioMaskTable PrioMaskTable;

INLINE inline OS::TProcessMap GetPrioTag(const byte pr) { return PrioMaskTable.Table[pr]; }

#if scmRTOS_PRIORITY_ORDER == 0
    INLINE inline byte GetHighPriority(TProcessMap pm)
    {
        byte pr = 0;

        while( !(pm & 0x0001) )
        {
            pr++;
            pm >>= 1;
        }
        return (TPriority)pr;
    }
#else
    INLINE inline TPriority GetHighPriority(TProcessMap pm)
    {
        byte pr = scmRTOS_PROCESS_COUNT;

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
INLINE inline TStatusReg GetInterruptState( )             { return SREG; }
INLINE inline void       SetInterruptState(TStatusReg sr) { SREG = sr; }

INLINE inline void EnableInterrupts() { sei();  }
INLINE inline void DisableInterrupts() { cli(); }


INLINE inline TStackItem* GetStackPointer() { return reinterpret_cast<TStackItem*>(SP); }

static INLINE inline word GetInitialStack()
{
    // symbol from gcrt1.S, initial stack value, set to RAMEND by default
    extern uint8_t __stack;
    return reinterpret_cast<word>(&__stack);
}

INLINE inline void SetISRStackPointer()
{
    /* !!!
     * inital stack position can be used, but things not so easy - main() can have
     * local variables and return address
     * But...  OS::Run() never returns and stack can be used ?
     *
     */
    SP = GetInitialStack();
}

INLINE inline void SetStackPointer(TStackItem* sp) { SP = reinterpret_cast<word>(sp); }

namespace OS
{
    INLINE inline void EnableContextSwitch()  { EnableInterrupts();  }
    INLINE inline void DisableContextSwitch() { DisableInterrupts(); }
}

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
        INLINE  inline TISRW()  { ISR_Enter(); }
        INLINE  inline ~TISRW() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE inline void ISR_Enter() // volatile
        {
            Kernel.ISR_NestCount++;
        }
        //-----------------------------------------------------
        INLINE inline void ISR_Exit()
        {
            DisableInterrupts();
            if(--Kernel.ISR_NestCount) return;
            Kernel.SchedISR();
        }
        //-----------------------------------------------------
    };

    class TISRW_SS
    {
    public:
        INLINE inline TISRW_SS()  { ISR_Enter(); }
        INLINE inline ~TISRW_SS() { ISR_Exit();  }

    private:
        //-----------------------------------------------------
        INLINE inline void ISR_Enter() // volatile
        {
            if(Kernel.ISR_NestCount++ == 0)
            {
                Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer = GetStackPointer();
                SetISRStackPointer();
            }
        }
        //-----------------------------------------------------
        INLINE inline void ISR_Exit()
        {
            DisableInterrupts();
            if(--Kernel.ISR_NestCount) return;
            SetStackPointer(Kernel.ProcessTable[Kernel.CurProcPriority]->StackPointer);
            Kernel.SchedISR();
        }
        //-----------------------------------------------------
    };
}
//-----------------------------------------------------------------------------

#endif // scmRTOS_AVR_H

