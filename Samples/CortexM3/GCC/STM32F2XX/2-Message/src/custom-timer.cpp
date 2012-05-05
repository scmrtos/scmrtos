//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision: 537 $
//*     $Date:: 2012-05-04 #$
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
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2012

#include "stm32f2xx.h"
#include "pin.h"
#include <scmRTOS.h>


extern "C" void __init_system_timer()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	NVIC_SetPriority(TIM4_IRQn, 255);
	NVIC_EnableIRQ(TIM4_IRQn);

	TIM4->PSC = 1;
	TIM4->ARR = 36000;          // 1KHz
	TIM4->EGR = TIM_EGR_UG;     // generate an update event to reload the prescaler value immediately
	TIM4->DIER = TIM_DIER_UIE;  // enable update interrupt
	TIM4->CR1 = TIM_CR1_CEN;    // run timer
}

OS_INTERRUPT void OS::SystemTimer_ISR()
{
	if (TIM4->SR & TIM_SR_UIF)
	{
		scmRTOS_ISRW_TYPE ISR;
		TIM4->SR = ~TIM_SR_UIF;
#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
		system_timer_user_hook();
#endif
		Kernel.system_timer();
	}
}
