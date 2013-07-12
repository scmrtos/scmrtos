/*****************************************************************************
 * test_Core0.cpp
 *****************************************************************************/

#include <ccblkfn.h>
#include "adi_initialize.h"
#include "test_Core0.h"
#include <services/tmr/adi_tmr.h>
#include <services/int/adi_int.h>
#include <services/int/adi_sec.h>


#include <scmRTOS.h>


#define INT_IVG14 (BITP_IPEND_IVG14)
#define INT_TMR   (BITP_IPEND_IVTMR)



ADI_TMR_HANDLE   hTimer;
uint8_t TimerMemory[ADI_TMR_MEMORY];

typedef OS::process<OS::pr0, 1024> TProc1;
typedef OS::process<OS::pr1, 1024> TProc2;
typedef OS::process<OS::pr2, 1024> TProc3;


TProc1 Troc1;
TProc2 Troc2;
TProc3 Troc3;

OS::TEventFlag ef_timer0;


template<> void TProc1::exec()
{
	int sum=0;

    for(;;)
    {
         sum+=2;
         *pREG_PORTG_DATA_TGL=0x4000;
         sleep(500);
    }
}

template<> void TProc2::exec()
{
	int sum=0;

    for(;;)
    {
         sum+=1;
         sleep(250);

    }
}

template<> void TProc3::exec()
{
	int sum=0;
    for(;;)
    {
    	 ef_timer0.wait();
         sum+=5;
         *pREG_PORTG_DATA_TGL=0x8000;

    }
}

static void TimerHandler(void *pCBParam, uint32_t Event, void *pArg)
{
   switch(Event)
    {
        case ADI_TMR_EVENT_DATA_INT:{

        	OS::TISRW ISR;
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

	    adi_rtl_register_dispatched_handler(ADI_RTL_CORE_IID(INT_TMR),
	    		                            OS::system_timer_isr,
	                                        NULL);
	    adi_rtl_activate_dispatched_handler(ADI_RTL_CORE_IID(INT_TMR));



	    adi_rtl_register_dispatched_handler (ADI_RTL_CORE_IID(INT_IVG14),
	   	    		                     context_switcher_isr,
	   	                                 NULL);
	    adi_rtl_activate_dispatched_handler(ADI_RTL_CORE_IID(INT_IVG14));

	   SetupGPTimer(0,TimerMemory,TimerHandler,&hTimer,3125,78);
	   adi_sec_SetCoreID(INTR_TIMER0_TMR0, ADI_SEC_CORE_0);
	   *pTCNTL   = 0x7;
	   adi_tmr_EnableDataInt(&hTimer,true);
    OS::run();
	return 0;
}

