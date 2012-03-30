/*----------------------------------------------------------------------------------------------
 *	pin_macros.h  (AVR/IAR)
 *----------------------------------------------------------------------------------------------
 *
 * Author:  Oleksandr Redchuk aka ReAl (real@real.kiev.ua)
 *
 * Description: port bits access macros for AVR uC family (IAR compiler)
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

#ifndef __IAR_SYSTEMS_ICC__
#error "This file should only be compiled with IAR C/C++ Compiler"
#endif // __IAR_SYSTEMS_ICC__

#ifndef PIN_MACROS_H
#define PIN_MACROS_H

#if  defined(__AT90PWM1__)  \
  || defined(__AT90PWM2__)  \
  || defined(__AT90PWM2B__) \
  || defined(__AT90PWM3__)  \
  || defined(__AT90PWM3B__) \
  || defined(__AT90PWM216__) \
  || defined(__AT90PWM316__) \
  || defined(__AT90PWM81__)  \
  || defined(__AT90USB82__)  \
  || defined(__AT90USB162__) \
  || defined(__ATmega8U2__)  \
  || defined(__ATmega16U2__) \
  || defined(__ATmega32U2__) \
  || defined(__ATmega16U4__) \
  || defined(__ATmega32U4__) \
  || defined(__ATmega32U6__) \
  || defined(__AT90USB646__) \
  || defined(__AT90USB647__) \
  || defined(__AT90USB1286__) \
  || defined(__AT90USB1287__) \
  || defined(__AT90CAN32__)  \
  || defined(__AT90CAN64__)  \
  || defined(__AT90CAN128__) \
  || defined(__ATmega16M1__) \
  || defined(__ATmega32M1__) \
  || defined(__ATmega64M1__) \
  || defined(__ATmega32C1__) \
  || defined(__ATmega64C1__) \
  || defined(__ATmega48__)  || defined(__ATmega48A__) \
  || defined(__ATmega88__)  || defined(__ATmega88A__) \
  || defined(__ATmega168__) || defined(__ATmega168A__) \
  || defined(__ATmega48P__) || defined(__ATmega48PA__) \
  || defined(__ATmega88P__) || defined(__ATmega88PA__) \
  || defined(__ATmega168P__) || defined(__ATmega168PA__) \
  || defined(__ATmega328__)  \
  || defined(__ATmega328P__) \
  || defined(__ATmega640__)  \
  || defined(__ATmega1280__) \
  || defined(__ATmega1281__) \
  || defined(__ATmega2560__) \
  || defined(__ATmega2561__) \
  || defined(__ATmega164A__) \
  || defined(__ATmega164P__) || defined(__ATmega164PA__) \
  || defined(__ATmega324A__) \
  || defined(__ATmega324P__) || defined(__ATmega324PA__) \
  || defined(__ATmega644__)  || defined(__ATmega644A__) \
  || defined(__ATmega644P__) || defined(__ATmega644PA__) \
  || defined(__ATmega1284P__) \
  || defined(__ATmega165__)  || defined(__ATmega165A__) \
  || defined(__ATmega165P__) || defined(__ATmega165PA__) \
  || defined(__ATmega325__)  || defined(__ATmega325A__)  \
  || defined(__ATmega325P__) \
  || defined(__ATmega3250__) \
  || defined(__ATmega3250P__) \
  || defined(__ATmega645__)  || defined(__ATmega645A__) \
  || defined(__ATmega645P__) \
  || defined(__ATmega6450__) || defined(__ATmega6450A__) \
  || defined(__ATmega6450P__) \
  || defined(__ATmega169__)  || defined(__ATmega169A__) \
  || defined(__ATmega169P__) || defined(__ATmega169PA__) \
  || defined(__ATmega329__)  || defined(__ATmega329A__) \
  || defined(__ATmega329P__) || defined(__ATmega329PA__) \
  || defined(__ATmega3290__) \
  || defined(__ATmega3290P__) \
  || defined(__ATmega649__)   || defined(__ATmega649A__) \
  || defined(__ATmega6490__)  || defined(__ATmega6490A__) \
  || defined(__ATmega6490P__) \
  || defined(__ATmega649P__)  \
  || defined(__ATmega406__) \
  || defined(__ATmega8HVA__) \
  || defined(__ATmega16HVA__) \
  || defined(__ATmega16HVA2__) \
  || defined(__ATmega16HVB__) \
  || defined(__ATmega32HVB__) \
  || defined(__ATmega64HVE__) \
  || defined(__ATtiny261__) || defined(__ATtiny261A__) \
  || defined(__ATtiny461__) || defined(__ATtiny461A__) \
  || defined(__ATtiny861__) || defined(__ATtiny861A__) \
  || defined(__ATtiny2313__) || defined(__ATtiny2313A__) \
  || defined(__ATtiny4313__) \
  || defined(__ATtiny13__) || defined(__ATtiny13A__) \
  || defined(__ATtiny25__) \
  || defined(__ATtiny45__) \
  || defined(__ATtiny85__) \
  || defined(__ATtiny24__) || defined(__ATtiny24A__) \
  || defined(__ATtiny44__) || defined(__ATtiny44A__) \
  || defined(__ATtiny84__) \
  || defined(__ATtiny43U__) \
  || defined(__ATtiny48__) || defined(__ATtiny88__) \
  || defined(__ATtiny87__) || defined(__ATtiny167__)
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
