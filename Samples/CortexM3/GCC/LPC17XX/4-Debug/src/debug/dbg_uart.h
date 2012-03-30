/**
*  @file dbg_uart.h
*
*  Created on: 18.01.2011
*  Copyright (c) 2011 by Anton Gusev aka AHTOXA
*
*  Changes for LPC17xx:
*  Copyright (c) 2012 by Oleksandr Redchuk aka ReAl
*
**/

#ifndef DBG_UART_H_INCLUDED
#define DBG_UART_H_INCLUDED
#include <scmRTOS.h>

#include "lpc17xx_uart.h"
#include "lpc17xx_clkpwr.h"

#include "ftoa.h"

/**
*  @brief UART template class.
*  @param uart_num: select which UART peripheral to use.
*  @param baud: select UART speed.
*/


typedef enum {
	UART_0,
	// UART_1, // TODO:
	UART_2, UART_3
} uart_num_t;


template<
	uart_num_t uart_num = UART_0,
	uint32_t baud = 115200
	>
class dbg_uart_t;

template<uart_num_t uart_num, uint32_t baud>
class dbg_uart_t
{
private:
/* TODO: TXD/RXD pins as template parameters
	typename pins_t::PinTX TX;
	typename pins_t::PinRX RX;
*/
	static const int pconp_mask = uart_num == UART_0 ? CLKPWR_PCONP_PCUART0 :
	                    //   uart_num == UART_1 ? CLKPWR_PCONP_PCUART1 :
	                       uart_num == UART_2 ? CLKPWR_PCONP_PCUART2 :
	                                            CLKPWR_PCONP_PCUART3 ;

	static const int clksel_shift = uart_num == UART_0 ? CLKPWR_PCLKSEL_UART0 :
	                    //     uart_num == UART_1 ? CLKPWR_PCLKSEL_UART1 :
	                         uart_num == UART_2 ? CLKPWR_PCLKSEL_UART2 :
	                                              CLKPWR_PCLKSEL_UART3 ;

	static const int UARTx_IRQn = uart_num == UART_0 ? UART0_IRQn :
	                    //     uart_num == UART_1 ? UART1_IRQn :
	                         uart_num == UART_2 ? UART2_IRQn :
	                                              UART3_IRQn ;

	// TODO: parameter and/or method argument for IRQ sources
	static const uint32_t IER_value =
			0
			//| UART_IER_RBRINT_EN      /* Receive Buffer */
			//| UART_IER_THREINT_EN     /* Transmit Hold Register Empty  */
			// | UART_IER_RLSINT_EN      /* RX line status */
#if 0
			// | UART1_IER_MSINT_EN      /* Modem status - UART1 only */
			// | UART1_IER_CTSINT_EN     /* CTS1 signal transition - UART1 only */
#endif
			// | UART_IER_ABEOINT_EN     /* end of auto-baud */
			// | UART_IER_ABTOINT_EN     /* auto-baud time-out */
			;

	static const uint32_t LCR_value =
		0
		| UART_LCR_WLEN8        /* 5,6,7,8 */
		//| UART_LCR_STOPBIT_SEL  /* Two Stop Bits */
		//| UART_LCR_PARITY_EN    /* Parity Enable */
		//| UART_LCR_PARITY_ODD   /* _ODD, _EVEN, _F_0, _F_1 */
		//| UART_LCR_BREAK_EN     /* Transmission Break enable */
		;

	static int tx_bytes_left;

public:
	static struct
	{
		// FIXME: LPC_UART1_TypeDef type for UART1
		LPC_UART_TypeDef * operator-> ()
		{
			return uart_num == UART_0 ? LPC_UART0 :
			//       uart_num == UART_1 ? LPC_UART1 :
			       uart_num == UART_2 ? LPC_UART2 :
			                            LPC_UART3 ;
		}
	} UARTx;

	INLINE dbg_uart_t()
	{
		// enable module
		LPC_SC->PCONP |= pconp_mask;
		// TODO: bitfiled_traits<>
		int shift = clksel_shift;

		// Set 100 MHz clock
		// TODO: make prescaler dependent on F_CPU
		//	(use another more descriptive name) and baud rate
		if (shift < 32) {
			LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & ~(0x03 << shift))
			                 | (CLKPWR_PCLKSEL_CCLK_DIV_1 << shift);
		} else {
			LPC_SC->PCLKSEL1 = (LPC_SC->PCLKSEL1 & ~(0x03 << (shift-32)))
			                 | (CLKPWR_PCLKSEL_CCLK_DIV_1 << (shift-32));
		}

