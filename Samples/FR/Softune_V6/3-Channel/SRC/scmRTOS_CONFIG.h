//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: FR (Fujitsu)
//*
//*     TOOLKIT:   Softune Workbench V6 (Fujitsu)
//*
//*     PURPOSE:   Project Level Configuration
//*
//*     Version:   3.00-beta
//*
//*     $Revision: 1 $
//*     $Date: 2006-12-15 12:51:04 +0500 (Пт, 15 дек 2006) $
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
//********************************************************************************

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

#include <commdefs.h>

typedef dword TTimeout;

//------------------------------------------------------------------------------
//
///    Specify scmRTOS Process Count. Must be less then 31
//
//
#define  scmRTOS_PROCESS_COUNT              3

//-----------------------------------------------------------------------------
//
///    scmRTOS System Timer Tick Counter Enable
//
//
#define scmRTOS_SYSTEM_TICKS_ENABLE         1


//-----------------------------------------------------------------------------
//
///    scmRTOS System Timer Hook.
//
//
#define scmRTOS_SYSTIMER_HOOK_ENABLE        0

//-----------------------------------------------------------------------------
//
///    scmRTOS Idle Process Hook.
//
//
#define scmRTOS_IDLE_HOOK_ENABLE            1

//-----------------------------------------------------------------------------
//
///    scmRTOS Idle Process Stack size (in bytes)
//
//
#define scmRTOS_IDLE_PROCESS_STACK_SIZE     96

#endif // scmRTOS_CONFIG_H
