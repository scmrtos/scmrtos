/**
*  @file dbg_uart.h
*
*  Created on: 18.01.2011
*  Copyright (c) 2011-2012by Anton Gusev aka AHTOXA
**/

#ifndef DBG_UART_H_INCLUDED
#define DBG_UART_H_INCLUDED
#include <scmRTOS.h>
#include "uart_regs.h"
#include "ftoa.h"

/**
*  @brief UART template class.
*  @param uart_num: select which UART peripheral to use.
*  @param baud: select UART speed.
*  @param remapped: switch remap on/off
*/
template<
	uart_num_t uart_num,
	uint32_t baud = 115200,
	remap_t remapped = REMAP_NONE
	>
class dbg_uart_t;

template<uart_num_t uart_num, uint32_t baud, remap_t remapped>
class dbg_uart_t
{
private:
	typedef uart_pins_t<uart_num, remapped> pins_t;
	typedef typename pins_t::PinTX TX;
	typedef typename pins_t::PinRX RX;

	typedef uart_regs_t<uart_num> uart_regs;
	typename uart_regs::APBxENR APBxENR;
	typename uart_regs::USARTxEN USARTxEN;
	typename uart_regs::BUS_FREQ BUS_FREQ;
	typename uart_regs::USARTx_IRQn USARTx_IRQn;
public:
	static struct
	{
		USART_TypeDef* operator-> ()
		{
			return
				uart_num == UART_1 ? USART1 :
				uart_num == UART_2 ? USART2 :
									 USART3 ;
		}
	}USARTx;

	INLINE dbg_uart_t()
	{
		// enable module
		APBxENR |= USARTxEN;

		// configure pins
		TX::Direct(ALT_OUTPUT);
		TX::Alternate(uart_num < 4 ? ALT_FUNC_USART1 : ALT_FUNC_UART4);
		RX::Direct(ALT_INPUT_PULLUP);
		RX::Alternate(uart_num < 4 ? ALT_FUNC_USART1 : ALT_FUNC_UART4);

		USARTx->CR1 = USART_CR1_RE | USART_CR1_TE;
		USARTx->CR2 = 0; // 1 stop
		USARTx->CR3 = 0; // no flow control
		USARTx->BRR = BUS_FREQ / baud;  // 9 - PLL multiplier
		USARTx->CR1 |= USART_CR1_UE;
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
	dbg_uart_t& operator<< (char value) { putch(value); return *this; }
	dbg_uart_t& operator<< (const char* value)  { puts(value); return *this; }
//	dbg_uart_t& operator<< (int value)  { put_hex(value); return *this; }
//	dbg_uart_t& operator<< (uint16_t value)  { put_hex(value); return *this; }
//	dbg_uart_t& operator<< (uint32_t value)  { put_hex(value); return *this; }
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
		puts(ftoa(value, buf, 1));
		return *this;
	}
	dbg_uart_t& operator<< (size_t value) { return operator<< ((uint32_t)value); }
};

template<uart_num_t uart_num, uint32_t baud, remap_t remapped>
void dbg_uart_t<uart_num, baud, remapped>::putch(char ch)
{
	while (!(USARTx->SR & USART_SR_TXE)) ;
	USARTx->DR = ch;
}

template<uart_num_t uart_num, uint32_t baud, remap_t remapped>
void dbg_uart_t<uart_num, baud, remapped>::puts(const char* value)
{
	while (*value)
		putch(*value++);
}

extern char HexChar(char ch);

template<uart_num_t uart_num, uint32_t baud, remap_t remapped>
void dbg_uart_t<uart_num, baud, remapped>::put_hex(uint8_t b)
{
	putch(HexChar(b >> 4));
	putch(HexChar(b & 0x0F));
}



#endif // DBG_UART_H_INCLUDED
