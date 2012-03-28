#include "stm32f10x.h"

static inline void init_clocks()
{
	// Enable HSE
	RCC->CR = (RCC->CR &~(RCC_CR_HSEON | RCC_CR_HSEBYP))| RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;

	// Enable Prefetch Buffer
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	// Flash 2 wait state (if freq in 24..48 MHz range - 1WS.)
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_2;

    // HCLK = SYSCLK, PCLK2 = HCLK, PCLK1 = HCLK/2
    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE2 | RCC_CFGR_PPRE1 | RCC_CFGR_ADCPRE)) |
			RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_ADCPRE_DIV6;

#ifdef STM32F10X_CL
	// PLL2/3 pre-divisor: PREDIV2 = 5 (25/5 = 5 MHz)
	RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_PREDIV2) | RCC_CFGR2_PREDIV2_DIV5;
	// PLL2 multiplier: PLL2CLK = 5 * 8 = 40 MHz
	RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_PLL2MUL) | RCC_CFGR2_PLL2MUL8;

	// Enable PLL2
	RCC->CR |= RCC_CR_PLL2ON;
	while(!(RCC->CR & RCC_CR_PLL2RDY)) ;

    // PREDIV1 configuration: SRC = PLL2, DIV = 5 (8MHz)
	RCC->CFGR2 = (RCC->CFGR2 & ~(RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC)) |
			RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5;

	// PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz
	RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL | RCC_CFGR_OTGFSPRE)) |
			RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLMULL9;
#else    
	// PLLCLK = 8MHz * 9 = 72 MHz
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
	RCC->CFGR |= (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);
#endif

	// Enable PLL
	RCC->CR |= RCC_CR_PLLON;

	// Wait till PLL is ready
	while(!(RCC->CR & RCC_CR_PLLRDY)) ;

	// Select PLL as system clock source
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;

    // Wait till PLL is used as system clock source
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) ;
}

extern "C" void init_HW(void);

void init_HW(void)
{
	// RCC system reset(for debug purpose)
	// Set HSION bit
	RCC->CR |= RCC_CR_HSION;
	// Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], ADCPRE[1:0] and MCO[2:0] bits
#ifndef STM32F10X_CL
	RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
	RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif
	// Reset HSEON, CSSON and PLLON bits
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);
	// Reset HSEBYP bit
	RCC->CR &= ~RCC_CR_HSEBYP;
	// Reset PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE bits
	RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifndef STM32F10X_CL
	// Disable all interrupts and clear pending bits
	RCC->CIR = 0x009F0000;
#else
	// Reset PLL2ON and PLL3ON bits
	RCC->CR &= (uint32_t)0xEBFFFFFF;

	// Disable all interrupts and clear pending bits
	RCC->CIR = 0x00FF0000;

	// Reset CFGR2 register
	RCC->CFGR2 = 0x00000000;
#endif

	init_clocks();

	// enable IOPx periph
	RCC->APB2ENR |=
			RCC_APB2ENR_IOPAEN |
			RCC_APB2ENR_IOPBEN |
			RCC_APB2ENR_IOPCEN |
			RCC_APB2ENR_IOPDEN |
#ifdef RCC_APB2ENR_IOPEEN
			RCC_APB2ENR_IOPEEN |
#endif
			RCC_APB2ENR_AFIOEN;

//	NVIC_SetPriorityGrouping(7);	// no preemption, 4 bit of subprio
	NVIC_SetPriorityGrouping(6);	// 1 bit preemption, 3 bit of subprio
//	NVIC_SetPriorityGrouping(5);	// 2 bit preemption, 2 bit of subprio
//	NVIC_SetPriorityGrouping(4);	// 3 bit preemption, 1 bit of subprio
//	NVIC_SetPriorityGrouping(3);	// 4 bit preemption, 0 bit of subprio
}

