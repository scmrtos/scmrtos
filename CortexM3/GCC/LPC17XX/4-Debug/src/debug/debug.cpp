/**
*  @file debug.cpp
*
*  Created on: 11.04.2011
*  Copyright (c) 2010-2012by Anton Gusev aka AHTOXA
*
*  Changes from STM32F1XX to LPC17XX:
*  Copyright (c) 2012 by Oleksandr Redchuk aka ReAl
*
**/

#include "lpc17xx_clkpwr.h"
#include "lpc17xx_rit.h"

#include <scmRTOS.h>

#include "Pin.h"
#include "dbg_uart.h"


typedef TProfiler<8> TProfilerBase;

class profiler_t : public TProfilerBase
{
private:
public:
	INLINE profiler_t()
		: TProfilerBase()
	{
		LPC_SC->PCONP    |= CLKPWR_PCONP_PCRIT;
		LPC_SC->PCLKSEL1  = (LPC_SC->PCLKSEL1 & ~(0x03 << (CLKPWR_PCLKSEL_RIT-32)))
		                  | (CLKPWR_PCLKSEL_CCLK_DIV_4 << (CLKPWR_PCLKSEL_RIT-32));
		LPC_RIT->RICOUNTER = 0;
		LPC_RIT->RICTRL    = RIT_CTRL_TEN | RIT_CTRL_ENBR;
	}
	uint32_t tick() { return LPC_RIT->RICOUNTER; }
};

/**
 * Profiler object
 */
profiler_t profiler;

template<>
uint32_t TProfilerBase::time_interval()
{
    static uint32_t  prev_ticks;

    uint32_t  ticks = LPC_RIT->RICOUNTER;
    uint32_t  diff = ticks - prev_ticks;
    prev_ticks = ticks;

    return diff;
}


void OS::context_switch_user_hook() { profiler.advance_counters(); }


/**
 * debug UART object
 */

// SK_MLPC1768 board pins
// UART0
typedef Pin<'0',2,'H',OUTPUT,PINSEL_1>    debug_txd;
typedef Pin<'0',3,'H',INPUT_HIZ,PINSEL_1> debug_rxd;

typedef dbg_uart_t<UART_0, 115200> uart_t;

uart_t uart;

/**
 * Readable priority names
 */
namespace {

	uart_t& operator << (uart_t& dst, OS::TPriority prio)
	{
		if (prio >= OS::PROCESS_COUNT) {
			dst << '?';
		} else {
			uint_fast8_t prio_value = prio;
			if (scmRTOS_PRIORITY_ORDER != 0)
				prio_value = OS::PROCESS_COUNT - prio_value - 1;
				                
			if (prio_value == OS::PROCESS_COUNT-1 ) {
				dst << "IDLE";
			} else {
				dst << "pr" << prio_value;
			}
		}
		return dst;
	}

} // namespace

//----------------------------------------------------------------------

typedef OS::process<OS::pr3, 600> TDebugProcess;

namespace OS
{
	template <>
	OS_PROCESS void TDebugProcess::exec()
	{
		// TODO: add to template parameters, initialise in UART constructor
		debug_txd::Init();
		debug_rxd::Init();
	
		for(;;) {
			OS::sleep(1000);
			uart << "\x1B" "c" "\x1B[2J"     // Reset terminal, clear screen and go home
				"4-Debug scmRTOS sample\r\n"
				"\x1B[1m\x1B[37;42m"     // set color attributes (white on green)
				"Process\tStack\tCPU%\r\n"
				"\x1B[1m\x1B[37;40m"     // set color attributes (white on black)
				;
			profiler.advance_counters();
			profiler.process_data();

			for(uint_fast8_t i = 0; i < OS::PROCESS_COUNT; i++) {
				uint32_t cpu = profiler.get_result(i);
				uart << OS::TPriority(i)
				     << '\t' << OS::get_proc(i)->stack_slack() * sizeof(stack_item_t)
				     << '\t' << (double)cpu / 100 << "\r\n";
			}
#if 0
			uart << "Profiler ticks:\t";
			uart.put_hex(profiler.tick());
			uart << "\r\nOS timer ticks:\t";
			uart.put_hex(OS::get_tick_count());
			uart << "\r\n";
#endif
		}
	}
}

TDebugProcess DebugProcess;

