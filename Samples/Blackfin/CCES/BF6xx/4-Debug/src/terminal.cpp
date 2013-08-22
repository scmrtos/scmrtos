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
//*      $Revision: 546 $
//*      $Date:: 2012-05-16 #$
//*
//------------------------------------------------------------------------------

#include <list>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "terminal.h"

typedef OS::process<OS::pr3, 1280> TTerminalProc;


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
//uint16_t sz[32];
uint16_t idx;
char buf[TX_BUF_SIZE/2];

int print(char *format, ...)
{
    va_list args;
    char buf[TX_BUF_SIZE/2];
    va_start(args, format);
    uint16_t size = vsprintf(buf, format, args);
    va_end(args);

    
   // sz[idx++] = size;
    TxBuf.write(buf, size);
    *pREG_UART0_IMSK_SET  |= BITM_UART_IMSK_SET_ETBEI;

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
unsigned char str_from_sint32(int x, unsigned char afterdot,  char* result)
{//Преобразует знаковый integer в строку. Разделитель целой и дробной части "."(точка)
//Ведущие нули отсутствуют
//afterdot=0 -> ЦЕЛОЕ (без десятичной точки)
//afterdot=1 -> С ОДНОЙ ЦИФРОЙ ПОСЛЕ ДЕСЯТИЧНОЙ ТОЧКИ
//afterdot=2 -> С ДВУМЯ ЦИФРАМИ ПОСЛЕ ДЕСЯТИЧНОЙ ТОЧКИ
//afterdot=3 -> С ТРЕМЯ ЦИФРАМИ ПОСЛЕ ДЕСЯТИЧНОЙ ТОЧКИ
//возвращает длину строки
  int d,r;
  unsigned char s[11];
  unsigned char i,z,p=0,neg=0,di=0,uu=0;
  if(x==0x80000000) uu=1; //Это -2147483648 (при рассчете будет -2147483647, последнюю цифру нужно будет исправить с 7 на 8)
  if(x<0) { neg=1; x=-x; } //Если отрицательное то берем модуль
  for(i=0;i<10;i++) //максимум девять цифр
  {//Цикл, цифры кладутся в обратном порядке
  	if(x>0)
  	{//Если не ноль
  	  d=x/10;   //Делим на 10
      r=x-d*10; //Находим остаток от деления (Искомая Цифра)
      x=d;      //Новое значение есть старое деленное на 10
  	}//Если не ноль
  	else r=0; //Если ноль, то остаток нулевой (Цифра "0")
  	s[p++]=0x30+r; //Кладем цифру как значение остатка в ASCII-коде
  	if(afterdot==(i+1)) { s[p++]='.'; di=1; } //Если точка в следующей цифре, то ставим ее
  	if(x==0)
  	{//число выродилось в ноль
  	  if(s[p-1]=='.') s[p++]=0x30; //Если была точка, то ставим перед ней ноль
  	  if((afterdot==0)||(di==1)) goto lab1; //Если целое или уже была точка то выход из цикла
  	}//число выродилось в ноль
  }//Цикл
lab1:
  if(neg!=0) s[p++]='-'; //Если входное число было отрицательное ставим еще и знак минус
  z=p-1; //Уменьшить указатель. Z хранит теперь число символов
  for(i=0;i<p;i++) result[i]=s[z--]; //Перевернуть символы в нормальный порядок
  result[i]=0; //Терминируем строку
  if(uu!=0) result[i-1]=0x38; //Если было -2147483648 то исправляем последнюю цифру 7 на 8.
  return p;
}//End of func*/

int print(int id,int cpu,int stack){
	int size;
	size=str_from_sint32(id,0,buf);
	TxBuf.write("Proc ",5);
	TxBuf.write(buf, size);
	TxBuf.write("|", 1);
	size=str_from_sint32(cpu,2,buf);
	TxBuf.write("CPU ",4);
	TxBuf.write(buf, size);
	if (size<5) TxBuf.write(" ",1);
	TxBuf.write("|", 1);
	size=str_from_sint32(stack,0,buf);
	TxBuf.write("Slack ",6);
	TxBuf.write(buf, size);
	if (size<2) TxBuf.write("  ",2);
	else
	if (size<3) TxBuf.write(" ",1);

	TxBuf.write("|\n\r", 3);
	*pREG_UART0_IMSK_SET  |= BITM_UART_IMSK_SET_ETBEI;
	return 0;
}

