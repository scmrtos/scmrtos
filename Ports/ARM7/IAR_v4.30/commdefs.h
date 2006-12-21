//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM7
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Common Type Definitions
//*
//*     Version:   3.00-beta
//*
//*     $Revision: 53 $
//*     $Date: 2006-12-19 16:09:53 +0200 (Вт, 19 дек 2006) $
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

#ifndef COMMONDEFS_H
#define COMMONDEFS_H


#ifndef __IAR_SYSTEMS_ASM__

typedef unsigned char  byte;
typedef signed char    sbyte;
typedef unsigned short word;
typedef unsigned long  dword;

typedef volatile byte  sfr_byte;
typedef volatile word  sfr_word;

#endif // __IAR_SYSTEMS_ASM__

#endif // COMMONDEFS_H

//-----------------------------------------------------------------------------

/*============================================================================*/

