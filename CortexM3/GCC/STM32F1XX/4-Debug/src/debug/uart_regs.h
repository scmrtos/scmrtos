/**
*  @file usart_regs.h
*  UART registers and pins selection templates
*
*  Created on: 09.11.2010
*  Copyright (c) 2009-2012by Anton Gusev aka AHTOXA
**/

#ifndef UART_REGS_H_INCLUDED
#define UART_REGS_H_INCLUDED
#include "stm32f10x.h"
#include "pin.h"

/**
*  @brief enum for UART device selection
*/
typedef enum { UART_1, UART_2, UART_3 } uart_num_t;

/**
*  @brief enum for remap state
*/
typedef enum { REMAP_NONE, REMAP_FULL, REMAP_PARTIAL } remap_t;

/**
*  @brief UART pins selection template. Used internally.
*/
template<uart_num_t uart_num, remap_t remapped = REMAP_NONE> struct uart_pins_t;

/**
*  @brief pins for UART1.
*/
template<> struct uart_pins_t<UART_1>
{
	typedef Pin<'A', 9> PinTX;
	typedef Pin<'A', 10> PinRX;
};

/**
*  @brief pins for UART1 remapped.
*/
template<> struct uart_pins_t<UART_1, REMAP_FULL>
{
	typedef Pin<'B', 6> PinTX;
	typedef Pin<'B', 7> PinRX;
};

/**
*  @brief pins for UART2.
*/
template<> struct uart_pins_t<UART_2>
{
	typedef Pin<'A', 2> PinTX;
	typedef Pin<'A', 3> PinRX;
};

/**
*  @brief pins for UART2 remapped.
*/
template<> struct uart_pins_t<UART_2, REMAP_FULL>
{
	typedef Pin<'D', 5> PinTX;
	typedef Pin<'D', 6> PinRX;
};

/**
*  @brief pins for UART3.
*/
template<> struct uart_pins_t<UART_3>
{
	typedef Pin<'B', 10> PinTX;
	typedef Pin<'B', 11> PinRX;
};

template<uart_num_t uart_num>
struct uart_regs_t
{
	#define DECLARE_REG(Name, rtype, Name1, Name2, Name3)	\
	typedef struct{											\
		rtype operator=(rtype value){						\
			uart_num == UART_1 ? Name1 = value :			\
			uart_num == UART_2 ? Name2 = value :			\
			Name3 = value;									\
			return value;									\
		}													\
		void operator|=(rtype value){						\
			uart_num == UART_1 ? Name1 |= value :			\
			uart_num == UART_2 ? Name2 |= value :			\
			Name3 |= value;									\
		}													\
		void operator&=(rtype value){						\
			uart_num == UART_1 ? Name1 &= value :			\
			uart_num == UART_2 ? Name2 &= value :			\
			Name3 &= value;									\
		}													\
		operator rtype(){									\
			return uart_num == UART_1 ? Name1 : 			\
			uart_num == UART_2 ? Name2 :		 			\
			Name3;											\
		}													\
	}Name

	#define DECLARE_CONST(Name, rtype, Val1, Val2, Val3)	\
	typedef struct{											\
		operator rtype() {									\
			return uart_num == UART_1 ? Val1 : 				\
			uart_num == UART_2 ? Val2 :		 				\
			Val3;											\
		}													\
	}Name

	DECLARE_REG(APBxENR, uint32_t, RCC->APB2ENR, RCC->APB1ENR, RCC->APB1ENR);
		DECLARE_CONST(USARTxEN, uint32_t, RCC_APB2ENR_USART1EN, RCC_APB1ENR_USART2EN, RCC_APB1ENR_USART3EN);

#if (defined STM32F10X_LD_VL) || (defined STM32F10X_MD_VL)
	DECLARE_CONST(BUS_FREQ, uint32_t, 24000000, 24000000, 24000000);
#else
	DECLARE_CONST(BUS_FREQ, uint32_t, 72000000, 36000000, 36000000);
#endif
	DECLARE_CONST(USARTx_IRQn, IRQn_Type, USART1_IRQn, USART2_IRQn, USART3_IRQn);
	DECLARE_CONST(USARTx_REMAP, uint32_t, AFIO_MAPR_USART1_REMAP, AFIO_MAPR_USART2_REMAP, AFIO_MAPR_USART3_REMAP);
};

#endif // UART_REGS_H_INCLUDED
