//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*               
//*     PURPOSE:  User Suport Library Header
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

#ifndef USRLIB_H
#define USRLIB_H

#include <commdefs.h>

//------------------------------------------------------------------------------
//
//  DESCRIPTON: user namespace for some useful types and functions
//
//
namespace usr
{
    //------------------------------------------------------------------------------
    //
    //     The Circular Buffer
    //
    //         Byte-wide FIFO.
    //
    //         Allows to:
    //             add byte,
    //             get byte,
    //             write bytes from array,
    //             read bytes to array,
    //             and some other service actions.
    //
    class TCbuf
    {
    public:
        TCbuf(byte* const Address, const byte Size);
        bool write(const byte* data, const byte Count);
        void read(byte* const data, const byte Count);
        byte get_count() const { return count; }
        byte get_free_size() const { return size - count; }
        byte get_byte(const byte index) const;
        void clear() { count = 0; last = first; }
        bool put(const byte item);
        byte get();

    private:
       //------------------------------------------------------------------------------
       //
       //  DESCRIPTON: For internal purposes
       //
        void push(const byte item); // Use this function with care - it doesn't perform free size check
        byte pop();                 // Use this function with care - it doesn't perform count check
       //------------------------------------------------------------------------------

    private:
        byte* buf;
        byte  size;
        volatile byte count;
        byte  first;
        byte  last;
    };
    //------------------------------------------------------------------------------



    //-----------------------------------------------------------------------
    //
    //     The Ring Buffer Template
    //
    //         Carries out FIFO functionality for
    //         arbitrary data types
    //
    //         Allows to:
    //             add item to back (default),
    //             add item to front,
    //             get item at front (default),
    //             get item from back,
    //             write items from array,
    //             read items to array and some other actions
    //
    //
    //
    template<typename T, word size, class S = byte>
    class ring_buffer
    {
    public:
        ring_buffer() : Size(size), Count(0), First(0), Last(0) { }

        //----------------------------------------------------------------
        //
        //    Data transfer functions
        //
        bool write(const T* data, const S cnt);
        void read(T* const data, const S cnt);

        bool push_back(const T item);
        bool push_front(const T item);

        T pop_front();
        T pop_back();

        bool push(const T item) { return push_back(item); }
        T pop() { return pop_front(); }

        //----------------------------------------------------------------
        //
        //    Service functions
        //
        S get_count() const { return Count; }
        S get_free_size() const { return Size - Count; }
        T& operator[](const S index);
        void flush() { Count = 0; Last = First; }

    private:
        //--------------------------------------------------------------
        //  DESCRIPTON: For internal purposes
        //              Use this functions with care: it don't perform
        //              free size and count check
        //
        void push_item(const T item);
        void push_item_front(const T item);
        T pop_item();
        T pop_item_back();
        //--------------------------------------------------------------

    private:
        S  Size;
        S  Count;
        S  First;
        S  Last;
        T  Buf[size];
    };
    //------------------------------------------------------------------
}
//---------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//    The ring buffer function-member definitions
//
//
//
template<typename T, word size, class S>
bool usr::ring_buffer<T, size, S>::write(const T* data, const S cnt)
{
    if( cnt > (Size - Count) )
        return false;

    for(S i = 0; i < cnt; i++)
        push_item(*(data++));

    return true;
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void usr::ring_buffer<T, size, S>::read(T* data, const S cnt)
{
    S nItems = cnt <= Count ? cnt : Count;

    for(S i = 0; i < nItems; i++)
        data[i] = pop_item();
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
T& usr::ring_buffer<T, size, S>::operator[](const S index)
{
    S x = First + index;

    if(x < Size)
        return Buf[x];
    else
        return Buf[x - Size];
}

//------------------------------------------------------------------------------
template<typename T, word size, class S>
bool usr::ring_buffer<T, size, S>::push_back(const T item)
{
    if(Count == Size)
        return false;

    push_item(item);
    return true;
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
bool usr::ring_buffer<T, size, S>::push_front(const T item)
{
    if(Count == Size)
        return false;

    push_item_front(item);
    return true;
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
T usr::ring_buffer<T, size, S>::pop_front()
{
    if(Count)
        return pop_item();
    else
        return Buf[First];
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
T usr::ring_buffer<T, size, S>::pop_back()
{
    if(Count)
        return pop_item_back();
    else
        return Buf[First];
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void usr::ring_buffer<T, size, S>::push_item(const T item)
{
    Buf[Last] = item;
    Last++;
    Count++;

    if(Last == Size)
        Last = 0;
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
void usr::ring_buffer<T, size, S>::push_item_front(const T item)
{
    if(First == 0)
        First = Size - 1;
    else
        --First;
    Buf[First] = item;
    Count++;
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
T usr::ring_buffer<T, size, S>::pop_item()
{
    T item = Buf[First];

    Count--;
    First++;
    if(First == Size)
        First = 0;

    return item;
}
//------------------------------------------------------------------------------
template<typename T, word size, class S>
T usr::ring_buffer<T, size, S>::pop_item_back()
{

    if(Last == 0)
        Last = Size - 1;
    else
        --Last;

    Count--;
    return Buf[Last];;
}
//------------------------------------------------------------------------------


#endif // USRLIB_H
