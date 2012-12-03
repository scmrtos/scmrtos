/**
*  GPIO pin manipulation class template for STM32F2xx and STM32F4xx.
*
*  Copyright (c) 2012 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*  Inspired by AVR macros from Askold Volkov
*
*
* USAGE:
*
*   I. Declare pin typedef:
* typedef Pin<'A', 5, 'H', PIN_SPEED_50MHZ> PA5;    // PA5, active level = high, pin speed = 50MHZ
* typedef Pin<'A', 6> PA6;               // PA6, default active level ('H'), default pin speed (PIN_SPEED_2MHZ)
* typedef Pin<'B', 12, 'L'> PB12;        // PB12, active level = low, default pin speed (PIN_SPEED_2MHZ)
*
*   II. Set pin mode:
* PA5::Mode(OUTPUT);                     // configure PA5 as output (push-pull, 100MHz)
* PA5::Direct(OUTPUT);                   // the same.
* PA6::Mode(INPUT);                      // configure PA6 as input floating
* PB12::Mode(OUTPUT);                    // configure PB12 as output
* TX::Mode(ALT_OUTPUT);                  // configure TX as alternate output push-pull
*                                        // (see PinConfig enum for list of all pin modes)
*
*   III. Select pin alternate function:
* TX::Alternate(ALT_FUNC_USART1);        // turn P15 alternate function on
*                                        // (see PinAltFunction enum for list of all alternate functions)
*
*   IV. Manipulate pin:
* PA5::On();                             // switch PA5 to active state (H)
* PB12::On();                            // switch PB12 to active state (L)
* PA5::Off();                            // switch PA5 to inactive state (L)
* PB12::Cpl();                           // invert PB12 output
*
*   V. Check pin state:
* if (PA5::Signalled())                  // returns non-zero if pin input = active state (H for PA5)
* if (PB12::Latched())                   // returns non-zero if pin output = active state (L for PB12)
*
*   VI. Use pin registers uniformly:
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

#ifndef PIN_STM32F4XX_H_
#define PIN_STM32F4XX_H_

#include <stdint.h>
#include <stddef.h>

#ifndef INLINE
#define INLINE __attribute__((__always_inline__)) inline
#endif

namespace {

typedef struct
{
  volatile uint32_t MODER;    ///!< GPIO port mode register
  volatile uint32_t OTYPER;   ///!< GPIO port output type register
  volatile uint32_t OSPEEDR;  ///!< GPIO port output speed register
  volatile uint32_t PUPDR;    ///!< GPIO port pull-up/pull-down register
  volatile uint32_t IDR;      ///!< GPIO port input data register
  volatile uint32_t ODR;      ///!< GPIO port output data register
  volatile uint32_t BSRR;     ///!< GPIO port bit set/reset low register
  volatile uint32_t LCKR;     ///!< GPIO port configuration lock register
  volatile uint32_t AFR[2];   ///!< GPIO alternate function registers
} GPIOxTypeDef;

enum
{
	pPERIPH_BASE     = 0x40000000UL,
	pPERIPH_BB_BASE  = 0x42000000UL,

	pGPIOA_BASE      = 0x40020000UL,
	pGPIOB_BASE      = 0x40020400UL,
	pGPIOC_BASE      = 0x40020800UL,
	pGPIOD_BASE      = 0x40020C00UL,
	pGPIOE_BASE      = 0x40021000UL,
	pGPIOF_BASE      = 0x40021400UL,
	pGPIOG_BASE      = 0x40021800UL,
	pGPIOH_BASE      = 0x40021C00UL,
	pGPIOI_BASE      = 0x40022000UL
};

}

/**
 * PinConfig enumeration. Defines all possible pin configuration variants.
 */
enum PinConfig
{
	INPUT,                   ///!< input floating
	INPUT_PULLUP,            ///!< input pull-up
	INPUT_PULLDOWN,          ///!< input pull-down
	ANALOG,                  ///!< analog

