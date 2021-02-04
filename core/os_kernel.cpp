//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Kernel Source
//*
//*     Version: v5.2.0
//*
//*
//*     Copyright (c) 2003-2021, scmRTOS Team
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
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************

#include "scmRTOS.h"

using namespace OS;

OS::TKernel OS::Kernel;

#if scmRTOS_SUSPENDED_PROCESS_ENABLE != 0
OS::TProcessMap OS::TBaseProcess::SuspendedProcessMap = (1ul << (PROCESS_COUNT)) - 1; 
#endif

TBaseProcess * TKernel::ProcessTable[scmRTOS_PROCESS_COUNT + 1];

//------------------------------------------------------------------------------
//
//    TKernel functions
//
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
void TKernel::sched()
{
    uint_fast8_t NextPrty = highest_priority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
    #if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
        context_switch_user_hook();
    #endif

        stack_item_t*  Next_SP      = ProcessTable[NextPrty]->StackPointer;
        stack_item_t** Curr_SP_addr = &(ProcessTable[CurProcPriority]->StackPointer);
        CurProcPriority = NextPrty;
        os_context_switcher(Curr_SP_addr, Next_SP);
    }
}
#else
//------------------------------------------------------------------------------
void TKernel::sched()
{
    uint_fast8_t NextPrty = highest_priority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
        SchedProcPriority = NextPrty;
    
        raise_context_switch();
        do
        {
            enable_context_switch();
            DUMMY_INSTR();
            disable_context_switch();
        } 
        while(CurProcPriority != SchedProcPriority); // until context switch done
    }
}
//------------------------------------------------------------------------------
stack_item_t* os_context_switch_hook(stack_item_t* sp) { return Kernel.context_switch_hook(sp); }
//------------------------------------------------------------------------------
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

//------------------------------------------------------------------------------
//
//       OS Process's constructor
//
//       Performs:  
//           * initializing process data;
//           * registering process in the kernel;
//           * initializing stack frame;
//                  
//
#if SEPARATE_RETURN_STACK == 0

TBaseProcess::TBaseProcess( stack_item_t * StackPoolEnd
                          , TPriority pr
                          , void (*exec)()
                      #if scmRTOS_DEBUG_ENABLE == 1
                          , stack_item_t * aStackPool
                          , const char   * name_str
                      #endif
                          ) : Timeout(0)
                            , Priority(pr)
                      #if scmRTOS_DEBUG_ENABLE == 1
                            , WaitingFor(0)
                            , StackPool(aStackPool)
                            , StackSize(StackPoolEnd - aStackPool)
                            , Name(name_str)
                      #endif 
                      #if scmRTOS_PROCESS_RESTART_ENABLE == 1
                            , WaitingProcessMap(0)
                      #endif

{
    TKernel::register_process(this);
    init_stack_frame( StackPoolEnd
                    , exec
                #if scmRTOS_DEBUG_ENABLE == 1     
                    , aStackPool
                #endif  
                    );
}

#else  // SEPARATE_RETURN_STACK

TBaseProcess::TBaseProcess( stack_item_t * Stack
                          , stack_item_t * RStack
                          , TPriority pr
                          , void (*exec)()
                      #if scmRTOS_DEBUG_ENABLE == 1
                          , stack_item_t * aStackPool
                          , stack_item_t * aRStackPool
                          , const char   * name_str
                      #endif
                          ) : StackPointer(Stack)
                            , Timeout(0)
                            , Priority(pr)
                      #if scmRTOS_DEBUG_ENABLE == 1
                            , WaitingFor(0)
                            , StackPool(aStackPool)
                            , StackSize(Stack - aStackPool)
                            , Name(name_str)
                            , RStackPool(aRStackPool)
                            , RStackSize(RStack - aRStackPool)
                      #endif 
                      #if scmRTOS_PROCESS_RESTART_ENABLE == 1
                            , WaitingProcessMap(0)
                      #endif

{
    TKernel::register_process(this);
    init_stack_frame( Stack
                    , RStack
                    , exec
                #if scmRTOS_DEBUG_ENABLE == 1     
                    , aStackPool
                    , aRStackPool
                #endif  
                    );
}
#endif // SEPARATE_RETURN_STACK
//------------------------------------------------------------------------------
void TBaseProcess::sleep(timeout_t timeout)
{
    TCritSect cs;

    Kernel.ProcessTable[Kernel.CurProcPriority]->Timeout = timeout;
    Kernel.set_process_unready(Kernel.CurProcPriority);
    Kernel.scheduler();
}
//------------------------------------------------------------------------------
void OS::TBaseProcess::wake_up()
{
    TCritSect cs;

    if(this->Timeout)
    {
        this->Timeout = 0;
        Kernel.set_process_ready(this->Priority);
        Kernel.scheduler();
    }
}
//------------------------------------------------------------------------------
void OS::TBaseProcess::force_wake_up()
{
    TCritSect cs;

    this->Timeout = 0;
    Kernel.set_process_ready(this->Priority);
    Kernel.scheduler();
}
//------------------------------------------------------------------------------
//
//
//   Idle Process
//
//
namespace OS
{
#ifndef __GNUC__  // avoid GCC bug ( http://gcc.gnu.org/bugzilla/show_bug.cgi?id=15867 )
    template<> void TIdleProc::exec();
#endif

#if scmRTOS_DEBUG_ENABLE == 1
    TIdleProc IdleProc("Idle");
#else
    TIdleProc IdleProc;
#endif


}

namespace OS
{
    template<> void TIdleProc::exec()
    {
        for(;;)
        {
        #if scmRTOS_IDLE_HOOK_ENABLE == 1
            idle_process_user_hook();
        #endif

        #if scmRTOS_TARGET_IDLE_HOOK_ENABLE == 1
            idle_process_target_hook();
        #endif
        }
    }
}
//------------------------------------------------------------------------------
#if scmRTOS_DEBUG_ENABLE == 1
#if SEPARATE_RETURN_STACK == 0
size_t TBaseProcess::stack_slack() const
{
     size_t slack = 0;
     const stack_item_t * Stack = StackPool;
     while (*Stack++ == scmRTOS_STACK_PATTERN)
         slack++;
     return slack;
}
#else  // SEPARATE_RETURN_STACK
static size_t calc_stack_slack(const stack_item_t * Stack)
{
     size_t slack = 0;
     while (*Stack++ == scmRTOS_STACK_PATTERN)
         slack++;
     return slack;
}
size_t TBaseProcess::stack_slack() const
{
     return calc_stack_slack(StackPool);
}
size_t TBaseProcess::rstack_slack() const
{
     return calc_stack_slack(RStackPool);
}
#endif // SEPARATE_RETURN_STACK
#endif // scmRTOS_DEBUG_ENABLE
//------------------------------------------------------------------------------
#if scmRTOS_PROCESS_RESTART_ENABLE == 1
void TBaseProcess::reset_controls()
{
    Kernel.set_process_unready(this->Priority);
    if(WaitingProcessMap)
    {
        clr_prio_tag( *WaitingProcessMap, get_prio_tag(Priority) );  // remove current process from service's process map
        WaitingProcessMap = 0;
    }
    Timeout    = 0;
#if scmRTOS_DEBUG_ENABLE == 1
    WaitingFor = 0;
#endif
}
#endif  // scmRTOS_PROCESS_RESTART_ENABLE
//------------------------------------------------------------------------------


