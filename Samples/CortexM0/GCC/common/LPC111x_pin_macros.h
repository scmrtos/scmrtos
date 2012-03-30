// *************************************************
// ****                                         ****
// ****        I/O bits altering macros         ****
// ****         Idea by Ascold Volkov           ****
// ****   presented in ru.embedded 18-Apr-2000  ****
// ****                                         ****
// ****   Adopted to ARM, AVR, MSP by           ****
// ****          Sergey A. Borshch, 2006-2011   ****
// ****                                         ****
// **** DRIVER idea by Alexander Redchuk (ReAl) ****
// ****                                         ****
// *************************************************
#ifndef LPC111x_PIN_MACROS__
#define LPC111x_PIN_MACROS__

// pin define examples:
//      LED on PIO1, bit 1, active level high,
//      key on PIO1, bit 6, active level low
// #define  LED    1, 1, H
// #define  KEY    1, 6, L
//
//            usage example:
// #include "pin_macros.h"
// void test()
// {
//      DRIVER(LED,OUTPUT);
//      TOGGLE(LED);        // toggle LED
//
//      if ( ACTIVE(KEY) )  // if key pressed
//      {
//          ON(LED);        // turn LED on
//      }
//
//      if ( !ACTIVE(KEY) ) // if key not pressed
//      {
//          OFF(LED);       // turn LED off
//      }
// }
#if defined(LPC111x) \
    || defined(LPC1111) || defined(LPC1112) || defined(LPC1113) || defined(LPC1114)
    #if !defined (__ASSEMBLER__)

        #define PIN_IN_L(port,bit)              (! (LPC_GPIO##port->DATA & (1UL << bit)))
        #define PIN_ON_H(port,bit)              LPC_GPIO##port->MASKED_ACCESS[1UL << bit] = 1UL << bit
        #define PIN_ON_L(port,bit)              LPC_GPIO##port->MASKED_ACCESS[1UL << bit] = 0
        #define PIN_LATCH_L(port,bit)           (! (LPC_GPIO##port->DATA & (1UL << (bit))))

        #define PIN_TOGGLE(port,bit,dummy)      LPC_GPIO##port->MASKED_ACCESS[1UL << bit] ^= (1UL << bit)
        #define PIN_DIR(port,bit,dummy)         (!! (LPC_GPIO##port->DIR & (1UL << bit)))

        // mode = OUTPUT or INPUT, PULL_UP or NO_PULL_UP|HIZ
        #define PIN_SET_OUTPUT(port,bit)        LPC_GPIO##port->DIR |= (1UL << bit)
        #define PIN_SET_INPUT(port,bit)         LPC_GPIO##port->DIR &= ~(1UL << bit)
    #endif   // C source
#endif
#endif  //  LPC111x_PIN_MACROS__
