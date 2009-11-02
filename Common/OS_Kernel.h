//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Kernel Header. Declarations And Definitions
//*
//*     Version: 3.05
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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
//*****************************************************************************

#ifndef OS_KERNEL_H
#define OS_KERNEL_H

#include <stddef.h>
#include <commdefs.h>
#include <usrlib.h>

//------------------------------------------------------------------------------

//==============================================================================
extern "C" void OS_Start(TStackItem* sp);

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
    extern "C" void OS_ContextSwitcher(TStackItem** Curr_SP, TStackItem* Next_SP);
#else
    extern "C" TStackItem* OS_ContextSwitchHook(TStackItem* sp);
#endif

//==============================================================================

//------------------------------------------------------------------------------
//
//
//     NAME       :   OS
//
//     PURPOSE    :   Namespace for all OS stuff
//
//     DESCRIPTION:   Includes:  Kernel,
//                               Processes,
//                               Mutexes,
//                               Event Flags,
//                               Byte-wide Channels,
//                               Arbitrary-type Channels,
//                               Messages
//
namespace OS
{
    class TBaseProcess;

    INLINE inline void SetPrioTag(TProcessMap& pm, const TProcessMap PrioTag) { pm |=  PrioTag; }
    INLINE inline void ClrPrioTag(TProcessMap& pm, const TProcessMap PrioTag) { pm &= ~PrioTag; }

    //--------------------------------------------------------------------------
    //
    //     NAME       :   TKernel
    //
    ///  Implements kernel-level operations such as
    ///  process management, process-level scheduling,
    ///  ISR-level scheduling, system timing.
    //
    //     DESCRIPTION:
    //
    //
    class TKernel
    {
        //-----------------------------------------------------------
        //
        //     Declarations
        //
        

        friend class TISRW;
        friend class TISRW_SS;
        friend class TBaseProcess;
        friend class TMutex;
        friend class TEventFlag;
        friend class TChannel;
        friend class TBaseMessage;

        template<typename T, word size, class S> friend class channel;
        template<typename T>                     friend class message;

        friend void          Run();
        friend void          WakeUpProcess(TBaseProcess& p);
        friend void          ForceWakeUpProcess(TBaseProcess& p);
        friend inline bool   IsProcessSleeping(const TBaseProcess& p);
        friend inline bool   IsProcessSuspended(const TBaseProcess& p);
        friend inline dword  GetTickCount();

        //-----------------------------------------------------------
        //
        //      Data
        //
    private:
        byte CurProcPriority;
        TProcessMap ReadyProcessMap;
        TBaseProcess* ProcessTable[scmRTOS_PROCESS_COUNT+1];
        volatile byte ISR_NestCount;

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        byte SchedProcPriority;
    #endif

    #if scmRTOS_SYSTEM_TICKS_ENABLE == 1
        volatile dword SysTickCount;
    #endif

    //-----------------------------------------------------------
    //
    //      Functions
    //
    public:
        INLINE TKernel()
            : CurProcPriority(pr0)
            , ReadyProcessMap( (1 << (scmRTOS_PROCESS_COUNT + 1)) - 1)  // set all processes ready
            , ISR_NestCount(0)
        {
        }

    private:
        INLINE inline void RegisterProcess(TBaseProcess* const p);

        void Sched();
        INLINE void Scheduler() { if(ISR_NestCount) return; else  Sched(); }
        INLINE inline void SchedISR();

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        INLINE inline bool IsContextSwitchDone() const volatile;
    #endif
        INLINE void SetProcessReady  (const byte pr) { TProcessMap PrioTag = GetPrioTag(pr); SetPrioTag( ReadyProcessMap, PrioTag); }
        INLINE void SetProcessUnready(const byte pr) { TProcessMap PrioTag = GetPrioTag(pr); ClrPrioTag( ReadyProcessMap, PrioTag); }

    public:
        INLINE inline void SystemTimer();
    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        INLINE inline TStackItem* ContextSwitchHook(TStackItem* sp);
    #endif

    };  // End of TKernel class definition
    //--------------------------------------------------------------------------
    extern TKernel Kernel;

    //--------------------------------------------------------------------------
    //
    /// BaseProcess
    ///
    /// Implements base class-type for application processes
    //
    //      DESCRIPTION:
    //
    //
    class TBaseProcess
    {
        friend class TKernel;
        friend class TISRW;
        friend class TISRW_SS;
        friend class TEventFlag;
        friend class TMutex;
        friend class TBaseMessage;

        template<typename T, word size, class S> friend class channel;
        template<typename T>                     friend class message;


        friend void         Run();
        friend void         WakeUpProcess(TBaseProcess& p);
        friend void         ForceWakeUpProcess(TBaseProcess& p);
        friend bool         IsProcessSleeping(const TBaseProcess& p);
        friend bool         IsProcessSuspended(const TBaseProcess& p);

    public:
    #if SEPARATE_RETURN_STACK == 0
        TBaseProcess( TStackItem* Stack, TPriority pr, void (*exec)() );
    #else
        TBaseProcess( TStackItem* Stack, TStackItem* RStack, TPriority pr, void (*exec)() );
    #endif

        static void Sleep(TTimeout timeout = 0);

    protected:
        TStackItem* StackPointer;
        TTimeout Timeout;
        TPriority Priority;
    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    ///  process
    ///
    ///  Implements template for application processes instantiation
    //
    //      DESCRIPTION:
    //
    //
    #if SEPARATE_RETURN_STACK == 0

