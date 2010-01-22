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
//*     PURPOSE:   Target Dependent Stuff Source
//*               
//*     Version: 3.10
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2010, Harry E. Zhurov
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
//*     FR port by Sergey Pinigin, Copyright (c) 2007-2010
//*
//********************************************************************************

#include <scmRTOS.h>

using namespace OS;

//------------------------------------------------------------------------------
//
///  Prepare Process Stack Frame
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
#if 0
    StackPointer -= 17;                    // emulate 17 "push rxx"
    *(--StackPointer) = (dword)exec;          /* RP */
    *(--StackPointer) = (dword)0x001f0030;    /* PS:  ILM=31(0x1f) S=1(USP) I=1 */
    *(--StackPointer) = (dword)exec;          /* PC */
#else
    *(--StackPointer) = (dword)0x00000100;    /* R0 */
    *(--StackPointer) = (dword)0x00000101;    /* R1 */
    *(--StackPointer) = (dword)0x00000102;    /* R2 */
    *(--StackPointer) = (dword)0x00000103;    /* R3 */
    *(--StackPointer) = (dword)0x00000104;    /* R4 */
    *(--StackPointer) = (dword)0x00000105;    /* R5 */
    *(--StackPointer) = (dword)0x00000106;    /* R6 */
    *(--StackPointer) = (dword)0x00000107;    /* R7 */
    *(--StackPointer) = (dword)0x00000108;    /* R8 */
    *(--StackPointer) = (dword)0x00000109;    /* R9 */
    *(--StackPointer) = (dword)0x00000110;    /* R10 */
    *(--StackPointer) = (dword)0x00000111;    /* R11 */
    *(--StackPointer) = (dword)0x00000112;    /* R12 */
    *(--StackPointer) = (dword)0x00000113;    /* R13 */
    *(--StackPointer) = (dword)0x00000114;    /* R14 */
    *(--StackPointer) = (dword)0x00000200;    /* MDH */
    *(--StackPointer) = (dword)0x00000201;    /* MDL */
    *(--StackPointer) = (dword)exec;          /* RP */
    *(--StackPointer) = (dword)0x001f0030;    /* PS:  ILM=31(0x1f) S=1(USP) I=1 */
    *(--StackPointer) = (dword)exec;          /* PC */
#endif
}

//------------------------------------------------------------------------------
typedef OS::process<OS::prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProc;

TIdleProc IdleProc;

/// scmRTOS IDLE PROCESS
OS_PROCESS void TIdleProc::Exec()
{
    for(;;)
    {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
        IdleProcessUserHook();
        #endif
    }
}
//------------------------------------------------------------------------------
/// System Timer ISR
extern "C" __interrupt void SystemTimer_ISR()
{
    TISRW ISR;

    scmRTOS_SYSTIMER_CLEAR_FLAG();

    Kernel.SystemTimer();

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    SystemTimerUserHook();
#endif
}
//------------------------------------------------------------------------------

