//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuc70xx (Analog Devices)
//*
//*     TOOLKIT:   EWARM (IAR Systems)
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
//*     =================================================================
//*     scmRTOS is free software; you can redistribute it and/or
//*     modify it under the terms of the GNU General Public License
//*     as published by the Free Software Foundation; either version 2
//*     of the License, or (at your option) any later version.
//*
//*     This program is distributed in the hope that it will be useful,
//*     but WITHOUT ANY WARRANTY; without even the implied warranty of
//*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//*     GNU General Public License for more details.
//*
//*     You should have received a copy of the GNU General Public License
//*     along with this program; if not, write to the Free Software
//*     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//*     MA  02110-1301, USA.
//*     =================================================================
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//********************************************************************************
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006

#ifndef DEVICE_H
#define DEVICE_H

#include <commdefs.h>

//------------------------------------------------------------------------------
#if defined(ADuC7019)
    #include    <ioADuC7019.h>
#elif defined(ADuC7020)
    #include    <ioADuC7020.h>
#elif defined(ADuC7021)
    #include    <ioADuC7021.h>
#elif defined(ADuC7022)
    #include    <ioADuC7022.h>
#elif defined(ADuC7024)
    #include    <ioADuC7024.h>
#elif defined(ADuC7025)
    #include    <ioADuC7025.h>
#elif defined(ADuC7026)
    #include    <ioADuC7026.h>
#elif defined(ADuC7027)
    #include    <ioADuC7027.h>
#endif

#include    <ADuC_bits.h>           // until compiler hasn't its own

#endif  /* DEVICE_H */
