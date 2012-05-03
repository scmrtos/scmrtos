/*----------------------------------------------------------------------------------------------
 *	pin_macros.h  (AVR/avr-gcc)
 *----------------------------------------------------------------------------------------------
 *
 * Author:  Oleksandr Redchuk aka ReAl (real@real.kiev.ua)
 *
 * Description: port bits access macros for AVR uC family (avr-gcc compiler)
 *
 * Based on macros by Ascold Volkov presented in RU.EMBEDDED 18-Apr-2000
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

#if  defined(__AVR_AT90PWM1__)  \
  || defined(__AVR_AT90PWM2__)  \
  || defined(__AVR_AT90PWM2B__) \
  || defined(__AVR_AT90PWM3__)  \
  || defined(__AVR_AT90PWM3B__) \
  || defined(__AVR_AT90PWM216__) \
  || defined(__AVR_AT90PWM316__) \
  || defined(__AVR_AT90PWM81__)  \
  || defined(__AVR_AT90USB82__)  \
  || defined(__AVR_AT90USB162__) \
  || defined(__AVR_ATmega8U2__)  \
  || defined(__AVR_ATmega16U2__) \
  || defined(__AVR_ATmega32U2__) \
  || defined(__AVR_ATmega16U4__) \
  || defined(__AVR_ATmega32U4__) \
  || defined(__AVR_ATmega32U6__) \
  || defined(__AVR_AT90USB646__) \
  || defined(__AVR_AT90USB647__) \
  || defined(__AVR_AT90USB1286__) \
  || defined(__AVR_AT90USB1287__) \
  || defined(__AVR_AT90CAN32__)  \
  || defined(__AVR_AT90CAN64__)  \
  || defined(__AVR_AT90CAN128__) \
  || defined(__AVR_ATmega16M1__) \
  || defined(__AVR_ATmega32M1__) \
  || defined(__AVR_ATmega64M1__) \
  || defined(__AVR_ATmega32C1__) \
  || defined(__AVR_ATmega64C1__) \
  || defined(__AVR_ATmega48__)  || defined(__AVR_ATmega48A__) \
  || defined(__AVR_ATmega88__)  || defined(__AVR_ATmega88A__) \
  || defined(__AVR_ATmega168__) || defined(__AVR_ATmega168A__) \
  || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) \
  || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) \
  || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168PA__) \
  || defined(__AVR_ATmega328__)  \
  || defined(__AVR_ATmega328P__) \
  || defined(__AVR_ATmega640__)  \
  || defined(__AVR_ATmega1280__) \
  || defined(__AVR_ATmega1281__) \
  || defined(__AVR_ATmega2560__) \
  || defined(__AVR_ATmega2561__) \
  || defined(__AVR_ATmega164A__) \
  || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__) \
  || defined(__AVR_ATmega324A__) \
  || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) \
  || defined(__AVR_ATmega644__)  || defined(__AVR_ATmega644A__) \
  || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) \
  || defined(__AVR_ATmega1284P__) \
  || defined(__AVR_ATmega165__)  || defined(__AVR_ATmega165A__) \
  || defined(__AVR_ATmega165P__) || defined(__AVR_ATmega165PA__) \
  || defined(__AVR_ATmega325__)  || defined(__AVR_ATmega325A__)  \
  || defined(__AVR_ATmega325P__) \
  || defined(__AVR_ATmega3250__) \
  || defined(__AVR_ATmega3250P__) \
  || defined(__AVR_ATmega645__)  || defined(__AVR_ATmega645A__) \
  || defined(__AVR_ATmega645P__) \
  || defined(__AVR_ATmega6450__) || defined(__AVR_ATmega6450A__) \
  || defined(__AVR_ATmega6450P__) \
  || defined(__AVR_ATmega169__)  || defined(__AVR_ATmega169A__) \
  || defined(__AVR_ATmega169P__) || defined(__AVR_ATmega169PA__) \
  || defined(__AVR_ATmega329__)  || defined(__AVR_ATmega329A__) \
  || defined(__AVR_ATmega329P__) || defined(__AVR_ATmega329PA__) \
  || defined(__AVR_ATmega3290__) \
  || defined(__AVR_ATmega3290P__) \
  || defined(__AVR_ATmega649__)   || defined(__AVR_ATmega649A__) \
  || defined(__AVR_ATmega6490__)  || defined(__AVR_ATmega6490A__) \
  || defined(__AVR_ATmega6490P__) \
  || defined(__AVR_ATmega649P__)  \
  || defined(__AVR_ATmega406__) \
  || defined(__AVR_ATmega8HVA__) \
  || defined(__AVR_ATmega16HVA__) \
  || defined(__AVR_ATmega16HVA2__) \
  || defined(__AVR_ATmega16HVB__) \
  || defined(__AVR_ATmega32HVB__) \
  || defined(__AVR_ATmega64HVE__) \
  || defined(__AVR_ATtiny261__) || defined(__AVR_ATtiny261A__) \
  || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny461A__) \
  || defined(__AVR_ATtiny861__) || defined(__AVR_ATtiny861A__) \
  || defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny2313A__) \
  || defined(__AVR_ATtiny4313__) \
  || defined(__AVR_ATtiny13__) || defined(__AVR_ATtiny13A__) \
  || defined(__AVR_ATtiny25__) \
  || defined(__AVR_ATtiny45__) \
  || defined(__AVR_ATtiny85__) \
  || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny24A__) \
  || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny44A__) \
  || defined(__AVR_ATtiny84__) \
  || defined(__AVR_ATtiny43U__) \
  || defined(__AVR_ATtiny48__) || defined(__AVR_ATtiny88__) \
  || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#  define PORT_TOGGLE_BY_PIN_WRITE 1
#else
#  define PORT_TOGGLE_BY_PIN_WRITE 0
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

