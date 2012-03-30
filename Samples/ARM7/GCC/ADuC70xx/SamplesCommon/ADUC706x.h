//******************************************************************************
//*
//*		FULLNAME:  ADuC706x	SFR	description	file
//*
//*		PROCESSOR: ADuC7060, ADuC7061 (Analog Devices)
//*
//*		TOOLKIT:   C/C++
//*
//*		Version: 3.10
//*
//*		$Revision$
//*		$Date::				$
//*
//*		Copyright (c) 2010, Anton B. Gusev
//*
//*		Permission is hereby granted, free of charge, to any person
//*		obtaining  a copy of this software and associated documentation
//*		files (the "Software"),	to deal	in the Software	without	restriction,
//*		including without limitation the rights	to use,	copy, modify, merge,
//*		publish, distribute, sublicense, and/or	sell copies	of the Software,
//*		and	to permit persons to whom the Software is furnished	to do so,
//*		subject	to the following conditions:
//*
//*		The	above copyright	notice and this	permission notice shall	be included
//*		in all copies or substantial portions of the Software.
//*
//*		THE	SOFTWARE IS	PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//*		EXPRESS	 OR	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//*		MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//*		IN NO EVENT	SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//*		CLAIM, DAMAGES OR OTHER	LIABILITY, WHETHER IN AN ACTION	OF CONTRACT,
//*		TORT OR	OTHERWISE, ARISING FROM, OUT OF	OR IN CONNECTION WITH
//*		THE	SOFTWARE OR	THE	USE	OR OTHER DEALINGS IN THE SOFTWARE.
//*
//******************************************************************************
#ifndef	ADUC706X_H__
#define	ADUC706X_H__ 

#ifndef	__ASSEMBLER__
#include <stdint.h>

// GPIO	ports
#define	GP0CON0		(*(volatile	uint32_t *)			0xFFFF0D00)
#define	GP0KEY1		(*(volatile	uint32_t *)			0xFFFF0464)
	#define	GP0KEY1_KEY	(0x07)
#define	GP0CON1		(*(volatile	uint32_t *)			0xFFFF0468)
#define	GP0KEY2		(*(volatile	uint32_t *)			0xFFFF046C)
	#define	GP0KEY2_KEY	(0x13)
#define	GP0DAT		(*(volatile	uint32_t *)			0xFFFF0D20)
#define	GP0SET		(*(volatile	uint32_t *)			0xFFFF0D24)
#define	GP0CLR		(*(volatile	uint32_t *)			0xFFFF0D28)
#define	GP0PAR		(*(volatile	uint32_t *)			0xFFFF0D2C)

#define	GP1CON		(*(volatile	uint32_t *)			0xFFFF0D04)
#define	GP1DAT		(*(volatile	uint32_t *)			0xFFFF0D30)
#define	GP1SET		(*(volatile	uint32_t *)			0xFFFF0D34)
#define	GP1CLR		(*(volatile	uint32_t *)			0xFFFF0D38)
#define	GP1PAR		(*(volatile	uint32_t *)			0xFFFF0D3C)

#define	GP2CON		(*(volatile	uint32_t *)			0xFFFF0D08)
#define	GP2DAT		(*(volatile	uint32_t *)			0xFFFF0D40)
#define	GP2SET		(*(volatile	uint32_t *)			0xFFFF0D44)
#define	GP2CLR		(*(volatile	uint32_t *)			0xFFFF0D48)
#define	GP2PAR		(*(volatile	uint32_t *)			0xFFFF0D4C)


// Interrupt controller
enum 
{
	ALL_INT_FIQ			= (1UL << 0),
	SWI_BIT				= (1UL << 1),

	TIMER0_BIT			= (1UL << 3),
	TIMER1_BIT			= (1UL << 4),
	TIMER2_BIT			= (1UL << 5),
	TIMER3_BIT			= (1UL << 6),

	ADC_BIT				= (1UL << 10),
	UART_BIT			= (1UL << 11),
	SPI_BIT				= (1UL << 12),
	EXT_IRQ0_BIT		= (1UL << 13),
	EXT_IRQ1_BIT		= (1UL << 14),
	I2C_MASTER_BIT		= (1UL << 15),
	I2C_SLAVE_BIT		= (1UL << 16),
	PWM_BIT				= (1UL << 17),
	EXT_IRQ2_BIT		= (1UL << 18),
	EXT_IRQ3_BIT		= (1UL << 19)
};

