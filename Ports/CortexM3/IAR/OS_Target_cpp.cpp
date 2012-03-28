//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   EWARM (IAR Systems)
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
//*     Ported by Andrey Chuikin, Copyright (c) 2008-2012


#include <scmRTOS.h>

using namespace OS;

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
    *(--StackPointer)  = 0x01000000L;             // xPSR
    *(--StackPointer)  = reinterpret_cast<dword>(exec); // Entry Point
    StackPointer -= 14;                           // emulate "push R14,R12,R3,R2,R1,R0,R11-R4"
    
    // The code below can be used for debug purpose. In this case comment
    // line above and uncomment block below.
/*
    *(--StackPointer)  = 0xFFFFFFFEL;             // R14 (LR) (init value will cause fault if ever used)
    *(--StackPointer)  = 0x12121212L;             // R12
    *(--StackPointer)  = 0x03030303L;             // R3
    *(--StackPointer)  = 0x02020202L;             // R2
    *(--StackPointer)  = 0x01010101L;             // R1
    *(--StackPointer)  = 0x00000000L;             // R0

                                                  // Remaining registers saved on process stack
    *(--StackPointer)  = 0x11111111L;             // R11
    *(--StackPointer)  = 0x10101010L;             // R10
    *(--StackPointer)  = 0x09090909L;             // R9
    *(--StackPointer)  = 0x08080808L;             // R8
    *(--StackPointer)  = 0x07070707L;             // R7
    *(--StackPointer)  = 0x06060606L;             // R6
    *(--StackPointer)  = 0x05050505L;             // R5
    *(--StackPointer)  = 0x04040404L;             // R4
*/
}
//------------------------------------------------------------------------------
//
//   Idle Process
//
typedef process<prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;

template<> OS_PROCESS void TIdleProcess::Exec()
{
    for(;;)
    {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
        #endif
    }
}
//------------------------------------------------------------------------------
OS_INTERRUPT void OS::SysTick_Handler()
{
    scmRTOS_ISRW_TYPE ISR;

    Kernel.SystemTimer();
    
#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
    DISABLE_NESTED_INTERRUPTS();
#endif
    
#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    SystemTimerUserHook();
#endif
}
//------------------------------------------------------------------------------

