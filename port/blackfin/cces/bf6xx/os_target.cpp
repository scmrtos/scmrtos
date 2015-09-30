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
//*     PURPOSE:   Target Dependent Stuff Source
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
//*     Blackfin/CrossCore Embedded Studio port by Evgeny Nesterov, Copyright (c) 2012-2015

#include <scmRTOS.h>


extern "C" unsigned int caller(unsigned);

using namespace OS;

//------------------------------------------------------------------------------
void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)() 
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    const uint_fast8_t CONTEXT_SIZE           = 43;
    const uint_fast8_t FUN_INCOMING_ARGS_SIZE = 3;
    const uint_fast8_t STACK_FRAME_SIZE     = CONTEXT_SIZE + FUN_INCOMING_ARGS_SIZE + 2;    
    
#if scmRTOS_DEBUG_ENABLE == 1
    //-----------------------------------------------------------------------
    //   Fill stack pool with predefined value for stack consumption checking
    //
    const size_t STACK_SIZE = Stack - StackBegin;
    const size_t FILL_SIZE  = STACK_SIZE - STACK_FRAME_SIZE;
          size_t i          = 0;
          
    for(; i < FILL_SIZE; ++i)
    {
        StackBegin[i] = STACK_DEFAULT_PATTERN;
    }
    for(; i < STACK_SIZE; ++i)
    {
        StackBegin[i] = 0;
    }
#endif // scmRTOS_DEBUG_ENABLE
     Stack       -=0x20;
     Stack       -= FUN_INCOMING_ARGS_SIZE;// reserve space for calling function incoming parameters
     *(--Stack)   = reinterpret_cast<uint32_t>(exec); // process main function address
     *(--Stack)     =caller(0);//rets in interrupt cec_dispatch_handler
     Stack++;
     Stack       -= CONTEXT_SIZE;                     // emulate 43 "push rxx"
     *(--Stack)   =   0xffe0;                         // enable interrupts
     StackPointer = Stack;

    

}
//------------------------------------------------------------------------------
EX_DISPATCHED_HANDLER_NESTED(OS::system_timer_isr, a, b, c)

{
    TISRW ISR;
    Kernel.system_timer();

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif
}
//------------------------------------------------------------------------------