#define	IRQSTA		(*(volatile	uint32_t const *)	0xFFFF0000)
#define	IRQSIG		(*(volatile	uint32_t const *)	0xFFFF0004)
#define	IRQEN		(*(volatile	uint32_t *)			0xFFFF0008)
#define	IRQCLR		(*(volatile	uint32_t *)			0xFFFF000C)
#define	SWICFG		(*(volatile	uint32_t *)			0xFFFF0010)
#define	IRQBASE		(*(volatile	uint32_t *)			0xFFFF0014)
#define	IRQVEC		(*(volatile	uint32_t const *)	0xFFFF001C)
#define	IRQP0		(*(volatile	uint32_t *)			0xFFFF0020)
#define	IRQP1		(*(volatile	uint32_t *)			0xFFFF0024)
#define	IRQP2		(*(volatile	uint32_t *)			0xFFFF0028)
#define	IRQCONN		(*(volatile	uint32_t *)			0xFFFF0030)
#define	IRQCONE		(*(volatile	uint32_t *)			0xFFFF0034)
#define	IRQCLRE		(*(volatile	uint32_t *)			0xFFFF0038)
#define	IRQSTAN		(*(volatile	uint32_t *)			0xFFFF003C)
#define	FIQSTA		(*(volatile	uint32_t const *)	0xFFFF0100)
#define	FIQSIG		(*(volatile	uint32_t const *)	0xFFFF0104)
#define	FIQEN		(*(volatile	uint32_t *)			0xFFFF0108)
#define	FIQCLR		(*(volatile	uint32_t *)			0xFFFF010C)
#define	FIQVEC		(*(volatile	uint32_t const *)	0xFFFF011C)
#define	FIQSTAN		(*(volatile	uint32_t *)			0xFFFF013C)

// System control
#define	REMAP		(*(volatile	uint8_t	*)			0xFFFF0220)
enum
{
	REMAP_FLASH			= (0UL << 0),
	REMAP_SRAM			= (1UL << 0)
};

#define	RSTSTA		(*(volatile	uint8_t	*)			0xFFFF0230)
enum
{
	RESET_SRC_POR			= (1UL << 0),
	RESET_SRC_WDT			= (1UL << 1),
	RESET_SRC_SOFT			= (1UL << 2),
	RESET_SRC_EXTERNAL		= (1UL << 3)
};

#define	RSTCLR		(*(volatile	uint8_t	*)			0xFFFF0234)

// Timer 0
#define	T0LD		(*(volatile	uint32_t *)			0xFFFF0320)
#define	T0VAL		(*(volatile	uint32_t const *)	0xFFFF0324)
#define	T0CON		(*(volatile	uint32_t *)			0xFFFF0328)
enum
{
	T0_DIV_1				= (0UL << 0),
	T0_DIV_16				= (4UL << 0),
	T0_DIV_256				= (8UL << 0),
	T0_DIV_32768			= (0xFUL <<	0),
	
	T0_BINARY				= (0UL << 4),
	T0_24_HOURS				= (2UL << 4),
	T0_255_HOURS			= (3UL << 4),

	T0_FREE_RUNNING			= (0UL << 6),
	T0_PERIODIC				= (1UL << 6),

	T0_DISABLED				= (0UL << 7),
	T0_ENABLED				= (1UL << 7),

	T0_DOWN					= (0UL << 8),
	T0_UP					= (1UL << 8),

	T0_32KHZ				= (0UL << 9),
	T0_10MHZ_CD				= (1UL << 9),
	T0_10MHZ				= (2UL << 9),
	T0_P1_0_CLK				= (3UL << 9),

	T0_EVENT_T0				= (1UL << 12),
	T0_EVENT_T1				= (2UL << 12),
	T0_EVENT_T2				= (3UL << 12),
	T0_EVENT_T3				= (4UL << 12),
	T0_EVENT_ADC			= (8UL << 12),
	T0_EVENT_UART			= (9UL << 12),
	T0_EVENT_SPI			= (10UL	<< 12),
	T0_EVENT_EXT_IRQ0		= (11UL	<< 12),
	T0_EVENT_EXT_IRQ1		= (12UL	<< 12),
	T0_EVENT_I2C_MASTER		= (13UL	<< 12),
	T0_EVENT_I2C_SLAVE		= (14UL	<< 12),
	T0_EVENT_PWM			= (15UL	<< 12),
	T0_EVENT_EXT_IRQ2		= (16UL	<< 12),
	T0_EVENT_EXT_IRQ3		= (17UL	<< 12),

