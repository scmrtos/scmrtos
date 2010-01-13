//******************************************************************************
//*
//*     FULLNAME:  ADuC7019, ADuC702x SFR description file
//*
//*     PROCESSOR: ADuC7019, ADuC702x (Analog Devices)
//*
//*     TOOLKIT:   C/C++
//*
//*     Version:   1.00
//*
//*     $Revision: 99 $
//*     $Date: 2007-12-31 17:13:51 +0200 (Пн, 31 дек 2007) $
//*
//*     Copyright (c) 2008, Sergey A. Borshch
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
//******************************************************************************
#ifndef ADUC702X_H__
#define ADUC702X_H__ 

#ifndef __ASSEMBLER__
#include    <stdint.h>


// Interrupt controller
enum 
{
    ALL_INT_BIT         = (1UL << 0),                      
    SWI_BIT             = (1UL << 1),                      
    RTOS_TIMER_BIT      = (1UL << 2),                      
    GP_TIMER_BIT        = (1UL << 3),                      
    WAKEUP_TIMER_BIT    = (1UL << 4),                      
    WATCHDOG_TIMER_BIT  = (1UL << 5),                      
    FLASHCON_BIT        = (1UL << 6),                      
    ADC_BIT             = (1UL << 7),                      
    PLL_LOCK_BIT        = (1UL << 8),                      
    I2C_SLAVE_BIT       = (1UL << 9),                      
    I2C_MASTER0_BIT     = (1UL << 10),                      
    I2C_MASTER1_BIT     = (1UL << 11),                      
    SPI_SLAVE_BIT       = (1UL << 12),                      
    SPI_MASTER_BIT      = (1UL << 13),                      
    UART_BIT            = (1UL << 14),                      
    EXT_IRQ0_BIT        = (1UL << 15),                      
    MONITOR_BIT         = (1UL << 16),                      
    PSM_BIT             = (1UL << 17),                      
    EXT_IRQ1_BIT        = (1UL << 18),                      
    PLA_IRQ0_BIT        = (1UL << 19),                      
    PLA_IRQ1_BIT        = (1UL << 20),                      
    EXT_IRQ2_BIT        = (1UL << 21),                      
    EXT_IRQ3_BIT        = (1UL << 22),                      
    PWM_BIT             = (1UL << 23),                                  
};

#define IRQSTA      (*(volatile uint32_t *)         0xFFFF0000)
#define IRQSIG      (*(volatile uint32_t *)         0xFFFF0004)
#define IRQEN       (*(volatile uint32_t *)         0xFFFF0008)
#define IRQCLR      (*(volatile uint32_t *)         0xFFFF000C)
#define SWICFG      (*(volatile uint32_t *)         0xFFFF0010)
#define FIQSTA      (*(volatile uint32_t *)         0xFFFF0100)
#define FIQSIG      (*(volatile uint32_t *)         0xFFFF0104)
#define FIQEN       (*(volatile uint32_t *)         0xFFFF0108)
#define FIQCLR      (*(volatile uint32_t *)         0xFFFF010C)

// System control
#define REMAP       (*(volatile uint8_t *)          0xFFFF0220)
#define RSTSTA      (*(volatile uint8_t *)          0xFFFF0230)
#define RSTCLR      (*(volatile uint8_t *)          0xFFFF0234)

// Timer 0 = RTOS timer
#define T0LD        (*(volatile uint16_t *)         0xFFFF0300)
#define T0VAL       (*(volatile uint16_t const *)   0xFFFF0304)
#define T0CON       (*(volatile uint16_t *)         0xFFFF0308)
enum
{
    T0_DIV_1        = (0UL << 2),
    T0_DIV_16       = (1UL << 2),
    T0_DIV_256      = (2UL << 2),
    
    T0_PERIODIC     = (0UL << 6),
    T0_FREE_RUNNING = (1UL << 6),

    T0_DISABLED     = (0UL << 7),
    T0_ENABLED      = (1UL << 7),
};
#define T0CLRI      (*(volatile uint8_t *)          0xFFFF030C)

