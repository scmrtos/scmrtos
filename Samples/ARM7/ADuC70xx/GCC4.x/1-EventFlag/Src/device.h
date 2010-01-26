//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuC70xx (Analog Devices)
//*
//*     TOOLKIT:   arm-elf-gcc (GNU)
//*
//*     PURPOSE:   Device Definitions
//*
//*     Version: 3.10
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2010, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2010

#ifndef DEVICE_H
#define DEVICE_H

#include <commdefs.h>

//------------------------------------------------------------------------------
#if defined(ADUC7019) || defined(ADUC7020) || defined(ADUC7021)     \
    || defined(ADUC7022) || defined(ADUC7022) || defined(ADUC7024)  \
    || defined(ADUC7025) || defined(ADUC7026) || defined(ADUC7027)

    #include    <ADUC702x.h>
#else
    #error appropriate #include <ADUC70xx.h> missed here
#endif

#endif  /* DEVICE_H */