        template<TPriority pr, word stack_size>
        class process : public TBaseProcess
        {
        public:
            process();

            OS_PROCESS static void Exec();

        private:
            TStackItem Stack[stack_size/sizeof(TStackItem)];
        };

        template<TPriority pr, word stack_size>
        OS::process<pr, stack_size>::process() : TBaseProcess( &Stack[stack_size/sizeof(TStackItem)]
                                                              , pr
                                                              , reinterpret_cast<void (*)()>(Exec) )
        {
        }

    #else

        template<TPriority pr, word stack_size, word rstack_size>
        class process : public TBaseProcess
        {
        public:
            process();

            OS_PROCESS static void Exec();

        private:
            TStackItem Stack [stack_size/sizeof(TStackItem)];
            TStackItem RStack[rstack_size/sizeof(TStackItem)];
        };

        template<TPriority pr, word stack_size, word rstack_size>
        process<pr, stack_size, rstack_size>::process() : TBaseProcess( &Stack[stack_size/sizeof(TStackItem)]
                                                                      , &RStack[rstack_size/sizeof(TStackItem)]
                                                                      , pr
                                                                      , reinterpret_cast<void (*)()>(Exec))
        {
        }

    #endif
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //       Miscellaneous
    //
    //
    INLINE inline void Run();
    INLINE inline void LockSystemTimer()   { TCritSect cs; LOCK_SYSTEM_TIMER();   }
    INLINE inline void UnlockSystemTimer() { TCritSect cs; UNLOCK_SYSTEM_TIMER(); }
    void WakeUpProcess(TBaseProcess& p);
    void ForceWakeUpProcess(TBaseProcess& p);
    INLINE inline void Sleep(TTimeout t = 0) { TBaseProcess::Sleep(t); }

    INLINE inline bool IsProcessSleeping(const TBaseProcess& p)
    {
        TCritSect cs;
        if(p.Timeout)
            return true;
        else
            return false;
    }

    INLINE inline bool IsProcessSuspended(const TBaseProcess& p)
    {
        TCritSect cs;
        if(Kernel.ReadyProcessMap & GetPrioTag(p.Priority))
            return false;
        else
            return true;
    }
    //--------------------------------------------------------------------------

#if scmRTOS_SYSTEM_TICKS_ENABLE == 1
    INLINE inline dword GetTickCount() { TCritSect cs; return Kernel.SysTickCount; }
#endif

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    INLINE_SYS_TIMER_HOOK void  SystemTimerUserHook();
#endif

#if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
    INLINE_CONTEXT_SWITCH_HOOK void  ContextSwitchUserHook();
#endif
    
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
///  Register Process
///
///  Places pointer to process in kernel's process table
//
void OS::TKernel::RegisterProcess(OS::TBaseProcess* const p)
{
    ProcessTable[p->Priority] = p;
}
//------------------------------------------------------------------------------
//
/// System Timer Implementation
///
/// Performs process's timeouts checking and
///               moving processes to ready-to-run state
//
void OS::TKernel::SystemTimer()
{
    SYS_TIMER_CRIT_SECT();
#if scmRTOS_SYSTEM_TICKS_ENABLE == 1
    SysTickCount++;
#endif

#if scmRTOS_PRIORITY_ORDER == 0
    const byte BaseIndex = 0;
#else
    const byte BaseIndex = 1;
#endif

    for(byte i = BaseIndex; i < (scmRTOS_PROCESS_COUNT + BaseIndex); i++)
    {
        TBaseProcess* p = ProcessTable[i];

        if(p->Timeout > 0)
        {
            if(--p->Timeout == 0)
            {
                SetProcessReady(p->Priority);
            }
        }
    }
}
//------------------------------------------------------------------------------
//
///    ISR optimized scheduler
///
///    !!! IMPORTANT: This function must be call from ISR services only !!!
//
//
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
void OS::TKernel::SchedISR()
{
    byte NextPrty = GetHighPriority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
        TStackItem*  Next_SP = ProcessTable[NextPrty]->StackPointer;
        TStackItem** Curr_SP_addr = &(ProcessTable[CurProcPriority]->StackPointer);
        CurProcPriority = NextPrty;
        OS_ContextSwitcher(Curr_SP_addr, Next_SP);
    }
}
#else
void OS::TKernel::SchedISR()
{
    byte NextPrty = GetHighPriority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
        SchedProcPriority    = NextPrty;
        RaiseContextSwitch();
    }
}
//------------------------------------------------------------------------------
bool OS::TKernel::IsContextSwitchDone() const volatile
{
     byte cur    = CurProcPriority;    ///< reading to temporary vars is performed due to
     byte sched  = SchedProcPriority;  ///< suppress warning about order of volatile access
     return cur == sched;
}
//------------------------------------------------------------------------------
TStackItem* OS::TKernel::ContextSwitchHook(TStackItem* sp)
{
    ProcessTable[CurProcPriority]->StackPointer = sp;
    sp = ProcessTable[SchedProcPriority]->StackPointer;

#if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
    ContextSwitchUserHook();
#endif 

    CurProcPriority = SchedProcPriority;
    return sp;
}
//------------------------------------------------------------------------------
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

//-----------------------------------------------------------------------------
/// Start Operation
INLINE inline void OS::Run()
{
    TStackItem* sp = Kernel.ProcessTable[pr0]->StackPointer;
    OS_Start(sp);
}

#include <OS_Services.h>

#endif // OS_KERNEL_H

