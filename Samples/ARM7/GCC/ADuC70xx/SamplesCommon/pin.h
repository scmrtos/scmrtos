/**
*  GPIO pin manipulation class template for ADuc70xx.
*
*  Copyright (c) 2010-2012Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*  Inspired by AVR macros from Askold Volkov
*
*
* USAGE:
*
*   I. Declare pin object:
* Pin<0, 5, 'H'> P05;    // P05, active level = high
* Pin<0, 6> P06;         // P06, active level = high ('H' is default parameter)
* Pin<1, 2, 'L'> P12;    // P12, active level = low
*
*   II. Set pin mode:
* P05.Mode(OUTPUT);      // configure P05 as output
* P06.Direct(OUTPUT);    // the same.
* P06.Mode(INPUT);       // configure P06 as input floating
* P12.Mode(OUTPUT);      // configure P12 as output
* TX.Alternate(ON);      // configure TX as alternate function
*
*   III. Manipulate pin:
* P05.On();              // switch P05 to active state (H)
* P12.On();              // switch P12 to active state (L)
* P05.Off();             // switch P05 to inactive state (L)
* P12.Cpl();             // invert P12 output
*
*   IV. Check pin state:
* if (P06.Signalled())   // returns non-zero if pin input = active state (H for P06)
* if (P12.Latched())     // returns non-zero if pin output = active state (L for P12)
*
*   V. Use pin registers uniformly:
* locked = P05.GPxPAR & P05.lock_mask; // read P05 lock state.
*
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED
#include "device.h"

// port direction enum
typedef enum { INPUT = 0, OUTPUT = 1 } direction;

// on/off state enum
typedef enum { OFF = 0, ON = 1 } on_off;

template<int port_no> struct port_regs_t;

#define DECLARE_REG(Name, rtype, OrigName)					\
typedef struct{												\
	rtype operator=(rtype value){							\
		OrigName = value;									\
		return value;										\
	}														\
	void operator|=(rtype value){ OrigName |= value; }		\
	void operator&=(rtype value){ OrigName &= value; }		\
	void operator^=(rtype value){ OrigName ^= value; }		\
	operator rtype(){ return OrigName; }					\
}Name

template<> struct port_regs_t<0>
{
	DECLARE_REG(GPxCON, uint32_t, GP0CON0);
	DECLARE_REG(GPxCON1, uint32_t, GP0CON1);
	DECLARE_REG(GPxDAT, uint32_t, GP0DAT);
	DECLARE_REG(GPxSET, uint32_t, GP0SET);
	DECLARE_REG(GPxCLR, uint32_t, GP0CLR);
	DECLARE_REG(GPxPAR, uint32_t, GP0PAR);
};

template<> struct port_regs_t<1>
{
	DECLARE_REG(GPxCON, uint32_t, GP1CON);
	DECLARE_REG(GPxDAT, uint32_t, GP1DAT);
	DECLARE_REG(GPxSET, uint32_t, GP1SET);
	DECLARE_REG(GPxCLR, uint32_t, GP1CLR);
	DECLARE_REG(GPxPAR, uint32_t, GP1PAR);
};

template<> struct port_regs_t<2>
{
	DECLARE_REG(GPxCON, uint32_t, GP2CON);
	DECLARE_REG(GPxDAT, uint32_t, GP2DAT);
	DECLARE_REG(GPxSET, uint32_t, GP2SET);
	DECLARE_REG(GPxCLR, uint32_t, GP2CLR);
	DECLARE_REG(GPxPAR, uint32_t, GP2PAR);
};

#undef DECLARE_REG

template<int port_no, int pin_no, char activestate = 'H'> struct Pin;

template<int port_no, int pin_no, char activestate>
struct Pin
{
	typedef port_regs_t<port_no> regs_t;
	typename regs_t::GPxCON GPxCON;
	typename regs_t::GPxDAT GPxDAT;
	typename regs_t::GPxSET GPxSET;
	typename regs_t::GPxCLR GPxCLR;
	typename regs_t::GPxPAR GPxPAR;
//	typename regs_t::GPxCON1 GPxCON1;

	enum { pin = pin_no };
	enum { port = port_no };
	enum { cfgmask = 1UL << (pin_no + 24) };
	enum { lockmask = 1UL << (pin_no + 24) };
	enum { altmask = 1UL << (pin_no << 2) };
	enum { setmask = 1UL << (pin_no + 16) };
	enum { readmask = 1UL << pin_no };

	void On()
	{
		activestate == 'L' ? GPxCLR = setmask : GPxSET = setmask;
	}
	void Off()
	{
		activestate == 'L' ? GPxSET = setmask : GPxCLR = setmask;
	}
	void Cpl(){ GPxDAT ^= setmask; }
	void Mode(direction dir)
	{
		dir == OUTPUT ? GPxDAT |= cfgmask : GPxDAT &= ~cfgmask;
	}
	void Direct(direction dir)
	{
		dir == OUTPUT ? GPxDAT |= cfgmask : GPxDAT &= ~cfgmask;
	}
	void PullUp(on_off on)
	{
		on ? GPxPAR |= readmask : GPxPAR &= ~readmask;
	}

	void Alternate(on_off on)
	{
		on ? GPxCON |= altmask : GPxPAR &= ~altmask;
	}

	int Latched()
	{
		int ret = GPxDAT & setmask;
		return activestate == 'L' ? !ret : ret;
	}

	int Signalled()
	{
		int ret = GPxDAT & readmask;
		return activestate == 'L' ? !ret : ret;
	}

};

#endif // PIN_H_INCLUDED


