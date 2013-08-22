/*
 **
 ** pinmux_config.c source file generated on Август 21, 2013 at 13:57:16.	
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
 ** UART0 (TX, RX, RTS, CTS)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PD07, PD08, PD09, PD10
 */

#include <sys/platform.h>
#include <stdint.h>

#define UART0_TX_PORTD_MUX  ((uint16_t) ((uint16_t) 1<<14))
#define UART0_RX_PORTD_MUX  ((uint32_t) ((uint32_t) 1<<16))
#define UART0_RTS_PORTD_MUX  ((uint32_t) ((uint32_t) 1<<18))
#define UART0_CTS_PORTD_MUX  ((uint32_t) ((uint32_t) 1<<20))

#define UART0_TX_PORTD_FER  ((uint16_t) ((uint16_t) 1<<7))
#define UART0_RX_PORTD_FER  ((uint32_t) ((uint32_t) 1<<8))
#define UART0_RTS_PORTD_FER  ((uint32_t) ((uint32_t) 1<<9))
#define UART0_CTS_PORTD_FER  ((uint32_t) ((uint32_t) 1<<10))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *pREG_PORTD_MUX = UART0_TX_PORTD_MUX | UART0_RX_PORTD_MUX
     | UART0_RTS_PORTD_MUX | UART0_CTS_PORTD_MUX;

    /* PORTx_FER registers */
    *pREG_PORTD_FER = UART0_TX_PORTD_FER | UART0_RX_PORTD_FER
     | UART0_RTS_PORTD_FER | UART0_CTS_PORTD_FER;
    return 0;
}

