#include "stm32l0xx.h"

static inline void InitClocks()
{

	// enable power control clock
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	// select voltage scaling range 1 (1.8 v, up to 32 MHz)
	PWR->CR = (PWR->CR & ~PWR_CR_VOS) | PWR_CR_VOS_0;

	// insert 1 wait state if frequency more than 16MHz
	FLASH->ACR |= FLASH_ACR_LATENCY;
	while (!(FLASH->ACR & FLASH_ACR_LATENCY))
		;

	// enable prefetch and preread
	FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_PRE_READ;

	// configure PLL
#ifdef USE_HSE_CLOCK
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY))
		;
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMUL12 | RCC_CFGR_PLLDIV3; // PLLVCO = 8MHz * 12 = 96MHz, SYSCLK = PLLVCO / 3 = 32 MHz
#else
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY))
		;
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI | RCC_CFGR_PLLMUL6 | RCC_CFGR_PLLDIV3; // PLLVCO = 16MHz * 6 = 96MHz, SYSCLK = PLLVCO / 3 = 32 MHz
#endif

	// enable PLL
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY))
		;

	// set up divisors for AHB, APB1 and APB2
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE2_DIV1;

	// switch to PLL
	RCC->CFGR |= RCC_CFGR_SW_PLL;
}

extern "C" void init_HW(void);

void init_HW(void)
{
	RCC->CR |= RCC_CR_MSION;    // Turn on MSI

	// Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], MCOSEL[2:0] and MCOPRE[2:0] bits
	RCC->CFGR &= ~(RCC_CFGR_SW | RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2 | RCC_CFGR_MCOSEL | RCC_CFGR_MCO_PRE);

	// Reset HSION, HSIDIVEN, HSEON, CSSON and PLLON bits
	RCC->CR &= ~(RCC_CR_HSION | RCC_CR_HSIDIVEN | RCC_CR_HSEON | RCC_CR_CSSHSEON | RCC_CR_PLLON);

	// Reset HSI48ON  bit
	RCC->CRRCR &= ~RCC_CRRCR_HSI48ON;

	// Reset HSEBYP bit
	RCC->CR &= ~RCC_CR_HSEBYP;

	// Reset PLLSRC, PLLMUL[3:0] and PLLDIV[1:0] bits
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL | RCC_CFGR_PLLDIV);

	// Disable all interrupts
	RCC->CIER = 0;

	InitClocks();

	// enable IOPx peripheral
	RCC->IOPENR |=
			RCC_IOPENR_GPIOAEN |
			RCC_IOPENR_GPIOBEN |
			RCC_IOPENR_GPIOCEN |
			RCC_IOPENR_GPIODEN |
			RCC_IOPENR_GPIOHEN;
}

