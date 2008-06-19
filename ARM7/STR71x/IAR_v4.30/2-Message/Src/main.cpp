//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STR71x (ST)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 3.05
//*
//*     $Revision$
//*     $Date::             $
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
        MamontMsg.wait();                          // wait for message
        Mamont = MamontMsg;                        // read message content to global test object
        if(Mamont.src == TMamont::PROC_SRC)
        {
            GPIO1->PD &= ~(1<<8);                  // GPIO1.8 = 0, turn off LED
        }
        else
        {
            GPIO1->PD &= ~(1<<8);                   // GPIO1.8 = 0, turn off LED
            GPIO1->PD |= (1<<8);                    // GPIO1.8 = 1, turn on LED
            GPIO1->PD &= ~(1<<8);                   // GPIO1.8 = 0, turn off LED
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
        GPIO1->PD |= (1<<8); // GPIO1.8 = 1, turn on LED
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

    TIM1->SR = ~(1<<STR71X_TIM_OCFB);   // clear OCFB flag only

    //--------------------------------------------------
    //
    //            Message test
    //
    //     Send data as message
    //
    TMamont m;              // create message content

    m.src  = TMamont::ISR_SRC;
    m.data = 10;
    MamontMsg = m;          // put the content to the OS::message object
    GPIO1->PD |= (1<<8);    // GPIO1.8 = 1, turn on LED
    MamontMsg.sendISR();    // send the message

}
//-----------------------------------------------------------------------------

_C_LIB_DECL
#pragma language=extended
#pragma location="ICODE"

#define CLK             4000000ULL  // 4MHz CK on IAR STR711-KS board
#define CLK2            (CLK / 1)
#define PLL1MUL         12          // 12, 16, 20, 24
#define PLL1DIV         1           // 1...7
#define PLL1CLK         ((CLK2 * PLL1MUL) / PLL1DIV)
#define CLK3            PLL1CLK
#define RCLK            CLK3
#define MCLK            (RCLK / 1)  // 1,2,4,8
#define PCLK1           (RCLK / 8)  // 1,2,4,8
#define PCLK2           (RCLK / 8)  // 1,2,4,8

#define RTOS_TICK_RATE  1000        // Hz
#define TEST_TIMER_RATE 3500        // Hz