	OUTPUT,                  ///!< output push-pull
	OUTPUT_OD,               ///!< output open-drain
	OUTPUT_OD_PULLUP,        ///!< output open-drain pull-up
	OUTPUT_OD_PULLDOWN,      ///!< output open-drain pull-down
	ALT_INPUT,               ///!< alternate function input
	ALT_INPUT_PULLUP,        ///!< alternate function input with pull-up
	ALT_INPUT_PULLDOWN,      ///!< alternate function input with pull-down
	ALT_OUTPUT,              ///!< alternate function output push-pull
	ALT_OUTPUT_OD,           ///!< alternate function output open-drain
	ALT_OUTPUT_OD_PULLUP,    ///!< alternate function output open-drain pull-up
	ALT_OUTPUT_OD_PULLDOWN   ///!< alternate function output open-drain pull-down
};


/**
 * PinMode enumeration. Defines all possible values for MODER register.
 */
enum PinMode
{
	MODER_INPUT  = 0,
	MODER_OUTPUT  = 1,
	MODER_ALTERNATE  = 2,
	MODER_ANALOG  = 3
};

/**
 * PullUpMode enumeration. Defines all possible values for PUPDR register.
 */
enum PullUpMode
{
	PUPDR_NONE  = 0,
	PUPDR_PULLUP = 1,
	PUPDR_PULLDOWN = 2
};

/**
 * PinSpeed enumeration. Defines all possible values for OSPEEDR register.
 */
enum PinSpeed
{
	PIN_SPEED_2MHZ = 0,
	PIN_SPEED_25MHZ = 1,
	PIN_SPEED_50MHZ = 2,
	PIN_SPEED_100MHZ = 3,
	PIN_SPEED_MASK = 3
};

/**
 * PinOutputType enumeration. Defines all possible values for OTYPER register.
 */
enum PinOutputType
{
	PUSH_PULL = 0,
	OPEN_DRAIN = 1
};

/**
 * PinAltFunction enumeration. Defines all possible arguments for Alternate() function.
 */
enum PinAltFunction
{
	ALT_FUNC_RTC_50Hz  = 0x00,          ///< RTC_50Hz Alternate Function mapping
	ALT_FUNC_MCO       = 0x00,          ///< MCO (MCO1 and MCO2) Alternate Function mapping
	ALT_FUNC_TAMPER    = 0x00,          ///< TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping
	ALT_FUNC_SWJ       = 0x00,          ///< SWJ (SWD and JTAG) Alternate Function mapping
	ALT_FUNC_TRACE     = 0x00,          ///< TRACE Alternate Function mapping

	ALT_FUNC_TIM1      = 0x01,          ///< TIM1 Alternate Function mapping
	ALT_FUNC_TIM2      = 0x01,          ///< TIM2 Alternate Function mapping

	ALT_FUNC_TIM3      = 0x02,          ///< TIM3 Alternate Function mapping
	ALT_FUNC_TIM4      = 0x02,          ///< TIM4 Alternate Function mapping
	ALT_FUNC_TIM5      = 0x02,          ///< TIM5 Alternate Function mapping

	ALT_FUNC_TIM8      = 0x03,          ///< TIM8 Alternate Function mapping
	ALT_FUNC_TIM9      = 0x03,          ///< TIM9 Alternate Function mapping
	ALT_FUNC_TIM10     = 0x03,          ///< TIM10 Alternate Function mapping
	ALT_FUNC_TIM11     = 0x03,          ///< TIM11 Alternate Function mapping

	ALT_FUNC_I2C1      = 0x04,          ///< I2C1 Alternate Function mapping
	ALT_FUNC_I2C2      = 0x04,          ///< I2C2 Alternate Function mapping
	ALT_FUNC_I2C3      = 0x04,          ///< I2C3 Alternate Function mapping

	ALT_FUNC_SPI1      = 0x05,          ///< SPI1 Alternate Function mapping
	ALT_FUNC_SPI2      = 0x05,          ///< SPI2/I2S2 Alternate Function mapping