// Timer 1 = General purpose timer
#define T1LD        (*(volatile uint32_t *)         0xFFFF0320)
#define T1VAL       (*(volatile uint32_t const *)   0xFFFF0324)
#define T1CON       (*(volatile uint16_t *)         0xFFFF0328)
enum
{
    T1_DIV_1                = (0UL << 0),
    T1_DIV_16               = (4UL << 0),
    T1_DIV_256              = (8UL << 0),
    T1_DIV_32768            = (16UL << 0),
    
    T1_BINARY               = (0UL << 4),
    T1_24_HOURS             = (2UL << 4),
    T1_255_HOURS            = (3UL << 4),

    T1_PERIODIC             = (0UL << 6),
    T1_FREE_RUNNING         = (1UL << 6),

    T1_DISABLED             = (0UL << 7),
    T1_ENABLED              = (1UL << 7),

    T1_DOWN                 = (0UL << 8),
    T1_UP                   = (1UL << 8),

    T1_HCLK                 = (0UL << 9),
    T1_EXT_32K_CLK          = (1UL << 9),
    T1_P1_0_CLK             = (2UL << 9),
    T1_P0_6_CLK             = (3UL << 9),
    
    T1_EVENT_T0             = (0UL << 12),                      
    T1_EVENT_T1             = (1UL << 12),                      
    T1_EVENT_T2             = (2UL << 12),                      
    T1_EVENT_T3             = (3UL << 12),                      
    T1_EVENT_FLASHCON       = (4UL << 12),                      
    T1_EVENT_ADC            = (5UL << 12),                      
    T1_EVENT_PLL_LOCK       = (6UL << 12),                      
    T1_EVENT_I2C_SLAVE      = (7UL << 12),                      
    T1_EVENT_I2C_MASTER0    = (8UL << 12),                      
    T1_EVENT_I2C_MASTER1    = (9UL << 12),                      
    T1_EVENT_SPI_SLAVE      = (10UL << 12),                      
    T1_EVENT_SPI_MASTER     = (11UL << 12),                      
    T1_EVENT_UART           = (12UL << 12),                      
    T1_EVENT_EXT_IRQ0       = (13UL << 12),                      
    T1_EVENT_MONITOR        = (14UL << 12),                      
    T1_EVENT_PSM            = (15UL << 12),                      
    T1_EVENT_EXT_IRQ1       = (16UL << 12),                      
    T1_EVENT_PLA_IRQ0       = (17UL << 12),                      
    T1_EVENT_PLA_IRQ1       = (18UL << 12),                      
    T1_EVENT_EXT_IRQ2       = (19UL << 12),                      
    T1_EVENT_EXT_IRQ3       = (20UL << 12),                      
    T1_EVENT_PWM            = (21UL << 12),                                  

    T1_EVENT_DISABLED       = (0UL <<  17),                                  
    T1_EVENT_ENABLED        = (1UL <<  17),                                  
};
#define T1CLRI      (*(volatile uint8_t *)          0xFFFF032C)
#define T1CAP       (*(volatile uint32_t const *)   0xFFFF0330)

// Timer 2 = Wake-up timer
#define T2LD        (*(volatile uint32_t *)         0xFFFF0340)
#define T2VAL       (*(volatile uint32_t const *)   0xFFFF0344)
#define T2CON       (*(volatile uint16_t *)         0xFFFF0348)
enum
{
    T2_DIV_1                = (0UL << 0),
    T2_DIV_16               = (4UL << 0),
    T2_DIV_256              = (8UL << 0),
    T2_DIV_32768            = (16UL << 0),
    
    T2_BINARY               = (0UL << 4),
    T2_24_HOURS             = (2UL << 4),
    T2_255_HOURS            = (3UL << 4),

    T2_PERIODIC             = (0UL << 6),
    T2_FREE_RUNNING         = (1UL << 6),

    T2_DISABLED             = (0UL << 7),
    T2_ENABLED              = (1UL << 7),

    T2_DOWN                 = (0UL << 8),
    T2_UP                   = (1UL << 8),

