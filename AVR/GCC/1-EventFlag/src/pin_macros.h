/*----------------------------------------------------------------------------------------------
 *	pin_macros.h  (AVR/avr-gcc)
 *----------------------------------------------------------------------------------------------
 *
 * Author:  Oleksandr Redchuk aka ReAl (real@real.kiev.ua)
 *
 * Description: port bits access macros for AVR uC family (avr-gcc compiler)
 *
 * Based on macros by Ascold Volkov, Andy Mozzevilov, Aleksey Musin
 *----------------------------------------------------------------------------------------------
 */

/*
examples

#define Pin1 A,2,H
#define Pin2 B,3,L
             ^ ^ ^
          port | |
             bit \active level

void main(void)
{
	DRIVER(Pin1,OUT);	//as output
	DRIVER(Pin2,IN);		//as input
	DRIVER(Pin2,PULLUP);	// with pullup
	ON(Pin1);
	if (ACTIVE(Pin2)) OFF(Pin1);
	if (LATCH(Pin1)) { //if active level presents on Pin1 for drive something
		//do something
	}
}
*/

#ifndef PIN_MACROS_H
#define PIN_MACROS_H

// assume chip has PORT_TOGGLE_BY_PIN_WRITE feature by default (all new AVR chips)
// check only old-style chips

#if	defined(__AVR_AT94K__) \
	|| defined(__AVR_AT43USB320__) || defined(__AVR_AT43USB355__) \
	|| defined(__AVR_AT76C711__) || defined(__AVR_AT86RF401__) \
	|| defined(__AVR_AT90C8534__) || defined(__AVR_AT90S4434__) \
	|| defined(__AVR_AT90S1200__) || defined(__AVR_AT90S2343__) \
	|| defined(__AVR_AT90S2333__) || defined(__AVR_AT90S2323__) \
	|| defined(__AVR_AT90S2313__) || defined(__AVR_AT90S4433__) \
	|| defined(__AVR_AT90S4414__) \
	|| defined(__AVR_AT90S8515__) || defined(__AVR_AT90S8535__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega103__) \
	|| defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) \
	|| defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) \
	|| defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATtiny11__) || defined(__AVR_ATtiny12__) \
	|| defined(__AVR_ATtiny15__) || defined(__AVR_ATtiny28__) \
	|| defined(__AVR_ATtiny22__) || defined(__AVR_ATtiny26__) \
	|| defined(__AVR_ATmega161__) || defined(__AVR_ATmega162__) \
	|| defined(__AVR_ATmega163__) || defined(__AVR_ATmega323__) \
	|| defined(__AVR_ATmega8HVA__) || defined(__AVR_ATmega16HVA__)
#  define PORT_TOGGLE_BY_PIN_WRITE 0
#else
#  define PORT_TOGGLE_BY_PIN_WRITE 1
#endif

#define PM_BITNUM(port,bit,val) (bit)
#define BITNUM(x) PM_BITNUM(x)
#define BITMASK(x) (1<<PM_BITNUM(x))

#define PM_SETOUT(port,bit) (DDR##port |= (1<<(bit)))
#define PM_SETIN(port,bit) (DDR##port &= ~(1<<(bit)))
#define PM_SETPULLUP(port,bit) (PORT##port |= (1<<(bit)))
#define PM_SETHIZ(port,bit) (PORT##port &= ~(1<<(bit)))
#define PM_DRIVER(port,bit,val,mode) PM_SET##mode(port,bit)
/* dmode = OUT or IN, PULLUP or HIZ */
#define DRIVER(x,mode) PM_DRIVER(x,mode)

#define PM_SETL(port,bit,dummy) (PORT##port &= ~(1<<(bit)))
#define PM_SETH(port,bit,dummy) (PORT##port |= (1<<(bit)))
#define PM_SET(port,bit,val) PM_SET##val(port,bit,dummy)
#define ON(x) PM_SET(x)
#define SET(x) PM_SETH(x)
#define CLR(x) PM_SETL(x)

#define PM_CLRL(port,bit,dummy) PM_SETH(port,bit,dummy)
#define PM_CLRH(port,bit,dummy) PM_SETL(port,bit,dummy)
#define PM_CLR(port,bit,val) PM_CLR##val(port,bit,dummy)
#define OFF(x) PM_CLR(x)

#define PM_PINH(port,bit,dummy) (PIN##port & (1<<(bit)))
#define PM_PINL(port,bit,dummy) !PM_PINH(port,bit,dummy)
#define PM_PIN(port,bit,val) PM_PIN##val(port,bit,dummy)
#define ACTIVE(x) PM_PIN(x)
#define PIN_H(x) PM_PINH(x)
#define PIN_L(x) PM_PINL(x)

#define PM_LATCHH(port,bit,dummy) (PORT##port & (1<<(bit)))
#define PM_LATCHL(port,bit,dummy) !PM_LATCHH(port,bit,dummy)
#define PM_LATCH(port,bit,val) PM_LATCH##val(port,bit,dummy)
#define LATCH(x) PM_LATCH(x)
#define LATCH_H(x) PM_LATCHH(x)
#define LATCH_L(x) PM_LATCHL(x)


#if PORT_TOGGLE_BY_PIN_WRITE
#  define PM_CPL(port,bit,val)      (PIN##port |= (1 << (bit)))
#else
#  define PM_CPL(port,bit,val)      (PORT##port ^= (1 << (bit)))
#endif

#define CPL(x) PM_CPL(x)
#define TOGGLE(x) PM_CPL(x)

#endif	// PIN_MACROS_H
