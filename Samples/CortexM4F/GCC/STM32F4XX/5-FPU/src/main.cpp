//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M4F
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//******************************************************************************
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2012

#include "pin.h"
#include <scmRTOS.h>
#include "hw.h"

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 300> TProc1;
typedef OS::process<OS::pr1, 300> TProc2;
typedef OS::process<OS::pr2, 300> TProc3;
typedef OS::process<OS::pr3, 300> TProc4;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
TProc4 Proc4;

/**
 * Class for PI calculation
 */
class PiCalculator
{
public:
	PiCalculator(uint32_t iterations)
	{
		limit = iterations;
		n = 0;
		s1 = .0f;
	}
	void step()
	{
		if (!done())
		{
			n++;
			s1 = s1 + 4.0f/(float)(2*n-1);
			n++;
			s1 = s1 - 4.0f/(float)(2*n-1);
		}
	}
	bool done() { return n >= limit; }
	double result() { return s1; }
private:
	uint32_t limit;
	uint32_t n;
	float s1;
};

OS_PROCESS void test_context(uint32_t param);

int main()
{
    // configure LEDs
    RedLED::Direct(OUTPUT);
    RedLED::Off();
    GreenLED::Direct(OUTPUT);
    GreenLED::Off();
    OrangeLED::Direct(OUTPUT);
    OrangeLED::Off();

    // run
    OS::run();
}

namespace OS
{
    template <>
    OS_PROCESS void TProc1::exec()
    {
    	sleep(2);
		for(;;)
		{
			PiCalculator piCalc(100000000);
			while (!piCalc.done())
			{
				for(int i = 0; i < 100; i++)
					piCalc.step();
				sleep(1);
			}
		}
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
		test_context(0x12345678);
    }

    template <>
    OS_PROCESS void TProc3::exec()
    {
		test_context(0x87654321);
    }

    // Heartbeat
    template <>
    OS_PROCESS void TProc4::exec()
    {
        for(;;)
        {
    		for(;;)
    		{
    			GreenLED::On();
    			sleep(50);
    			GreenLED::Off();
    			sleep(950);
    		}
        }
    }
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
