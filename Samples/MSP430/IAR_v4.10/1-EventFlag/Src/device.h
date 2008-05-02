//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   EW430 (IAR Systems)
//*
//*     PURPOSE:   Device Definitions
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date$
//*
//*     Copyright (c) 2003-2006, Harry E. Zhurov
//*
//*     Permission is hereby granted, free of charge, to any person 
//*     obtaining  a copy of this software and associated documentation 
//*     files (the "Software"), to deal in the Software without restriction, 
//*     including without limitation the rights to use, copy, modify, merge, 
//*     publish, distribute, sublicense, and/or sell copies of the Software, 
//*     and to permit persons to whom the Software is furnished to do so, 
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included 
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//******************************************************************************

#ifndef DEVICE_H
#define DEVICE_H

#include <commdefs.h>

//------------------------------------------------------------------------------
#if defined(F110) || defined(F112)
#include <msp430x11x.h>
#endif
//------------------------------------------------------------------------------
#if defined(F1101) || defined(F1111) || defined(F1121)
#include <msp430x11x1.h>
#endif
//------------------------------------------------------------------------------
#if defined(F1122) || defined(F1132)
#include <msp430x11x2.h>
#endif
//------------------------------------------------------------------------------
#if defined(F122) || defined(F123)
#include <msp430x12x.h>
#endif
//------------------------------------------------------------------------------
#if defined(F1222) || defined(F1232)
#include <msp430x12x2.h>
#endif
//------------------------------------------------------------------------------
#if defined(F133) || defined(F134) || defined(F135)
#include <msp430x13x.h>
#endif
//------------------------------------------------------------------------------
#if defined(F147) || defined(F148) || defined(F149)
#include <msp430x14x.h>
#endif
//------------------------------------------------------------------------------
#if defined(F167) || defined(F168) || defined(F169)
#include <msp430x16x.h>
#endif
//------------------------------------------------------------------------------


#endif  /* DEVICE_H */
