//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuC70xx (Analog Devices)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00a
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
//*     ADuC70xx port maintenance: Anton B. Gusev aka AHTOXA, Copyright (c) 2011

#include "device.h"

#if defined(ADUC7060) || defined(ADUC7061)

#define INT_OSC         32768UL
#define PLL_CLK         (10240000UL)
#define SLCLK           INT_OSC
#define ECLK            PLL_CLK

#define RTOS_TICK_RATE		100			// Hz
#define TEST_TIMER_RATE		100			// Hz

extern "C" void __low_level_init(void)
{
	POWKEY1 = 0x1;
	POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
	POWKEY2 = 0xF4;

	// timer 0 - RTOS tick timer
	T0LD  = ECLK/RTOS_TICK_RATE;
	T0CON = T0_10MHZ | T0_DIV_1 | T0_ENABLED | T0_DOWN | T0_PERIODIC;

	IRQEN = TIMER0_BIT;
}

#else // defined(ADUC7060) || defined(ADUC7061)

#define INT_OSC         32768UL
#define PLL_CLK         (INT_OSC * 1376)
#define SLCLK           (INT_OSC)
#define ECLK            (PLL_CLK)

#define RTOS_TICK_RATE  1000        // Hz
#define TEST_TIMER_RATE 3500        // Hz

extern "C" void __low_level_init(void)
{
    // Start PLL
    PLLKEY1 = 0xAA;
    PLLCON = PLL_INTERNAL_CLK | CLK_INT_PLL;
    PLLKEY2 = 0x55;

    POWKEY1 = 0x01;
    POWCON = MODE_ACTIVE | CLK_DIV_1;
    POWKEY2 = 0xF4;

    T0LD = ECLK / RTOS_TICK_RATE - 1;
    T0CON = T0_ENABLED | T0_PERIODIC | T0_DIV_1;
    IRQEN = RTOS_TIMER_BIT;
}

#endif // defined(ADUC7060) || defined(ADUC7061)