	ALT_FUNC_SPI3      = 0x06,          ///< SPI3/I2S3 Alternate Function mapping

	ALT_FUNC_USART1    = 0x07,          ///< USART1 Alternate Function mapping
	ALT_FUNC_USART2    = 0x07,          ///< USART2 Alternate Function mapping
	ALT_FUNC_USART3    = 0x07,          ///< USART3 Alternate Function mapping
	ALT_FUNC_I2S3ext   = 0x07,          ///< I2S3ext Alternate Function mapping

	ALT_FUNC_UART4     = 0x08,          ///< UART4 Alternate Function mapping
	ALT_FUNC_UART5     = 0x08,          ///< UART5 Alternate Function mapping
	ALT_FUNC_USART6    = 0x08,          ///< USART6 Alternate Function mapping

	ALT_FUNC_CAN1      = 0x09,          ///< CAN1 Alternate Function mapping
	ALT_FUNC_CAN2      = 0x09,          ///< CAN2 Alternate Function mapping
	ALT_FUNC_TIM12     = 0x09,          ///< TIM12 Alternate Function mapping
	ALT_FUNC_TIM13     = 0x09,          ///< TIM13 Alternate Function mapping
	ALT_FUNC_TIM14     = 0x09,          ///< TIM14 Alternate Function mapping

	ALT_FUNC_OTG_FS    = 0x0A,          ///< OTG_FS Alternate Function mapping
	ALT_FUNC_OTG_HS    = 0x0A,          ///< OTG_HS Alternate Function mapping

	ALT_FUNC_ETH       = 0x0B,          ///< ETHERNET Alternate Function mapping

	ALT_FUNC_FSMC      = 0x0C,          ///< FSMC Alternate Function mapping
	ALT_FUNC_OTG_HS_FS = 0x0C,          ///< OTG HS configured in FS, Alternate Function mapping
	ALT_FUNC_SDIO      = 0x0C,          ///< SDIO Alternate Function mapping

	ALT_FUNC_DCMI      = 0x0D,          ///< DCMI Alternate Function mapping

	ALT_FUNC_EVENTOUT  = 0x0F           ///< EVENTOUT Alternate Function mapping
};



template<char port> struct port_gpio_t;

template<> struct port_gpio_t<'A'>
{
	enum { GPIOx_BASE = pGPIOA_BASE };
};

template<> struct port_gpio_t<'B'>
{
	enum { GPIOx_BASE = pGPIOB_BASE };
};

template<> struct port_gpio_t<'C'>
{
	enum { GPIOx_BASE = pGPIOC_BASE };
};

template<> struct port_gpio_t<'D'>
{
	enum { GPIOx_BASE = pGPIOD_BASE };
};

template<> struct port_gpio_t<'E'>
{
	enum { GPIOx_BASE = pGPIOE_BASE };
};

template<> struct port_gpio_t<'F'>
{
	enum { GPIOx_BASE = pGPIOF_BASE };
};

template<> struct port_gpio_t<'G'>
{
	enum { GPIOx_BASE = pGPIOG_BASE };
};

template<> struct port_gpio_t<'H'>
{
	enum { GPIOx_BASE = pGPIOH_BASE };
};

template<> struct port_gpio_t<'I'>
{
	enum { GPIOx_BASE = pGPIOI_BASE };
};

template<
	char port,
	int pin_no,
	char activestate = 'H',
	PinSpeed speed = PIN_SPEED_100MHZ
	> struct Pin;

template<char port, int pin_no, char activestate, PinSpeed speed>
struct Pin
{
	static const int pin = pin_no;
	static const int port_no = port-'A';
	static const uint32_t mask = 1UL << pin;
	static const uint32_t clearmask = 1UL << (pin + 16);
	static const uint32_t shift_x4 = (pin % 8) * 4;
	static const uint32_t mask_x4 = 0xFUL << shift_x4;
	enum { GPIOx_BASE = port_gpio_t<port>::GPIOx_BASE };