	T0_EVENT_DISABLED		= (0UL <<  17),
	T0_EVENT_ENABLED		= (1UL <<  17),

	T0_INT_SRC_TIMER0		= (0UL <<  18),
	T0_INT_SRC_POSTSCALER	= (1UL <<  18),

	T0_POSTSCALER_FLAG		= (1UL <<  19),

	T0_POSTSCALER_DISABLED	= (0UL <<  23),
	T0_POSTSCALER_ENABLED	= (1UL <<  23)
};

#define	T0CLRI		(*(volatile	uint8_t	*)			0xFFFF032C)
#define	T0CAP		(*(volatile	uint32_t const *)	0xFFFF0330)

// Timer 1 = Wake-up timer
#define	T1LD		(*(volatile	uint32_t *)			0xFFFF0340)
#define	T1VAL		(*(volatile	uint32_t const *)	0xFFFF0344)
#define	T1CON		(*(volatile	uint16_t *)			0xFFFF0348)
enum
{
	T1_DIV_1				= (0UL << 0),
	T1_DIV_16				= (4UL << 0),
	T1_DIV_256				= (8UL << 0),
	T1_DIV_32768			= (0xFUL <<	0),
	
	T1_BINARY				= (0UL << 4),
	T1_24_HOURS				= (2UL << 4),
	T1_255_HOURS			= (3UL << 4),

	T1_FREE_RUNNING			= (0UL << 6),
	T1_PERIODIC				= (1UL << 6),

	T1_DISABLED				= (0UL << 7),
	T1_ENABLED				= (1UL << 7),

	T1_DOWN					= (0UL << 8),
	T1_UP					= (1UL << 8),

	T1_32KHZ				= (0UL << 9),
	T1_10MHZ_CD				= (1UL << 9),
	T1_XTALI				= (2UL << 9),
	T1_10MHZ				= (3UL << 9)
};

#define	T1CLRI		(*(volatile	uint8_t	*)			0xFFFF034C)

// Timer 2 = Watchdog timer
#define	T2LD		(*(volatile	uint16_t *)			0xFFFF0360)
#define	T2VAL		(*(volatile	uint16_t const *)	0xFFFF0364)
#define	T2CON		(*(volatile	uint16_t *)			0xFFFF0368)
enum
{
	T2_RUN_IN_POWERDOWN		= (0UL << 0),
	T2_STOP_IN_POWERDOWN	= (1UL << 0),
	
	T2_WDT_ACTION_RESET		= (0UL << 1),
	T2_WDT_ACTION_IRQ		= (1UL << 1),

	T2_32KHZ_DIV_1			= (0UL << 2),
	T2_32KHZ_DIV_16			= (1UL << 2),
	T2_32KHZ_DIV_256		= (2UL << 2),

	T2_TIMER_MODE			= (0UL << 5),
	T2_WDT_MODE				= (1UL << 5),

	T2_FREE_RUNNING			= (0UL << 6),
	T2_PERIODIC				= (1UL << 6),

	T2_DISABLED				= (0UL << 7),
	T2_ENABLED				= (1UL << 7),

	T2_DOWN					= (0UL << 8),
	T2_UP					= (1UL << 8)
};
#define	T2CLRI		(*(volatile	uint8_t	*)			0xFFFF036C)

// Timer 3
#define	T3LD		(*(volatile	uint16_t *)			0xFFFF0380)
#define	T3VAL		(*(volatile	uint16_t const *)	0xFFFF0384)
#define	T3CON		(*(volatile	uint32_t *)			0xFFFF0388)
enum
{
	T3_DIV_1				= (0UL << 0),
	T3_DIV_16				= (4UL << 0),
	T3_DIV_256				= (8UL << 0),
	T3_DIV_32768			= (0xFUL <<	0),
	
	T3_FREE_RUNNING			= (0UL << 6),
	T3_PERIODIC				= (1UL << 6),

	T3_DISABLED				= (0UL << 7),
	T3_ENABLED				= (1UL << 7),

	T3_DOWN					= (0UL << 8),
	T3_UP					= (1UL << 8),

	T3_32KHZ				= (0UL << 9),
	T3_10MHZ_CD				= (1UL << 9),
	T3_10MHZ				= (2UL << 9),

