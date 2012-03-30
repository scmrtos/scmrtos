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
//*                LPC17xx samples, common microcontroller initialisation
//*
//*     Version: 4.00a
//*
//*     $Revision: 445 $
//*     $Date:: 2011-09-29 #$
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
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2011
//*     LPC17xx samples by Oleksandr O. Redchuk aka ReAl, Copyright (c) 2012


#include "LPC17xx.h"
#include "lpc17xx_clkpwr.h"

// TODO: Move frequency parameters and PLL usage flag into progect configuration file
#define USE_PLL 1

#define OSCRANGE_VAL 0 // 1..20 MHz
#define XTAL_FREQ 12000000UL
#define PLL0_FIN_FREQ XTAL_FREQ
#define PLL0_CCO_FREQ 300000000UL

// TODO: Auto calculations ?
// CCO = (2 * FIN * M) / N
#define PLL0_N_VALUE (2-1)
#define PLL0_M_VALUE (25-1)
#define CCLK_DIVIDER 3

// No defines in NXP include files?
enum
{
	// LPC_SC->SCS
	OSCRANGE = 4, OSCEN = 5, OSCSTAT = 6,
};

enum {	FLASH_RSV_MASK = 0xFFF, FLASH_DIV_SHIFT = 12 };

static inline void setup_flash(int clocks)
{
	if (clocks < 1 || clocks > 6) clocks = 6;
	LPC_SC->FLASHCFG = ((clocks-1) << FLASH_DIV_SHIFT) | (LPC_SC->FLASHCFG & FLASH_RSV_MASK);
}


static inline void init_clocks(bool use_pll)
{
	// Enable XTAL osc and wait for stability
	LPC_SC->SCS = (1UL << OSCEN) | (OSCRANGE_VAL << OSCRANGE);
	while( !(LPC_SC->SCS & (1UL << OSCSTAT)) ) ;

	if (use_pll) {
		// 4.5.13 PLL0 setup sequence
		// 1. Disconnect
		if (LPC_SC->PLL0STAT & CLKPWR_PLL0STAT_PLLC) {
			LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_CONNECT;
			LPC_SC->PLL0FEED = 0xAA;
			LPC_SC->PLL0FEED = 0x55;
		}
		// 2. Disable
		LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_ENABLE;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

		// 4,5. Select source clock for PLL
		LPC_SC->CLKSRCSEL = CLKPWR_CLKSRCSEL_CLKSRC_MAINOSC;
		LPC_SC->PLL0CFG = CLKPWR_PLL0CFG_NSEL(PLL0_N_VALUE)
		                | CLKPWR_PLL0CFG_MSEL(PLL0_M_VALUE);
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

		// 6. Enable PLL
		LPC_SC->PLL0CON |= CLKPWR_PLL0CON_ENABLE;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

		// 7. Set clk divider settings
		// 300/3 = 100MHz
		LPC_SC->CCLKCFG  = CCLK_DIVIDER-1;
		// other peripherals 100/4 = 25MHz by default
		LPC_SC->PCLKSEL0 = 0;
		LPC_SC->PCLKSEL1 = 0;

		// 8. Wait for the PLL to achieve lock
		while(! (LPC_SC->PLL0STAT & CLKPWR_PLL0STAT_PLOCK) ) ;

		// 9. Connect
		LPC_SC->PLL0CON |= CLKPWR_PLL0CON_CONNECT;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

	} else {

		// Disconnect and disable PLL
		if (LPC_SC->PLL0STAT & CLKPWR_PLL0STAT_PLLC) {
			LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_CONNECT;
			LPC_SC->PLL0FEED = 0xAA;
			LPC_SC->PLL0FEED = 0x55;
		}
		LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_ENABLE;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;
		// 
		LPC_SC->CLKSRCSEL = CLKPWR_CLKSRCSEL_CLKSRC_MAINOSC;
		// 12/1 = 12MHz
		LPC_SC->CCLKCFG  = 0;
		// other peripherals 12/4 = 3 MHz by default
		LPC_SC->PCLKSEL0 = 0;
		LPC_SC->PCLKSEL1 = 0;
	}
}

extern "C" void init_HW(void);

void init_HW(void)
{
#if defined(USE_PLL) && USE_PLL
	setup_flash(6);
	init_clocks(true);
	setup_flash(5); // 100 MHz
#else
	init_clocks(false);
	setup_flash(0);
#endif
}

