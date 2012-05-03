/**
*  GPIO pin manipulation class template for STM8.
*
*  Copyright (c) 2011-2012Oleksandr Rechuk aka ReAl (http://real.kiev.ua)
*
*  Based on GPIO pin class tempalte for STM32 by Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*     $Revision$
*     $Date::             $
*
* USAGE:
*
*   I. Declare pin object:
* Pin<'A', 5, 'H'> PA5;    // PA5, active level = high
* Pin<'A', 6> PA6;         // PA6, active level = high ('H' is default parameter)
* Pin<'B', 7, 'L'> PB7;    // PB7, active level = low
*
*   II. Set pin mode:
*  Use stm8s_gpio.h GPIO_Mode_TypeDef enum values as mode identifier
* PA5.Mode(GPIO_MODE_OUT_PP_LOW_FAST); // configure PA5 as output: push-pull, 10MHz, initially LOW
* PA6.Mode(GPIO_MODE_IN_FL_NO_IT);     // configure PA6 as input: floating, no interrupts
* PB7.Mode(GPIO_MODE_OUT_OD_HIZ_SLOW); // configure PB7 as output: open-drain, 2MHz, initially Hi-Z
*
*   III. Manipulate pin:
* PA5.On();                // switch PA5 to active state (H)
* PB7.On();                // switch PB7 to active state (L)
* PA5.Off();               // switch PA5 to inactive state (L)
* PB7.Cpl();               // invert PB7 output
*
*   IV. Check pin state:
* if (PA6.Signalled())     // returns non-zero if pin input = active state (H for PA6)
* if (PB7.Latched())       // returns non-zero if pin output = active state (L for PB7)
*
*   V. Use pin registers uniformly:
* locked = PA5.GPIOx->ODR & PA5.mask; // read PA5 output state.
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED

#include "stm8_target.h"

template<char port> struct port_gpio_t;

template<> struct port_gpio_t<'A'>
{
	enum { GPIOx_BASE = GPIOA_BaseAddress };
};

template<> struct port_gpio_t<'B'>
{
	enum { GPIOx_BASE = GPIOB_BaseAddress };
};

template<> struct port_gpio_t<'C'>
{
	enum { GPIOx_BASE = GPIOC_BaseAddress };
};

template<> struct port_gpio_t<'D'>
{
	enum { GPIOx_BASE = GPIOD_BaseAddress };
};

template<> struct port_gpio_t<'E'>
{
	enum { GPIOx_BASE = GPIOE_BaseAddress };
};

template<> struct port_gpio_t<'F'>
{
	enum { GPIOx_BASE = GPIOF_BaseAddress };
};

template<> struct port_gpio_t<'G'>
{
	enum { GPIOx_BASE = GPIOG_BaseAddress };
};

template<> struct port_gpio_t<'H'>
{
	enum { GPIOx_BASE = GPIOH_BaseAddress };
};

template<> struct port_gpio_t<'I'>
{
	enum { GPIOx_BASE = GPIOI_BaseAddress };
};

template<char port, int pin_no, char activestate = 'H'> struct Pin;

template<char port, int pin_no, char activestate>
struct Pin
{
	enum { GPIOx_BASE = port_gpio_t<port>::GPIOx_BASE };

	static const uint8_t MODE_DDR_MASK = 0x80;
        static const uint8_t MODE_CR1_MASK = 0x40;
	static const uint8_t MODE_CR2_MASK = 0x20;
        static const uint8_t MODE_ODR_MASK = 0x10;

	static struct
	{
		GPIO_TypeDef* operator-> () { return (GPIO_TypeDef*)GPIOx_BASE; }
	} GPIOx;

	static const uint8_t mask = 1 << pin_no;

	INLINE static void On()
	{
		activestate == 'L' ? GPIOx->ODR &= ~mask : GPIOx->ODR |= mask;
	}
	INLINE static void Off()
	{
		activestate == 'L' ? GPIOx->ODR |= mask : GPIOx->ODR &= ~mask;
	}
	INLINE static void Cpl()
	{
		// TODO: How to force to BCPL usage?
		GPIOx->ODR ^= mask;
	}

	INLINE static void Mode(GPIO_Mode_TypeDef mode)
	{
		// stm8s_gpio.c GPIO_Init() clears CR2 bit at start
		// TODO: Setup sequence depend on high/low output value and present i/o mode?
		if (mode & MODE_DDR_MASK) {
			// output mode
			mode & MODE_ODR_MASK ? GPIOx->ODR |= mask : GPIOx->ODR &= ~mask;
			// input-pullup/output-OD mode
			mode & MODE_CR1_MASK ? GPIOx->CR1 |= mask : GPIOx->CR1 &= ~mask;
			GPIOx->DDR |= mask;
		} else {
			// input-pullup/output-OD mode
			mode & MODE_CR1_MASK ? GPIOx->CR1 |= mask : GPIOx->CR1 &= ~mask;
			GPIOx->DDR &= ~mask;
		}
		// input-interrupt/fast-output mode
		mode & MODE_CR2_MASK ? GPIOx->CR2 |= mask : GPIOx->CR2 &= ~mask;
	}

#if 0
// TODO: Залишити, але не міняти ODR?
	void Direct(direction dir)
	{
	}
#endif

	INLINE static uint8_t Latched()
	{
		uint8_t ret = GPIOx->ODR & mask;
		return activestate == 'L' ? !ret : ret;
	}

	INLINE static uint8_t Signalled()
	{
		uint8_t ret = GPIOx->IDR & mask;
		return activestate == 'L' ? !ret : ret;
	}

};

#endif // PIN_H_INCLUDED
