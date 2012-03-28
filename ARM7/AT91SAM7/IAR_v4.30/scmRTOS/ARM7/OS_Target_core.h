//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Target chip depended file selector
//*
//*     Version: 3.11
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2012

#ifndef TARGET_CORE_H__
#define TARGET_CORE_H__

#if defined(AT91SAM7) \
    | defined(AT91SAM7S16) | defined(AT91SAM7S161) \
    | defined(AT91SAM7S32) | defined(AT91SAM7S321) \
    | defined(AT91SAM7S64) | defined(AT91SAM7S128) | defined(AT91SAM7S256) | defined(AT91SAM7S512) \
    | defined(AT91SAM7SE32) | defined(AT91SAM7SE128) | defined(AT91SAM7SE256) | defined(AT91SAM7SE512) \
    | defined(AT91SAM7X128) | defined(AT91SAM7X256) | defined(AT91SAM7X512) \
    | defined(AT91SAM7XC128) | defined(AT91SAM7XC256) | defined(AT91SAM7XC512)
    #include    <Target_AT91SAM7.h>
#elif defined(LPC2119) | defined(LPC2129) | defined(LPC2212) | defined(LPC2214)
    #include    <Target_LPC2xxx.h>
#elif defined(ADuC7019) | defined(ADuC7020) | defined(ADuC7021) | defined(ADuC7022) \
    | defined(ADuC7024) | defined(ADuC7025) | defined(ADuC7026) | defined(ADuC7027)
    #include    <Target_ADuC70xx.h>
#elif defined(STR710) | defined(STR711) | defined(STR712) | defined(STR715)
    #include    <Target_STR71x.h>
#endif

#endif  // TARGET_CORE_H__