	T3_EVENT_T0				= (1UL << 12),
	T3_EVENT_T1				= (2UL << 12),
	T3_EVENT_T2				= (3UL << 12),
	T3_EVENT_T3				= (4UL << 12),
	T3_EVENT_ADC			= (8UL << 12),
	T3_EVENT_UART			= (9UL << 12),
	T3_EVENT_SPI			= (10UL	<< 12),
	T3_EVENT_EXT_IRQ0		= (11UL	<< 12),
	T3_EVENT_EXT_IRQ1		= (12UL	<< 12),
	T3_EVENT_I2C_MASTER		= (13UL	<< 12),
	T3_EVENT_I2C_SLAVE		= (14UL	<< 12),
	T3_EVENT_PWM			= (15UL	<< 12),
	T3_EVENT_EXT_IRQ2		= (16UL	<< 12),
	T3_EVENT_EXT_IRQ3		= (17UL	<< 12),

	T3_EVENT_DISABLED		= (0UL <<  17),
	T3_EVENT_ENABLED		= (1UL <<  17)
};
#define	T3CLRI		(*(volatile	uint8_t	*)			0xFFFF038C)
#define	T3CAP		(*(volatile	uint16_t const *)	0xFFFF0390)

// PLL
#define	PLLKEY1		(*(volatile	uint16_t *)			0xFFFF0410)
	#define PLLKEY1_KEY		(0xAA)
#define	PLLCON		(*(volatile	uint8_t	*)			0xFFFF0414)
enum
{
	PLL_CLK_INT_32KHZ		= (0UL << 0),
	PLL_CLK_EXT_32KHZ		= (2UL << 0),
	PLL_CLK_EXT_P20			= (1UL << 2)
};
#define	PLLKEY2		(*(volatile	uint16_t *)			0xFFFF0418)
	#define PLLKEY2_KEY		(0x55)

// Power control
#define	POWKEY1		(*(volatile	uint16_t *)			0xFFFF0404)
	#define	POWKEY1_KEY		(1)
#define	POWCON0		(*(volatile	uint8_t	*)			0xFFFF0408)
enum
{
	CLK_10240_KHZ		= (0UL << 0),
	CLK_51200_KHZ		= (1UL << 0),
	CLK_2560_KHZ		= (2UL << 0),
	CLK_1280_KHZ		= (3UL << 0),
	CLK_640_KHZ			= (4UL << 0),
	CLK_320_KHZ			= (5UL << 0),
	CLK_160_KHZ			= (6UL << 0),
	CLK_80_KHZ			= (7UL << 0),

	CORE_POWER_ON		= (1UL << 3),
	PERIPH_POWER_ON		= (1UL << 4),
	PLL_POWER_ON		= (1UL << 5),
	XTAL_POWER_ON		= (1UL << 6)
};
#define	POWKEY2		(*(volatile	uint16_t *)			0xFFFF040C)
	#define	POWKEY2_KEY		(0xF4)

#define	POWKEY3		(*(volatile	uint16_t *)			0xFFFF0434)
	#define	POWKEY3_KEY		(0x76)
#define	POWCON1		(*(volatile	uint16_t	*)		0xFFFF0438)
enum
{
	I2C_SPI_POWER_ON	= (1UL << 2),
	UART_POWER_ON		= (1UL << 5),
	PWM_POWER_ON		= (1UL << 8)
};
#define	POWKEY4		(*(volatile	uint16_t *)			0xFFFF043C)
	#define	POWKEY4_KEY		(0xB1)

// UART
#define	COMTX		(*(volatile	uint8_t	*)			0xFFFF0700)
#define	COMRX		(*(volatile	uint8_t	const *)	0xFFFF0700)
#define	COMDIV0		(*(volatile	uint8_t	*)			0xFFFF0700)
#define	COMIEN0		(*(volatile	uint8_t	*)			0xFFFF0704)
enum
{
	COMIEN0_RX_BUF_FULL		= (1 << 0),
	COMIEN0_TX_BUF_EMPTY	= (1 << 1),
	COMIEN0_RX_STATUS		= (1 << 2),
	COMIEN0_MODEM_STATUS	= (1 << 3)
};
#define	COMDIV1		(*(volatile	uint8_t	*)			0xFFFF0704)
#define	COMIID0		(*(volatile	uint8_t	const *)	0xFFFF0708)
enum
{
	COMIID_NO_INTERRUPT		= (1 << 0),
	COMIID_MODEM_STATUS		= (0 << 1),
	COMIID_TX_BUF_EMPTY		= (1 << 1),
	COMIID_RX_BUF_FULL		= (2 << 1),
	COMIID_RX_STATUS		= (3 << 1)
};
#define	COMCON0		(*(volatile	uint8_t	*)			0xFFFF070C)
enum
{
	COMCON0_DATABITS_5			= (0 << 0),
	COMCON0_DATABITS_6			= (1 << 0),
	COMCON0_DATABITS_7			= (2 << 0),
	COMCON0_DATABITS_8			= (3 << 0),

