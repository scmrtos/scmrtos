#ifndef UART_H
#define UART_H
#include    <stdint.h>
#include    <scmRTOS.h>
#include    "hardware.h"    // to get MCK symbol

class iodevice
{
public:
    virtual uint8_t hasinput();
    virtual bool    receive(uint8_t& data, tick_count_t time_x);
    virtual uint8_t receive();

    enum format_t
    {
        UNSIGNED        = (0 << 0),
        SIGNED          = (1 << 1),

        ALIGN_RIGHT     = (0 << 1),
        ALIGN_LEFT      = (1 << 1),

        LEADING_ZEROS   = (1 << 2),

        LEADING_SPACE   = (1 << 3),
        TRAILING_SPACE  = (1 << 4),
    };

    virtual void putch(char symbol);
            void send(char const* string);
            // send as HEX
            void send(uint8_t data);
            void send(uint16_t data);
            void send(uint32_t data);
            //  send decimal number
            void send(uint_fast32_t number, uint_fast8_t places, uint_fast8_t format = ALIGN_RIGHT);
            //  send fixed-point number
            void send(uint_fast32_t number, uint_fast8_t places, uint_fast8_t decimals, uint_fast8_t format);
private:
};

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
class uart : public iodevice
{
public:
    uint8_t hasinput() { return Rx_buffer.get_count(); }
    bool    receive(uint8_t& data, timeout_t time_x);
    uint8_t receive();

    void    putch(char symbol);

    INLINE void handler();
protected:
    uart(AT91PS_USART puart, uint32_t const& baud_code, uint32_t const& mode);
protected:
    AT91PS_USART                    pUART;
    OS::channel<uint8_t, rx_size>   Rx_buffer;
    OS::channel<uint8_t, tx_size>   Tx_buffer;

    static uint32_t const MODE_8_N_1 = 0
            | AT91C_US_CHRL_8_BITS | AT91C_US_PAR_NONE | AT91C_US_NBSTOP_1_BIT;
};

// --------------------------------------------------------------------------------------------

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
class dbgu : public uart<rx_size, tx_size>
{
public:
    INLINE dbgu(uint32_t const& baudrate);
private:
    static INLINE uint32_t baud_code(uint_fast32_t baudrate);
};

// --------------------------------------------------------------------------------------------

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
class std_uart : public uart<rx_size, tx_size>
{
public:
    INLINE std_uart(AT91PS_USART puart, uint32_t const& baudrate);
private:
    static INLINE uint32_t baud_code(uint_fast32_t baudrate);
};

// --------------------------------------------------------------------------------------------
// implementation
template<uint_fast8_t rx_size, uint_fast8_t tx_size>
inline uart<rx_size, tx_size>::uart(AT91PS_USART puart, uint32_t const& baud_code, uint32_t const& mode)
    : pUART(puart)
{
    pUART->US_CR = AT91C_US_RXEN | AT91C_US_TXEN | AT91C_US_RSTSTA;

    pUART->US_MR = 0
            | AT91C_US_USMODE_NORMAL | AT91C_US_CLKS_CLOCK | ( 0 * AT91C_US_SYNC)
            | ( 0 * AT91C_US_MSBF ) | (0 * AT91C_US_MODE9) | (0 * AT91C_US_CKLO)
            | ( 1 * AT91C_US_OVER )
            | mode;

    pUART->US_BRGR = baud_code;
    pUART->US_IER = AT91C_US_RXRDY;
}

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
bool uart<rx_size, tx_size>::receive(uint8_t& data, timeout_t time_x)
{
    timeout_t Time_remains = time_x - OS::get_tick_count();
    if(Time_remains - 1 > (timeout_t)-1 / 2)  // time_x elapsed
        return false;

    return Rx_buffer.pop(data, Time_remains);
}

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
uint8_t uart<rx_size, tx_size>::receive()
{
    uint8_t Tmp;
    Rx_buffer.pop(Tmp, 0);
    return Tmp;
}

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
void uart<rx_size, tx_size>::putch(char symbol)
{
    Tx_buffer.push(symbol);
    pUART->US_IER = AT91C_US_TXRDY;
}

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
void uart<rx_size, tx_size>::handler()
{
    uint32_t Flags = pUART->US_CSR;
    Flags &= pUART->US_IMR;
    if(Flags & AT91C_US_TXRDY)
    {
        if(Tx_buffer.get_count())
        {
            uint8_t Data;
            Tx_buffer.pop(Data, 1);
            pUART->US_THR = Data;
        }
        else
            pUART->US_IDR = AT91C_US_TXRDY;
    }

    if(Flags & AT91C_US_RXRDY)
    {
        uint8_t Data = pUART->US_RHR;       // read anyway
        pUART->US_CR = AT91C_US_RSTSTA;     // clear errors if any
        if(Rx_buffer.get_free_size())
            Rx_buffer.push(Data);
    }
}

// --------------------------------------------------------------------------------------------
template<uint_fast8_t rx_size, uint_fast8_t tx_size>
uint32_t dbgu<rx_size, tx_size>::baud_code(uint_fast32_t baudrate)
{
    return MCK / 16 / baudrate + 0.5 ;
}

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
inline dbgu<rx_size, tx_size>::dbgu(uint32_t const& baudrate)
: uart<rx_size, tx_size>
(
    reinterpret_cast<AT91PS_USART>(AT91C_BASE_DBGU),
    baud_code(baudrate),
    uart<rx_size, tx_size>::MODE_8_N_1
)
{
}

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
uint32_t std_uart<rx_size, tx_size>::baud_code(uint_fast32_t baudrate)
{
    return MCK / 8 / baudrate + 0.5 ;
}

template<uint_fast8_t rx_size, uint_fast8_t tx_size>
inline std_uart<rx_size, tx_size>::std_uart(AT91PS_USART  puart, uint32_t const& baudrate)
    : uart<rx_size, tx_size>
    (
        puart,
        baud_code(baudrate),
        uart<rx_size, tx_size>::MODE_8_N_1
    )
{
}

#endif  // UART_H
