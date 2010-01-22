//********************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: FR (Fujitsu)
//*
//*     TOOLKIT:   Softune Workbench V6 (Fujitsu)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 3.10
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2010, Harry E. Zhurov
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
//********************************************************************************

//---------------------------------------------------------------------------
#include <scmRTOS.h>
#include <hwtools.h>
#include <pins.h>

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 256> TProc1;
typedef OS::process<OS::pr1, 256> TProc2;
typedef OS::process<OS::pr2, 256> TProc3;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1  Proc1;
TProc2  Proc2;
TProc3  Proc3;
//---------------------------------------------------------------------------
OS::TEventFlag ef;               //


struct TMamont                   //  data type for sending by message
{                                //
    enum TSource
    {
        PROC_SRC,
        ISR_SRC
    } 
    src;
    int data;                    //
};                               //

TMamont Mamont;                  // global test object for recieve data from message

OS::message<TMamont> MamontMsg;  // OS::message object

//---------------------------------------------------------------------------
int main(void)
{

    HardwareInit();

    scmRTOS_SYSTIMER_SETUP();

    OS::Run();

    for(;;);
}

//---------------------------------------------------------------------------
template<> void TProc1::Exec()
{
    for(;;)
    {
        //--------------------------------------------------
        //
        //            Message test
        //
        //
        //     Receive data as message
        //
        MamontMsg.wait();                                     // wait for message
        Mamont = MamontMsg;                                   // read message content to global test object 
        if(Mamont.src == TMamont::PROC_SRC)
        {
            off(LED2);
        }
        else
        {
            off(LED2);
            on(LED2);
            off(LED2);
        }
    }     
}
//---------------------------------------------------------------------------
template<> void TProc2::Exec()
{
    for(;;)
    {
        Sleep(20);
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::Exec()
{
    for(;;)
    {
        Sleep(1);
        TMamont m;           // create message content

        m.src  = TMamont::PROC_SRC;
        m.data = 5;
        MamontMsg = m;       // put the content to the OS::message object
        on(LED2);
        MamontMsg.send();    // send the message
    }
}
//---------------------------------------------------------------------------
//void OS::SystemTimerUserHook() { }

//---------------------------------------------------------------------------
void OS::IdleProcessUserHook() { }

//---------------------------------------------------------------------------
extern "C" __interrupt void ih_Timer2(void)
{
    OS::TISRW ISR;

    TMCSR2_UF = 0;      // Clear INT flag

    HWDCS_CL = 0x00;    // Reset hardware watchdog

    //--------------------------------------------------
    //
    //            Message test
    //
    //     Send data as message
    //
    TMamont m;           // create message content

    m.src  = TMamont::ISR_SRC;
    m.data = 10;
    MamontMsg = m;       // put the content to the OS::message object
    on(LED1);
    MamontMsg.sendISR();    // send the message

}
//---------------------------------------------------------------------------