	COMCON0_STOPBITS_1			= (0 << 2),
	COMCON0_STOPBITS_1_5		= (1 << 2),

	COMCON0_PARITY_NONE			= (0 << 3),
	COMCON0_PARITY_ENABLE		= (1 << 3),

	COMCON0_PARITY_ODD			= (0 << 4),
	COMCON0_PARITY_EVEN			= (1 << 4),

	COMCON0_PARITY_STICK		= (1 << 5),

	COMCON0_BREAK_ENABLE		= (1 << 6),
	COMCON0_ACCESS_DL			= (1 << 7)
};
#define	COMCON1		(*(volatile	uint8_t	*)			0xFFFF0710)
#define	COMSTA0		(*(volatile	uint8_t	const *)	0xFFFF0714)
enum
{
	DATA_READY			= (1 << 0),
	OVERRUN_ERR			= (1 << 1),
	PARITY_ERR			= (1 << 2),
	FRAMING_ERR			= (1 << 3),
	BREAK_RECEIVED		= (1 << 4),
	TX_BUF_EMPTY		= (1 << 5),
	TX_DONE				= (1 << 6)
};
#define	COMSTA1		(*(volatile	uint8_t	const *)	0xFFFF0718)
#define	COMDIV2		(*(volatile	uint16_t *)			0xFFFF072C)

// ADC
#define	ADCSTA		(*(volatile	uint16_t const *)	0xFFFF0500)
enum
{
	ADC0RDY				= (1 << 0),
	ADC1RDY				= (1 << 1),
	ADC0OVR				= (1 << 3),
	ADC0THEX			= (1 << 4),
	ADC0ATHEX			= (1 << 6),
	ADC0CERR			= (1 << 12),
	ADC1CERR			= (1 << 13),
	ADCCALSTA			= (1 << 15)
};
#define	ADCMSKI		(*(volatile	uint16_t *)			0xFFFF0504)
enum
{
	ADC0RDY_INTEN		= (1 << 0),
	ADC1RDY_INTEN		= (1 << 1),
	ADC0OVR_INTEN		= (1 << 3),
	ADC0THEX_INTEN		= (1 << 4),
	ADC0ATHEX_INTEN		= (1 << 6)
};
#define	ADCMDE		(*(volatile	uint8_t	*)			0xFFFF0508)
enum
{
	ADCMDE_ADCMD			= (7 << 0),
	ADCMDE_POWERDOWN		= (0 << 0),
	ADCMDE_CONTINUOUS		= (1 << 0),
	ADCMDE_SINGLE			= (2 << 0),
	ADCMDE_IDLE				= (3 << 0),
	ADCMDE_OFFSET_CAL		= (4 << 0),
	ADCMDE_GAIN_CAL			= (5 << 0),
	ADCMDE_ZERO_CAL			= (6 << 0),
	ADCMDE_FULL_CAL			= (7 << 0),

	ADCMDE_LPMCFG			= (3 << 3),
	ADCMDE_NORMAL_POWER		= (0 << 3),
	ADCMDE_LOW_POWER		= (1 << 3),
	ADCMDE_NORMAL_POWER2	= (2 << 3),
	ADCMDE_LOW_POWER_PLUS	= (3 << 3),

	ADCLPMEN				= (1 << 4),

	ADCCLKSEL_131KHZ		= (0 << 7),
	ADCCLKSEL_512KHZ		= (1 << 7)

};
#define	ADC0CON		(*(volatile	uint16_t *)			0xFFFF050C)
enum
{
	ADC0CON_GAIN				= (0xF << 0),
	ADC0CON_GAIN_1				= (0 << 0),
	ADC0CON_GAIN_2				= (1 << 0),
	ADC0CON_GAIN_4				= (2 << 0),
	ADC0CON_GAIN_8				= (3 << 0),
	ADC0CON_GAIN_16				= (4 << 0),
	ADC0CON_GAIN_32				= (5 << 0),
	ADC0CON_GAIN_64				= (6 << 0),
	ADC0CON_GAIN_128			= (7 << 0),
	ADC0CON_GAIN_256			= (8 << 0),
	ADC0CON_GAIN_512			= (9 << 0),

