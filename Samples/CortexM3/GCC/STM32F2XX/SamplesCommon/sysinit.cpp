#include "stm32f2xx.h"

// PLL_VCO = (HS{E,I}_VALUE / PLL_M) * PLL_N
#define PLL_M      25
#define PLL_N      240

// SYSCLK = PLL_VCO / PLL_P
#define PLL_P      2

// USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ
#define PLL_Q      5

static inline void init_clocks()
{
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;

    // Maximum frequency of the AHB domain is 120MHz.
    // HCLK = SYSCLK / 1
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    // Maximum allowed frequency of the high-speed APB2 domain is 60MHz.
    // PCLK2 = HCLK / 2
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

    // Maximum allowed frequency of the low-speed APB1 domain is 30MHz.
    // PCLK1 = HCLK / 4
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

    // Configure the main PLL
    RCC->PLLCFGR = 0
    		| RCC_PLLCFGR_PLLSRC_HSE             // select HSE as PLL source
    		| PLL_M
    		| (PLL_N << 6)
    		| (((PLL_P >> 1) -1) << 16)
    		| (PLL_Q << 24)
    		;

    // Enable the main PLL
    RCC->CR |= RCC_CR_PLLON;

    // Wait till the main PLL is ready
    while((RCC->CR & RCC_CR_PLLRDY) == 0) ;

    // Configure Flash prefetch, Instruction cache, Data cache and wait state
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_3WS;

    // Select the main PLL as system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait till the main PLL is used as system clock source
    while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL) ;

}

extern "C" void init_HW(void);

void init_HW(void)
{
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	// ensure default configuration:
	RCC->CR |= RCC_CR_HSION;
	RCC->CFGR = 0;
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);
	RCC->PLLCFGR = 0x24003010;                                  // power-on value
	RCC->CR &= ~(RCC_CR_HSEBYP);
	RCC->CIR = 0;                                               // disable all clock interrupts

	init_clocks();

	// enable IOPx periph
	RCC->AHB1ENR |=
			RCC_AHB1ENR_GPIOAEN |
			RCC_AHB1ENR_GPIOBEN |
			RCC_AHB1ENR_GPIOCEN |
			RCC_AHB1ENR_GPIODEN |
			RCC_AHB1ENR_GPIOEEN |
			RCC_AHB1ENR_GPIOFEN |
			RCC_AHB1ENR_GPIOGEN |
			RCC_AHB1ENR_GPIOHEN ;

	//	NVIC_SetPriorityGrouping(7);	// no preemption,           4 bit of subprio (0..15)
	//	NVIC_SetPriorityGrouping(6);	// 1 bit preemption (0..1), 3 bit of subprio (0..7)
		NVIC_SetPriorityGrouping(5);	// 2 bit preemption (0..3), 2 bit of subprio (0..3)
	//	NVIC_SetPriorityGrouping(4);	// 3 bit preemption (0..3), 1 bit of subprio (0..1)
	//	NVIC_SetPriorityGrouping(3);	// 4 bit preemption(0..15), no subprio
}

