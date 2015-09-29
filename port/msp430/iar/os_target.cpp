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
//*     Version: 4.00
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
//*     IAR/MSP430 port by Harry E. Zhurov, Copyright (c) 2003-2012

#include <scmRTOS.h>

using namespace OS;

OS::TPrioMaskTable OS::PrioMaskTable;

//------------------------------------------------------------------------------
void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)() 
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    const uint_fast8_t CONTEXT_SIZE = 12;
#if __CORE__ == __430X__
    const uint_fast8_t STACK_ITEM_SIZE = 2;
#else
    const uint_fast8_t STACK_ITEM_SIZE = 1;
#endif

#if scmRTOS_DEBUG_ENABLE == 1
    //-----------------------------------------------------------------------
    //   Fill stack pool with predefined value for stack consumption checking
    //
    size_t StackSize = (Stack - StackBegin) - (CONTEXT_SIZE*STACK_ITEM_SIZE + 2);
    for(size_t i = 0; i < StackSize; ++i)
    {
        StackBegin[i] = STACK_DEFAULT_PATTERN;
    }
#endif // scmRTOS_DEBUG_ENABLE

    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
#if __CORE__ == __430X__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0

    uint32_t addr = reinterpret_cast<uint32_t>(exec);
    uint16_t addr_l = addr;
    uint16_t addr_h = addr >> 16;
    *(--Stack)      = addr_h;                         // return from interrupt address (4 MSBs)
    *(--Stack)      = addr_l;                         // return from interrupt address (16 LSBs)
    *(--Stack)      = 0x0008;                         // SR value: GIE set; ret from ISR address (4 MSBs)
    Stack          -= CONTEXT_SIZE*STACK_ITEM_SIZE;   // emulate 12 "push rxx"
    StackPointer    = Stack;

#else

    uint32_t addr = reinterpret_cast<uint32_t>(exec);
    uint16_t addr_l = addr;
    uint16_t addr_h = addr >> 16;
    *(--Stack)      = addr_l;                         // return from interrupt address (16 LSBs)
    *(--Stack)      = 0x0008 + (addr_h << 12);        // SR value: GIE set; ret from ISR address (4 MSBs)
    Stack          -= CONTEXT_SIZE*STACK_ITEM_SIZE;   // emulate 12 "push rxx"
    StackPointer    = Stack;


#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

#else

    *(--Stack)   = reinterpret_cast<uint16_t>(exec);  // return from interrupt address
    *(--Stack)   =   0x0008;                          // SR value: GIE set
    Stack       -= CONTEXT_SIZE*STACK_ITEM_SIZE;      // emulate 12 "push rxx"
    StackPointer = Stack;

#endif

}
//------------------------------------------------------------------------------
#pragma vector=SYSTEM_TIMER_VECTOR
OS_INTERRUPT void OS::system_timer_isr()
{
    scmRTOS_ISRW_TYPE ISR;

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif

    Kernel.system_timer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 1
    ENABLE_NESTED_INTERRUPTS();
#endif

}
//--------------------------------------------------------------------------