	template <uint32_t addr> struct BitBandOneBit {
		enum { BB_ADDR  = pPERIPH_BB_BASE + (GPIOx_BASE + addr - pPERIPH_BASE) * 32 + pin * 4 };
	};

	template <uint32_t addr> struct BitBandTwoBit {
		enum { BB_ADDR  = pPERIPH_BB_BASE + (GPIOx_BASE + addr - pPERIPH_BASE) * 32 + pin * 2 * 4 };
	};

	enum
	{
		MODER_BB_ADDR    = BitBandTwoBit<offsetof(GPIOxTypeDef, MODER)>::BB_ADDR,
		OTYPER_BB_ADDR   = BitBandOneBit<offsetof(GPIOxTypeDef, OTYPER)>::BB_ADDR,
		OSPEEDR_BB_ADDR  = BitBandTwoBit<offsetof(GPIOxTypeDef, OSPEEDR)>::BB_ADDR,
		PUPDR_BB_ADDR    = BitBandTwoBit<offsetof(GPIOxTypeDef, PUPDR)>::BB_ADDR,
		IDR_BB_ADDR      = BitBandOneBit<offsetof(GPIOxTypeDef, IDR)>::BB_ADDR,
		ODR_BB_ADDR      = BitBandOneBit<offsetof(GPIOxTypeDef, ODR)>::BB_ADDR,

		GPIO_BB_ADDR     = MODER_BB_ADDR
	};

	/*
	 * Here all bit-band addresses are joined into the one structure.
	 * This makes GCC compiler generate much more optimal code.
	 */
	typedef struct
	{
		volatile uint32_t MODER_BIT0;   // MODER bits
		volatile uint32_t MODER_BIT1;
		uint32_t reserved1[(OTYPER_BB_ADDR - MODER_BB_ADDR)/4 - 2];     // skip remaining bits

		volatile uint32_t OTYPER_BIT0;  // OTYPER bit 0
		uint32_t reserved2[(OSPEEDR_BB_ADDR - OTYPER_BB_ADDR)/4 - 1];

		volatile uint32_t OSPEEDR_BIT0; // OSPEEDR bits
		volatile uint32_t OSPEEDR_BIT1;
		uint32_t reserved3[30];

		volatile uint32_t PUPDR_BIT0;   // PUPDR bits
		volatile uint32_t PUPDR_BIT1;
		uint32_t reserved4[(IDR_BB_ADDR - PUPDR_BB_ADDR)/4 - 2];

		volatile uint32_t IDR_BIT0;     // IDR bit 0
		uint32_t reserved5[31];

		volatile uint32_t ODR_BIT0;     // ODR bit 0
		uint32_t reserved6[31];

		volatile uint32_t BSRR_SET;     // BSRR bits
		uint32_t reserved7[15];
		volatile uint32_t BSRR_CLR;
	} GPIOxBbBits;


	static struct
	{
		GPIOxTypeDef* operator-> () { return (GPIOxTypeDef*)GPIOx_BASE; }
	}GPIOx;

	static struct
	{
		GPIOxBbBits* operator-> () { return (GPIOxBbBits*)GPIO_BB_ADDR; }
	}BBBits;

	INLINE static void On(bool set_on=true)
	{
		(activestate == 'H') == set_on ? GPIOx->BSRR = mask : GPIOx->BSRR = clearmask;
	}
	INLINE static void OnA(bool set_on=true)
	{
		(activestate == 'H') == set_on ? BBBits->BSRR_SET = 1 : BBBits->BSRR_CLR = 1;
	}
	INLINE static void Off() { On(false); }
	INLINE static void Cpl()
	{
		BBBits->ODR_BIT0 = ~BBBits->ODR_BIT0;
	}

