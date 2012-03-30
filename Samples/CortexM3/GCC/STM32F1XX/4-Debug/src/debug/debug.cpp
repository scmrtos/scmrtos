/**
*  @file debug.cpp
*
*  Created on: 11.04.2011
*  Copyright (c) 2010 by Anton Gusev aka AHTOXA
**/

#include "stm32f10x.h"
#include <scmRTOS.h>
#include "dbg_uart.h"

typedef TProfiler<0> TProfilerBase;

class profiler_t : public TProfilerBase
{
private:
public:
	INLINE profiler_t()
		: TProfilerBase()
	{
		// enable TIM3 clock
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		// count up to ARR, no divisor, auto reload
		TIM3->CR1 = 0;
		// period (full scale)
		TIM3->ARR = 0xFFFF;
		// set prescaler (72MHz/0xFFFF/1098 = 1Hz)
		TIM3->PSC = 1097;
		// generate an update event to reload the prescaler value immediately
		TIM3->EGR = TIM_EGR_UG;
		// run timer
		TIM3->CR1 |= TIM_CR1_CEN;
	}
};

/**
 * Profiler object
 */
profiler_t profiler;

/**
 * debug UART object
 */
dbg_uart_t<UART_1, 115200> uart;

/**
 * Readable priority names
 */
static const char* priorities[] =
{
	"IDLE",
#if scmRTOS_PROCESS_COUNT   > 9
	"pr9 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 8
	"pr8 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 7
	"pr7 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 6
	"pr6 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 5
	"pr5 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 4
	"pr4 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 3
	"pr3 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 2
	"pr2 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 1
	"pr1 ",
#endif
#if scmRTOS_PROCESS_COUNT   > 0
	"pr0 ",
#endif
};

template<>
uint32_t TProfilerBase::time_interval()
{
    static uint16_t  prev_ticks;

    uint16_t  ticks = TIM3->CNT;
    uint16_t  diff = ticks - prev_ticks;
    prev_ticks = ticks;
    return diff;
}

void OS::context_switch_user_hook() { profiler.advance_counters(); }

typedef OS::process<OS::pr3, 600> TDebugProcess;

namespace OS
{
	template <>
	OS_PROCESS void TDebugProcess::exec()
	{
		for(;;)
		{
			OS::sleep(1000);
			profiler.advance_counters();
			profiler.process_data();
			uart << "\x1B[2J";				// clear screen
			uart << "\x1B[1;1H";			// go to 1,1
			uart << "\x1B[1m\x1B[37;42m"	// set color attributes (white on green)
				<< "Process\tStack\tCPU%\r\n"
				<< "\x1B[1m\x1B[37;40m";	// set color attributes (white on black)
			for(uint_fast8_t i = 0; i < OS::PROCESS_COUNT; i++)
			{
				uint32_t cpu = profiler.get_result(i);
				uart << priorities[i] << '\t'
					<< OS::get_proc(i)->stack_slack() * sizeof(stack_item_t)  << '\t'
					<< (double)cpu / 100 << "\r\n";
			}
		}
	}
}

TDebugProcess DebugProcess;
