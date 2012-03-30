/*******************************************************************************
*	Startup file for LPC111x Cortex-M0 MCU
*
* The file is prepared for:
*
*	LPC1111, LPC1112, LPC1113, LPC1114
*
*******************************************************************************/
void Reset_Handler(void) __attribute__((__interrupt__));
extern int main(void);

	/* Core interrupt vectors */
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSVC_ISR(void);
void SystemTimer_ISR(void);

	/* Device interrupt vectors */
void Wakeup0_IRQ_Handler();
void Wakeup1_IRQ_Handler();
void Wakeup2_IRQ_Handler();
void Wakeup3_IRQ_Handler();
void Wakeup4_IRQ_Handler();
void Wakeup5_IRQ_Handler();
void Wakeup6_IRQ_Handler();
void Wakeup7_IRQ_Handler();
void Wakeup8_IRQ_Handler();
void Wakeup9_IRQ_Handler();
void Wakeup10_IRQ_Handler();
void Wakeup11_IRQ_Handler();
void Wakeup12_IRQ_Handler();
void SSP1_IRQ_Handler();
void I2C_IRQ_Handler();
void Timer16_0_IRQ_Handler();
void Timer16_1_IRQ_Handler();
void Timer32_0_IRQ_Handler();
void Timer32_1_IRQ_Handler();
void SSP0_IRQ_Handler();
void UART_IRQ_Handler();
void ADC_IRQ_Handler();
void WDT_IRQ_Handler();
void BOD_IRQ_Handler();
void EINT3_IRQ_Handler();
void EINT2_IRQ_Handler();
void EINT1_IRQ_Handler();
void EINT0_IRQ_Handler();

/******************************************************************************
*
* Vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
#include    <stdint.h>

extern uint32_t _estack[];
typedef void( * const intfunc )( void );
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
	/* Core interrupt vectors */
    (intfunc)_estack,
	Reset_Handler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	SVC_Handler,
	0,
	0,
	PendSVC_ISR,
	SystemTimer_ISR,

	/* Device interrupt vectors */
	/* 0x40 */
	Wakeup0_IRQ_Handler,
	Wakeup1_IRQ_Handler,
	Wakeup2_IRQ_Handler,
	Wakeup3_IRQ_Handler,
	Wakeup4_IRQ_Handler,
	Wakeup5_IRQ_Handler,
	Wakeup6_IRQ_Handler,
	Wakeup7_IRQ_Handler,
	Wakeup8_IRQ_Handler,
	Wakeup9_IRQ_Handler,
	Wakeup10_IRQ_Handler,
	Wakeup11_IRQ_Handler,
	Wakeup12_IRQ_Handler,
	0,
	SSP1_IRQ_Handler,
	I2C_IRQ_Handler,
	Timer16_0_IRQ_Handler,
	Timer16_1_IRQ_Handler,
	Timer32_0_IRQ_Handler,
	Timer32_1_IRQ_Handler,
	SSP0_IRQ_Handler,
	UART_IRQ_Handler,
	0,
	0,
	ADC_IRQ_Handler,
	WDT_IRQ_Handler,
	BOD_IRQ_Handler,
	0,
	EINT3_IRQ_Handler,
	EINT2_IRQ_Handler,
	EINT1_IRQ_Handler,
	EINT0_IRQ_Handler,
};

extern void init_HW(void);

extern uint32_t _etext;
extern uint32_t _sidata[];
extern uint32_t _sdata[];
extern uint32_t _edata[];
extern uint32_t _sbss[];
extern uint32_t _ebss[];
extern void(* const __ctors_start__[])();
extern void(* const __ctors_end__[])();

static inline __attribute__((always_inline))
void __Init_Data(void)
{
    /* Init hardware before calling constructors */
    init_HW();

    uint32_t *pulSrc, *pulDest;

    pulSrc = _sidata;

    for(pulDest = _sdata; pulDest < _edata; )
        *(pulDest++) = *(pulSrc++);

    for(pulDest = _sbss; pulDest < _ebss; )
        *(pulDest++) = 0;

    /* Call constructors */
    void(* const *ctors)();
    for( ctors = __ctors_start__; ctors < __ctors_end__; )
        (*ctors++)();
}

void Reset_Handler(void)
{
	__Init_Data();

	main();
}

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/
#pragma weak HardFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak PendSVC_ISR = Default_Handler
#pragma weak SystemTimer_ISR = Default_Handler
#pragma weak Wakeup0_IRQ_Handler = Default_Handler
#pragma weak Wakeup1_IRQ_Handler = Default_Handler
#pragma weak Wakeup2_IRQ_Handler = Default_Handler
#pragma weak Wakeup3_IRQ_Handler = Default_Handler
#pragma weak Wakeup4_IRQ_Handler = Default_Handler
#pragma weak Wakeup5_IRQ_Handler = Default_Handler
#pragma weak Wakeup6_IRQ_Handler = Default_Handler
#pragma weak Wakeup7_IRQ_Handler = Default_Handler
#pragma weak Wakeup8_IRQ_Handler = Default_Handler
#pragma weak Wakeup9_IRQ_Handler = Default_Handler
#pragma weak Wakeup10_IRQ_Handler = Default_Handler
#pragma weak Wakeup11_IRQ_Handler = Default_Handler
#pragma weak Wakeup12_IRQ_Handler = Default_Handler
#pragma weak SSP1_IRQ_Handler = Default_Handler
#pragma weak I2C_IRQ_Handler = Default_Handler
#pragma weak Timer16_0_IRQ_Handler = Default_Handler
#pragma weak Timer16_1_IRQ_Handler = Default_Handler
#pragma weak Timer32_0_IRQ_Handler = Default_Handler
#pragma weak Timer32_1_IRQ_Handler = Default_Handler
#pragma weak SSP0_IRQ_Handler = Default_Handler
#pragma weak UART_IRQ_Handler = Default_Handler
#pragma weak ADC_IRQ_Handler = Default_Handler
#pragma weak WDT_IRQ_Handler = Default_Handler
#pragma weak BOD_IRQ_Handler = Default_Handler
#pragma weak EINT3_IRQ_Handler = Default_Handler
#pragma weak EINT2_IRQ_Handler = Default_Handler
#pragma weak EINT1_IRQ_Handler = Default_Handler
#pragma weak EINT0_IRQ_Handler = Default_Handler
#include "hardware.h"
#include "lpc11xx.h"
void Default_Handler(void)
{
	for (;;)
	{
	    ON(LED_GREEN);
	    OFF(LED_GREEN);
	}
	    ;
}

