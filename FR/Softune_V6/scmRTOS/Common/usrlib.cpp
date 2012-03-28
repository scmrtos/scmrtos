//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*               
//*     PURPOSE:  User Suport Library Source
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

#include <usrlib.h>
#include <commdefs.h>

using namespace usr;

//------------------------------------------------------------------------------
//
///   Circular buffer function-member description
//
//
//
TCbuf::TCbuf(byte* const Address, const byte Size) :
        buf(Address),
        size(Size),
        count(0),
        first(0),
        last(0)
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
/// \note
/// For internal purposes.
/// Use this function with care - it doesn't perform free size check.
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
/// \note
/// For internal purposes.
/// Use this function with care - it doesn't perform free size check.
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