    T2_EXT_CRYSTALL         = (0UL << 9),
    T2_INTERNAL_OSC         = (2UL << 9),
    T2_CORE_CLOCK           = (3UL << 9),
};
#define T2CLRI      (*(volatile uint8_t *)          0xFFFF034C)

// Timer 3 = Watchdog timer
#define T3LD        (*(volatile uint16_t *)         0xFFFF0360)
#define T3VAL       (*(volatile uint16_t const *)   0xFFFF0364)
#define T3CON       (*(volatile uint16_t *)         0xFFFF0368)
enum
{
    T3_DIV_1        = (0UL << 2),
    T3_DIV_16       = (1UL << 2),
    T3_DIV_256      = (2UL << 2),
    
    T3_SECURE_CLEAR = (1UL << 4),

    T3_WDT_MODE     = (1UL << 5),

    T3_PERIODIC     = (0UL << 6),
    T3_FREE_RUNNING = (1UL << 6),

    T3_DISABLED     = (0UL << 7),
    T3_ENABLED      = (1UL << 7),
};
#define T3CLRI      (*(volatile uint8_t *)          0xFFFF036C)

// PLL
#define PLLKEY1     (*(volatile uint16_t *)         0xFFFF0410)
#define PLLCON      (*(volatile uint8_t *)          0xFFFF0414)
enum
{
    MDCLK_0             = (0UL << 0),
    MDCLK_1             = (1UL << 0),
    MDCLK_3             = (2UL << 0),
    MDCLK_4             = (3UL << 0),
    CLK_INT_PLL         = MDCLK_1,
    CLK_EXTERNAL        = MDCLK_3,

    OSEL                = (1UL << 5),
    PLL_EXTERNAL_CLK    = 0,
    PLL_INTERNAL_CLK    = OSEL,
};
#define PLLKEY2     (*(volatile uint16_t *)         0xFFFF0418)

// Power control
#define POWKEY1     (*(volatile uint16_t *)         0xFFFF0404)
#define POWCON      (*(volatile uint16_t *)         0xFFFF0408)
enum
{
    CD_0                = (0UL << 0),
    CD_1                = (1UL << 0),
    CD_2                = (2UL << 0),
    CD_3                = (3UL << 0),
    CD_4                = (4UL << 0),
    CD_5                = (5UL << 0),
    CD_6                = (6UL << 0),
    CD_7                = (7UL << 0),
    CLK_DIV_1           = CD_0,
    CLK_DIV_2           = CD_1,
    CLK_DIV_4           = CD_2,
    CLK_DIV_8           = CD_3,
    CLK_DIV_16          = CD_4,
    CLK_DIV_32          = CD_5,
    CLK_DIV_64          = CD_6,
    CLK_DIV_128         = CD_7,

    PC_0                = (0UL << 4),
    PC_1                = (1UL << 4),
    PC_2                = (2UL << 4),
    PC_3                = (3UL << 4),
    PC_4                = (4UL << 4),
    MODE_ACTIVE         = PC_0,
    MODE_PAUSE          = PC_1,
    MODE_NAP            = PC_2,
    MODE_SLEEP          = PC_3,
    MODE_STOP           = PC_4,

};
#define POWKEY2     (*(volatile uint16_t *)         0xFFFF040C)

// Power supply monitor
#define PSMCON 	    (*(volatile uint16_t *)         0xFFFF0440)
#define CMPCON 	    (*(volatile uint16_t *)         0xFFFF0444)

// Reference
#define REFCON 	    (*(volatile uint8_t *)          0xFFFF048C)

// ADC
#define ADCCON 	    (*(volatile uint16_t *)         0xFFFF0500)
#define ADCCP       (*(volatile uint8_t *)          0xFFFF0504)
#define ADCCN       (*(volatile uint8_t *)          0xFFFF0508)
#define ADCSTA      (*(volatile uint8_t const *)    0xFFFF050C)
#define ADCDAT      (*(volatile uint32_t const *)   0xFFFF0510)
#define ADCRST      (*(volatile uint8_t *)          0xFFFF0514)
#define ADCGN       (*(volatile uint16_t *)         0xFFFF0530)
#define ADCOF       (*(volatile uint16_t *)         0xFFFF0534)