	ADC0CON_REF					= (3 << 4),
	ADC0CON_REF_INT				= (0 << 4),
	ADC0CON_REF_EXT				= (1 << 4),
	ADC0CON_REF_EXT_AUX			= (2 << 4),
	ADC0CON_REF_AVDD_DIV_2		= (3 << 4),

	ADC0CON_CHANNEL				= (0xF << 6),
	ADC0CON_CHANNEL_DIFF_0_1	= (0 << 6),
	ADC0CON_CHANNEL_0_5			= (1 << 6),
	ADC0CON_CHANNEL_1_5			= (2 << 6),
	ADC0CON_CHANNEL_VREF		= (3 << 6),
	ADC0CON_CHANNEL_DIFF_2_3	= (5 << 6),
	ADC0CON_CHANNEL_2_5			= (6 << 6),
	ADC0CON_CHANNEL_3_5			= (7 << 6),
	ADC0CON_CHANNEL_SHORT_0		= (8 << 6),
	ADC0CON_CHANNEL_SHORT_1		= (9 << 6),

	ADC0CON_CODE_2_COMPLEMENT	= (0 << 10),
	ADC0CON_CODE_UNIPOLAR		= (1 << 10),

	ADC0CON_AMP_CM_ZERO			= (0 << 11),
	ADC0CON_AMP_CM_AVDD_DIV_2	= (1 << 11),

	ADC0CON_EXTREF_MORE_1_35V	= (1 << 12),

	ADC0CON_DIAG				= (3 << 13),
	ADC0CON_DIAG_OFF			= (0 << 13),
	ADC0CON_DIAG_POSITIVE		= (1 << 13),
	ADC0CON_DIAG_NEGATIVE		= (2 << 13),
	ADC0CON_DIAG_BOTH			= (3 << 13),

	ADC0CON_ADC0EN				= (1 << 15)
};
#define	ADC1CON		(*(volatile	uint16_t *)			0xFFFF0510)
enum
{
	ADC1CON_GAIN				= (3 << 0),
	ADC1CON_GAIN_1				= (0 << 0),
	ADC1CON_GAIN_2				= (1 << 0),
	ADC1CON_GAIN_4				= (2 << 0),
	ADC1CON_GAIN_8				= (3 << 0),

	ADC1CON_BUFF				= (3 << 2),
	ADC1CON_BUFF_ON				= (0 << 2),
	ADC1CON_BUFF_POSITIVE		= (1 << 2),
	ADC1CON_BUFF_NEGATIVE		= (2 << 2),
	ADC1CON_BUFF_OFF			= (3 << 2),

	ADC1CON_REF					= (7 << 4),
	ADC1CON_REF_INT				= (0 << 4),
	ADC1CON_REF_EXT				= (1 << 4),
	ADC1CON_REF_EXT_AUX			= (2 << 4),
	ADC1CON_REF_AVDD_DIV_2		= (3 << 4),
	ADC1CON_REF_AVDD_ADC3		= (4 << 4),

	ADC1CON_CHANNEL				= (0xF << 7),
	ADC1CON_CHANNEL_2_3_DIFF	= (0 << 7),
	ADC1CON_CHANNEL_4_5_DIFF	= (1 << 7),
	ADC1CON_CHANNEL_6_7_DIFF	= (2 << 7),
	ADC1CON_CHANNEL_8_9_DIFF	= (3 << 7),
	ADC1CON_CHANNEL_2_5			= (4 << 7),
	ADC1CON_CHANNEL_3_5			= (5 << 7),
	ADC1CON_CHANNEL_4_5			= (6 << 7),
	ADC1CON_CHANNEL_6_5			= (7 << 7),
	ADC1CON_CHANNEL_7_5			= (8 << 7),
	ADC1CON_CHANNEL_8_5			= (9 << 7),
	ADC1CON_CHANNEL_9_5			= (10 << 7),
	ADC1CON_CHANNEL_TEMP		= (11 << 7),
	ADC1CON_CHANNEL_VREF		= (12 << 7),
	ADC1CON_CHANNEL_DAC			= (13 << 7),
	ADC1CON_CHANNEL_ADC3		= (15 << 7),

	ADC1CON_CODE_2_COMPLEMENT	= (0 << 11),
	ADC1CON_CODE_UNIPOLAR		= (1 << 11),

	ADC1CON_EXTREF_MORE_1_35V	= (1 << 12),

	ADC1CON_DIAG				= (3 << 13),
	ADC1CON_DIAG_OFF			= (0 << 13),
	ADC1CON_DIAG_POSITIVE		= (1 << 13),
	ADC1CON_DIAG_NEGATIVE		= (2 << 13),
	ADC1CON_DIAG_BOTH			= (3 << 13),

