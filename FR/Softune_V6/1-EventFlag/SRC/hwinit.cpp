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
//*     PURPOSE:   Hardware Initialization Stuff
//*
//*     Version: 3.05
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2008, Harry E. Zhurov
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


//---------------------------------------------------------------------------
#include <commdefs.h>
#include <device_def.h>

#include <scmRTOS_TARGET_CFG.h>

#include "pins.h"


extern "C" void InitIrqLevels(void);

//---------------------------------------------------------------------------
extern "C" void HardwareInit()
{

    InitIrqLevels();                            /* init interrupts   */
    __set_il(20);                               /* allow all levels  */
    __EI();                                     /* enable interrupts */

    direct(LED1, O);
    direct(LED2, O);

    off(LED1);
    off(LED2);

    // Setup Timer#2
    TMCSR2=0;
    TMRLR2=50000-1;
    TMCSR2_CSL1=1;
    TMCSR2_CSL0=0;
    TMCSR2_RELD=1;
    TMCSR2_INTE=1;
    TMCSR2_UF=0;
    TMCSR2_CNTE=1;
    TMCSR2_TRG=1;

    ICR10 = 29;     // set interrupt level for Timer#2 to 29
}
//---------------------------------------------------------------------------