// DAC
#define DAC0CON     (*(volatile uint8_t *)          0xFFFF0600)
#define DAC0DAT     (*(volatile uint32_t *)         0xFFFF0604)
#define DAC1CON     (*(volatile uint8_t *)          0xFFFF0608)
#define DAC1DAT     (*(volatile uint32_t *)         0xFFFF060C)
#define DAC2CON     (*(volatile uint8_t *)          0xFFFF0610)
#define DAC2DAT     (*(volatile uint32 *)           0xFFFF0614)
#define DAC3CON     (*(volatile uint8_t *)          0xFFFF0618)
#define DAC3DAT     (*(volatile uint32_t *)         0xFFFF061C)

// UART
#define COMTX       (*(volatile uint8_t *)          0xFFFF0700)
#define COMRX       (*(volatile uint8_t const *)    0xFFFF0700)
#define COMDIV0     (*(volatile uint8_t *)          0xFFFF0700)
#define COMIEN0     (*(volatile uint8_t *)          0xFFFF0704)
#define COMDIV1     (*(volatile uint8_t *)          0xFFFF0704)
#define COMIID0     (*(volatile uint8_t const *)    0xFFFF0708)
#define COMCON0     (*(volatile uint8_t *)          0xFFFF070C)
#define COMCON1     (*(volatile uint8_t *)          0xFFFF0710)
#define COMSTA0     (*(volatile uint8_t const *)    0xFFFF0714)
#define COMSTA1     (*(volatile uint8_t const *)    0xFFFF0718)
#define COMSCR      (*(volatile uint8_t *)          0xFFFF071C)
#define COMIEN1     (*(volatile uint8_t *)          0xFFFF0720)
#define COMIID1     (*(volatile uint8_t const *)    0xFFFF0724)
#define COMADR      (*(volatile uint8_t *)          0xFFFF0728)
#define COMDIV2     (*(volatile uint16_t *)         0xFFFF072C)

// I2C 0
#define I2C0MSTA    (*(volatile uint8_t const *)    0xFFFF0800)
#define I2C0SSTA    (*(volatile uint8_t const *)    0xFFFF0804)
#define I2C0SRX     (*(volatile uint8_t const *)    0xFFFF0808)
#define I2C0STX     (*(volatile uint8_t *)          0xFFFF080C)
#define I2C0MRX     (*(volatile uint8_t const *)    0xFFFF0810)
#define I2C0MTX     (*(volatile uint8_t *)          0xFFFF0814)
#define I2C0CNT     (*(volatile uint8_t *)          0xFFFF0818)
#define I2C0ADR     (*(volatile uint8_t *)          0xFFFF081C)
#define I2C0BYTE    (*(volatile uint8_t *)          0xFFFF0824)
#define I2C0ALT     (*(volatile uint8_t *)          0xFFFF0828)
#define I2C0CFG     (*(volatile uint8_t *)          0xFFFF082C)
#define I2C0DIV     (*(volatile uint16_t *)         0xFFFF0830)
#define I2C0DIVL    (*(volatile uint8_t *)          0xFFFF0830)
#define I2C0DIVH    (*(volatile uint8_t *)          0xFFFF0831)
#define I2C0ID0     (*(volatile uint8_t *)          0xFFFF0838)
#define I2C0ID1     (*(volatile uint8_t *)          0xFFFF083C)
#define I2C0ID2     (*(volatile uint8_t *)          0xFFFF0840)
#define I2C0ID3     (*(volatile uint8_t *)          0xFFFF0844)
#define I2C0CCNT    (*(volatile uint8_t *)          0xFFFF0848)
#define I2C0FSTA    (*(volatile uint16_t const *)   0xFFFF084C)

