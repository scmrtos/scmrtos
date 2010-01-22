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
//*     Version: 3.10
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2010
#ifndef IOSTR71X_H__
#define IOSTR71X_H__

// ---------------- EIC IRQ CHANNELS--------
#define STR71X_IRQ_T0                   0
#define STR71X_IRQ_FLASH                1
#define STR71X_IRQ_PRCCU                2
#define STR71X_IRQ_RTC                  3
#define STR71X_IRQ_WDG                  4
#define STR71X_IRQ_XTI                  5
#define STR71X_IRQ_USB_HI               6
#define STR71X_IRQ_I2C0_ERR             7
#define STR71X_IRQ_I2C1_ERR             8
#define STR71X_IRQ_UART0                9
#define STR71X_IRQ_UART1                10
#define STR71X_IRQ_UART2                11
#define STR71X_IRQ_UART3                12
#define STR71X_IRQ_SPI0                 13
#define STR71X_IRQ_SPI1                 14
#define STR71X_IRQ_I2C0                 15
#define STR71X_IRQ_I2C1                 16
#define STR71X_IRQ_CAN                  17
#define STR71X_IRQ_ADC                  18
#define STR71X_IRQ_T1                   19
#define STR71X_IRQ_T2                   20
#define STR71X_IRQ_T3                   21
#define STR71X_IRQ_HDLC                 25
#define STR71X_IRQ_USB_LO               26
#define STR71X_IRQ_T0_OVF               29
#define STR71X_IRQ_T0_OCMPA             30
#define STR71X_IRQ_T0_OCMPB             31

// ---------------- SFR BITS ---------------
// ---------------- EIC ICR ----------------
#define STR71X_EIC_IRQ_EN               0
#define STR71X_EIC_FIQ_EN               1

// ---------------- RCCU CCR ---------------
#define STR71X_RCCU_LOPWFI              0
#define STR71X_RCCU_WFI_CKSEL           1
#define STR71X_RCCU_CKAF_SEL            2
#define STR71X_RCCU_SRESEN              3
#define STR71X_RCCU_EN_LOCK             7
#define STR71X_RCCU_EN_CKAF             8
#define STR71X_RCCU_EN_CK2_16           9
#define STR71X_RCCU_EN_STOP             10
// ---------------- RCCU CFR ---------------
#define STR71X_RCCU_CSU_CKSEL           0
#define STR71X_RCCU_LOCK                1
#define STR71X_RCCU_CKAF_ST             2
#define STR71X_RCCU_CK2_16              3
#define STR71X_RCCU_CKSTOP_EN           4
#define STR71X_RCCU_SOFT_RES            5
#define STR71X_RCCU_WDG_RES             6
#define STR71X_RCCU_RTC_ALARM           7
#define STR71X_RCCU_LVD_RES             9
#define STR71X_RCCU_WKP_RES             10
#define STR71X_RCCU_LOCK_I              11
#define STR71X_RCCU_CKAF_I              12
#define STR71X_RCCU_CK2_16_I            13
#define STR71X_RCCU_STOP_I              14
#define STR71X_RCCU_DIV2                15
// ---------------- RCCU PLL1CR ------------
#define STR71X_RCCU_DX0                 0
#define STR71X_RCCU_DX1                 1
#define STR71X_RCCU_DX2                 2
#define STR71X_RCCU_MX0                 4
#define STR71X_RCCU_MX1                 5
#define STR71X_RCCU_FREF_RANGE          6
#define STR71X_RCCU_FREEN               7

