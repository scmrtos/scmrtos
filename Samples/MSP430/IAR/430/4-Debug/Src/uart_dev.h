//******************************************************************************
//*
//*      Project:   TBx
//*
//*      File:      UART device 
//*
//*      Version 1.0
//*
//*      Copyright (c) 2009, Harry E. Zhurov
//*
//*      $Revision$
//*      $Date::             $
//*
//------------------------------------------------------------------------------

#ifndef UART_DEV_H
#define UART_DEV_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <scmRTOS.h>


namespace UART
{
    void init();
    void send(const char  c);
    void send(const char *s);
}

const uint16_t TX_BUF_SIZE = 256;
const uint16_t RX_BUF_SIZE = 64;

INLINE void enable_tx_int()  { IE2 |= UTXIE1;  }
INLINE void disable_tx_int() { IE2 &= ~UTXIE1; }
INLINE void enable_rx_int()  { IE2 |= URXIE1;  }
INLINE void disable_rx_int() { IE2 &= ~URXIE1; }

extern usr::ring_buffer<char, TX_BUF_SIZE, uint16_t> TxBuf;
extern OS::TEventFlag NewLineIncoming;
extern char RxBuf[RX_BUF_SIZE];

#endif // UART_DEV_H
