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
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version:   3.00-beta
//*
//*     $Revision: 31 $
//*     $Date: 2007-02-08 18:51:14 +0600 (Чт, 08 фев 2007) $
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007

#include <scmRTOS.h>

using namespace OS;

OS::TPrioMaskTable OS::PrioMaskTable;


//    AVR hardware stack pointer (SP) points to empty location, post-decrement used,
//  "push reg" is "*SP-- = reg"
//    StackPointer point to first element _after_ stack memory and *--StackPointer places
//  values in right positions, but StackPointer must be decremented by 1 more than items
//  "pushed"

#define REGS_COUNT 31 // all except r1 (aka __zero_reg__)

#ifdef RAMPZ
    #define RAMPZ_PLACE 1
#else
    #define RAMPZ_PLACE 0
#endif

// __AVR_3_BYTE_PC__  not supported yet, EIND_PLACE not added

// all except r1 + saved SFRs + "post-decrement correction"
#define STACK_POINTER_CORRECTION ((REGS_COUNT) + (RAMPZ_PLACE) + 1)


//------------------------------------------------------------------------------
//
//

OS::TBaseProcess::TBaseProcess(TStackItem* Stack, TPriority pr, void (*exec)())
    : StackPointer(Stack)
    , Timeout(0)
    , Priority(pr)
{
    Kernel.RegisterProcess(this);

    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
    *(--StackPointer) = reinterpret_cast<word>(exec);       // return from interrupt address (low  byte)
    *(--StackPointer) = reinterpret_cast<word>(exec) >> 8;  // return from interrupt address (high byte)
    *(--StackPointer) = 0;                                  // initalize __zero_reg__ for this process
    *(--StackPointer) = (1 << SREG_I);                      // SREG value: I-bit set, enable interrupts
    StackPointer     -= STACK_POINTER_CORRECTION;
}
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//
//    Idle Process
//
//
typedef process<prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;

namespace OS {

template<> OS_PROCESS void TIdleProcess::Exec()
{

    for(;;)
    {
      #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
      #endif
    }
}

}

//------------------------------------------------------------------------------
//
//	System timer ISR
//
OS_INTERRUPT void SYSTEM_TIMER_VECTOR(void)
{
    scmRTOS_ISRW_TYPE ISR;
    Kernel.SystemTimer();

  #if scmRTOS_SYSTIMER_HOOK_ENABLE == 1

    // enable nested interrupts ONLY if user hook enabled
  #if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 1
    ENABLE_NESTED_INTERRUPTS();
  #endif

    SystemTimerUserHook();
  #endif
}
//------------------------------------------------------------------------------