	ADC1CON_ADC0EN				= (1 << 15)
};
#define	ADCFLT		(*(volatile	uint16_t *)			0xFFFF0514)
enum
{
	ADCFLT_FREQ					= (0x7F << 0),
	ADCFLT_FREQ_1000HZ			= (7 << 0),
	ADCFLT_FREQ_500HZ			= (15 << 0),
	ADCFLT_FREQ_200HZ			= (39 << 0),
	ADCFLT_FREQ_100HZ			= (79 << 0),
	ADCFLT_FREQ_60HZ			= (126 << 0),
	ADCFLT_FREQ_50HZ			= (127 << 0),

	ADCFLT_NOTCH2				= (1 << 7),

	ADCFLT_AVG_FACTOR			= (0x3F << 8),

	ADCFLT_RUNNING_AVERAGE		= (1 << 14),
	ADCFLT_CHOP_ENABLE			= (1 << 15)
};
#define	ADCCFG		(*(volatile	uint8_t	*)			0xFFFF0518)
enum
{
	ADCCFG_ADCRCEN				= (1 << 0),
	ADCCFG_GNDSW_RES_EN			= (1 << 1),
	ADCCFG_ADC0_OREN			= (1 << 2),

	ADCCFG_ADC0CMPEN_0			= (1 << 3),
	ADCCFG_ADC0CMPEN_1			= (1 << 4),

	ADCCFG_ADC0ACCEN_0			= (1 << 5),
	ADCCFG_ADC0ACCEN_1			= (1 << 6),

	ADCCFG_GNDSW_EN				= (1 << 7)
};
#define	ADC0DAT		(*(volatile	uint32_t const *)	0xFFFF051C)
#define	ADC1DAT		(*(volatile	uint32_t const *)	0xFFFF0520)
#define	ADC0OF		(*(volatile	uint16_t *)			0xFFFF0524)
#define	ADC1OF		(*(volatile	uint16_t *)			0xFFFF0528)
#define	ADC0GN		(*(volatile	uint16_t *)			0xFFFF052C)
#define	ADC1GN		(*(volatile	uint16_t *)			0xFFFF0530)
#define	ADC0RCR		(*(volatile	uint16_t *)			0xFFFF0534)
#define	ADC0RCV		(*(volatile	uint16_t const *)	0xFFFF0538)
#define	ADC0TH		(*(volatile	uint16_t *)			0xFFFF053C)
#define	ADC0THC		(*(volatile	uint16_t *)			0xFFFF0540)
#define	ADC0THV		(*(volatile	uint16_t const *)	0xFFFF0544)
#define	ADC0ACC		(*(volatile	uint32_t const *)	0xFFFF0548)
#define	ADC0ATH		(*(volatile	uint32_t *)			0xFFFF054C)
#define	IEXCON		(*(volatile	uint8_t *)			0xFFFF0570)

// DAC
#define	DAC0CON		(*(volatile uint16_t *)			0xFFFF0600)
enum
{
	DAC0_RANGE_INTREF			= (0 << 0),
	DAC0_RANGE_EXTREF			= (1 << 0),
	DAC0_RANGE_EXTREF_ALT		= (2 << 0),
	DAC0_RANGE_AVDD				= (3 << 0),

	DAC0_RATE_UCLK_DIV_32		= (0 << 2),
	DAC0_RATE_UCLK_DIV_16		= (1 << 2),

	DAC0_MODE_12_BIT			= (0 << 3),
	DAC0_MODE_16_BIT			= (1 << 3),

	DAC0_CLEAR					= (0 << 4),
	DAC0_NORMAL_OPERATION		= (1 << 4),

	DAC0_CLOCK_HCLK				= (0 << 5),
	DAC0_CLOCK_TIMER1			= (1 << 5),

	DAC0_BUFFERED				= (0 << 6),
	DAC0_UNBUFFERED				= (1 << 6),

	DAC0_OPAMP_MODE				= (1 << 7),

	DAC0_BUF_LOW_POWER			= (1 << 8),

	DAC0_POWERDOWN				= (1 << 9)
};
#define	DAC0DAT		(*(volatile uint32_t *)			0xFFFF0604)

