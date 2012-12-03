/**
*  @file hw.h
*
*  Created on: 03.12.2012
*  Copyright (c) 2010 by Anton Gusev aka AHTOXA
**/

#ifndef HW_H_
#define HW_H_

#include <scmRTOS.h>
#include "pin.h"
//---------------------------------------------------------------------------
//
//      IO Pins (stm32f4discovery LEDs)
//
typedef Pin<'D', 15> BlueLED;
typedef Pin<'D', 14> RedLED;
typedef Pin<'D', 12> GreenLED;
typedef Pin<'D', 13> OrangeLED;


#endif /* HW_H_ */
