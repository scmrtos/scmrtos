//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STM8 (STMicroelectronics)
//*
//*     TOOLKIT:   EWSTM8 (IAR Systems)
//*
//*     PURPOSE:   STM8/IAR Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision: 401 $
//*     $Date:: 2011-05-02 #$
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
//*     STM8/IAR port by Oleksandr O. Redchuk, Copyright (c) 2011-2012

#ifndef STM8_TARGET_H
#define STM8_TARGET_H

// stm8_target.h -- Standard file name for both STM8S and STM8L StdPeriph_Driver libraries
// Switching between the libraries can be done by changing include path
// from STM8S_StdPeriph_Driver to STM8L15x_StdPeriph_Driver
 
#include "stm8s_conf.h"

#define TARGET_STM8S

#endif // STM8_TARGET_H

