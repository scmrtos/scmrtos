#ifndef ADUC_BITS_H__
#define ADUC_BITS_H__

// PLLCON
#define OSEL                5
#define PLL_EXTERNAL_CLK    (0<<OSEL)
#define PLL_INTERNAL_CLK    (1<<OSEL)
#define MDCLK1              1
#define MDCLK0              0
#define CLK_EXT             ((1<<MDCLK1) | (1<<MDCLK0))
#define CLK_INT_PLL         ((0<<MDCLK1) | (1<<MDCLK0))

//POWCON
#define PC2                 6
#define PC1                 5
#define PC0                 4
#define MODE_ACTIVE         ((0<<PC2) | (0<<PC1) | (0<<PC0))
#define MODE_PAUSE          ((0<<PC2) | (0<<PC1) | (1<<PC0))
#define MODE_NAP            ((0<<PC2) | (1<<PC1) | (0<<PC0))
#define MODE_SLEEP          ((0<<PC2) | (1<<PC1) | (1<<PC0))
#define CD2                 2
#define CD1                 1
#define CD0                 0
#define CLK_DIV_1           ((0<<CD2) | (0<<CD1) | (0<<CD0))
#define CLK_DIV_2           ((0<<CD2) | (0<<CD1) | (1<<CD0))
#define CLK_DIV_4           ((0<<CD2) | (1<<CD1) | (0<<CD0))
#define CLK_DIV_8           ((0<<CD2) | (1<<CD1) | (1<<CD0))
#define CLK_DIV_16          ((1<<CD2) | (0<<CD1) | (0<<CD0))
#define CLK_DIV_32          ((1<<CD2) | (0<<CD1) | (1<<CD0))
#define CLK_DIV_64          ((1<<CD2) | (1<<CD1) | (0<<CD0))
#define CLK_DIV_128         ((1<<CD2) | (1<<CD1) | (1<<CD0))

//T0CON
#define T0EN                7
#define T0_ENABLED          (1<<T0EN)
#define T0_DISABLED         (0<<T0EN)
#define T0MODE              6
#define T0_PERIODIC         (1<<T0MODE)
#define T0_FREERUNING       (0<<T0MODE)
#define T0PS1               3
#define T0PS0               2
#define T0_DIV_1            ((0<<T0PS1) | (0<<T0PS0))
#define T0_DIV_16           ((0<<T0PS1) | (1<<T0PS0))
#define T0_DIV_256          ((1<<T0PS1) | (0<<T0PS0))

//T1CON

#define T1EVSEL             17
#define T1_EV_ENABLE        (1<<T1EVSEL)
#define T1_EV_DISABLE       (0<<T1EVSEL)
#define T1EVRANGE           12
#define T1_EVENT_TIMER0     (0x00<<T1EVRANGE)
#define T1_EVENT_TIMER1     (0x01<<T1EVRANGE)
#define T1_EVENT_TIMER2     (0x02<<T1EVRANGE)
#define T1_EVENT_TIMER3     (0x03<<T1EVRANGE)
#define T1_EVENT_FLASHCON   (0x04<<T1EVRANGE)
#define T1_EVENT_ADC        (0x05<<T1EVRANGE)
#define T1_EVENT_PLL_LOCK   (0x06<<T1EVRANGE)
#define T1_EVENT_SM_SLAVE   (0x07<<T1EVRANGE)
#define T1_EVENT_SM_MASTER0 (0x08<<T1EVRANGE)
#define T1_EVENT_SM_MASTER1 (0x09<<T1EVRANGE)
#define T1_EVENT_SPI_SLAVE  (0x0A<<T1EVRANGE)
#define T1_EVENT_SPI_MASTER (0x0B<<T1EVRANGE)
#define T1_EVENT_UART       (0x0C<<T1EVRANGE)
#define T1_EVENT_XIRQ0      (0x0D<<T1EVRANGE)
#define T1_EVENT_MONITOR    (0x0E<<T1EVRANGE)
#define T1_EVENT_PSM        (0x0F<<T1EVRANGE)
#define T1_EVENT_XIRQ1      (0x10<<T1EVRANGE)
#define T1_EVENT_PLA_IRQ0   (0x11<<T1EVRANGE)
#define T1_EVENT_PLA_IRQ1   (0x12<<T1EVRANGE)
#define T1_EVENT_SPM4_IO    (0x13<<T1EVRANGE)
#define T1_EVENT_SPM5_IO    (0x14<<T1EVRANGE)
#define T1_EVENT_PWM_TRIP   (0x15<<T1EVRANGE)
#define T1CLOCK             8
#define T1_HCLK             (0<<T1CLOCK)
#define T1_EXT32K_CLK       (1<<T1CLOCK)
#define T1_P10_CLK          (2<<T1CLOCK)
#define T1_P06_CLK          (3<<T1CLOCK)
#define T1UP                7
#define T1_UP               (1<<T1UP)
#define T1_DOWN             (0<<T1UP)
#define T1EN                7
#define T1_ENABLED          (1<<T1EN)
#define T1_DISABLED         (0<<T1EN)
#define T1MODE              6
#define T1_PERIODIC         (1<<T1MODE)
#define T1_FREERUNING       (0<<T1MODE)
#define T1FORMAT            5
#define T1_BINARY           (0<<T1FORMAT)
#define T1_RTC_24H          (2<<T1FORMAT)
#define T1_RTC_256H         (3<<T1FORMAT)
#define T1PS3               3
#define T1PS2               2
#define T1PS1               1
#define T1PS0               0
#define T1_DIV_1            ((0<<T1PS3) | (0<<T1PS2) | (0<<T1PS1) | (0<<T1PS0))
#define T1_DIV_16           ((0<<T1PS3) | (1<<T1PS2) | (0<<T1PS1) | (0<<T1PS0))
#define T1_DIV_256          ((1<<T1PS3) | (0<<T1PS2) | (0<<T1PS1) | (0<<T1PS0))
#define T1_DIV_32768        ((1<<T1PS3) | (1<<T1PS2) | (1<<T1PS1) | (1<<T1PS0))
#endif	//ADUC_BITS_H__
