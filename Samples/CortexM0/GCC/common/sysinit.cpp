#include    <LPC11xx.h>

static inline void init_clocks()
{
#ifndef NDEBUG
    // Set IRC as MAIN clock source
    LPC_SYSCON->MAINCLKSEL = LPC_MAINCLK_IRC;
    LPC_SYSCON->MAINCLKUEN = (0 << LPC_CLK_ENA);
    LPC_SYSCON->MAINCLKUEN = (1 << LPC_CLK_ENA);
#endif

    // Turn on PLL
    LPC_SYSCON->PDRUNCFG = ~((1 << 9) | (1 << 12)) &
            (0
            | (0 << LPC_IRCOUT_PD)
            | (0 << LPC_IRC_PD)
            | (0 << LPC_FLASH_PD)
            | (1 << LPC_BOD_PD)
            | (0 << LPC_ADC_PD)
            | (1 << LPC_SYSOSC_PD)
            | (1 << LPC_WDTOSC_PD)
            | (0 << LPC_SYSPLL_PD)
            | (1 << 8)                  // Mandatory
            | (1 << 10)                 // Mandatory
            | (1 << 11)                 // Mandatory
            | (0x07 << 13)              // Mandatory
            )
            ;


    // Set IRC as PLL clock source
    LPC_SYSCON->SYSPLLCLKSEL = LPC_PLLCLK_IRC;
    LPC_SYSCON->SYSPLLCLKUEN = (0 << LPC_CLK_ENA);
    LPC_SYSCON->SYSPLLCLKUEN = (1 << LPC_CLK_ENA);

    LPC_SYSCON->SYSPLLCTRL = 0
            | ( (PLL_MUL - 1) << LPC_MSEL)
            | ( PLL_DIV << LPC_PSEL)
            ;

    // wait until PLL locked
    while(!(LPC_SYSCON->SYSPLLSTAT & (1 << LPC_PLL_LOCK)))
            ;

    // 3 FLASH waitstates
    *(uint32_t *)0x4003C010 = 3;

    // Set PLL output as MAIN clock source
    LPC_SYSCON->MAINCLKSEL = LPC_MAINCLK_PLLOUT;
    LPC_SYSCON->MAINCLKUEN = (0 << LPC_CLK_ENA);
    LPC_SYSCON->MAINCLKUEN = (1 << LPC_CLK_ENA);
}

extern "C" void init_HW(void);

void init_HW(void)
{
    init_clocks();

    LPC_SYSCON->SYSAHBCLKCTRL = 0
            | (1 << LPC_AHBCLK_SYS)
            | (1 << LPC_AHBCLK_ROM)             // enable to allow flash update
            | (1 << LPC_AHBCLK_RAM)
            | (1 << LPC_AHBCLK_FLASHREG)
            | (1 << LPC_AHBCLK_FLASHARRAY)
            | (0 << LPC_AHBCLK_I2C)
            | (1 << LPC_AHBCLK_GPIO)
            | (0 << LPC_AHBCLK_CT16B0)
            | (0 << LPC_AHBCLK_CT16B1)
            | (0 << LPC_AHBCLK_CT32B0)
            | (0 << LPC_AHBCLK_CT32B1)
            | (0 << LPC_AHBCLK_SSP0)
            | (0 << LPC_AHBCLK_UART)
            | (0 << LPC_AHBCLK_ADC)
            | (0 << LPC_AHBCLK_WDT)
            | (1 << LPC_AHBCLK_IOCON)
            | (0 << LPC_AHBCLK_SSP1)
            ;
    LPC_GPIO0->DIR = 0
            | (1 << 11)     // NC
            | (1 << 10)     // NC
            | (1 << 9)      // NC
            | (1 << 8)      // NC
            | (1 << 7)      // NC
            | (1 << 6)      // NC
            | (1 << 5)      // NC
            | (1 << 4)      // LED
            | (1 << 3)      // NC
            | (1 << 2)      // NC
            | (1 << 1)      // NC
            | (0 << 0)      // Reset pin
            ;
    LPC_GPIO0->DATA = 0
            | (0 << 11)     // NC
            | (0 << 10)     // NC
            | (0 << 9)      // NC
            | (0 << 8)      // NC
            | (0 << 7)      // NC
            | (0 << 6)      // NC
            | (0 << 5)      // NC
            | (0 << 4)      // LED
            | (0 << 3)      // NC
            | (0 << 2)      // NC
            | (0 << 1)      // NC
            | (0 << 0)      // Reset pin
            ;

    LPC_GPIO1->DIR = 0
            | (1 << 11)     // NC
            | (1 << 10)     // NC
            | (1 << 9)      // NC
            | (1 << 8)      // NC
            | (1 << 7)      // TXD
            | (0 << 6)      // RXD
            | (1 << 5)      // NC
            | (1 << 4)      // NC
            | (1 << 3)      // NC
            | (1 << 2)      // NC
            | (1 << 1)      // NC
            | (1 << 0)      // NC
            ;
    LPC_GPIO1->DATA = 0
            | (0 << 11)     // NC
            | (0 << 10)     // NC
            | (0 << 9)      // NC
            | (0 << 8)      // NC
            | (1 << 7)      // TXD
            | (0 << 6)      // RXD
            | (0 << 5)      // NC
            | (0 << 4)      // NC
            | (0 << 3)      // NC
            | (0 << 2)      // NC
            | (0 << 1)      // NC
            | (0 << 0)      // NC
            ;
    LPC_GPIO2->DIR = 0
            | (1 << 0)      // NC
            ;
    LPC_GPIO3->DIR = 0
            | (1 << 5)      // NC
            | (1 << 4)      // NC
            | (1 << 2)      // NC
            ;
    LPC_GPIO3->DATA = 0
            | (0 << 5)      // NC
            | (0 << 4)      // NC
            | (0 << 2)      // NC
            ;
/*
    // setup UART pins
    LPC_IOCON->PIO1_6 = 0
            | ( 1 << 0)     // RXD func
            | ( 0 << 3)     // no pull-up/pull-down
            | ( 1 << 5)     // enable hysteresis
            ;
    LPC_IOCON->PIO1_7 = 0
            | ( 1 << 0)     // TXD func
            | ( 0 << 3)     // no pull-up/pull-down
            | ( 1 << 5)     // enable hysteresis
            ;
    LPC_SYSCON->UARTCLKDIV = (1 << LPC_CLK_DIV);
*/

/*
    LPC_SYSCON->CLKOUTCLKSEL = 3;   // main_clk
    LPC_SYSCON->CLKOUTUEN = 0;
    LPC_SYSCON->CLKOUTUEN = 1;
    LPC_SYSCON->CLKOUTDIV = 1;

    LPC_IOCON->PIO0_1 = 0
            | ( 1 << 0 )    // CLKOUT func
            | ( 0 << 3 )    // no pull-ups
            | ( 0 << 5 )    // no hysteresis
            | ( 3 << 6 )    // reserved
            ;
*/
}
