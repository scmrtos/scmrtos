/**
*  GPIO pin manipulation class template for STM32.
*
*  Copyright (c) 2009-2012Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*  Inspired by AVR macros from Askold Volkov
*
*
* USAGE:
*
*   I. Declare pin typedef:
* typedef Pin<'A', 5, 'H'> PA5;    // PA5, active level = high
* typedef Pin<'A', 6> PA6;         // PA6, active level = high ('H' is default parameter)
* typedef Pin<'B', 12, 'L'> PB12;  // PB12, active level = low
*
*   II. Set pin mode:
* PA5::Mode(OUTPUT);       // configure PA5 as output (push-pull, 50MHz)
* PA5::Direct(OUTPUT);     // the same.
* PA6::Mode(INPUT);        // configure PA6 as input floating (use object and "." notation)
* PB12::Mode(OUTPUT);      // configure PB12 as output
* TX::Mode(ALT_OUTPUT);    // configure TX as alternate output push-pull
*                          // (see "direction" enum for list of all pin modes)
*
*   III. Manipulate pin:
* PA5::On();               // switch PA5 to active state (H)
* PB12::On();              // switch PB12 to active state (L)
* PA5::Off();              // switch PA5 to inactive state (L)
* PB12::Cpl();             // invert PB12 output
*
*   IV. Check pin state:
* if (PA5::Signalled())     // returns non-zero if pin input = active state (H for PA5)
* if (PB12::Latched())      // returns non-zero if pin output = active state (L for PB12)
*
*   V. Use pin registers uniformly:
* locked = PA5::GPIOx->LCKR & PA5::mask; // read PA5 lock state.
*
*   It is also possible to declare object of defined type:
* PA5 PinA5;
* In this case, one can use "dot" notation to call object functions, i.e.
* PinA5.On();
* PB12.Mode(INPUT);
* Note : using objects instead of types can (in some cases) increase memory consumption.
*
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED
#include "stm32f10x.h"
#include <stddef.h>

#define		MAKE_PIN_CFG(MODE, CNF)	( (MODE) | (CNF)<<2 )

enum direction
{
	ANALOGINPUT = 			MAKE_PIN_CFG ( 0, 0 ),
	INPUT =					MAKE_PIN_CFG ( 0, 1 ),
	INPUTPULLED =			MAKE_PIN_CFG ( 0, 2 ),

	OUTPUT_10MHZ =			MAKE_PIN_CFG ( 1, 0 ),
	OUTPUT_OD_10MHZ =		MAKE_PIN_CFG ( 1, 1 ),
	ALT_OUTPUT_10MHZ =		MAKE_PIN_CFG ( 1, 2 ),
	ALT_OUTPUT_OD_10MHZ =	MAKE_PIN_CFG ( 1, 3 ),

	OUTPUT_2MHZ =			MAKE_PIN_CFG ( 2, 0 ),
	OUTPUT_OD_2MHZ =		MAKE_PIN_CFG ( 2, 1 ),
	ALT_OUTPUT_2MHZ =		MAKE_PIN_CFG ( 2, 2 ),
	ALT_OUTPUT_OD_2MHZ =	MAKE_PIN_CFG ( 2, 3 ),

	OUTPUT =				MAKE_PIN_CFG ( 3, 0 ),
	OUTPUT_OD =				MAKE_PIN_CFG ( 3, 1 ),
	ALT_OUTPUT =			MAKE_PIN_CFG ( 3, 2 ),
	ALT_OUTPUT_OD =			MAKE_PIN_CFG ( 3, 3 )
};

#undef MAKE_PIN_CFG

template<char port> struct port_gpio_t;

template<> struct port_gpio_t<'A'>
{
	enum { GPIOx_BASE = GPIOA_BASE };
};

template<> struct port_gpio_t<'B'>
{
	enum { GPIOx_BASE = GPIOB_BASE };
};

template<> struct port_gpio_t<'C'>
{
	enum { GPIOx_BASE = GPIOC_BASE };
};

template<> struct port_gpio_t<'D'>
{
	enum { GPIOx_BASE = GPIOD_BASE };
};

template<> struct port_gpio_t<'E'>
{
	enum { GPIOx_BASE = GPIOE_BASE };
};

template<> struct port_gpio_t<'F'>
{
	enum { GPIOx_BASE = GPIOF_BASE };
};

template<> struct port_gpio_t<'G'>
{
	enum { GPIOx_BASE = GPIOG_BASE };
};

template<char port, int pin_no, char activestate = 'H'> struct Pin;

template<char port, int pin_no, char activestate>
struct Pin
{
	enum { GPIOx_BASE = port_gpio_t<port>::GPIOx_BASE };
	enum { IDR_BB_ADDR = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIO_TypeDef, IDR) - PERIPH_BASE) * 32 + pin_no * 4 };
	enum { ODR_BB_ADDR = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIO_TypeDef, ODR) - PERIPH_BASE) * 32 + pin_no * 4 };
	static struct
	{
		GPIO_TypeDef* operator-> () { return (GPIO_TypeDef*)GPIOx_BASE; }
	}GPIOx;


	static struct{
		uint32_t operator=(uint32_t value){
			pin_no < 8 ? GPIOx->CRL = value :
			GPIOx->CRH = value;
			return value;
		}
		void operator|=(uint32_t value){
			pin_no < 8 ? GPIOx->CRL |= value :
			GPIOx->CRH |= value;
		}
		void operator&=(uint32_t value){
			pin_no < 8 ? GPIOx->CRL &= value :
			GPIOx->CRH &= value;
		}
		operator uint32_t(){
			return pin_no < 8 ? GPIOx->CRL :
			GPIOx->CRH;
		}
	}CRx;

	static const int pin = pin_no;
	static const int port_no = port-'A';
	static const uint32_t mask = 1UL << pin_no;
	static const uint32_t shift = (pin_no % 8) << 2;

	static void On()
	{
		activestate == 'L' ? GPIOx->BRR = mask : GPIOx->BSRR = mask;
	}
	static void Off()
	{
		activestate == 'L' ? GPIOx->BSRR = mask : GPIOx->BRR = mask;
	}
	static void Cpl()
	{
		*(volatile uint32_t *)ODR_BB_ADDR = ~*(volatile uint32_t *)ODR_BB_ADDR;
	}

	static void Mode(direction dir)
	{
		CRx = (CRx & ~(0x0F<<shift)) | (dir<<shift);
	}
	static void Direct(direction dir)
	{
		CRx = (CRx & ~(0x0F<<shift)) | (dir<<shift);
	}
	static void PullUp() { GPIOx->BSRR = mask; }
	static void PullDown() { GPIOx->BRR = mask; }

	static int Latched()
	{
		int ret = *(volatile uint32_t *)ODR_BB_ADDR;
		return activestate == 'L' ? !ret : ret;
	}

	static int Signalled()
	{
		int ret = *(volatile uint32_t *)IDR_BB_ADDR;
		return activestate == 'L' ? !ret : ret;
	}

};

#endif // PIN_H_INCLUDED