extern "C" void ContextSwitcher_ISR();
int __low_level_init(void)
{
// ***************************************************************************
// ** GPIO
// ***************************************************************************
    // GPIO1: Set pin 8 as push-pull output
    GPIO1->PC0 = (1<<8);
    GPIO1->PC1 = (0<<8);
    GPIO1->PC2 = (1<<8);

// ***************************************************************************
// ** RCCU, PCU
// ***************************************************************************
    // System clock, set RCK = CLK3
    RCCU->CCR = 0
        |(0 << STR71X_RCCU_SRESEN)      // soft reset disabled
        |(0 << STR71X_RCCU_CKAF_SEL)    // RCLK = CLK3
        |(1 << STR71X_RCCU_WFI_CKSEL)   // slow clock during WFI if available
        |(1 << STR71X_RCCU_LOPWFI)      // low power mode during WFI
        ;
    // PLL
    RCCU->PLL1CR = 0
        |(0 << STR71X_RCCU_FREEN)       // Free running mode disabled
        |(1 << STR71X_RCCU_FREF_RANGE)  // CLK2 > 3 Mhz
        |STR71X_PLL1_MUL12              // CLK2 * 12
        |STR71X_PLL1_DIV1               // (CLK2 * 12) / 2
        ;
    RCCU->CFR = 0
        |(0 << STR71X_RCCU_DIV2)        // CLK2 = CLK
        |(0 << STR71X_RCCU_CKSTOP_EN)   // keep PLL runinig if CK_AF selected
        |(1 << STR71X_RCCU_CK2_16)      // turn on PLL
        |(0 << STR71X_RCCU_CSU_CKSEL)   // CLK3 = CLK2, PLL1 not locked yet
        ;

    while(!(RCCU->CFR & (1 << STR71X_RCCU_LOCK)));  // wait until PLL1 lock

    RCCU->CFR = 0
        |(0 << STR71X_RCCU_DIV2)        // CLK2 = CLK/2
        |(0 << STR71X_RCCU_CKSTOP_EN)   // keep PLL runinig if CK_AF selected
        |(1 << STR71X_RCCU_CK2_16)      // turn on PLL
        |(1 << STR71X_RCCU_CSU_CKSEL)   // CLK3 = PLL1CLK
        ;
    // Main clock
    PCU->MDIVR = (STR71X_PCU_RCLK_DIV1 << STR71X_PCU_FACT); // MCLK = RCLK
    // Peripherial clock
    PCU->PDIVR = 0
        |(STR71X_PCU_RCLK_DIV8 << STR71X_PCU_FACT1) // PCLK1 = RCLK/8
        |(STR71X_PCU_RCLK_DIV8 << STR71X_PCU_FACT2) // PLCK2 = RCLK/8
        ;
    // turn off unused peripherial's clock
    RCCU->PER = 0;


// ***************************************************************************
// ** TIM0
// ***************************************************************************
//          RTOS system timer
    TIM0->OCAR = 0xFFFC;     // funny timer, it resets to FFFC instead of 0x0000
    TIM0->OCBR = (PCLK2 / RTOS_TICK_RATE - 5);
    TIM0->CR1 = 0
        |(1 << STR71X_TIM_EN)       // Timer running
        |(0 << STR71X_TIM_OLVLB)    //
        |(1 << STR71X_TIM_OLVLA)    // pulses :)
        |(0 << STR71X_TIM_OCBE)     // OCMPB pin is GPIO
        |(0 << STR71X_TIM_OCAE)     // OCMPA pin is GPIO
        |(0 << STR71X_TIM_OPM)      // one pulse mode disabled
        |(1 << STR71X_TIM_PWM)      // PWM mode enabled
        |(0 << STR71X_TIM_ECKEN)    // internal clock used
        ;
    TIM0->CR2 = 0                   // all ints disabled
        |(1 << STR71X_TIM_OCBIE)    // except output capture B - RTOS ticks
        |(1 << STR71X_TIM_OCAIE)    // and output capture A - used for context switching
        |(0 << STR71X_TIM_CC0)      // CC0-7,   T0CLK = PCLK2
        ;
// ***************************************************************************
// ** TIM1
// ***************************************************************************
//          EventFlag test timer
    TIM1->OCAR = 0xFFFC;     // funny timer, it resets to FFFC instead of 0x0000
    TIM1->OCBR = (PCLK2 / TEST_TIMER_RATE - 5);
    TIM1->CR1 = 0
        |(1 << STR71X_TIM_EN)       // Timer running
        |(0 << STR71X_TIM_OLVLB)    //
        |(1 << STR71X_TIM_OLVLA)    // pulses :)
        |(0 << STR71X_TIM_OCBE)     // OCMPB pin is GPIO
        |(0 << STR71X_TIM_OCAE)     // OCMPA pin is GPIO
        |(0 << STR71X_TIM_OPM)      // one pulse mode disabled
        |(1 << STR71X_TIM_PWM)      // PWM mode enabled
        |(0 << STR71X_TIM_ECKEN)    // internal clock used
        ;
    TIM1->CR2 = 0                   // all ints disabled
        |(1 << STR71X_TIM_OCBIE)    // except output capture B - periodical ticks
        |(0 << STR71X_TIM_CC0)      // CC0-7,   T0CLK = PCLK2
        ;
//***************************************************************************
// ** EIC
//***************************************************************************
#pragma segment="INT_HANDLERS"
    EIC->IVR = (dword)__segment_begin("INT_HANDLERS");
    // Lowest priority for system timer
    EIC->SIR[SYSTEM_TIMER_INT] = ((dword)OS::SystemTimer_ISR << 16) | (1 << 0);
    // Higher priority for periodic timer
    EIC->SIR[STR71X_IRQ_T1] = ((dword)Timer_ISR << 16) | (3 << 0);

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
    // Little bit higher than sys timer priority for context switcher
    EIC->SIR[CONTEXT_SWITCH_INT] = ((dword)ContextSwitcher_ISR << 16) | (2 << 0);
#endif
    // Enable RTOS timer and periodical timer interrupts
    EIC->IER = (1U << SYSTEM_TIMER_INT) | (1U << STR71X_IRQ_T1);

    EIC->IPR = ~0;      // Clear all pending ints
    EIC->ICR = (1 << STR71X_EIC_IRQ_EN);    // Enable EIC IRQ

    return 1;
}
#pragma language=default
_END_C_LIB_DECL
