

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

EX_DISPATCHED_HANDLER_NESTED(RX_IrqHandler,a,b,c){
	OS::TISRW ISR;
	  uint8_t data = *pREG_UART0_RBR;  // read data and clear flag


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

EX_DISPATCHED_HANDLER_NESTED(TX_IrqHandler,a,b,c){
	OS::TISRW ISR;

	 if(TxBuf.get_count())
	        {

		        *pREG_UART0_THR = TxBuf.pop();;
	        }
	        else
	        {
	        	*pREG_UART0_IMSK_CLR=BITM_UART_IMSK_SET_ETBEI;
	        }
}
//---------------------------------------------------------------------------
void UART::init()
{
	*pREG_UART0_CLK=68;//115200 бод
	*pREG_UART0_CTL=BITM_UART_CTL_WLS & ENUM_UART_CTL_WL8BITS;
	adi_int_InstallHandler(INTR_UART0_RXDMA, (ADI_INT_HANDLER_PTR)RX_IrqHandler, NULL, true);
	adi_int_InstallHandler(INTR_UART0_TXDMA, (ADI_INT_HANDLER_PTR)TX_IrqHandler, NULL, true);
    *pREG_UART0_IMSK_SET=BITM_UART_IMSK_SET_ERBFI;
    *pREG_UART0_CTL|=BITM_UART_CTL_EN;
}
//---------------------------------------------------------------------------
void UART::send(const char c)
{
	*pREG_UART0_THR  = c;
	*pREG_UART0_IMSK_SET=BITM_UART_IMSK_SET_ETBEI;
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
    *pREG_UART0_IMSK_SET=BITM_UART_IMSK_SET_ETBEI;

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