	INLINE static void Mode(PinConfig cfg)
	{
		switch(cfg)
		{
		case  INPUT:
			SetMode(MODER_INPUT);
			PullNone();
			break;

		case  INPUT_PULLUP:
			SetMode(MODER_INPUT);
			PullUp();
			break;

		case INPUT_PULLDOWN:
			SetMode(MODER_INPUT);
			PullDown();
			break;

		case ANALOG:
			SetMode(MODER_ANALOG);
			PullNone();
			break;

		case OUTPUT:
			SetMode(MODER_OUTPUT);
			SetSpeed(speed);
			SetPushPull();
			PullNone();
			break;

		case OUTPUT_OD:
			SetMode(MODER_OUTPUT);
			SetSpeed(speed);
			SetOpenDrain();
			PullNone();
			break;

		case OUTPUT_OD_PULLUP:
			SetMode(MODER_OUTPUT);
			SetSpeed(speed);
			SetOpenDrain();
			PullUp();
			break;

		case OUTPUT_OD_PULLDOWN:
			SetMode(MODER_OUTPUT);
			SetSpeed(speed);
			SetOpenDrain();
			PullDown();
			break;

		case ALT_INPUT:
			SetMode(MODER_ALTERNATE);
			PullNone();
			break;

		case ALT_INPUT_PULLUP:
			SetMode(MODER_ALTERNATE);
			PullUp();
			break;

		case ALT_INPUT_PULLDOWN:
			SetMode(MODER_ALTERNATE);
			PullDown();
			break;

		case ALT_OUTPUT:
			SetMode(MODER_ALTERNATE);
			SetSpeed(speed);
			SetPushPull();
			PullNone();
			break;

		case ALT_OUTPUT_OD:
			SetMode(MODER_ALTERNATE);
			SetSpeed(speed);
			SetOpenDrain();
			PullNone();
			break;

		case ALT_OUTPUT_OD_PULLUP:
			SetMode(MODER_ALTERNATE);
			SetSpeed(speed);
			SetOpenDrain();
			PullUp();
			break;

		case ALT_OUTPUT_OD_PULLDOWN:
			SetMode(MODER_ALTERNATE);
			SetSpeed(speed);
			SetOpenDrain();
			PullDown();
			break;
		}
	}
	INLINE static void Direct(PinConfig cfg) { Mode(cfg); }

	/**
	 * Set Pull-UP/Pull-Down mode.
	 */
	INLINE static void SetPullUp(PullUpMode mode)
	{
		BBBits->PUPDR_BIT0 = mode & 1;
		BBBits->PUPDR_BIT1 = bool(mode & 2);
	}
	INLINE static void PullUp()   { SetPullUp(PUPDR_PULLUP); }
	INLINE static void PullDown() { SetPullUp(PUPDR_PULLDOWN); }
	INLINE static void PullNone() { SetPullUp(PUPDR_NONE); }

	INLINE static void SetSpeed(PinSpeed s)
	{
		BBBits->OSPEEDR_BIT0 = s & 1;
		BBBits->OSPEEDR_BIT1 = bool(s & 2);
	}

	INLINE static void SetMode(PinMode mode)
	{
		BBBits->MODER_BIT0 = mode & 1;
		BBBits->MODER_BIT1 = bool(mode & 2);
	}

	INLINE static void SetOutputType(PinOutputType val) { BBBits->OTYPER_BIT0 = val; }
	INLINE static void SetPushPull() { SetOutputType(PUSH_PULL); }
	INLINE static void SetOpenDrain() { SetOutputType(OPEN_DRAIN);}

	INLINE static void Alternate(PinAltFunction val)
	{
		GPIOx->AFR[pin / 8] = (GPIOx->AFR[pin / 8] & ~mask_x4) | (val << shift_x4);
	}

	INLINE static int Latched()
	{
		int ret = BBBits->ODR_BIT0;
		return activestate == 'L' ? !ret : ret;
	}

	INLINE static int Signalled()
	{
		int ret = BBBits->IDR_BIT0;
		return activestate == 'L' ? !ret : ret;
	}

};


#endif /* PIN_STM32F4XX_H_ */
