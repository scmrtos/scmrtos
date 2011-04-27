/*----------------------------------------------------------------------------------------------
 *	pin_macros.h  (ADuC70xx/arm-elf-gcc)
 *----------------------------------------------------------------------------------------------
 *
 * Author:  Oleksandr Redchuk aka ReAl (real@real.kiev.ua)
 *
 * Description: port bits access macros for AVR uC family (avr-gcc compiler)
 *
 * Based on macros by Ascold Volkov, Andy Mozzevilov, Aleksey Musin
 *----------------------------------------------------------------------------------------------
 * ported to ADuC70xx by Sergey A. Borshch
 */

/*
examples

#define Pin1 1,2,H
#define Pin2 1,3,L
             ^ ^ ^
     GPIO port | |
             bit \active level

void main(void)
{
    DRIVER(Pin1,OUT);       //as output
    DRIVER(Pin2,IN);        //as input
    DRIVER(Pin2,PULLUP);    //with pullup
    ON(Pin1);
    if (ACTIVE(Pin2)) OFF(Pin1);
    if (LATCH(Pin1)) { //if active level presents on Pin1 for drive something
        //do something
    }
}
*/

#ifndef PIN_MACROS_H
#define PIN_MACROS_H

#if	defined(__GNUC__) &&                                            \
    ( defined(ADUC7019) || defined(ADUC7020) || defined(ADUC7021)   \
    || defined(ADUC7022) || defined(ADUC7022) || defined(ADUC7024)  \
    || defined(ADUC7025) || defined(ADUC7026) || defined(ADUC7027)  \
    )

#define PM_BITNUM(port,bit,val)     (bit)
#define BITNUM(x)                   PM_BITNUM(x)
#define BITMASK(x)                  (1 << PM_BITNUM(x))

#define PM_SETOUT(port,bit)         (GP##port##DAT |= (1 << ((bit) + 24)))
#define PM_SETIN(port,bit)          (GP##port##DAT &= ~(1 << ((bit) + 24)))
#define PM_SETPULLUP(port,bit)      (GP##port##PAR &= ~(1 << ((bit) * 4)))
#define PM_SETHIZ(port,bit)         (GP##port##PAR |= (1 << ((bit) * 4)))
#define PM_DRIVER(port,bit,val,mode) PM_SET##mode(port,bit)
/* dmode = OUT or IN, PULLUP or HIZ */
#define DRIVER(x,mode)              PM_DRIVER(x,mode)

#define PM_SETL(port,bit,dummy)     (GP##port##CLR = (1 << ((bit) + 16)))
#define PM_SETH(port,bit,dummy)     (GP##port##SET = (1 << ((bit) + 16)))
#define PM_SET(port,bit,val)        PM_SET##val(port,bit,dummy)
#define ON(x)                       PM_SET(x)
#define SET(x)                      PM_SETH(x)
#define CLR(x)                      PM_SETL(x)

#define PM_CLRL(port,bit,dummy)     PM_SETH(port,bit,dummy)
#define PM_CLRH(port,bit,dummy)     PM_SETL(port,bit,dummy)
#define PM_CLR(port,bit,val)        PM_CLR##val(port,bit,dummy)
#define OFF(x)                      PM_CLR(x)

#define PM_PINL(port,bit,dummy)     (!(GP##port##DAT & (1 << (bit))))
#define PM_PINH(port,bit,dummy)     (!PM_PINL(port,bit,dummy))
#define PM_PIN(port,bit,val)        PM_PIN##val(port,bit,dummy)
#define ACTIVE(x)                   PM_PIN(x)
#define PIN_H(x)                    PM_PINH(x)
#define PIN_L(x)                    PM_PINL(x)

#define PM_LATCHH(port,bit,dummy)   (GP##port##DAT & (1 << ((bit) + 16))
#define PM_LATCHL(port,bit,dummy)   !PM_LATCHH(port,bit,dummy)
#define PM_LATCH(port,bit,val)      PM_LATCH##val(port,bit,dummy)
#define LATCH(x)                    PM_LATCH(x)
#define LATCH_H(x)                  PM_LATCHH(x)
#define LATCH_L(x)                  PM_LATCHL(x)

#define PM_CPL(port,bit,val)        (GP##port##DAT ^= (1 << ((bit) + 16)))

#define CPL(x)                      PM_CPL(x)
#define TOGGLE(x)                   PM_CPL(x)

#endif  // __GNUC__

#endif	// PIN_MACROS_H
