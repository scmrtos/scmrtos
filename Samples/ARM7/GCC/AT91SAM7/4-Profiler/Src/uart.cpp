#include    "uart.h"


void iodevice::send(char const * string)
{
    while(char c = *string++)
        putch(c);
}

void iodevice::send(uint8_t data)
{
    static char const Table[] = "0123456789ABCDEF";
    putch(Table[data >> 4]);
    putch(Table[data & 0x0F]);
}
void iodevice::send(uint16_t data)
{
    send(uint8_t(data >> 8));
    send(uint8_t(data >> 0));
}
void iodevice::send(uint32_t data)
{
    send(uint16_t(data >> 16));
    send(uint16_t(data >> 0));
}

void iodevice::send(uint_fast32_t number, uint_fast8_t places, uint_fast8_t format)
{
    send(number, places, 0, format);
}

#include    <stdlib.h>  // ldiv_t
// assume places never can be 0 and decimals < places - 1
void iodevice::send(uint_fast32_t number, uint_fast8_t places, uint_fast8_t decimals, uint_fast8_t format)
{

    char Buffer[12];    // 2^32 has 10 digits + decimal point + trailing '\0'
    Buffer[11] = '\0';

    char * pDst = &Buffer[sizeof(Buffer) - 1];
    for(uint8_t i = 0; i < sizeof(Buffer) - 2; ++i)
    {
        if(decimals && i == decimals)
            *--pDst = '.';
        ldiv_t Res = ldiv(number, 10);
        *--pDst = Res.rem + '0';
        number = Res.quot;
    }

    if(!(format & LEADING_ZEROS))
    {
        char *Tmp = pDst;
        for(uint8_t i = 0; i < sizeof(Buffer) - 3; ++i) // don't erase last '0' if number = 0
        {
            if(Tmp[0] == '0' && Tmp[1] != '.')
                Tmp[0] = ' ';
            else
                break;
            ++Tmp;
        }
    }
    if(format & LEADING_SPACE)
        putch(' ');
    send(&Buffer[sizeof(Buffer) - 1 - places]);
    if(format & TRAILING_SPACE)
        putch(' ');
}

/*
    //  send decimal number
    void send(uint_fast32_t number, uint_fast8_t places, uint_fast8_t format = ALIGN_RIGHT);
    //  send fixed-point number
    void send(uint_fast32_t number, uint_fast8_t places, uint_fast8_t decimals, uint8_t format);
*/
