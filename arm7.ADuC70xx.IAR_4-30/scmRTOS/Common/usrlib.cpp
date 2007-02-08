//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*               
//*     PURPOSE:  User Suport Library Source
//*               
//*     Version:  3.00-beta
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

#include <usrlib.h>
#include <commdefs.h>

using namespace usr;

//------------------------------------------------------------------------------
//
//    Circular buffer function-member description
//
//
//
TCbuf::TCbuf(byte* const Address, const byte Size) :
        buf(Address),
        size(Size),
        first(0),
        last(0),
    count(0)
{
}
//------------------------------------------------------------------------------
bool TCbuf::write(const byte* data, const byte Count)
{
    if( Count > (size - count) )
        return false;

    for(byte i = 0; i < Count; i++)
        push(*(data++));

    return true;
}
//------------------------------------------------------------------------------
void TCbuf::read(byte* data, const byte Count)
{
    byte N = Count <= count ? Count : count;

    for(byte i = 0; i < N; i++)
        data[i] = pop();
}
//------------------------------------------------------------------------------
byte TCbuf::get_byte(const byte index) const
{
    byte x = first + index;

    if(x < size)
        return buf[x];
    else
        return buf[x - size];
}

//------------------------------------------------------------------------------
bool TCbuf::put(const byte item)
{
    if(count == size)
        return false;

    push(item);
    return true;
}
//------------------------------------------------------------------------------
byte TCbuf::get()
{
    if(count)
        return pop();
    else
        return 0;
}
//------------------------------------------------------------------------------
//
//  DESCRIPTON: For internal purposes
//              Use this function with care - it doesn't perform free size check
//
void TCbuf::push(const byte item)
{
    buf[last] = item;
    last++;
    count++;

    if(last == size)
        last = 0;
}
//------------------------------------------------------------------------------
//
//  DESCRIPTON: For internal purposes
//              Use this function with care - it doesn't perform count check
//
byte TCbuf::pop()
{
    byte item = buf[first];

    count--;
    first++;
    if(first == size)
        first = 0;

    return item;
}
//------------------------------------------------------------------------------
