/*
 **
 ** pinmux_config.c source file generated on Èþëü 3, 2013 at 11:38:56.	
 **
 ** Copyright (C) 2000-2013 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in 
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** TIMER0 (TMR0)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PE14
 */

#include <sys/platform.h>
#include <stdint.h>

#define TIMER0_TMR0_PORTE_MUX  ((uint32_t) ((uint32_t) 2<<28))

#define TIMER0_TMR0_PORTE_FER  ((uint32_t) ((uint32_t) 1<<14))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *pREG_PORTE_MUX = TIMER0_TMR0_PORTE_MUX;

    /* PORTx_FER registers */
    *pREG_PORTE_FER = TIMER0_TMR0_PORTE_FER;
    return 0;
}