#define STR71X_PLL1_MUL12               ((0 << STR71X_RCCU_MX1) | (1 << STR71X_RCCU_MX0))
#define STR71X_PLL1_MUL16               ((1 << STR71X_RCCU_MX1) | (1 << STR71X_RCCU_MX0))
#define STR71X_PLL1_MUL20               ((0 << STR71X_RCCU_MX1) | (0 << STR71X_RCCU_MX0))
#define STR71X_PLL1_MUL24               ((1 << STR71X_RCCU_MX1) | (0 << STR71X_RCCU_MX0))
#define STR71X_PLL1_DIV1                ((0 << STR71X_RCCU_DX2) | (0 << STR71X_RCCU_DX1) | (0 << STR71X_RCCU_DX0))
#define STR71X_PLL1_DIV2                ((0 << STR71X_RCCU_DX2) | (0 << STR71X_RCCU_DX1) | (1 << STR71X_RCCU_DX0))
#define STR71X_PLL1_DIV3                ((0 << STR71X_RCCU_DX2) | (1 << STR71X_RCCU_DX1) | (0 << STR71X_RCCU_DX0))
#define STR71X_PLL1_DIV4                ((0 << STR71X_RCCU_DX2) | (1 << STR71X_RCCU_DX1) | (1 << STR71X_RCCU_DX0))
#define STR71X_PLL1_DIV5                ((1 << STR71X_RCCU_DX2) | (0 << STR71X_RCCU_DX1) | (0 << STR71X_RCCU_DX0))
#define STR71X_PLL1_DIV6                ((1 << STR71X_RCCU_DX2) | (0 << STR71X_RCCU_DX1) | (1 << STR71X_RCCU_DX0))
#define STR71X_PLL1_DIV7                ((1 << STR71X_RCCU_DX2) | (1 << STR71X_RCCU_DX1) | (0 << STR71X_RCCU_DX0))
#define STR71X_PLL1_DIV_DISCONNECT      ((1 << STR71X_RCCU_DX2) | (1 << STR71X_RCCU_DX1) | (1 << STR71X_RCCU_DX0))
// ---------------- PCU MDIVR, PDIVR -------
#define STR71X_PCU_RCLK_DIV1            0
#define STR71X_PCU_RCLK_DIV2            1
#define STR71X_PCU_RCLK_DIV4            2
#define STR71X_PCU_RCLK_DIV8            3
// ---------------- PCU MDIVR --------------
#define STR71X_PCU_FACT                 0
// ---------------- PCU PDIVR --------------
#define STR71X_PCU_FACT1                0
#define STR71X_PCU_FACT2                2
// ---------------- TIMx CR1 ---------------
#define STR71X_TIM_ECKEN                0
#define STR71X_TIM_EXEDG                1
#define STR71X_TIM_IEDGA                2
#define STR71X_TIM_IEDGB                3
#define STR71X_TIM_PWM                  4
#define STR71X_TIM_OPM                  5
#define STR71X_TIM_OCAE                 6
#define STR71X_TIM_OCBE                 7
#define STR71X_TIM_OLVLA                8
#define STR71X_TIM_OLVLB                9
#define STR71X_TIM_FOLVLA               10
#define STR71X_TIM_FOLVLB               11
#define STR71X_TIM_PWMI                 14
#define STR71X_TIM_EN                   15
// ---------------- TIMx CR2 ---------------
#define STR71X_TIM_CC0                  0
#define STR71X_TIM_CC1                  1
#define STR71X_TIM_CC2                  2
#define STR71X_TIM_CC3                  3
#define STR71X_TIM_CC4                  4
#define STR71X_TIM_CC5                  5
#define STR71X_TIM_CC6                  6
#define STR71X_TIM_CC7                  7
#define STR71X_TIM_OCBIE                11
#define STR71X_TIM_ICBIE                12
#define STR71X_TIM_TOE                  13
#define STR71X_TIM_OCAIE                14
#define STR71X_TIM_ICAIE                15
// ---------------- TIMx SR ----------------
#define STR71X_TIM_OCFB                 11
#define STR71X_TIM_ICFB                 12
#define STR71X_TIM_TOF                  13
#define STR71X_TIM_OCFA                 14
#define STR71X_TIM_ICFA                 15

#ifdef  __IAR_SYSTEMS_ICC__

typedef struct _STR71X_EIC
{
    volatile unsigned int   ICR;
    volatile unsigned int   CICR;
    volatile unsigned int   CIPR;
    volatile unsigned int   dummy1[3];
    volatile unsigned int   IVR;
    volatile unsigned int   FIR;
    volatile unsigned int   IER;
    volatile unsigned int   dummy2[7];
    volatile unsigned int   IPR;
    volatile unsigned int   dummy3[7];
    volatile unsigned int   SIR[32];
} STR71X_EIC, *PSTR71X_EIC;

typedef struct _STR71X_GPIO
{
    volatile unsigned short PC0;
    volatile unsigned short dummy1;
    volatile unsigned short PC1;
    volatile unsigned short dummy2;
    volatile unsigned short PC2;
    volatile unsigned short dummy3;
    volatile unsigned short PD;
    volatile unsigned short dummy4;
} STR71X_GPIO, *PSTR71X_GPIO;

typedef struct _STR71X_RCCU
{
    volatile unsigned int   CCR;
    volatile unsigned int   dummy1;
    volatile unsigned int   CFR;
    volatile unsigned int   dummy2[3];
    volatile unsigned int   PLL1CR;
    volatile unsigned int   PER;
    volatile unsigned int   SMR;
} STR71X_RCCU, *PSTR71X_RCCU;

