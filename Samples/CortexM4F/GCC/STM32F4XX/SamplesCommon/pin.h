/**
*  GPIO pin manipulation class template for STM32 series.
*
*  Copyright (c) 2009-2012 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*  Inspired by AVR macros from Askold Volkov
*
* USAGE: see corresponding include file
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED

#if (defined STM32F2XX) || (defined STM32F4XX)
#  include "pin_stm32F4xx.h"
#else
#  include "pin_stm32F1xx.h"
#endif

#endif // PIN_H_INCLUDED
