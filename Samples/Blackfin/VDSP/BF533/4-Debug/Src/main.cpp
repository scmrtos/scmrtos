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
//*     PURPOSE:   Port Test File
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
//******************************************************************************

//---------------------------------------------------------------------------
#include <sysreg.h>
#include <scmRTOS.h>
#include "debug.h"
#include "macro.h"
#include "terminal.h"

//---------------------------------------------------------------------------
class TProcProfiler : public TProfiler<SUM_SHIFT>
{
public:
    TProcProfiler() {}
    void get_results(timeout_t acquire_period);
};

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1          Proc1;
TProc2          Proc2;
TProc3          Proc3;
TBackgroundProc BackgroundProc;
//---------------------------------------------------------------------------
tick_count_t T;                  // global variable for OS::GetTickCount testing
                                 //
OS::TEventFlag ef;               //

EX_INTERRUPT_HANDLER(timer0_isr);
OS::TEventFlag ef_timer0;
TProcProfiler Profiler;

//---------------------------------------------------------------------------
//#pragma noreturn
void main()
{                 
    //----------------------------------------------------------------------
    //
    //    Set Pcocessor Core clock to 200 MHz, peripheral clock - to 100 MHz
    //    Set Processor Core voltage at 0.85 v
    //
    pll_set_system_vco(8, 0, 0x300);
    pll_set_system_clocks(0, 2);
    ssync();
    
    /////////////////////////////////////////////////////////////////////
    //
    //    System resources setup
    // 
    //-------------------------------------------------------------------
    //
    //  System Timer setup and start
    //
    MMR32(TCNTL)   = 1;                 // turn on the timer
    MMR32(TSCALE)  = 0;                 //
    MMR32(TPERIOD) = SYS_TIMER_PERIOD;  // 5ns * 200 000 = 1 ms
    MMR32(TCNTL)   = 0x07;              // run timer 
    //-------------------------------------------------------------------
    //
    //    Register System Interrupt Handlers
    //
    //
    register_handler_ex(ik_timer, OS::system_timer_isr, 1);
    register_handler_ex(ik_ivg14, context_switcher_isr, 1);
    //-------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////


    MMR16(FIO_DIR) |= (1 << 8) + (1 << 9);

    register_handler_ex(ik_ivg11, timer0_isr, 1);
    MMR32(SIC_IMASK) = (1ul << 16)  // Timer0
                     | (1ul << 14)  // UART Rx
                     | (1ul << 15)  // UART Tx
                     ;


    
    MMR16(TIMER0_CONFIG) = PWM_OUT  
                         + IRQ_ENA 
                         + PERIOD_CNT 
                         + OUT_DIS; 

    MMR32(TIMER0_PERIOD) = 10011;
    MMR32(TIMER0_WIDTH)  = 5000;
    MMR16(TIMER_ENABLE)  = TIMEN0;                 // timer0 enable

    UART::init();

    OS::run();
}
//---------------------------------------------------------------------------
template<> void TProc1::exec()
{
    for(;;)
    {
        ef_timer0.wait();
        MMR16(FIO_FLAG_C) = (1 << 9);
    }
}
//---------------------------------------------------------------------------
template<> void TProc2::exec()
{
    for(;;)
    {
        ef.wait();
        MMR16(FIO_FLAG_C) = (1 << 8);
        for(int i = 0; i < 100000; ++i)
        {
            asm( " nop;");
        }
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::exec()
{
    for(;;)
    {
        sleep(3);
        for(int i = 0; i < 10000; ++i)
        {
            asm( " nop;");
        }
        MMR16(FIO_FLAG_S) = (1 << 8);
        ef.signal();
    }
}
//---------------------------------------------------------------------------
template<> void TBackgroundProc::exec()
{
    for(;;)
    {
        Profiler.get_results(3000);
    }
}
//---------------------------------------------------------------------------
void OS::system_timer_user_hook() { /*Profiler.advance_counters();*/ }
//---------------------------------------------------------------------------
void OS::idle_process_user_hook() { }
//---------------------------------------------------------------------------
void OS::context_switch_user_hook() { Profiler.advance_counters(); }
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(timer0_isr)
{
    OS::TISRW ISR;
    MMR16(TIMER_STATUS) = TIMIL0;

    MMR16(FIO_FLAG_S) = (1 << 9);
    ef_timer0.signal_isr();
}
//---------------------------------------------------------------------------
template<uint_fast8_t sum_shift> 
uint32_t TProfiler<sum_shift>::time_interval()
{
    //return 1;
    static uint32_t Cycles;

    uint32_t Cyc = sysreg_read(reg_CYCLES);
    uint32_t Res = Cyc - Cycles;
    Cycles       = Cyc;

    return Res;
}
//---------------------------------------------------------------------------
void TProcProfiler::get_results(timeout_t acquire_period)
{
    OS::sleep(acquire_period);
    TProfiler::process_data();
    print("------------------------------\n");
    for(uint_fast8_t i = 0; i < OS::PROCESS_COUNT; ++i)
    {
        print("Proc %d | CPU %5.2f | Slack %d\n", i, Profiler.get_result(i)/100.0, OS::get_proc(i)->stack_slack() );
    }
}
//---------------------------------------------------------------------------