// I2C 1
#define I2C1MSTA    (*(volatile uint8_t const *)    0xFFFF0900)
#define I2C1SSTA    (*(volatile uint8_t const *)    0xFFFF0904)
#define I2C1SRX     (*(volatile uint8_t const *)    0xFFFF0908)
#define I2C1STX     (*(volatile uint8_t *)          0xFFFF090C)
#define I2C1MRX     (*(volatile uint8_t const *)    0xFFFF0910)
#define I2C1MTX     (*(volatile uint8_t *)          0xFFFF0914)
#define I2C1CNT     (*(volatile uint8_t *)          0xFFFF0918)
#define I2C1ADR     (*(volatile uint8_t *)          0xFFFF091C)
#define I2C1BYTE    (*(volatile uint8_t *)          0xFFFF0924)
#define I2C1ALT     (*(volatile uint8_t *)          0xFFFF0928)
#define I2C1CFG     (*(volatile uint8_t *)          0xFFFF092C)
#define I2C1DIV     (*(volatile uint16_t *)         0xFFFF0930)
#define I2C1DIVL    (*(volatile uint8_t *)          0xFFFF0930)
#define I2C1DIVH    (*(volatile uint8_t *)          0xFFFF0931)
#define I2C1ID0     (*(volatile uint8_t *)          0xFFFF0938)
#define I2C1ID1     (*(volatile uint8_t *)          0xFFFF093C)
#define I2C1ID2     (*(volatile uint8_t *)          0xFFFF0940)
#define I2C1ID3     (*(volatile uint8_t *)          0xFFFF0944)
#define I2C1CCNT    (*(volatile uint8_t *)          0xFFFF0948)
#define I2C1FSTA    (*(volatile uint16_t const *)   0xFFFF094C)

// SPI
#define SPISTA      (*(volatile uint8_t const *)    0xFFFF0A00)
#define SPIRX       (*(volatile uint8_t const *)    0xFFFF0A04)
#define SPITX       (*(volatile uint8_t *)          0xFFFF0A08)
#define SPIDIV      (*(volatile uint8_t *)          0xFFFF0A0C)
#define SPICON      (*(volatile uint16_t *)         0xFFFF0A10)

// PLA
#define PLAELM0     (*(volatile uint16_t *)         0xFFFF0B00)
#define PLAELM1     (*(volatile uint16_t *)         0xFFFF0B04)
#define PLAELM2     (*(volatile uint16_t *)         0xFFFF0B08)
#define PLAELM3     (*(volatile uint16_t *)         0xFFFF0B0C)
#define PLAELM4     (*(volatile uint16_t *)         0xFFFF0B10)
#define PLAELM5     (*(volatile uint16_t *)         0xFFFF0B14)
#define PLAELM6     (*(volatile uint16_t *)         0xFFFF0B18)
#define PLAELM7     (*(volatile uint16_t *)         0xFFFF0B1C)
#define PLAELM8     (*(volatile uint16_t *)         0xFFFF0B20)
#define PLAELM9     (*(volatile uint16_t *)         0xFFFF0B24)
#define PLAELM10    (*(volatile uint16_t *)         0xFFFF0B28)
#define PLAELM11    (*(volatile uint16_t *)         0xFFFF0B2C)
#define PLAELM12    (*(volatile uint16_t *)         0xFFFF0B30)
#define PLAELM13    (*(volatile uint16_t *)         0xFFFF0B34)
#define PLAELM14    (*(volatile uint16_t *)         0xFFFF0B38)
#define PLAELM15    (*(volatile uint16_t *)         0xFFFF0B3C)
#define PLACLK      (*(volatile uint8_t *)          0xFFFF0B40)
#define PLAIRQ      (*(volatile uint32_t *)         0xFFFF0B44)
#define PLAADC      (*(volatile uint32_t *)         0xFFFF0B48)
#define PLADIN      (*(volatile uint32_t *)         0xFFFF0B4C)
#define PLADOUT     (*(volatile uint32_t const *)   0xFFFF0B50)
#define PLALCK      (*(volatile uint8_t *)          0xFFFF0B54)

