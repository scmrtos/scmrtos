/**
*
*  GPIO pin manipulation class template for LPC17xx.
*
*  Copyright (c) 2012 Oleksandr Rechuk aka ReAl (http://real.kiev.ua)
*
*  Based on:
*       GPIO pin manipulation class template for STM32.*
*       Copyright (c) 2009-2012Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*     $Revision: $
*     $Date::            #$
*
* USAGE:
*
*   I. Declare pin typedef:
* typedef Pin<'0', 5, 'H'> P0_5;    // P0.5, active level = high
* typedef Pin<'0', 6> P0_6;         // P0.6, active level = high ('H' is default parameter)
* typedef Pin<'0', 10, 'L'> P0_10;  // P0.10, active level = low
*
*  Override default INPUT_HIZ pin mode and PINSEL_0 selector
* typedef Pin<'0',2,'H',OUTPUT,PINSEL_1> TX0; // P0.2, UART0 TX pin
*
*   II. Set pin mode:
* P0_5::Mode(OUTPUT);           // configure P0_5 as push-pull output
* P0_6::Mode(OUTPUT_OD_PULLED); // configure P0_6 as open-drain output with internal pull-up
* P0_10::Mode(INPUT_PULLUP);    // configure P0_10 as input with internal pull-up
* P0_10::Mode(OUTPUT_OD);       // configure P0_10 as open-drain output
* TX0::Init();             // Use default pin settings from typedef
*                          // Useful for pins types as another template parameters
*
*   III. Manipulate pin:
* P0_5::On();               // switch P0.5 to active state (H)
* P0_10::On();              // switch P0_10 to active state (L)
* P0_5::Off();              // switch P0.5 to inactive state (L)
* P0_10::Cpl();             // invert P0_10 output
*
*   IV. Check pin state:
* if (P0_10::Signalled())     // returns non-zero if pin input = active state (L for P0_10)
* if (P0_5::Latched())        // returns non-zero if pin output = active state (H for P0_5)
*
*   V. Use pin registers uniformly:
* direction = P0_5::GPIOx->FIODIR & P0_5::mask; // read P0_5 direction state.
*
*   It is also possible to declare object of defined type:
* P0_5 Pin005;
* P0_10 Pin010;
* In this case, one can use "dot" notation to call object functions, i.e.
* Pin05.On();
* Pin010.Mode(INPUT);
* Note : using objects instead of types can (in some cases) increase memory consumption.
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED

#include <stdint.h>
#include <stddef.h> /* offsetof() */


#ifndef INLINE
#define INLINE __attribute__((__always_inline__)) inline
#endif


/*  Cortex-M3
 *
 *  SRAM   BB region  0x20000000..0x200FFFFF -> 0x22000000..0x23FFFFFF
 *	LPC17xx: LPC_GPIO_BASE = 0x2009C000UL
 *
 *  PERIPH BB region  0x40000000..0x400FFFFF -> 0x42000000..0x43FFFFFF
 *	LPC17xx: LPC_GPIOINT_BASE
 *	         LPC_PINCON_BASE (PINSEL, PINMODE, PINMODE_OD, I2CPADCFG)
 */

#define BAND_OFFSET(addr)  ((addr) & 0x000FFFFFUL)
#define BAND_BB_BASE(addr) (((addr) & 0xF0000000UL) | 0x02000000UL)
#define BB_ADDR(addr,pin)  (BAND_BB_BASE(addr) + 32 * BAND_OFFSET(addr) + 4 * (pin_no)) 

enum PinMode
{
 	  // Hi-Z input and input with weak pull-up
 	INPUT_PULLUP = 0, INPUT_KEEPER = 1, INPUT_HIZ = 2, INPUT_PULLDOWN = 3,
 	  // OpenDrain pulled -- high only
 	OUTPUT, OUTPUT_OD, OUTPUT_OD_PULLUP
};

enum PinSelector { PINSEL_0 = 0, PINSEL_1, PINSEL_2, PINSEL_3 };

template<char port_letter> struct port_gpio_t;

#define DECLARE_PORT_GPIO(port_letter,port_des)         \
    template<> struct port_gpio_t< port_letter > {      \
      enum PINCON_ADDR {                                \
	GPIOx_BASE       = LPC_GPIO ## port_des ## _BASE, \
	GPIOx_PINSEL_L = LPC_PINCON_BASE + offsetof(LPC_PINCON_TypeDef,PINSEL0)   \
			+ 2 * port_des * sizeof(uint32_t),                        \
	GPIOx_PINSEL_H = LPC_PINCON_BASE + offsetof(LPC_PINCON_TypeDef,PINSEL1)   \
			+ 2 * port_des * sizeof(uint32_t),                        \
	GPIOx_PINMODE_L = LPC_PINCON_BASE + offsetof(LPC_PINCON_TypeDef,PINMODE0) \
			+ 2 * port_des * sizeof(uint32_t),                        \
	GPIOx_PINMODE_H = LPC_PINCON_BASE + offsetof(LPC_PINCON_TypeDef,PINMODE1) \
			+ 2 * port_des * sizeof(uint32_t),                        \
	GPIOx_PINMODE_OD = LPC_PINCON_BASE + offsetof(LPC_PINCON_TypeDef,PINMODE_OD0) \
			+ port_des * sizeof(uint32_t)                             \
      }; \
    }


DECLARE_PORT_GPIO('0',0);
DECLARE_PORT_GPIO('1',1);
DECLARE_PORT_GPIO('2',2);
DECLARE_PORT_GPIO('3',3);
DECLARE_PORT_GPIO('4',4);

