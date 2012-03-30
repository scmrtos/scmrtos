//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STM8 (STMicroelectronics)
//*
//*     TOOLKIT:   EWSTM8 (IAR Systems)
//*
//*     PURPOSE:   STM8/IAR Port Test File
//*                Sample '4-Debug' debug process module
//*
//*     Version: 4.00
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
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011

#include "scmRTOS.h"

#include <stdio.h>

#include "pin.h"

#include "prio_names.h"
#include "debug.h"

//------------------------------------------------------------------------------
//  Context switch takes about 250-300 MCU cycles depend on context switch
// scheme. Prescaler clk/64..clk/128 looks reasonable for profiler timebase.
// With prescaler clk/64 TIM3 overflow frequency is F_CPU/64/65536
// ~3.8 Hz for 16 MHz crystal.
// Without TIM3 extension by variable function TProfiler::time_interval() must
// be called more frequently. Force context switch every 200ms by setup profler
// process sleep time to 200 ticks.
// UART printing is done every 5-th wake-up, 1 second interval.

typedef TProfiler<0> TProfilerBase;

class TProfilerDemo : public TProfilerBase
{
public:
    INLINE TProfilerDemo()
    {
        TIM2->PSCR = 6; // clk/64
        TIM2->ARRH = 0xFF;
        TIM2->ARRL = 0xFF;
        TIM2->CR1 = TIM2_CR1_CEN; 
    }
};

template<>
uint32_t TProfilerBase::time_interval()
{
    static uint16_t  prev_ticks;
    uint8_t  hi = TIM2->CNTRH;
    uint16_t ticks = (hi << 8) | TIM2->CNTRL;
    uint16_t diff = ticks - prev_ticks;
    prev_ticks = ticks;
    return diff;
}

TProfilerDemo profiler;

void OS::context_switch_user_hook()
{
    profiler.advance_counters();
}

//---------------------------------------------------------------------------
//  Minimalistic UART support:
//    Printing only, use stdio library for formatting
//    No UART class, UART initialisation is done in debug process
//

extern "C" int putchar(int ch);

int putchar(int ch)
{
    if (ch == '\n') putchar('\r');
    while ((UART2->SR & UART2_SR_TXE) == 0) {}
    UART2->DR = ch;
    return ch;
}

//---------------------------------------------------------------------------
//
//  Debug process
//

TDebugProc DebugProc;

Pin<'D', 5> TXD_OUT;

namespace OS {

template<> void TDebugProc::exec()
{
    const timeout_t sleep_time = 200;
    const uint8_t   report_period = 1000 / sleep_time;
    const uint32_t baud = 115200UL;
    const uint32_t divider = (F_MASTER + baud/2) / baud;

    // TXD - slow mode push-pull output
    TXD_OUT.Mode(GPIO_MODE_OUT_PP_HIGH_SLOW);

    // UART2 setup
    // divider[15:12] is zero for high baud rates
    UART2->BRR2 = divider & 0x0F;
    UART2->BRR1 = divider >> 4;
    UART2->CR1  = 0; // 8N
    UART2->CR2  = UART2_CR2_TEN; // Receiving is not needed.
    UART2->CR3  = 0; // 1 stop bit

    printf("\n\nscmRTOS STM8/IAR port:  4-Debug sample\n");

    for (;;) {
        uint8_t report_div = report_period;
        do {
            sleep(sleep_time);
        } while(--report_div);

        profiler.process_data();

        printf("\n\nPrio  ");
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            printf("%7s", get_prio_name(i));
        }

        printf("\nStack ");
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            unsigned stack = OS::get_proc(i)->stack_slack() * sizeof(stack_item_t);
            printf("%7u", stack);
        }

        printf("\nCPU %% ");
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            unsigned cpu = profiler.get_result(i);
            printf("%4u.%02u", cpu/100, cpu%100);
        }
    }

} // TProc4::exec()

} // namespace OS
