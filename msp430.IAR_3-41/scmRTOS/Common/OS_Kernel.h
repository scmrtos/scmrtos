//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*               
//*     PURPOSE:  OS Kernel Header. Declarations And Definitions
//*               
//*     Version:  3.00-beta
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
    INLINE inline void SetPrioTag(TProcessMap& pm, const TProcessMap PrioTag) { pm |=  PrioTag; }
    INLINE inline void ClrPrioTag(TProcessMap& pm, const TProcessMap PrioTag) { pm &= ~PrioTag; }


    //--------------------------------------------------------------------------
    //
    //     NAME       :   TKernel
    //
    //     PURPOSE    :   Implements kernel-level operations such as
    //                    process management, process-level scheduling,
    //                    ISR-level scheduling, system timing.
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
        byte ISR_NestCount;

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        byte SchedProcPriority;
    #endif 

    #if scmRTOS_SYSTEM_TICKS_ENABLE == 1
        dword SysTickCount;
    #endif


    //-----------------------------------------------------------
    //
    //      Functions
    //
    public:
        TKernel() 
            : CurProcPriority(pr0) 
            , ReadyProcessMap(0)
            , ISR_NestCount(0)
        { 
            TProcessMap pm = 0x01;
            for(byte i = 0; i < scmRTOS_PROCESS_COUNT+1; i++)
            {
                ReadyProcessMap |= pm;
                pm <<= 1;
            }
        }

    private:
        INLINE inline void RegisterProcess(TBaseProcess* const p);

        void Sched();
        INLINE void Scheduler() { if(ISR_NestCount) return; else  Sched(); }
        INLINE inline void SchedISR();

        //INLINE inline void WaitForContextSwitch() const volatile;
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
    //      NAME       :   BaseProcess
    //
    //      PURPOSE    :   Implements base class-type for application processes
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
    //      NAME       :   process
    //
    //      PURPOSE    :   Implements template for application processes instantiation
    //
    //      DESCRIPTION:
    //
    //
    #if SEPARATE_RETURN_STACK == 0
        template<TPriority pr, word stack_size>
        class process : public TBaseProcess
        {
        public:
            process() : TBaseProcess(&Stack[stack_size/sizeof(TStackItem)]
                                      , pr
                                      , (void (*)())Exec)
            {
            }
    
            OS_PROCESS static void Exec();
    
        private:
            TStackItem Stack[stack_size/sizeof(TStackItem)];
        };
    #else
        template<TPriority pr, word stack_size, word rstack_size>
        class process : public TBaseProcess
        {
        public:
            process() : TBaseProcess( &Stack[stack_size/sizeof(TStackItem)]
                                    , &RStack[rstack_size/sizeof(TStackItem)]
                                    , pr
                                    , (void (*)())Exec)
            {
            }
    
            OS_PROCESS static void Exec();
    
        private:
            TStackItem Stack [stack_size/sizeof(TStackItem)];
            TStackItem RStack[rstack_size/sizeof(TStackItem)];
        };
    #endif
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //       Miscellaneous
    //
    //
    INLINE inline void LockSystemTimer()   { TCritSect cs; LOCK_SYSTEM_TIMER();   }
    INLINE inline void UnlockSystemTimer() { TCritSect cs; UNLOCK_SYSTEM_TIMER(); }
    void WakeUpProcess(TBaseProcess& p);
    void ForceWakeUpProcess(TBaseProcess& p);

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
    void  SystemTimerUserHook();
#endif

};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//   Register Process : Places pointer to process in kernel's process table
// 
// 
void OS::TKernel::RegisterProcess(OS::TBaseProcess* const p)
{
    ProcessTable[p->Priority] = p;
}
//------------------------------------------------------------------------------
//
//   System Timer Implementation : Performs process's timeouts checking and
//                                 moving processes to ready-to-run state
// 
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
//    ISR optimized sheduler
// 
//    !!! IMPORTANT: This function must be call from ISR services only !!!
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
     byte cur    = CurProcPriority;    // reading to temporary vars is performed due to
     byte sched  = SchedProcPriority;  // suppress warning about order of volatile access
     return cur == sched;
}
//------------------------------------------------------------------------------
TStackItem* OS::TKernel::ContextSwitchHook(TStackItem* sp)
{
    ProcessTable[CurProcPriority]->StackPointer = sp;
    sp = ProcessTable[SchedProcPriority]->StackPointer;

    CurProcPriority = SchedProcPriority;
    return sp;
}
//------------------------------------------------------------------------------
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

#include <OS_Services.h>

#endif // OS_KERNEL_H

