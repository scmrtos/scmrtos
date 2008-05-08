//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AT91SAM7xxx (Atmel)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2008


//---------------------------------------------------------------------------
#include <scmRTOS.h>

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 200> TProc1;
typedef OS::process<OS::pr1, 200> TProc2;
typedef OS::process<OS::pr2, 200> TProc3;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------

struct TMamont                   //  data type for sending by message
{                                //
    enum TSource
    {
        PROC_SRC,
        ISR_SRC
    }
    src;
    int data;                    //
};                               //

TMamont Mamont;                  // global test object for recieve data from message

OS::message<TMamont> MamontMsg;  // OS::message object

//---------------------------------------------------------------------------
int main()
{
    OS::Run();
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc1::Exec()
{
    for(;;)
    {
        //--------------------------------------------------
        //
        //            Message test
        //
        //
        //     Receive data as message
        //
        MamontMsg.wait();                                     // wait for message
        Mamont = MamontMsg;                                   // read message content to global test object
        if(Mamont.src == TMamont::PROC_SRC)
        {
            AT91C_BASE_PIOA->PIO_CODR = (1 << 0);
        }
        else
        {
            AT91C_BASE_PIOA->PIO_CODR = (1 << 0);
            AT91C_BASE_PIOA->PIO_SODR = (1 << 0);
            AT91C_BASE_PIOA->PIO_CODR = (1 << 0);
        }
    }
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc2::Exec()
{
    for(;;)
    {
        Sleep(20);
    }
}
//---------------------------------------------------------------------------
OS_PROCESS void TProc3::Exec()
{
    for(;;)
    {
        Sleep(1);
        TMamont m;           // create message content

        m.src  = TMamont::PROC_SRC;
        m.data = 5;
        MamontMsg = m;       // put the content to the OS::message object
        AT91C_BASE_PIOA->PIO_SODR = (1 << 0);
        MamontMsg.send();    // send the message
    }
}
//---------------------------------------------------------------------------
void OS::SystemTimerUserHook() { }
//---------------------------------------------------------------------------
void OS::IdleProcessUserHook() { }
//---------------------------------------------------------------------------
OS_INTERRUPT void Timer_ISR()
{
    OS::TISRW ISRW;
    volatile dword Tmp = AT91C_BASE_TCB->TCB_TC0.TC_SR;   // read to clear int flag

    //--------------------------------------------------
    //
    //            Message test
    //
    //     Send data as message
    //
    TMamont m;           // create message content

    m.src  = TMamont::ISR_SRC;
    m.data = 10;
    MamontMsg = m;       // put the content to the OS::message object
    AT91C_BASE_PIOA->PIO_SODR = (1 << 0);
    MamontMsg.sendISR();    // send the message

}
//-----------------------------------------------------------------------------

_C_LIB_DECL
#pragma language=extended
#pragma location="ICODE"

#define SLCK            32768L      // something about :-(
#define MAINCLK         18432000LL
#define PLLMUL          26
#define PLLDIV          5
#define PLLCLK          ((MAINCLK * PLLMUL) / PLLDIV)
#define MCK             (PLLCLK / 2)
#define PCK             SLCK

#define RTOS_TICK_RATE  1000        // Hz
#define TEST_TIMER_RATE 3500        // Hz

#ifndef AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE     // ioAT91SAM7Sxx.h v4.30A patch
#define AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED
#endif

#ifndef AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL        // ioAT91SAM7Sxx.h v4.30A patch
#define AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL    AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
extern "C" void ContextSwitcher_ISR();
#endif
int __low_level_init(void)
{
	AT91C_BASE_WDTC->WDTC_WDMR = (1*AT91C_WDTC_WDDIS);                  // disable Watchdog
	AT91C_BASE_RSTC->RSTC_RMR = AT91C_RSTC_URSTEN | (0xA5UL << 24);     // enable external reset pin

    AT91C_BASE_PIOA->PIO_MDDR = ~0;                 // push-pull
    AT91C_BASE_PIOA->PIO_PPUDR = ~0;                // pull-up disable
    AT91C_BASE_PIOA->PIO_OER = (1 << 0);            // pin 0 = output

    #if MCK > 30000000LL
    // Flash memory: 1 wait state at MCLK frequences above 30 MHz
    AT91C_BASE_MC->MC_FMR = AT91C_MC_FWS_1FWS;
    #endif

    // Main oscillator
    AT91C_BASE_CKGR->CKGR_MOR = (1 * AT91C_CKGR_MOSCEN) | (0 * AT91C_CKGR_OSCBYPASS) | (0xFF * AT91C_CKGR_OSCOUNT);
    while( ! (AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS) );

    // PLL
    AT91C_BASE_CKGR->CKGR_PLLR = (PLLDIV * AT91C_CKGR_DIV / 0xFF) | (0x1FLL * AT91C_CKGR_PLLCOUNT / 0x3F) | (0 * AT91C_CKGR_OUT / 0x03) \
                                | ((PLLMUL - 1LL) * AT91C_CKGR_MUL / 0x7FF) | (0 * AT91C_CKGR_USBDIV / 0x03);
    while( ! (AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCK) ) ;

    // Main clock
    AT91C_BASE_PMC->PMC_MCKR = AT91C_PMC_CSS_PLL_CLK | AT91C_PMC_PRES_CLK_2;
    // System (core) clock
    AT91C_BASE_PMC->PMC_SCER = AT91C_PMC_PCK;       // Proc clock enabled
    // Peripherial clock
    AT91C_BASE_PMC->PMC_PCER = (1<<AT91C_ID_TC0);   // Timer clock enable
    // RTOS System Timer
    AT91C_BASE_PITC->PITC_PIMR = (((MCK / 16) / RTOS_TICK_RATE - 1) & AT91C_PITC_PIV) \
                                | (1 * AT91C_PITC_PITEN) | (1 * AT91C_PITC_PITIEN);
    // Periodic timer
    AT91C_BASE_TCB->TCB_BMR = AT91C_TCB_TC0XC0S_NONE | AT91C_TCB_TC1XC1S_NONE | AT91C_TCB_TC2XC2S_NONE;

    AT91C_BASE_TCB->TCB_TC0.TC_CMR =
                         AT91C_TC_BSWTRG_NONE | AT91C_TC_BEEVT_NONE | AT91C_TC_BCPC_NONE | AT91C_TC_BCPB_NONE   // TIOB: nothing
                        | AT91C_TC_ASWTRG_NONE | AT91C_TC_AEEVT_NONE | AT91C_TC_ACPC_NONE | AT91C_TC_ACPA_NONE  // TIOA: nothing
                        | AT91C_TC_WAVE | AT91C_TC_WAVESEL_UP_AUTO                      // waveform mode, up to RC
                        | AT91C_TC_ENETRG | AT91C_TC_EEVT_XC2 | AT91C_TC_EEVTEDG_NONE   // no ext. trigger
                        | (0 * AT91C_TC_CPCDIS) | (0 * AT91C_TC_CPCSTOP) | AT91C_TC_BURST_NONE
                        | (0 * AT91C_TC_CLKI) | AT91C_TC_CLKS_TIMER_DIV1_CLOCK;         // clock mck / 2, inc on rising edge
    AT91C_BASE_TCB->TCB_TC0.TC_RC = MCK / 2 / TEST_TIMER_RATE;          // Timeout
    AT91C_BASE_TCB->TCB_TC0.TC_IER = AT91C_TC_CPCS;                     // enable ints on RC compare
    AT91C_BASE_TCB->TCB_TC0.TC_CCR = AT91C_TC_SWTRG | AT91C_TC_CLKEN;   // reset and enable TC0 clock

    // Set RTOS timer handler with priority a little bit higher than context switcher but lower than other interrupts
    AT91C_BASE_AIC->AIC_SMR[AT91C_ID_SYS] = AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL | AT91C_AIC_PRIOR_LOWEST + 1;
    AT91C_BASE_AIC->AIC_SVR[AT91C_ID_SYS] = (dword)OS::SystemTimer_ISR;

    // Set timer handler with higher priority than system timer
    AT91C_BASE_AIC->AIC_SMR[AT91C_ID_TC0] = AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE | AT91C_AIC_PRIOR_LOWEST + 2;
    AT91C_BASE_AIC->AIC_SVR[AT91C_ID_TC0] = (dword)Timer_ISR;

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        // set context switcher handler with the lowest possible priority
        AT91C_BASE_AIC->AIC_SMR[CONTEXT_SWITCH_INT] = AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE | AT91C_AIC_PRIOR_LOWEST;
        AT91C_BASE_AIC->AIC_SVR[CONTEXT_SWITCH_INT] = (dword)ContextSwitcher_ISR;

        AT91C_BASE_AIC->AIC_IECR = (1<<AT91C_ID_SYS)|(1<<CONTEXT_SWITCH_INT)|(1<<AT91C_ID_TC0);
    #else
        AT91C_BASE_AIC->AIC_IECR = (1<<AT91C_ID_SYS)|(1<<AT91C_ID_TC0);
    #endif
    AT91C_BASE_AIC->AIC_EOICR = 0;                                      // Reset AIC logic

    return 1;
}
#pragma language=default
_END_C_LIB_DECL