typedef struct _STR71X_PCU
{
    volatile unsigned short MDIVR;
    volatile unsigned short dummy1;
    volatile unsigned short PDIVR;
    volatile unsigned short dummy2;
    volatile unsigned short RSTR;
    volatile unsigned short dummy3;
    volatile unsigned short PLL2CR;
    volatile unsigned short dummy4;
    volatile unsigned short BOOTCR;
    volatile unsigned short dummy5;
    volatile unsigned short PWRCR;
} STR71X_PCU, *PSTR71X_PCU;

typedef struct _STR71X_TIM
{
    volatile unsigned short ICAR;
    volatile unsigned short dummy1;
    volatile unsigned short ICBR;
    volatile unsigned short dummy2;
    volatile unsigned short OCAR;
    volatile unsigned short dummy3;
    volatile unsigned short OCBR;
    volatile unsigned short dummy4;
    volatile unsigned short CNTR;
    volatile unsigned short dummy5;
    volatile unsigned short CR1;
    volatile unsigned short dummy6;
    volatile unsigned short CR2;
    volatile unsigned short dummy7;
    volatile unsigned short SR;
} STR71X_TIM, *PSTR71X_TIM;

#define EIC         ((PSTR71X_EIC)      0xFFFFF800)
#define GPIO0       ((PSTR71X_GPIO)     0xE0003000)
#define GPIO1       ((PSTR71X_GPIO)     0xE0004000)
#define GPIO2       ((PSTR71X_GPIO)     0xE0005000)
#define RCCU        ((PSTR71X_RCCU)     0xA0000000)
#define PCU         ((PSTR71X_PCU)      0xA0000040)
#define TIM0        ((PSTR71X_TIM)      0xE0009000)
#define TIM1        ((PSTR71X_TIM)      0xE000A000)
#define TIM2        ((PSTR71X_TIM)      0xE000B000)
#define TIM3        ((PSTR71X_TIM)      0xE000C000)

#endif // __IAR_SYSTEMS_ICC__

#ifdef __IAR_SYSTEMS_ASM__
// ----------------- EIC -------------------
STR71X_EIC_ICR      EQU 0xFFFFF800
STR71X_EIC_CICR     EQU 0xFFFFF804
STR71X_EIC_CIPR     EQU 0xFFFFF808
STR71X_EIC_IVR      EQU 0xFFFFF818
STR71X_EIC_FIR      EQU 0xFFFFF81C
STR71X_EIC_IER      EQU 0xFFFFF820
STR71X_EIC_IPR      EQU 0xFFFFF840
STR71X_EIC_SIR0     EQU 0xFFFFF860
STR71X_EIC_SIR1     EQU 0xFFFFF864
STR71X_EIC_SIR2     EQU 0xFFFFF868
STR71X_EIC_SIR3     EQU 0xFFFFF86C
STR71X_EIC_SIR4     EQU 0xFFFFF870
STR71X_EIC_SIR5     EQU 0xFFFFF874
STR71X_EIC_SIR6     EQU 0xFFFFF878
STR71X_EIC_SIR7     EQU 0xFFFFF87C
STR71X_EIC_SIR8     EQU 0xFFFFF880
STR71X_EIC_SIR9     EQU 0xFFFFF884
STR71X_EIC_SIR10    EQU 0xFFFFF888
STR71X_EIC_SIR11    EQU 0xFFFFF88C
STR71X_EIC_SIR12    EQU 0xFFFFF890
STR71X_EIC_SIR13    EQU 0xFFFFF894
STR71X_EIC_SIR14    EQU 0xFFFFF898
STR71X_EIC_SIR15    EQU 0xFFFFF89C
STR71X_EIC_SIR16    EQU 0xFFFFF8A0
STR71X_EIC_SIR17    EQU 0xFFFFF8A4
STR71X_EIC_SIR18    EQU 0xFFFFF8A8
STR71X_EIC_SIR19    EQU 0xFFFFF8AC
STR71X_EIC_SIR20    EQU 0xFFFFF8B0
STR71X_EIC_SIR21    EQU 0xFFFFF8B4
STR71X_EIC_SIR22    EQU 0xFFFFF8B8
STR71X_EIC_SIR23    EQU 0xFFFFF8BC
STR71X_EIC_SIR24    EQU 0xFFFFF8C0
STR71X_EIC_SIR25    EQU 0xFFFFF8C4
STR71X_EIC_SIR26    EQU 0xFFFFF8C8
STR71X_EIC_SIR27    EQU 0xFFFFF8CC
STR71X_EIC_SIR28    EQU 0xFFFFF8D0
STR71X_EIC_SIR29    EQU 0xFFFFF8D4
STR71X_EIC_SIR30    EQU 0xFFFFF8D8
STR71X_EIC_SIR31    EQU 0xFFFFF8DC
// ---------------- GPIO -------------------
STR71X_GPIO0_PC1    EQU 0xE0003000
STR71X_GPIO0_PC2    EQU 0xE0003004
STR71X_GPIO0_PC3    EQU 0xE0003008
STR71X_GPIO0_PD     EQU 0xE000300C

