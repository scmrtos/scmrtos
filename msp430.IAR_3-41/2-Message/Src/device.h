//********************************************************************************
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
