//******************************************************************************
//*
//*      Project:   TBx
//*
//*      File:      Terminal source file
//*
//*      Version 1.0
//*
//*      Copyright (c) 2009-2012, Harry E. Zhurov
//*
//*      $Revision$
//*      $Date::             $
//*
//------------------------------------------------------------------------------

#include <list>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "debug.h"
#include "terminal.h"

TTerminalProc TerminalProc;       
OS::TEventFlag NewLineIncoming;

char command[16];

char *command_dict[] = 
{
    "help"   // print avaliable commands list
};

void help(char *s);

void (*fptr[])(char *s) = 
{
    help
};

//------------------------------------------------------------------------------
uint16_t sz[32];
uint16_t idx;
int print(char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buf[TX_BUF_SIZE/2];
    uint16_t size = vsprintf(buf, format, args);
    va_end(args);

    
   // sz[idx++] = size;
    TxBuf.write(buf, size);
    MMR16(UART_IER)  |= ETBEI;

    return size;
}
//---------------------------------------------------------------------------
template<> void TTerminalProc::exec()
{
    sleep(1000);
    
    for(;;)
    {
    LBegin:
        NewLineIncoming.wait();
        uint16_t n = strcspn(RxBuf, " \0");
        if(n == 0)
        {
            UART::send("\n\n");
            continue;
        }
        strncpy(command, RxBuf, n);
        command[n] = 0;
        for(uint16_t i = 0; i < sizeof(command_dict)/sizeof(command_dict[0]); i++)
        {
            if(strcmp(command, command_dict[i]) == 0)
            {
                UART::send("... Ok\r");
                char *s = RxBuf + n + 1;
                (*fptr[i])(s);
                goto LBegin;
            }
        }
        UART::send("... error: unknown command\r");
    }
}
//---------------------------------------------------------------------------
void help(char *s)
{
    TCritSect cs;
    
    UART::send("Supported commands:\n");
    for(uint16_t i = 0; i < sizeof(command_dict)/sizeof(command_dict[0]); i++)
    {
        UART::send("\n");
        UART::send(command_dict[i]);
    }
    UART::send("\n");
}
//---------------------------------------------------------------------------