		// TODO: configure pins
		// TXD::Init();
		// RXD::Init();

		// Set IrDA to default state
		if (uart_num == UART_3) UARTx->ICR = 0;
		// off autobaud
		UARTx->ACR = 0;

		UARTx->IER = IER_value;
		if (IER_value) {
			// NVIC setup for UART interrupts
			NVIC->IP[ UARTx_IRQn ] = 0x80;
			NVIC->ISER[0] = (1 << UARTx_IRQn);
		} else {
			NVIC->ICER[0] = (1 << UARTx_IRQn);
		}

		UARTx->FCR =
			0
			| UART_FCR_FIFO_EN      /* FIFO enable */
			| UART_FCR_RX_RS        /* RX FIFO reset */
			| UART_FCR_TX_RS        /* TX FIFO reset */
			// | UART_FCR_DMAMODE_SEL  /* DMA mode */
			| UART_FCR_TRG_LEV0     /* 0=1byte, 1=4bytes, 2=8bytes, 3=14bytes */
			;

		tx_bytes_left = UART_TX_FIFO_SIZE;

		UARTx->LCR = UART_LCR_DLAB_EN | LCR_value;
		// TODO: (sub)optimal fractional divider
		const uint16_t divider = (100000000UL + 8*baud) / (16*baud);
		UARTx->DLL = divider & 0xFF;
		UARTx->DLM = divider >> 8;
		UARTx->LCR = LCR_value;
		UARTx->FDR = UART_FDR_DIVADDVAL(0) | UART_FDR_MULVAL(1);
		UARTx->TER = UART_TER_TXEN;
	}

	void putch(char ch);
	void puts(const char * s);
	void put_hex(uint8_t b);
	void put_hex(uint16_t w) __attribute__((__noinline__))
	{
		put_hex((uint8_t)(w >> 8));
		put_hex((uint8_t)w);
	}
	void put_hex(uint32_t w) __attribute__((__noinline__))
	{
		put_hex((uint16_t)(w >> 16));
		put_hex((uint16_t)w);
	}
	void put_hex(int i) { put_hex((uint32_t)i); }
	void put_hex(unsigned int i) { put_hex((uint32_t)i); }

	dbg_uart_t& operator<< (char value) { putch(value); return *this; }
	dbg_uart_t& operator<< (const char* value)  { puts(value); return *this; }

	dbg_uart_t& operator<< (int value)
	{
		char buf[20];
		puts(ftoa(value, buf, 0));
		return *this;
	}
	dbg_uart_t& operator<< (uint16_t value)
	{
		char buf[20];
		puts(ftoa(value, buf, 0));
		return *this;
	}
	dbg_uart_t& operator<< (uint32_t value)
	{
		char buf[20];
		puts(ftoa(value, buf, 0));
		return *this;
	}
	dbg_uart_t& operator<< (double value)
	{
		char buf[20];
		puts(ftoa(value, buf, 2));
		return *this;
	}
	dbg_uart_t& operator<< (size_t value) { return operator<< ((uint32_t)value); }
};

template<uart_num_t uart_num, uint32_t baud>
int dbg_uart_t<uart_num, baud>::tx_bytes_left;

template<uart_num_t uart_num, uint32_t baud>
void dbg_uart_t<uart_num, baud>::putch(char ch)
{
	if (--tx_bytes_left <= 0) {
		while (!(UARTx->LSR & UART_LSR_THRE)) {
			OS::sleep(2);
		}
		tx_bytes_left = 16;
	}
	UARTx->THR = ch;
}

template<uart_num_t uart_num, uint32_t baud>
void dbg_uart_t<uart_num, baud>::puts(const char* value)
{
	while (*value)
		putch(*value++);
}

char HexChar(char ch)
{
	return("0123456789ABCDEF"[ch&0x0F]);
}

template<uart_num_t uart_num, uint32_t baud>
void dbg_uart_t<uart_num, baud>::put_hex(uint8_t b)
{
	putch(HexChar(b >> 4));
	putch(HexChar(b & 0x0F));
}


#endif // DBG_UART_H_INCLUDED
