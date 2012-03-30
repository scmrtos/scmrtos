#ifndef PIN_MACROS__
#define PIN_MACROS__
#if defined(AT91SAM7) \
    || defined(AT91SAM7S32) || defined(AT91SAM7S321) || defined(AT91SAM7S64) || defined(AT91SAM7S128) \
    || defined(AT91SAM7S256) || defined(AT91SAM7S512) \
    || defined(AT91SAM7SE32) || defined(AT91SAM7SE256) || defined(AT91SAM7SE512) \
    || defined(AT91SAM7X128) || defined(AT91SAM7X256) || defined(AT91SAM7X512) \
    || defined(AT91SAM7XC128) || defined(AT91SAM7XC256) || defined(AT91SAM7XC512) \
    || defined(AT91SAM7A3)
    #include    "SAM7_pin_macros.h"
#elif defined(LPC111x) \
    || defined(LPC1111) || defined(LPC1112) || defined(LPC1113) || defined(LPC1114)
    #include    "LPC111x_pin_macros.h"
#elif defined(__AVR__)
    #include    "AVR_pin_macros.h"
#endif
    // Cross - platform
    #if !defined (__ASSEMBLER__)
        #define PIN_IN_H(port,bit)                  (!PIN_IN_L(port,bit))
        #define PIN_LATCH_H(port,bit)               (!PIN_LATCH_L(port,bit))
    #endif   // C source

    #define PIN_ON(port,bit,val)                PIN_ON_##val(port,bit)
    #define PIN_OFF(port,bit,val)               PIN_OFF_##val(port,bit)
    #define PIN_OFF_L(port,bit)                 PIN_ON_H(port,bit)
    #define PIN_OFF_H(port,bit)                 PIN_ON_L(port,bit)
    #define PIN_IN(port,bit,val)                PIN_IN_H(port,bit)
    #define PIN_ACTIVE(port,bit,val)            PIN_IN_##val(port,bit)
    #define PIN_LATCH(port,bit,val)             PIN_LATCH_##val(port,bit)

    #define PIN_BITNUM_(port, bit, val)         (bit)
    #define PIN_BITNUM(pin)                     PIN_BITNUM_(pin)
    #define PIN_BITMASK(pin)                    (1<<PIN_BITNUM_(pin))

    // read pin
    #define ACTIVE(pin)                         PIN_ACTIVE(pin)
    #define PIN(pin)                            PIN_IN(pin)
    // read pin latch
    #define LATCH(x)                            PIN_LATCH(x)

    // set output
    #define ON(pin)                             PIN_ON(pin)
    #define OFF(pin)                            PIN_OFF(pin)
    #define SET(pin)                            PIN_ON_H(pin)
    #define CLR(pin)                            PIN_ON_L(pin)
    #define TOGGLE(pin)                         PIN_TOGGLE(pin)

    // get pin direction
    #define DIR_OUTPUT(x)                       PIN_DIR(x)
    #define DIR_INPUT(x)                        (!PIN_DIR(x))
    // set pin mode
    #define DRIVER(pin, mode)                   PIN_DRIVER(pin, mode)
    #define PIN_DRIVER(port, bit, val, mode)    PIN_SET_##mode(port,bit)

#endif  //  PIN_MACROS__
