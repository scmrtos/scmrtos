//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
//*
//*     =================================================================
//*     scmRTOS is free software; you can redistribute it and/or
//*     modify it under the terms of the GNU General Public License
//*     as published by the Free Software Foundation; either version 2
//*     of the License, or (at your option) any later version.
//*
//*     This program is distributed in the hope that it will be useful,
//*     but WITHOUT ANY WARRANTY; without even the implied warranty of
//*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//*     GNU General Public License for more details.
//*
//*     You should have received a copy of the GNU General Public License
//*     along with this program; if not, write to the Free Software
//*     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//*     MA  02110-1301, USA.
//*     =================================================================
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//********************************************************************************
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006

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
    *(--StackPointer) = (dword)exec;		// return from interrupt address
    // debug: initial register values.

    *(--StackPointer) = 0xcccccccc;			// r12
    *(--StackPointer) = 0xbbbbbbbb;			// r11
    *(--StackPointer) = 0xaaaaaaaa;			// r10
    *(--StackPointer) = 0x99999999;			// r9
    *(--StackPointer) = 0x88888888;			// r8
    *(--StackPointer) = 0x77777777;			// r7
    *(--StackPointer) = 0x66666666;			// r6
    *(--StackPointer) = 0x55555555;			// r5
    *(--StackPointer) = 0x44444444;			// r4
    *(--StackPointer) = 0x33333333;			// r3
    *(--StackPointer) = 0x22222222;			// r2
    *(--StackPointer) = 0x11111111;			// r1
    *(--StackPointer) = 0x00000000;			// r0
    *(--StackPointer) = 0xdddddddd;			// LR

//	StackPointer -= 14;						// emulate "push R0-R12, LR"
#if __CPU_MODE__ == 1
    *(--StackPointer) =   0x003F;			// SR value: system mode, FIQ & IRQ enabled, THUMB
#else
    *(--StackPointer) =   0x001F;			// SR value: system mode, FIQ & IRQ enabled, ARM
#endif
}
//-----------------------------------------------------------------------------
//
//   Idle Process
//
//
typedef process<prIDLE, (16 + 1) * sizeof(TStackItem) + scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProcess;

TIdleProcess IdleProcess;

OS_PROCESS void TIdleProcess::Exec()
{
    for(;;)
    {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
        #endif
    }
}
//------------------------------------------------------------------------------
namespace OS
{
    void SystemTimer_Handler();
}

inline __arm void OS::SystemTimer_Handler()
{
    Kernel.SystemTimer();
#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    SystemTimerUserHook();
#endif
}

OS_INTERRUPT void OS::SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

    SYSTEM_TIMER_HANDLER();

    IRQ_DONE();
}
//--------------------------------------------------------------------------
namespace OS {
#if scmRTOS_PRIORITY_ORDER == 0
    #if scmRTOS_PROCESS_COUNT == 1
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            prIDLE, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 2
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            prIDLE, pr0, pr1, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 3
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 4
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 5
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        };
    #else // scmRTOS_PROCESS_COUNT > 5
        extern TPriority const PriorityTable[64] =
        {
            (TPriority)32,      (TPriority)0,       (TPriority)1,       (TPriority)12,
            (TPriority)2,       (TPriority)6,       (TPriority)0xFF,    (TPriority)13,
            (TPriority)3,       (TPriority)0xFF,    (TPriority)7,       (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)14,
            (TPriority)0,       (TPriority)4,       (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)8,       (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)25,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)21,      (TPriority)27,      (TPriority)15,
            (TPriority)31,      (TPriority)11,      (TPriority)5,       (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)9,       (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)24,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)20,      (TPriority)26,
            (TPriority)30,      (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)23,      (TPriority)0xFF,    (TPriority)19,
            (TPriority)29,      (TPriority)0xFF,    (TPriority)22,      (TPriority)18,
            (TPriority)28,      (TPriority)17,      (TPriority)16,      (TPriority)0xFF
        };
    #endif	// scmRTOS_PROCESS_COUNT
#else 	// scmRTOS_PRIORITY_ORDER == 1
    #if scmRTOS_PROCESS_COUNT == 1
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            prIDLE,
            pr0, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 2
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            prIDLE,
            pr1, pr1,
            pr0, pr0, pr0, pr0
       };
    #elif scmRTOS_PROCESS_COUNT == 3
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            prIDLE,
            pr2, pr2,
            pr1, pr1, pr1, pr1,
            pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 4
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            prIDLE,
            pr3, pr3,
            pr2, pr2, pr2, pr2,
            pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1,
            pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0
        };
    #elif scmRTOS_PROCESS_COUNT == 5
        extern TPriority const PriorityTable[] =
        {
            (TPriority)0xFF,
            prIDLE,
            pr4, pr4,
            pr3, pr3, pr3, pr3,
            pr2, pr2, pr2, pr2, pr2, pr2, pr2, pr2,
            pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1, pr1,
            pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0, pr0
        };
    #else // scmRTOS_PROCESS_COUNT > 5
        extern TPriority const PriorityTable[64] =
        {
            (TPriority)0xFF,    (TPriority)0,       (TPriority)0xFF,    (TPriority)15,
            (TPriority)0xFF,    (TPriority)1,       (TPriority)28,      (TPriority)0xFF,
            (TPriority)16,      (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)0xFF,
            (TPriority)2,       (TPriority)21,      (TPriority)29,      (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)19,      (TPriority)17,
            (TPriority)10,      (TPriority)0xFF,    (TPriority)12,      (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)3,       (TPriority)0xFF,    (TPriority)6,
            (TPriority)0xFF,    (TPriority)22,      (TPriority)30,      (TPriority)0xFF,
            (TPriority)14,      (TPriority)0xFF,    (TPriority)27,      (TPriority)0xFF,
            (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)20,      (TPriority)0xFF,
            (TPriority)18,      (TPriority)9,       (TPriority)11,      (TPriority)0xFF,
            (TPriority)5,       (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)13,
            (TPriority)26,      (TPriority)0xFF,    (TPriority)0xFF,    (TPriority)8,
            (TPriority)0xFF,    (TPriority)4,       (TPriority)0xFF,    (TPriority)25,
            (TPriority)0xFF,    (TPriority)7,       (TPriority)24,      (TPriority)0xFF,
            (TPriority)23,      (TPriority)0xFF,    (TPriority)31,      (TPriority)0xFF
        };
    #endif	// scmRTOS_PROCESS_COUNT
#endif // scmRTOS_PRIORITY_ORDER
}	//namespace
//--------------------------------------------------------------------------
