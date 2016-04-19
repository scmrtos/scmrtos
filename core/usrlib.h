//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*               
//*     PURPOSE:  User Suport Library Header
//*               
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
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
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************

#ifndef USRLIB_H
#define USRLIB_H

#include <stdint.h>

//------------------------------------------------------------------------------
//
//  DESCRIPTON: user namespace for some useful types and functions
//
//
namespace usr
{
    //------------------------------------------------------------------------------
    //
    ///     The Circular Buffer
    //
    ///         Byte-wide FIFO.
    //
    ///         Allows to:
    ///             add byte,
    ///             get byte,
    ///             write bytes from array,
    ///             read bytes to array,
    ///             and some other service actions.
    //
    class TCbuf
    {
    public:
        TCbuf(uint8_t* const Address, const uint8_t Size);
        bool write(const uint8_t* data, const uint8_t Count);
        void read(uint8_t* const data, const uint8_t Count);
        uint8_t get_count() const { return count; }
        uint8_t get_free_size() const { return size - count; }
        uint8_t get_byte(const uint8_t index) const;
        void clear() { count = 0; last = first; }
        bool put(const uint8_t item);
        uint8_t get();

    private:
       //------------------------------------------------------------------------------
       //
       //  DESCRIPTON: For internal purposes
       //
        void push(const uint8_t item); ///< Use this function with care - it doesn't perform free size check
        uint8_t pop();                 ///< Use this function with care - it doesn't perform count check
       //------------------------------------------------------------------------------

    private:
        uint8_t* buf;
        uint8_t  size;
        volatile uint8_t count;
        uint8_t  first;
        uint8_t  last;
    };
    //------------------------------------------------------------------------------



    //-----------------------------------------------------------------------
    //
    ///     The Ring Buffer Template
    ///
    ///         Carries out FIFO functionality for
    ///         arbitrary data types
    ///
    ///         Allows to:
    ///             add item to back (default),
    ///             add item to front,
    ///             get item at front (default),
    ///             get item from back,
    ///             write items from array,
    ///             read items to array and some other actions
    //
    //
    //
    template<typename T, uint16_t Size, typename S = uint8_t>
    class ring_buffer
    {
    public:
        ring_buffer() : Count(0), First(0), Last(0) { }

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
        S  Count;
        S  First;
        S  Last;
        T  Buf[Size];
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
template<typename T, uint16_t Size, typename S>
bool usr::ring_buffer<T, Size, S>::write(const T* data, const S cnt)
{
    if( cnt > (Size - Count) )
        return false;

    for(S i = 0; i < cnt; i++)
        push_item(*(data++));

    return true;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
void usr::ring_buffer<T, Size, S>::read(T* data, const S cnt)
{
    S nItems = cnt <= Count ? cnt : Count;

    for(S i = 0; i < nItems; i++)
        data[i] = pop_item();
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
T& usr::ring_buffer<T, Size, S>::operator[](const S index)
{
    S x = First + index;

    if(x < Size)
        return Buf[x];
    else
        return Buf[x - Size];
}

//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
bool usr::ring_buffer<T, Size, S>::push_back(const T item)
{
    if(Count == Size)
        return false;

    push_item(item);
    return true;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
bool usr::ring_buffer<T, Size, S>::push_front(const T item)
{
    if(Count == Size)
        return false;

    push_item_front(item);
    return true;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
T usr::ring_buffer<T, Size, S>::pop_front()
{
    if(Count)
        return pop_item();
    else
        return Buf[First];
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
T usr::ring_buffer<T, Size, S>::pop_back()
{
    if(Count)
        return pop_item_back();
    else
        return Buf[First];
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
void usr::ring_buffer<T, Size, S>::push_item(const T item)
{
    Buf[Last] = item;
    Last++;
    Count++;

    if(Last == Size)
        Last = 0;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
void usr::ring_buffer<T, Size, S>::push_item_front(const T item)
{
    if(First == 0)
        First = Size - 1;
    else
        --First;
    Buf[First] = item;
    Count++;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
T usr::ring_buffer<T, Size, S>::pop_item()
{
    T item = Buf[First];

    Count--;
    First++;
    if(First == Size)
        First = 0;

    return item;
}
//------------------------------------------------------------------------------
template<typename T, uint16_t Size, typename S>
T usr::ring_buffer<T, Size, S>::pop_item_back()
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