STR71X_GPIO1_PC1    EQU 0xE0004000
STR71X_GPIO1_PC2    EQU 0xE0004004
STR71X_GPIO1_PC3    EQU 0xE0004008
STR71X_GPIO1_PD     EQU 0xE000400C

STR71X_GPIO2_PC1    EQU 0xE0005000
STR71X_GPIO2_PC2    EQU 0xE0005004
STR71X_GPIO2_PC3    EQU 0xE0005008
STR71X_GPIO2_PD     EQU 0xE000500C
// ---------------- RCCU -------------------
STR71X_RCCU_CCR     EQU 0xA0000000
STR71X_RCCU_CFR     EQU 0xA0000008
STR71X_RCCU_PLL1CR  EQU 0xA0000018
STR71X_RCCU_PER     EQU 0xA000001C
STR71X_RCCU_SMR     EQU 0xA0000020
// ---------------- PCU --------------------
STR71X_PCU_MDIVR    EQU 0xA0000040
STR71X_PCU_PDIVR    EQU 0xA0000044
STR71X_PCU_RSTR     EQU 0xA0000048
STR71X_PCU_PLL2CR   EQU 0xA000004C
STR71X_PCU_BOOTCR   EQU 0xA0000050
STR71X_PCU_PWRCR    EQU 0xA0000054
// ---------------- TIM0 -------------------
STR71X_TIM0_ICAR    EQU 0xE0009000
STR71X_TIM0_ICBR    EQU 0xE0009004
STR71X_TIM0_OCAR    EQU 0xE0009008
STR71X_TIM0_OCBR    EQU 0xE000900C
STR71X_TIM0_CNTR    EQU 0xE0009010
STR71X_TIM0_CR1     EQU 0xE0009014
STR71X_TIM0_CR2     EQU 0xE0009018
STR71X_TIM0_SR      EQU 0xE000901C
// ---------------- TIM1 -------------------
STR71X_TIM1_ICAR    EQU 0xE000A000
STR71X_TIM1_ICBR    EQU 0xE000A004
STR71X_TIM1_OCAR    EQU 0xE000A008
STR71X_TIM1_OCBR    EQU 0xE000A00C
STR71X_TIM1_CNTR    EQU 0xE000A010
STR71X_TIM1_CR1     EQU 0xE000A014
STR71X_TIM1_CR2     EQU 0xE000A018
STR71X_TIM1_SR      EQU 0xE000A01C
// ---------------- TIM2 -------------------
STR71X_TIM2_ICAR    EQU 0xE000B000
STR71X_TIM2_ICBR    EQU 0xE000B004
STR71X_TIM2_OCAR    EQU 0xE000B008
STR71X_TIM2_OCBR    EQU 0xE000B00C
STR71X_TIM2_CNTR    EQU 0xE000B010
STR71X_TIM2_CR1     EQU 0xE000B014
STR71X_TIM2_CR2     EQU 0xE000B018
STR71X_TIM2_SR      EQU 0xE000B01C
// ---------------- TIM3 -------------------
STR71X_TIM3_ICAR    EQU 0xE000C000
STR71X_TIM3_ICBR    EQU 0xE000C004
STR71X_TIM3_OCAR    EQU 0xE000C008
STR71X_TIM3_OCBR    EQU 0xE000C00C
STR71X_TIM3_CNTR    EQU 0xE000C010
STR71X_TIM3_CR1     EQU 0xE000C014
STR71X_TIM3_CR2     EQU 0xE000C018
STR71X_TIM3_SR      EQU 0xE000C01C
#endif  // __IAR_SYSTEMS_ASM__
#endif  // IOSTR71X_H__

