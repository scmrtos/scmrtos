//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   avr-gcc (GNU)
//*
//*     PURPOSE:   avr-gcc Port Test File
//*                Sample '4-Debug' debug process module
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007-2012

#include <avr/io.h>
#include <stdio.h>
#include "pin_macros.h"

#include "debug.h"

#include "prio_names.h"

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

namespace {

int uart_putc(char ch, FILE *stream)
{
    if (ch == '\n') uart_putc('\r', stream);
    while (!(UCSR0A & (1<<UDRE0))) {}
    UDR0 = ch;
    return 0;
}

}  // namespace


//---------------------------------------------------------------------------
//
//  Debug process
//

TDebugProc DebugProc;

namespace OS {

template<> OS_PROCESS void TDebugProc::exec()
{
    const timeout_t sleep_time = 200;
    const uint8_t   report_period = 1000 / sleep_time;
    const uint32_t baud = 115200UL;
    const uint32_t divider = (F_CPU + 8 * baud) / (16 * baud) - 1;

    UCSR0B = 0;
    UCSR0A = 0;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UBRR0H = divider >> 8;
    UBRR0L = divider;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);    

    FILE uart_file;
    fdev_setup_stream( &uart_file, uart_putc, NULL, _FDEV_SETUP_WRITE);

    stdout = &uart_file;

    // Reset VT100 properties, clear screen and go home, print sample header
    printf_P(PSTR("\x1B" "c" "\x1B[2J" "\tscmRTOS: 4-Debug sample\n" "Prio "));
    for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
        printf_P(PSTR("%7s"), get_prio_name(i));
    }

    for (;;) {
        uint8_t report_div = report_period;
        do {
            sleep(sleep_time);
        } while(--report_div);

        profiler.process_data();

        // Go to 3'd line, clear to end of screen and print statistics
        printf_P(PSTR("\x1B[3;1H" "\x1B[J" "Stack"));
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            unsigned stack = OS::get_proc(i)->stack_slack() * sizeof(stack_item_t);
            printf_P(PSTR("%7u"), stack);
        }

        printf_P(PSTR("\nCPU %%"));
        for(uint8_t i = 0; i < OS::PROCESS_COUNT; i++) {
            unsigned cpu = profiler.get_result(i);
            printf_P(PSTR("%4u.%02u"), cpu/100, cpu%100);
        }
    }

} // TProc4::exec()

} // namespace OS


