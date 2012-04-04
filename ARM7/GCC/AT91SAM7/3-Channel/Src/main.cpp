//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AT91SAM7xxx (Atmel)
//*
//*     TOOLKIT:   arm-elf-gcc (GNU)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2012


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
tick_count_t T;                  // global variable for OS::GetTickCount testing
                                 //

//------------------------------------------------------------------------------
//
//   Message "body"
//
//
class TSlon
{
public:
    TSlon() { }
    virtual void eat() = 0;      // feed the slon. For non-russians: slon == elephant ;)
};
//------------------------------------------------------------------------------
class TAfricanSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;

        AT91C_BASE_PIOA->PIO_SODR = (1 << 0);
        AT91C_BASE_PIOA->PIO_CODR = (1 << 0);
    }
};
//------------------------------------------------------------------------------
class TIndianSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs;

        AT91C_BASE_PIOA->PIO_SODR = (1 << 0);
        AT91C_BASE_PIOA->PIO_CODR = (1 << 0);
        AT91C_BASE_PIOA->PIO_SODR = (1 << 0);
        AT91C_BASE_PIOA->PIO_CODR = (1 << 0);
    }
};
//------------------------------------------------------------------------------

TAfricanSlon African;
TIndianSlon  Indian;

OS::channel<TSlon*, 8> SlonQueue; // OS::channel object for 8 'TSlon*' items

OS::TEventFlag Timer_Ovf;
//---------------------------------------------------------------------------
int main()
{
    OS::run();
}
//---------------------------------------------------------------------------
namespace OS
{
    template<>
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
            Timer_Ovf.wait();
            SlonQueue.push(&African);
        }
    }
//---------------------------------------------------------------------------
    template<>
    OS_PROCESS void TProc2::exec()
    {
        for(;;)
        {
            T += OS::get_tick_count();

            sleep(1);
            SlonQueue.push(&Indian);
        }
    }
//---------------------------------------------------------------------------
    template<>
    OS_PROCESS void TProc3::exec()
    {
        for(;;)
        {
            //--------------------------------------------------
            //
            //            Channel test
            //
            //
            //     Get data through channel
            //
            TSlon *p;
            SlonQueue.pop(p);     // get pointer from queue
            p->eat();             // feed the appropriate Slon
        }
    }
}   // namespace OS
//---------------------------------------------------------------------------
void OS::system_timer_user_hook() { }
//---------------------------------------------------------------------------
void OS::idle_process_user_hook() { }
//---------------------------------------------------------------------------
OS_INTERRUPT void timer_isr()
{
    OS::TISRW ISRW;
    AT91C_BASE_TCB->TCB_TC0.TC_SR;   // read to clear int flag

    Timer_Ovf.signal_isr();

    AT91C_BASE_AIC->AIC_EOICR = 0;
}
//-----------------------------------------------------------------------------

#define SLCK            32768L      // something about :-(
#define MAINCLK         18432000LL
#define PLLMUL          26
#define PLLDIV          5
#define PLLCLK          ((MAINCLK * PLLMUL) / PLLDIV)
#define MCK             (PLLCLK / 2)
#define PCK             SLCK

#define RTOS_TICK_RATE  1000        // Hz
#define TEST_TIMER_RATE 3500        // Hz

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
extern "C" void context_switcher_isr();
#endif

extern "C" int __low_level_init(void)
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
    while( ! (AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS) )
        ;

    // PLL
    AT91C_BASE_CKGR->CKGR_PLLR = (PLLDIV * AT91C_CKGR_DIV / 0xFF) | (0x1FLL * AT91C_CKGR_PLLCOUNT / 0x3F) | (0 * AT91C_CKGR_OUT / 0x03) \
                                | ((PLLMUL - 1LL) * AT91C_CKGR_MUL / 0x7FF) | (0 * AT91C_CKGR_USBDIV / 0x03);
    while( ! (AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCK) )
        ;

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
    AT91C_BASE_AIC->AIC_SMR[AT91C_ID_SYS] = AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE | (AT91C_AIC_PRIOR_LOWEST + 1);
    AT91C_BASE_AIC->AIC_SVR[AT91C_ID_SYS] = (uintptr_t)OS::system_timer_isr;

    // Set timer handler with higher priority than system timer
    AT91C_BASE_AIC->AIC_SMR[AT91C_ID_TC0] = AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE | (AT91C_AIC_PRIOR_LOWEST + 2);
    AT91C_BASE_AIC->AIC_SVR[AT91C_ID_TC0] = (uintptr_t)timer_isr;

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        // set context switcher handler with the lowest possible priority
        // context switching int must be edge-triggered to allow software interrupt be implemented by writing to AIC_ISCR
        AT91C_BASE_AIC->AIC_SMR[CONTEXT_SWITCH_INT] = AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED | AT91C_AIC_PRIOR_LOWEST;
        AT91C_BASE_AIC->AIC_SVR[CONTEXT_SWITCH_INT] = (uintptr_t)context_switcher_isr;

        AT91C_BASE_AIC->AIC_IECR = (1<<AT91C_ID_SYS)|(1<<CONTEXT_SWITCH_INT)|(1<<AT91C_ID_TC0);
    #else
        AT91C_BASE_AIC->AIC_IECR = (1<<AT91C_ID_SYS)|(1<<AT91C_ID_TC0);
    #endif
    AT91C_BASE_AIC->AIC_EOICR = 0;                                      // Reset AIC logic

    return 1;
}
