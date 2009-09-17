/**
*  GPIO pin manipulation class template for STM32.
*
*  Copyright (c) 2009 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*  Inspired by AVR macros from Askold Volkov
*
*
* USAGE:
*
*   I. Declare pin object:
* Pin<'A', 5, 'H'> PA5;    // PA5, active level = high
* Pin<'A', 6> PA6;         // PA6, active level = high ('H' is default parameter)
* Pin<'B', 12, 'L'> PB12;  // PB12, active level = low
*
*   II. Set pin mode:
* PA5.Mode(OUTPUT);        // configure PA5 as output (push-pull, 50MHz)
* PA5.Direct(OUTPUT);      // the same.
* PA6.Mode(INPUT);         // configure PA6 as input floating
* PB12.Mode(OUTPUT);       // configure PB12 as output
* TX.Mode(ALT_OUTPUT);     // configure TX as alternate output push-pull
*  (see "direction" enum for list of all pin modes)
*
*   III. Manipulate pin:
* PA5.On();                // switch PA5 to active state (H)
* PB12.On();               // switch PB12 to active state (L)
* PA5.Off();               // switch PA5 to inactive state (L)
* PB12.Cpl();              // invert PB12 output
*
*   IV. Check pin state:
* if (PA6.Signalled())     // returns non-zero if pin input = active state (H for PA6)
* if (PB12.Latched())      // returns non-zero if pin output = active state (L for PB12)
*
*   V. Use pin registers uniformly:
* locked = PA5.GPIOx->LCKR & PA5.mask; // read PA5 lock state.
*
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED
#include "stm32f10x.h"

#define		MAKE_PIN_CFG(MODE, CNF)	( (MODE) | (CNF)<<2 )

typedef enum {
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
} direction;

#undef MAKE_PIN_CFG

template<char port, int pin_no, char activestate = 'H'> struct Pin;

template<char port, int pin_no, char activestate>
struct Pin
{
	static struct
	{
		GPIO_TypeDef* operator-> ()
		{
			return
				port == 'A' ? GPIOA :
				port == 'B' ? GPIOB :
				port == 'C' ? GPIOC :
				port == 'D' ? GPIOD :
				port == 'E' ? GPIOE :
				port == 'F' ? GPIOF :
							GPIOG;
		}
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

	void On()
	{
		activestate == 'L' ? GPIOx->ODR &= ~mask : GPIOx->ODR |= mask;
	}
	void Off()
	{
		activestate == 'L' ? GPIOx->ODR |= mask : GPIOx->ODR &= ~mask;
	}
	void Cpl(){ GPIOx->ODR ^= mask; }
	void Mode(direction dir)
	{
		CRx = (CRx & ~(0x0F<<shift)) | (dir<<shift);
	}
	void Direct(direction dir)
	{
		CRx = (CRx & ~(0x0F<<shift)) | (dir<<shift);
	}
	void PullUp() { GPIOx->ODR |= mask; }
	void PullDown() { GPIOx->ODR &= ~mask; }

	int Latched()
	{
		int ret = GPIOx->ODR & mask;
		return activestate == 'L' ? !ret : ret;
	}

	int Signalled()
	{
		int ret = GPIOx->IDR & mask;
		return activestate == 'L' ? !ret : ret;
	}

};

#endif // PIN_H_INCLUDED


