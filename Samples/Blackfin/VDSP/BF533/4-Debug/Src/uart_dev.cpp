

#include <device.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <scmRTOS.h>
#include <macro.h>
#include "uart_dev.h"

                                           
//---------------------------------------------------------------------------
char     RxBuf[RX_BUF_SIZE];
uint16_t RxIndex;

usr::ring_buffer<char, TX_BUF_SIZE, uint16_t> TxBuf;

EX_INTERRUPT_HANDLER(uart_isr);

//---------------------------------------------------------------------------
void UART::init()
{
    register_handler_ex(ik_ivg10, uart_isr, 1);

    MMR16(UART_GCTL) = UCEN;
    MMR16(UART_LCR)  = WLS(8) + DLAB;
    MMR16(UART_DLL)  = 651 & 0xff;        // 9600
    MMR16(UART_DLH)  = 651 >> 8;          // 9600
    MMR16(UART_LCR) &= ~DLAB;
    MMR16(UART_IER)  = ERBFI;

}
//---------------------------------------------------------------------------
void UART::send(const char c)
{
    MMR16(UART_THR)   = c;
    MMR16(UART_IER)  |= ETBEI;
}
//---------------------------------------------------------------------------
void UART::send(const char* s)
{
    uint16_t i = 0;
    while(s[i])
    {
        TxBuf.push(s[i++]);
    }

//    MMR16(UART_THR)   = TxBuf.pop();
    MMR16(UART_IER)  |= ETBEI;

}
//---------------------------------------------------------------------------
//void UART::send(const uint8_t *data, const uint16_t count)
//{
//    for(uint16_t i = 0; i < count; i++)
//    {
//        if( TxBuf.get_count() )
//        {
//            TxBuf.push(data[i]);
//        }
//    }
//
//    MMR16(UART_IER)  |= ETBEI;
//}
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(uart_isr)
{
    OS::TISRW ISR;

    uint16_t status = MMR16(UART_IIR);

    //-----------------------------------------
    //
    //    Rx
    //
    if(status == 4)
    {
        uint8_t data = MMR16(UART_RBR);  // read data and clear flag
        status    = MMR16(UART_IIR);  // repeated read - check for Tx event

        switch(data)
        {
        case 27:                               // Esc - kill line
            UART::send("\\\r\n");
            RxIndex = 0;
            break;
        case '\n':
        break;
        case '\b':                             // backspace
            if(RxIndex)
            {
                --RxIndex;
                UART::send("\b \b");           // erase char
            }
            else
            {
                UART::send('\a');               // beep instead of echo
            }
            break;
        default:
            RxBuf[RxIndex++] = data;          // place char to buffer
            UART::send(data);                  // echo
            if(RxIndex < sizeof(RxBuf) - 1)
            break;                             // else buffer overflow
        case '\r':                             // CR - execute
            RxBuf[RxIndex] = 0;
            RxIndex = 0;
            NewLineIncoming.signal_isr();
        }       
    }

    //-----------------------------------------
    //
    //    Tx
    //
    if(status == 2)
    {
        if(TxBuf.get_count())
        {
            MMR16(UART_THR) = TxBuf.pop();
        }
        else
        {
            MMR16(UART_IER)  &= ~ETBEI;
        }
    }
}
//---------------------------------------------------------------------------