#undef DECLARE_PORT_GPIO


template<
	char port_letter, int pin_no, char activestate = 'H',
	PinMode default_mode = INPUT_PULLUP, PinSelector default_sel = PINSEL_0
> struct Pin
{
	enum {
		GPIOx_BASE = port_gpio_t<port_letter>::GPIOx_BASE,
		GPIOx_SEL  = pin_no < 16
		           ? port_gpio_t<port_letter>::GPIOx_PINSEL_L
		           : port_gpio_t<port_letter>::GPIOx_PINSEL_H,
		GPIOx_MODE = pin_no < 16
		           ? port_gpio_t<port_letter>::GPIOx_PINMODE_L
		           : port_gpio_t<port_letter>::GPIOx_PINMODE_H,
		GPIOx_MODE_OD = port_gpio_t<port_letter>::GPIOx_PINMODE_OD
	};

#define FIO_BB_ADDR(REG) BB_ADDR( GPIOx_BASE + offsetof(LPC_GPIO_TypeDef, REG), pin_no )

	enum {
		FIODIR_BB_ADDR = FIO_BB_ADDR( FIODIR ),
		FIOPIN_BB_ADDR = FIO_BB_ADDR( FIOPIN ),
		FIOSET_BB_ADDR = FIO_BB_ADDR( FIOSET )
	};
	
#undef FIO_BB_ADDR

	static struct
	{
		LPC_GPIO_TypeDef* operator-> () { return (LPC_GPIO_TypeDef*)GPIOx_BASE; }
	} GPIOx;
	static struct
	{
		operator uint32_t () { return *(volatile uint32_t*)GPIOx_SEL; }
		void operator = (uint32_t val) { *(volatile uint32_t*)GPIOx_SEL = val; }
		void operator |= (uint32_t val) { *(volatile uint32_t*)GPIOx_SEL |= val; }
		void operator &= (uint32_t val) { *(volatile uint32_t*)GPIOx_SEL &= val; }
	} SELx;
	static struct
	{
		operator uint32_t () { return *(volatile uint32_t*)GPIOx_MODE; }
		void operator = (uint32_t val) { *(volatile uint32_t*)GPIOx_MODE = val; }
		void operator |= (uint32_t val) { *(volatile uint32_t*)GPIOx_MODE |= val; }
		void operator &= (uint32_t val) { *(volatile uint32_t*)GPIOx_MODE &= val; }
	} MODEx;

	static const int pin = pin_no;
	static const int port_no = port_letter-'0';
	static const int port    = port_letter;
	static const uint32_t mask = 1UL << pin_no;
	static const uint32_t shift_2 = (pin_no % 16) << 1;
	static const uint32_t mask_2  = 0x03UL << shift_2;

	INLINE static void On(bool set_on=true)
	{
		(activestate == 'H') == set_on ? GPIOx->FIOSET = mask : GPIOx->FIOCLR = mask;
	}
	INLINE static void Off() { On(false); }

	INLINE static void Cpl()
	{
		*(volatile uint32_t *)FIOPIN_BB_ADDR = ~*(volatile uint32_t *)FIOSET_BB_ADDR;
	}

	// Non-atomic
	INLINE static void Selector(PinSelector sel)
	{
		SELx = (SELx & ~mask_2) | (sel << shift_2);
	}

	// Non-atomic
	INLINE static void Mode(PinMode mode)
	{
		switch(mode) {
		case INPUT_PULLUP:
		case INPUT_KEEPER:
		case INPUT_HIZ:
		case INPUT_PULLDOWN:
			//GPIOx->FIODIR &= ~mask;
			*(volatile uint32_t*)FIODIR_BB_ADDR = 0;
			MODEx = (MODEx & ~mask_2) | (mode << shift_2);
			*(volatile uint32_t*)GPIOx_MODE_OD &= ~mask;
			break;
		case OUTPUT:
			MODEx = (MODEx & ~mask_2) | (INPUT_HIZ << shift_2);
			*(volatile uint32_t*)GPIOx_MODE_OD &= ~mask;
			//GPIOx->FIODIR |= mask;
			*(volatile uint32_t*)FIODIR_BB_ADDR = 1;
			break;
		case OUTPUT_OD:
			MODEx = (MODEx & ~mask_2) | (INPUT_HIZ << shift_2);
			*(volatile uint32_t*)GPIOx_MODE_OD |= mask;
			//GPIOx->FIODIR |= mask;
			*(volatile uint32_t*)FIODIR_BB_ADDR = 1;
			break;
		case OUTPUT_OD_PULLUP:
			MODEx = (MODEx & ~mask_2) | (INPUT_PULLUP << shift_2);
			*(volatile uint32_t*)GPIOx_MODE_OD |= mask;
			//GPIOx->FIODIR |= mask;
			*(volatile uint32_t*)FIODIR_BB_ADDR = 1;
			break;
		}
	}

	INLINE static void Init(PinMode mode = default_mode, PinSelector sel = default_sel)
	{
		Selector(sel);
		Mode(mode);
	}

	INLINE static int Latched()
	{
		int ret = *(volatile uint32_t *)FIOSET_BB_ADDR;
		return activestate == 'L' ? !ret : ret;
	}

	INLINE static int Signalled()
	{
		int ret = *(volatile uint32_t *)FIOPIN_BB_ADDR;
		return activestate == 'L' ? !ret : ret;
	}

};

#endif // PIN_H_INCLUDED


