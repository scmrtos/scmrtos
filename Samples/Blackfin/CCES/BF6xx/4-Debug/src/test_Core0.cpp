/*****************************************************************************
 * test_Core0.cpp
 *****************************************************************************/

#include <ccblkfn.h>
#include "adi_initialize.h"
#include "test_Core0.h"
#include <services/tmr/adi_tmr.h>
#include <services/int/adi_int.h>
#include <services/int/adi_sec.h>

#include <sysreg.h>
#include <scmRTOS.h>
#include "macro.h"

#include <terminal.h>


#define INT_IVG14 (BITP_IPEND_IVG14)
#define INT_TMR   (BITP_IPEND_IVTMR)


const uint_fast8_t SUM_SHIFT        = 10;

ADI_TMR_HANDLE   hTimer;
uint8_t TimerMemory[ADI_TMR_MEMORY];



typedef OS::process<OS::pr0, 1024> TProc1;
typedef OS::process<OS::pr1, 1024> TProc2;
typedef OS::process<OS::pr2, 1024> TProc3;
typedef OS::process<OS::pr4, 1500> TBackgroundProc;

class TProcProfiler : public TProfiler<SUM_SHIFT>
{
public:
    TProcProfiler() {}
    void get_results(timeout_t acquire_period);
};


TProc1 Troc1;
TProc2 Troc2;
TProc3 Troc3;
TBackgroundProc BackgroundProc;



OS::TEventFlag ef_timer0;
OS::TEventFlag ef;
TProcProfiler Profiler;



void OS::idle_process_user_hook() { }
void OS::context_switch_user_hook() {
	Profiler.advance_counters();
}

template<> void TProc1::exec()
{

    for(;;)
    {
    	ef_timer0.wait();
    }

}

template<> void TProc2::exec()
{
	 for(;;)
	    {
		 ef.wait();
		 for(int i = 0; i < 100000; ++i)
		        {
		            asm( " nop;");
		        }
	    }

}

template<> void TProc3::exec()
{
	 for(;;)
	    {
		 sleep(3);
		 for(int i = 0; i < 10000; ++i)
		        {
		            asm( " nop;");
		        }
		 ef.signal();
	    }

}

template<> void TBackgroundProc::exec()
{
    for(;;)
    {
        Profiler.get_results(1000);
    }
}


static void TimerHandler(void *pCBParam, uint32_t Event, void *pArg)
{
   switch(Event)
    {
        case ADI_TMR_EVENT_DATA_INT:{

        	OS::TISRW ISR;
        	  //--------------------------------------------------
        	    //
        	    //            Message test
        	    //
        	    //     Send data as message
        	    //

            	ef_timer0.signal_isr();


            break;
        }
        default:
            break;
    }

}

void SetupGPTimer(unsigned int nTimerNum,void *const pMemory,ADI_CALLBACK pfCallback, ADI_TMR_HANDLE *const phTimer,
		          uint32_t nPeriod,uint32_t nWidth)
{
	ADI_TMR_RESULT 	 eTmrResult;
/* Open the timer */
           if( (eTmrResult = adi_tmr_Open (nTimerNum,
                       		pMemory,
                       		ADI_TMR_MEMORY,
                       		pfCallback,
                       		NULL,
                       		phTimer)) != ADI_TMR_SUCCESS)
            {
                /* Failed to open the timer handle the error here */
            }

           /*
            * Use the GP timer's API's to configure and enable the timer
            *
            */
           eTmrResult = adi_tmr_EnableDataInt(*phTimer,false);
           eTmrResult = adi_tmr_EnableStatusInt(*phTimer,false);
       	/* Set the mode to PWM OUT */
           eTmrResult = adi_tmr_SetMode(*phTimer, ADI_TMR_MODE_CONTINUOUS_PWMOUT);

           /* Set the IRQ mode to get interrupt after counts till TMR_PERIOD register value */
           eTmrResult = adi_tmr_SetIRQMode(*phTimer, ADI_TMR_IRQMODE_PERIOD);
           /* Set the Period */
           eTmrResult = adi_tmr_SetPeriod(*phTimer,nPeriod);

           /* Set the timer width */
       	   eTmrResult = adi_tmr_SetWidth(*phTimer, nWidth);

       	   /* Enable the timer */
       	   eTmrResult = adi_tmr_Enable(*phTimer, true);


}
template<uint_fast8_t sum_shift>
uint32_t TProfiler<sum_shift>::time_interval()
{
    //return 1;
    static uint32_t Cycles;

    uint32_t Cyc = sysreg_read(reg_CYCLES);
    uint32_t Res = Cyc - Cycles;
    Cycles       = Cyc;

    return Res;
}
//---------------------------------------------------------------------------
void TProcProfiler::get_results(timeout_t acquire_period)
{
    OS::sleep(acquire_period);
    TProfiler::process_data();
    //print("---------------------------\n");
    UART::send("---------------------------\n\r");

    for(uint_fast8_t i = 0; i < OS::PROCESS_COUNT; ++i)

    {
       // print("Proc %d | CPU %5.2f | Slack %d\n", i, Profiler.get_result(i)/100.0, OS::get_proc(i)->stack_slack() );
    	print(i,Profiler.get_result(i),OS::get_proc(i)->stack_slack());
    }
}


int main(void)
{

	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */


	adi_initComponents();

	/**
	 * The default startup code does not include any functionality to allow
	 * core 0 to enable core 1. A convenient way to enable core 1 is to use the
	 * 'adi_core_1_enable' function. 
	 */

	/* Begin adding your custom code here */
	*pREG_PORTG_DIR|=0x8000;
	*pREG_PORTG_DIR|=0x4000;
	*pTCNTL   = 1;                                   /* Turn on timer, TMPWR                           */
	*pTSCALE  = 0;                                   /* Load scale                                     */
	*pTCOUNT  = 500000;//200000;                              /* Load counter                                   */
	*pTPERIOD = 500000;//200000;                              /* Load counter into period as well               */
     UART::init();
	    adi_rtl_register_dispatched_handler(ADI_RTL_CORE_IID(INT_TMR),
	    		                            OS::system_timer_isr,
	                                        NULL);
	    adi_rtl_activate_dispatched_handler(ADI_RTL_CORE_IID(INT_TMR));



	    adi_rtl_register_dispatched_handler (ADI_RTL_CORE_IID(INT_IVG14),
	   	    		                     context_switcher_isr,
	   	                                 NULL);
	    adi_rtl_activate_dispatched_handler(ADI_RTL_CORE_IID(INT_IVG14));

	   SetupGPTimer(0,TimerMemory,TimerHandler,&hTimer,5000000,1000000);
	   adi_sec_SetCoreID(INTR_TIMER0_TMR0, ADI_SEC_CORE_0);
	   *pTCNTL   = 0x7;
	   adi_tmr_EnableDataInt(&hTimer,true);
    OS::run();
	return 0;
}

