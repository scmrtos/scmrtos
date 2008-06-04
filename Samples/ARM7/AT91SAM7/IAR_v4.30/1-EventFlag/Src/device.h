//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AT91SAM7xxx (Atmel)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Device Definitions
//*
//*     Version:   3.00-beta
//*
//*     $Revision$
//*     $Date::             $
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006

#ifndef DEVICE_H
#define DEVICE_H

#include <commdefs.h>

//------------------------------------------------------------------------------
#if defined(AT91SAM7S16)
    #include    <ioAT91SAM7S16.h>
#elif defined(AT91SAM7S161)
    #include    <ioAT91SAM7S161.h>
#elif defined(AT91SAM7S32)
    #include    <ioAT91SAM7S32.h>
#elif defined(AT91SAM7S321)
    #include    <ioAT91SAM7S321.h>
#elif defined(AT91SAM7S64)
    #include    <ioAT91SAM7S64.h>
#elif defined(AT91SAM7S128)
    #include    <ioAT91SAM7S128.h>
#elif defined(AT91SAM7S256)
    #include    <ioAT91SAM7S256.h>
#elif defined(AT91SAM7S512)
    #include    <ioAT91SAM7S512.h>
#elif defined(AT91SAM7SE32)
    #include    <ioAT91SAM7SE32.h>
#elif defined(AT91SAM7SE128)
    #include    <ioAT91SAM7SE128.h>
#elif defined(AT91SAM7SE256)
    #include    <ioAT91SAM7SE256.h>
#elif defined(AT91SAM7SE512)
    #include    <ioAT91SAM7SE512.h>
#elif defined(AT91SAM7X128)
    #include    <ioAT91SAM7X128.h>
#elif defined(AT91SAM7X256)
    #include    <ioAT91SAM7X256.h>
#elif defined(AT91SAM7X512)
    #include    <ioAT91SAM7X512.h>
#elif defined(AT91SAM7XC128)
    #include    <ioAT91SAM7XC128.h>
#elif defined(AT91SAM7XC256)
    #include    <ioAT91SAM7XC256.h>
#elif defined(AT91SAM7XC512)
    #include    <ioAT91SAM7XC512.h>
#endif

#endif  /* DEVICE_H */