// External memory interface
#define XMCFG       (*(volatile uint8_t *)          0xFFFFF000)
#define XM0CON      (*(volatile uint8_t *)          0xFFFFF010)
#define XM1CON      (*(volatile uint8_t *)          0xFFFFF014)
#define XM2CON      (*(volatile uint8_t *)          0xFFFFF018)
#define XM3CON      (*(volatile uint8_t *)          0xFFFFF01C)
#define XM0PAR      (*(volatile uint16_t *)         0xFFFFF020)
#define XM1PAR      (*(volatile uint16_t *)         0xFFFFF024)
#define XM2PAR      (*(volatile uint16_t *)         0xFFFFF028)
#define XM3PAR      (*(volatile uint16_t *)         0xFFFFF02C)

// GPIO ports
#define GP0CON      (*(volatile uint32_t *)         0xFFFFF400)
#define GP0DAT      (*(volatile uint32_t *)         0xFFFFF420)
#define GP0SET      (*(volatile uint32_t *)         0xFFFFF424)
#define GP0CLR      (*(volatile uint32_t *)         0xFFFFF428)
#define GP0PAR      (*(volatile uint32_t *)         0xFFFFF42C)

#define GP1CON      (*(volatile uint32_t *)         0xFFFFF404)
#define GP1DAT      (*(volatile uint32_t *)         0xFFFFF430)
#define GP1SET      (*(volatile uint32_t *)         0xFFFFF434)
#define GP1CLR      (*(volatile uint32_t *)         0xFFFFF438)
#define GP1PAR      (*(volatile uint32_t *)         0xFFFFF43C)

#define GP2CON      (*(volatile uint32_t *)         0xFFFFF408)
#define GP2DAT      (*(volatile uint32_t *)         0xFFFFF440)
#define GP2SET      (*(volatile uint32_t *)         0xFFFFF444)
#define GP2CLR      (*(volatile uint32_t *)         0xFFFFF448)

#define GP3CON      (*(volatile uint32_t *)         0xFFFFF40C)
#define GP3DAT      (*(volatile uint32_t *)         0xFFFFF450)
#define GP3SET      (*(volatile uint32_t *)         0xFFFFF454)
#define GP3CLR      (*(volatile uint32_t *)         0xFFFFF458)
#define GP3PAR      (*(volatile uint32_t *)         0xFFFFF45C)

#define GP4CON      (*(volatile uint32_t *)         0xFFFFF410)
#define GP4DAT      (*(volatile uint32_t *)         0xFFFFF460)
#define GP4SET      (*(volatile uint32_t *)         0xFFFFF464)
#define GP4CLR      (*(volatile uint32_t *)         0xFFFFF468)

// Flash/EE memory
#define FEESTA      (*(volatile uint8_t const *)    0xFFFFF800)
#define FEEMOD      (*(volatile uint16_t *)         0xFFFFF804)
#define FEECON      (*(volatile uint8_t *)          0xFFFFF808)
#define FEEDAT      (*(volatile uint16_t *)         0xFFFFF80C)
#define FEEADR      (*(volatile uint16_t *)         0xFFFFF810)
#define FEESIGN     (*(volatile uint32_t const *)   0xFFFFF818)
#define FEEPRO      (*(volatile uint32_t *)         0xFFFFF81C)
#define FEEHIDE     (*(volatile uint32_t *)         0xFFFFF820)

// PWM
#define PWMCON      (*(volatile uint16_t *)         0xFFFFFC00)
#define PWMSTA      (*(volatile uint16_t *)         0xFFFFFC04)
#define PWMDAT0     (*(volatile uint16_t *)         0xFFFFFC08)
#define PWMDAT1     (*(volatile uint16_t *)         0xFFFFFC0C)
#define PWMCFG      (*(volatile uint16_t *)         0xFFFFFC10)
#define PWMCH0      (*(volatile uint16_t *)         0xFFFFFC14)
#define PWMCH1      (*(volatile uint16_t *)         0xFFFFFC18)
#define PWMCH2      (*(volatile uint16_t *)         0xFFFFFC1C)
#define PWMEN       (*(volatile uint16_t *)         0xFFFFFC20)
#define PWMDAT2     (*(volatile uint16_t *)         0xFFFFFC24)

#endif  // __ASSEMBLER__
#endif  // ADUC702X_H__