// Flash/EE	memory
#define	FEESTA		(*(volatile	uint16_t const *)	0xFFFF0E00)
enum
{
	FEESTA_COMMAND_DONE		= (1 << 0),
	FEESTA_COMMAND_FAIL		= (1 << 1),
	FEESTA_BUSY				= (1 << 2),
	FEESTA_IF				= (1 << 3)
};
#define	FEEMOD		(*(volatile	uint16_t *)			0xFFFF0E04)
#define	FEECON		(*(volatile	uint8_t	*)			0xFFFF0E08)
#define	FEEDAT		(*(volatile	uint16_t *)			0xFFFF0E0C)
#define	FEEADR		(*(volatile	uint32_t *)			0xFFFF0E10)
#define	FEESIGN		(*(volatile	uint32_t const *)	0xFFFF0E18)
#define	FEEPRO		(*(volatile	uint32_t *)			0xFFFF0E1C)
#define	FEEHIDE		(*(volatile	uint32_t *)			0xFFFF0E20)

// I2C
#define	I2CMCON		(*(volatile uint32_t *)			0xFFFF0900)
#define	I2CMSTA		(*(volatile uint32_t *)			0xFFFF0904)
#define	I2CMRX		(*(volatile uint32_t *)			0xFFFF0908)
#define	I2CMTX		(*(volatile uint32_t *)			0xFFFF090C)
#define	I2CMCNT0	(*(volatile uint32_t *)			0xFFFF0910)
#define	I2CMCNT1	(*(volatile uint32_t *)			0xFFFF0914)
#define	I2CADR0		(*(volatile uint32_t *)			0xFFFF0918)
#define	I2CADR1		(*(volatile uint32_t *)			0xFFFF091C)
#define	I2CREP		(*(volatile uint32_t *)			0xFFFF0920)
#define	I2CDIV		(*(volatile uint32_t *)			0xFFFF0924)
#define	I2CSCON		(*(volatile uint32_t *)			0xFFFF0928)
#define	I2CSSTA		(*(volatile uint32_t *)			0xFFFF092C)
#define	I2CSRX		(*(volatile uint32_t *)			0xFFFF0930)
#define	I2CSTX		(*(volatile uint32_t *)			0xFFFF0934)
#define	I2CALT		(*(volatile uint32_t *)			0xFFFF0938)
#define	I2CID0		(*(volatile uint32_t *)			0xFFFF093C)
#define	I2CID1		(*(volatile uint32_t *)			0xFFFF0940)
#define	I2CID2		(*(volatile uint32_t *)			0xFFFF0944)
#define	I2CID3		(*(volatile uint32_t *)			0xFFFF0948)
#define	I2CFSTA		(*(volatile uint32_t *)			0xFFFF094C)
#define	I2CRCON		(*(volatile uint32_t *)			0xFFFF0950)

// SPI
#define	SPISTA		(*(volatile uint32_t *)			0xFFFF0A00)
#define	SPIRX		(*(volatile uint32_t *)			0xFFFF0A04)
#define	SPITX		(*(volatile uint32_t *)			0xFFFF0A08)
#define	SPIDIV		(*(volatile uint32_t *)			0xFFFF0A0C)
#define	SPICON		(*(volatile uint32_t *)			0xFFFF0A10)

// PWM
#define	PWMBASE		(*(volatile uint32_t *)			0xFFFF0F80)
#define	PWMCON		(*(volatile uint32_t *)			0xFFFF0F80)
#define	PWM0COM0	(*(volatile uint32_t *)			0xFFFF0F84)
#define	PWM0COM1	(*(volatile uint32_t *)			0xFFFF0F88)
#define	PWM0COM2	(*(volatile uint32_t *)			0xFFFF0F8C)
#define	PWM0LEN		(*(volatile uint32_t *)			0xFFFF0F90)
#define	PWM1COM0	(*(volatile uint32_t *)			0xFFFF0F94)
#define	PWM1COM1	(*(volatile uint32_t *)			0xFFFF0F98)
#define	PWM1COM2	(*(volatile uint32_t *)			0xFFFF0F9C)
#define	PWM1LEN		(*(volatile uint32_t *)			0xFFFF0FA0)
#define	PWM2COM0	(*(volatile uint32_t *)			0xFFFF0FA4)
#define	PWM2COM1	(*(volatile uint32_t *)			0xFFFF0FA8)
#define	PWM2COM2	(*(volatile uint32_t *)			0xFFFF0FAC)
#define	PWM2LEN		(*(volatile uint32_t *)			0xFFFF0FB0)
#define	PWMCLRI		(*(volatile uint32_t *)			0xFFFF0FB8)

#endif	// __ASSEMBLER__
#endif	// ADUC702X_H__
