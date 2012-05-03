//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   EWAVR (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*                Sample '4-Debug' debug process module
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
//*     4-Debug sample by Oleksandr O. Redchuk, Copyright (c) 2011-2012

#include "scmRTOS.h"

#include <stdio.h>
#include <pgmspace.h>
#include "pin_macros.h"
#include "prio_names.h"
#include "debug.h"

//------------------------------------------------------------------------------
//  Context switch takes about 240-250 MCU cycles depend on context switch
// scheme. Prescaler clk/256 is too coarse for profiler timebase.
// With prescaler clk/64 T1 overflow frequency is F_CPU/64/65536
//  ~1.76 Hz for 7.3728 MHz and ~3.52 Hz for 14.7456 MHz crystal.
// Without TCNT1 extension by variable function TProfiler::time_interval() must
// be called more frequently. Force context switch every 200ms by setup profler
// process sleep time to 200 ticks.
// UART printing is done every 5th wake-up, 1 second interval.

typedef TProfiler<0> TProfilerBase;

class TProfilerDemo : public TProfilerBase
{
public:
    INLINE TProfilerDemo()
    {
        TCCR1A = 0;
        TCCR1B = (1 << CS01) | (1 << CS10);    // Free running, clk/64
        TIMSK1 = 0;
    }
};

template<>
uint32_t TProfilerBase::time_interval()
{
    static uint16_t  prev_ticks;

    uint16_t  ticks = TCNT1;
    uint16_t  diff = ticks - prev_ticks;
    prev_ticks = ticks;
    return diff;
}

TProfilerDemo profiler;

void OS::context_switch_user_hook() { profiler.advance_counters(); }

//---------------------------------------------------------------------------
//  Minimalistic UART support:
//    Printing only, use stdio library for formatting
//    No UART class, UART initialisation is done in debug process
//
#define TXD0 D,1,H

extern "C" int putchar(int ch);
int putchar(int ch)
{
    if (ch == '\n') putchar('\r');
    while (!(UCSR0A & (1<<UDRE0))) {}
    UDR0 = ch;
    return ch;
}

namespace {

const char __flash prio_header[]  = "\n\nPrio  ";
const char __flash stack_header[] =   "\nStack ";
const char __flash rstack_header[] =  "\nRstack";
const char __flash cpu_header[]   =   "\nCPU %% ";
const char __flash prio_format[]  = "%7s";  // :-( IAR has no %S format 
const char __flash stack_format[] = "%7u";
const char __flash cpu_format[]   = "%4u.%02u";

}  // namespace


//---------------------------------------------------------------------------
//
//  Debug process
//

TDebugProc DebugProc;

namespace OS {

template<> void TDebugProc::exec()
{
    const timeout_t sleep_time = 200;
    const uint8_t   report_period = 1000 / sleep_time;
    const uint32_t baud = 115200UL;
    const uint32_t divider = (F_CPU + 4 * baud) / (8 * baud) - 1;

    ON(TXD0);
    DRIVER(TXD0,OUT);

    UCSR0B = 0;
    UCSR0A = (1 << U2X0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UBRR0H = divider >> 8;
    UBRR0L = divider;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);    

    for (;;) {
        uint8_t report_div = report_period;
        do {
            sleep(sleep_time);
        } while(--report_div);

        profiler.process_data();

        printf_P(prio_header);

        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            printf_P(prio_format, get_prio_name(i));
        }

        printf_P(stack_header);
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            unsigned stack = OS::get_proc(i)->stack_slack() * sizeof(stack_item_t);
            printf_P(stack_format, stack);
        }
        printf_P(rstack_header);
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            unsigned stack = OS::get_proc(i)->rstack_slack() * sizeof(stack_item_t);
            printf_P(stack_format, stack);
        }

        printf_P(cpu_header);
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            unsigned cpu = profiler.get_result(i);
            printf_P(cpu_format, cpu/100, cpu%100);
        }
    }

} // TProc4::exec()

} // namespace OS


