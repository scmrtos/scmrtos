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
//*     lpc2xxx GCC parts by Anton B. Gusev aka AHTOXA, Copyright (c) 2010-2011

#include <scmRTOS.h>

#define OSC             (12000000UL)
#define CCLK            (OSC * 5)
#define PCLK            (CCLK)

#define RTOS_TICK_RATE  (1000)          // Hz
#define TEST_TIMER_RATE (100)           // Hz

#define PLLSTAT_PLOCK   (0x400)
#define VIC_TIMER1      (5)

#define PCONP_PCTIM0    (0x00000002)
#define PCONP_PCTIM1    (0x00000004)


#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
extern "C" void context_switcher_isr();
#endif

extern void Timer_ISR();

extern "C" int  __low_level_init(void)
{
    MEMMAP = 1;

    PLLCFG = (1<<5) | (CCLK / OSC - 1);     // psel = 1; msel = (CCLK / OSC - 1)
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    PLLCON = 1;                             // PLLE=1, Enable PLL
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    while(!(PLLSTAT & PLLSTAT_PLOCK)) ;     // wait for lock

    PLLCON = 3;                             // PLLC = 1, PLLE = 1, Connect PLL
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    VPBDIV = 1;                             // pclk = cclk

    MAMCR=0x02;
    MAMTIM=0x04;

// ***************************************************************************
// ** GPIO
// ***************************************************************************
    IODIR0  |= (1<<10) | (1<<11);            // Test pins (P0.10 and P0.11) -> output
    IOSET0  = (1<<10) | (1<<11);             // leds off

// ***************************************************************************
// ** TIMER0
// ***************************************************************************
//  RTOS system timer
    PCONP |= PCONP_PCTIM0;
    T0IR = 0xFFFFFFFF;                      // clear int requests

    T0PR = 0;                               // prescaler
    T0MR0 = PCLK / RTOS_TICK_RATE;          // int at TICK_RATE
    T0MCR = (1UL<<1) | (11UL<<0);           // MR0INT = 1, MR0RES = 1
    T0TCR = (1UL<<0);                       // CE = 1, enable timer

// ***************************************************************************
// ** TIMER1
// ***************************************************************************
//   EventFlag test timer
    PCONP |= PCONP_PCTIM1;
    T1IR = 0xFFFFFFFF;                      // clear int requests

    T1PR = 0;                               // prescaler
    T1MR0 = PCLK / TEST_TIMER_RATE;          // int at TICK_RATE
    T1MCR = (1UL<<1) | (11UL<<0);           // MR0INT = 1, MR0RES = 1
    T1TCR = (1UL<<0);                       // CE = 1, enable timer

//***************************************************************************
// ** VIC
//***************************************************************************
    // initialize VIC
    VICIntEnClr = 0xFFFFFFFF;
    VICVectAddr = 0;
    VICIntSelect = 0;

    // Set periodical timer interrupt with highest priority
    VICVectAddr0 = (uint32_t)Timer_ISR;
    VICVectCntl0 = (1<<5) | VIC_TIMER1;

    // Set system timer interrupt vector with little bit higher priority than context switcher
    VICVectAddr14 = (uint32_t)OS::system_timer_isr;
    VICVectCntl14 = (1<<5) | SYSTEM_TIMER_INT;
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    // Set context switcher interrupt handler with lowest possible priority
    VICVectAddr15 = (uint32_t)context_switcher_isr;
    VICVectCntl15 = (1<<5) | CONTEXT_SWITCH_INT;

    VICIntEnable =  (1UL<<SYSTEM_TIMER_INT) | (1UL<<CONTEXT_SWITCH_INT) | (1UL<<VIC_TIMER1);
#else
    VICIntEnable =  (1UL<<SYSTEM_TIMER_INT) | (1UL<<VIC_TIMER1);
#endif

    VICVectAddr = 0;    // Reset VIC logic
    return 1;
}

