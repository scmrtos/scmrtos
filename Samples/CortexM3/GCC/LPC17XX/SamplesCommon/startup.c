/*******************************************************************************
*	Startup file for LPC175x, LPC176x Cortex-M3 MCU
*
* Based on STM32 startup file by Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*       (see scmRTOS Cortex-M3/STM32F1XX examples)
*
*******************************************************************************/

extern unsigned long _etext;
extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _estack;
extern unsigned long __ctors_start__;
extern unsigned long __ctors_end__;

extern unsigned long __dtors_start__;
extern unsigned long __dtors_end__;

extern int main(void);
void __Init_Data(void);

#if 0
// n.a. for LPC175x, LPC176x
// available for LPC177x, LPC178x
	/* Project-level external memory bus initialisation function */
void SystemInit_ExtMemCtl(void);
#endif

// ?? void WEAK Default_Handler(void); // Let user can replace default handler

	/* Core interrupt vectors */
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSVC_ISR(void);
void SystemTimer_ISR(void);

	/* Device interrupt vectors */
void WDT_IRQHandler(void);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void TIMER3_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);
void PWM1_IRQHandler(void);
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
void I2C2_IRQHandler(void);
void SPI_IRQHandler(void);
void SSP0_IRQHandler(void);
void SSP1_IRQHandler(void);
void PLL0_IRQHandler(void);
void RTC_IRQHandler(void);
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_GPIO_IRQHandler(void);
void ADC_IRQHandler(void);
void BOD_IRQHandler(void);
void USB_IRQHandler(void);
void CAN_IRQHandler(void);
void DMA_IRQHandler(void);
void I2S_IRQHandler(void);
void ENET_IRQHandler(void);
void RIT_IRQHandler(void);
void MCPWM_IRQHandler(void);
void QEI_IRQHandler(void);
void PLL1_IRQHandler(void);
void USBActivity_IRQHandler(void);
void CANActivity_IRQHandler(void);


/******************************************************************************
*
* Vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
typedef void( *const intfunc )( void );

__attribute__ ((section(".isr_vector")))
intfunc g_pfnVectors[] =
{
	/* Core interrupt vectors */
(intfunc)((unsigned long)&_estack),
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0, // programmer insert image CRC here (for LPC bootloader)
	0,
	0,
	0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSVC_ISR,
	SystemTimer_ISR,

	/* Device interrupt vectors */
	/* 0x40 */
        WDT_IRQHandler,
        TIMER0_IRQHandler,
        TIMER1_IRQHandler,
        TIMER2_IRQHandler,
        TIMER3_IRQHandler,
        UART0_IRQHandler,
        UART1_IRQHandler,
        UART2_IRQHandler,
        UART3_IRQHandler,
        PWM1_IRQHandler,
        I2C0_IRQHandler,
        I2C1_IRQHandler,
        I2C2_IRQHandler,
        SPI_IRQHandler,
        SSP0_IRQHandler,
        SSP1_IRQHandler,
        PLL0_IRQHandler,
        RTC_IRQHandler,
        EINT0_IRQHandler,
        EINT1_IRQHandler,
        EINT2_IRQHandler,
        EINT3_GPIO_IRQHandler,
        ADC_IRQHandler,
        BOD_IRQHandler,
        USB_IRQHandler,
        CAN_IRQHandler,
        DMA_IRQHandler,
        I2S_IRQHandler,
        ENET_IRQHandler,
        RIT_IRQHandler,
        MCPWM_IRQHandler,
        QEI_IRQHandler,
        PLL1_IRQHandler,
	USBActivity_IRQHandler,
	CANActivity_IRQHandler
};

void Reset_Handler(void)
{
	__Init_Data();

	main();

}

extern void init_HW(void);

void __Init_Data(void)
{
	unsigned long *pulSrc, *pulDest;

	pulSrc = &_sidata;

	/* init HW (with clocks) before data/bss initalising ? */

	for(pulDest = &_sdata; pulDest < &_edata; )
		*(pulDest++) = *(pulSrc++);

	for(pulDest = &_sbss; pulDest < &_ebss; )
		*(pulDest++) = 0;

	/* Init hardware before calling constructors */
	init_HW();
#if 0
	/* External memory bus initialisation */
	SystemInit_ExtMemCtl();
#endif
	/* Call constructors */
	unsigned long *ctors;
	for(ctors = &__ctors_start__; ctors < &__ctors_end__; )
		((void(*)(void))(*ctors++))();
}

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/
#pragma weak NMI_Handler = Default_Handler
#pragma weak HardFault_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSVC_ISR = Default_Handler
#pragma weak SystemTimer_ISR = Default_Handler

#pragma weak WDT_IRQHandler = Default_Handler
#pragma weak TIMER0_IRQHandler = Default_Handler
#pragma weak TIMER1_IRQHandler = Default_Handler
#pragma weak TIMER2_IRQHandler = Default_Handler
#pragma weak TIMER3_IRQHandler = Default_Handler
#pragma weak UART0_IRQHandler = Default_Handler
#pragma weak UART1_IRQHandler = Default_Handler
#pragma weak UART2_IRQHandler = Default_Handler
#pragma weak UART3_IRQHandler = Default_Handler
#pragma weak PWM1_IRQHandler = Default_Handler
#pragma weak I2C0_IRQHandler = Default_Handler
#pragma weak I2C1_IRQHandler = Default_Handler
#pragma weak I2C2_IRQHandler = Default_Handler
#pragma weak SPI_IRQHandler = Default_Handler
#pragma weak SSP0_IRQHandler = Default_Handler
#pragma weak SSP1_IRQHandler = Default_Handler
#pragma weak PLL0_IRQHandler = Default_Handler
#pragma weak RTC_IRQHandler = Default_Handler
#pragma weak EINT0_IRQHandler = Default_Handler
#pragma weak EINT1_IRQHandler = Default_Handler
#pragma weak EINT2_IRQHandler = Default_Handler
#pragma weak EINT3_GPIO_IRQHandler = Default_Handler
#pragma weak ADC_IRQHandler = Default_Handler
#pragma weak BOD_IRQHandler = Default_Handler
#pragma weak USB_IRQHandler = Default_Handler
#pragma weak CAN_IRQHandler = Default_Handler
#pragma weak DMA_IRQHandler = Default_Handler
#pragma weak I2S_IRQHandler = Default_Handler
#pragma weak ENET_IRQHandler = Default_Handler
#pragma weak RIT_IRQHandler = Default_Handler
#pragma weak MCPWM_IRQHandler = Default_Handler
#pragma weak QEI_IRQHandler = Default_Handler
#pragma weak PLL1_IRQHandler = Default_Handler
#pragma weak USBActivity_IRQHandler = Default_Handler
#pragma weak CANActivity_IRQHandler = Default_Handler

#if 0
// n.a. for LPC175x, LPC176x
// available for LPC177x, LPC178x
#pragma weak SystemInit_ExtMemCtl = SystemInit_ExtMemCtl_Dummy

void SystemInit_ExtMemCtl_Dummy(void) { }
#endif

void Default_Handler(void)
{
	for (;;) ;
}

