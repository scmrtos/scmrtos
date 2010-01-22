#include "stm32f10x.h"

static inline void init_clocks()
{
	// Enable HSE
	RCC->CR |= RCC_CR_HSEON;

	// Wait till HSE is ready
	while (!(RCC->CR & RCC_CR_HSERDY)) ;

	// Enable Prefetch Buffer
   	FLASH->ACR |= FLASH_ACR_PRFTBE;

    // Flash 2 wait state (if freq in 24..48 MHz range - 1WS.)
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // HCLK = SYSCLK, PCLK2 = HCLK, PCLK1 = HCLK/2
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV2;

    // PLLCLK = 8MHz * 9 = 72 MHz
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
    RCC->CFGR |= (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;

    // Wait till PLL is ready
    while(!(RCC->CR & RCC_CR_PLLRDY)) ;

    // Select PLL as system clock source
    RCC->CFGR &= ~(RCC_CFGR_SW);
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait till PLL is used as system clock source
    while ((RCC->CFGR & RCC_CFGR_SWS) != 0x08) ;
}

extern "C" void init_HW(void);

void init_HW(void)
{
	// RCC system reset(for debug purpose)
	// Set HSION bit
	RCC->CR |= 0x00000001;
	// Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], ADCPRE[1:0] and MCO[2:0] bits
	RCC->CFGR &= (uint32_t)0xF8FF0000;
	// Reset HSEON, CSSON and PLLON bits
	RCC->CR &= (uint32_t)0xFEF6FFFF;
	// Reset HSEBYP bit
	RCC->CR &= (uint32_t)0xFFFBFFFF;
	// Reset PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE bits
	RCC->CFGR &= (uint32_t)0xFF80FFFF;
	// Disable all interrupts
	RCC->CIR = 0x00000000;

	init_clocks();

	// enable IOPx periph
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;

//	NVIC_SetPriorityGrouping(7);	// no preemption, 4 bit of subprio
	NVIC_SetPriorityGrouping(6);	// 1 bit preemption, 3 bit of subprio
//	NVIC_SetPriorityGrouping(5);	// 2 bit preemption, 2 bit of subprio
//	NVIC_SetPriorityGrouping(4);	// 3 bit preemption, 1 bit of subprio
//	NVIC_SetPriorityGrouping(3);	// 4 bit preemption, 0 bit of subprio
}

