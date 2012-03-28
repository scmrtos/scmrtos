//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   EW430 (IAR Systems)
//*               
//*     PURPOSE:   Target Dependent Stuff Source
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

#include <scmRTOS.h>

using namespace OS;

OS::TPrioMaskTable OS::PrioMaskTable;

//------------------------------------------------------------------------------
//
//       OS Process's constructor
//
//       Performs:  
//           * initializing process data;
//           * registering of the process in kernel;
//           * preparing stack frame;
//                  
//
TBaseProcess::TBaseProcess(TStackItem* Stack, TPriority pr, void (*exec)())
    : StackPointer(Stack)
    , Priority(pr)
    , Timeout(0)
{
    Kernel.RegisterProcess(this);

    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
#if __CORE__ == __430X__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

    dword addr = reinterpret_cast<dword>(exec);
    word addr_l = addr;
    word addr_h = addr >> 16;
    *(--StackPointer) = addr_h;                        // return from interrupt address (4 MSBs)
    *(--StackPointer) = addr_l;                        // return from interrupt address (16 LSBs)
    *(--StackPointer) =   0x0008;                      // SR value: GIE set; ret from ISR address (4 MSBs)
    StackPointer -= 12*2;                              // emulate 12 "push rxx"

#else

    dword addr = reinterpret_cast<dword>(exec);
    word addr_l = addr;
    word addr_h = addr >> 16;
    *(--StackPointer) = addr_l;                        // return from interrupt address (16 LSBs)
    *(--StackPointer) =   0x0008 + (addr_h << 12);     // SR value: GIE set; ret from ISR address (4 MSBs)
    StackPointer -= 12*2;                              // emulate 12 "push rxx"

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

#else

    *(--StackPointer) = reinterpret_cast<word>(exec);  // return from interrupt address
    *(--StackPointer) =   0x0008;                      // SR value: GIE set
    StackPointer -= 12;                                // emulate 12 "push rxx"

#endif

}
//------------------------------------------------------------------------------
//
//   Idle Process
//
typedef process<prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;

template<> void TIdleProcess::Exec()
{
    for(;;)
    {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
        #endif
    }
}
//------------------------------------------------------------------------------
OS_INTERRUPT void OS::SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

    Kernel.SystemTimer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 1
    ENABLE_NESTED_INTERRUPTS();
#endif

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    SystemTimerUserHook();
#endif
}
//--------------------------------------------------------------------------

