//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   avr-gcc (GNU)
//*
//*     PURPOSE:   avr-gcc Port Test File
//*                Sample '4-Debug' debug process module
//*
//*     Version: 4.00
//*
//*     $Revision: 404 $
//*     $Date:: 2011-05-08 #$
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007-2012

#ifndef  DEBUG_H
#define  DEBUG_H

#include <scmRTOS.h>

//------------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 150> TProc1;
typedef OS::process<OS::pr1, 100> TProc2;
typedef OS::process<OS::pr2, 100> TProc3;
typedef OS::process<OS::pr3, 200> TDebugProc;

// Explicit specialization of function must precede its first use. But ...
// avoid GCC bug ( http://gcc.gnu.org/bugzilla/show_bug.cgi?id=15867 )
#if 0
namespace OS {
    template<> void TProc1::exec();
    template<> void TProc2::exec();
    template<> void TProc3::exec();
    template<> void TDebugProc::exec();
} // namespace OS
#endif


//------------------------------------------------------------------------------

#endif // DEBUG_H
