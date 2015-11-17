//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   arm-(elf/none-eabi)-gcc (GNU)
//*
//*     PURPOSE:   Target Dependent Stuff Header. Target chip depended file selector
//*
//*     Version: 5.0.0
//*
//*
//*     Copyright (c) 2003-2015, scmRTOS Team
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
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2015

#ifndef TARGET_CORE_H__
#define TARGET_CORE_H__

#define MODE_USER       0x10
#define MODE_FIQ        0x11
#define MODE_IRQ        0x12
#define MODE_SVC        0x13
#define MODE_ABORT      0x17
#define MODE_UND        0x1B
#define MODE_SYS        0x1F

#define NIRQ            (1<<7)
#define NFIQ            (1<<6)
#define THUMB           (1<<5)

// bug present in gcc 4.2.3 and fixed in gcc 4.3.3.
// I don't know about intermediate versions, so I check for 4.3.3
#if (__GNUC__ <= 4) && (__GNUC_MINOR__ < 3) && (__GNUC_PATCHLEVEL__ < 3)
    // see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=16634
    #define GCC_IRQ_PATCH_REQUIRED
#endif

#if defined(AT91SAM7) \
    | defined(AT91SAM7S16) | defined(AT91SAM7S161) \
    | defined(AT91SAM7S32) | defined(AT91SAM7S321) \
    | defined(AT91SAM7S64) | defined(AT91SAM7S128) | defined(AT91SAM7S256) | defined(AT91SAM7S512) \
    | defined(AT91SAM7SE32) | defined(AT91SAM7SE128) | defined(AT91SAM7SE256) | defined(AT91SAM7SE512) \
    | defined(AT91SAM7X128) | defined(AT91SAM7X256) | defined(AT91SAM7X512) \
    | defined(AT91SAM7XC128) | defined(AT91SAM7XC256) | defined(AT91SAM7XC512)
    #include    <target_at91sam7.h>
#elif defined(LPC2119) | defined(LPC2129) | defined(LPC2212) | defined(LPC2214) | defined(LPC2148)
    #include    <target_lpc2xxx.h>
#elif defined(ADUC7019) | defined(ADUC7020) | defined(ADUC7021) | defined(ADUC7022) \
    | defined(ADUC7024) | defined(ADUC7025) | defined(ADUC7026) | defined(ADUC7027) \
	| defined(ADUC7060) | defined(ADUC7061)
    #include    <target_aduc70xx.h>
#endif

#endif  // TARGET_CORE_H__
