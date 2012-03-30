/*******************************************************************************
*	Startup file for STM32F10x Cortex-M3 MCU
*
* The file is prepared for:
*
*	STM32F10X_LD_VL, STM32F10X_MD_VL, STM32F10X_HD_VL,
*	STM32F10X_LD,    STM32F10X_MD,    STM32F10X_HD,    STM32F10X_XL,
*	STM32F10X_CL
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

	/* Project-level external memory bus initialization function */
void SystemInit_ExtMemCtl(void);

// ?? void WEAK Default_Handler(void);

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
void WWDG_IRQHandler(void);
void PVD_IRQHandler(void);
void TAMPER_IRQHandler(void);
void RTC_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
void DMA1_Channel2_IRQHandler(void);
void DMA1_Channel3_IRQHandler(void);
void DMA1_Channel4_IRQHandler(void);
void DMA1_Channel5_IRQHandler(void);
void DMA1_Channel6_IRQHandler(void);
void DMA1_Channel7_IRQHandler(void);
#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
	void ADC1_IRQHandler(void);
#else
	/* STM32F10X_LD, STM32F10X_MD, STM32F10X_HD, STM32F10X_XL, STM32F10X_CL */
	void ADC1_2_IRQHandler(void);
#endif
#if   defined(STM32F10X_CL)
	void CAN1_TX_IRQHandler(void);
	void CAN1_RX0_IRQHandler(void);
#elif defined(STM32F10X_LD) || defined(STM32F10X_MD) || defined(STM32F10X_HD) || defined(STM32F10X_XL)
	void USB_HP_CAN1_TX_IRQHandler(void);
	void USB_LP_CAN1_RX0_IRQHandler(void);
#endif
#if   defined(STM32F10X_CL) \
   || defined(STM32F10X_LD) || defined(STM32F10X_MD) || defined(STM32F10X_HD) || defined(STM32F10X_XL)
	void CAN1_RX1_IRQHandler(void);
	void CAN1_SCE_IRQHandler(void);
#endif
void EXTI9_5_IRQHandler(void);
void TIM1_BRK_IRQHandler(void);
void TIM1_UP_IRQHandler(void);
void TIM1_TRG_COM_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
#if   defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL) \
   || defined(STM32F10X_MD) || defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	void TIM4_IRQHandler(void);
#endif
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void SPI1_IRQHandler(void);
#if   defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL) \
   || defined(STM32F10X_MD) || defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	void I2C2_EV_IRQHandler(void);
	void I2C2_ER_IRQHandler(void);
	void SPI2_IRQHandler(void);
#endif
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
#if   defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL) \
   || defined(STM32F10X_MD) || defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	void USART3_IRQHandler(void);
#endif
void EXTI15_10_IRQHandler(void);
void RTCAlarm_IRQHandler(void);
#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
	void CEC_IRQHandler(void);
#elif defined(STM32F10X_CL)
	void OTG_FS_WKUP_IRQHandler(void);
#else
	/* STM32F10X_LD, STM32F10X_MD, STM32F10X_HD, STM32F10X_XL */
	void USBWakeUp_IRQHandler(void);
#endif

#if   defined(STM32F10X_HD_VL)
	void TIM12_IRQHandler(void);
	void TIM13_IRQHandler(void);
	void TIM14_IRQHandler(void);
#elif defined(STM32F10X_HD)
	void TIM8_BRK_IRQHandler(void);
	void TIM8_UP_IRQHandler(void);
	void TIM8_TRG_COM_IRQHandler(void);
	void TIM8_CC_IRQHandler(void);
#elif defined(STM32F10X_XL)
	void TIM8_BRK_TIM12_IRQHandler(void);
	void TIM8_UP_TIM13_IRQHandler(void);
	void TIM8_TRG_COM_TIM14_IRQHandler(void);
	void TIM8_CC_IRQHandler(void);
#endif

#if   defined(STM32F10X_HD) || defined(STM32F10X_XL)
	void ADC3_IRQHandler(void);
#endif

#if   defined(STM32F10X_HD_VL) || defined(STM32F10X_HD) || defined(STM32F10X_XL)
	void FSMC_IRQHandler(void);
#endif

#if   defined(STM32F10X_HD) || defined(STM32F10X_XL)
	void SDIO_IRQHandler(void);
#endif

#if   defined(STM32F10X_HD_VL) || defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	void TIM5_IRQHandler(void);
	void SPI3_IRQHandler(void);
	void UART4_IRQHandler(void);
	void UART5_IRQHandler(void);
#endif

#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
	void TIM6_DAC_IRQHandler(void);
#elif defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	void TIM6_IRQHandler(void);
#endif

#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL) \
   || defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	void TIM7_IRQHandler(void);
#endif

#if   defined(STM32F10X_HD_VL) ||  defined(STM32F10X_CL) \
   || defined(STM32F10X_HD) || defined(STM32F10X_XL)
	void DMA2_Channel1_IRQHandler(void);
	void DMA2_Channel2_IRQHandler(void);
	void DMA2_Channel3_IRQHandler(void);
#endif

/* For High-density value line devices, the DMA2 Channel 5 is mapped at postion 60
 * only if the MISC_REMAP bit in the AFIO_MAPR2 register is set and DMA2 Channel 5
 * is connected with DMA2 Channel 4 at position 59 when the MISC_REMAP bit
 * in the AFIO_MAPR2 register is reset.
 */

#if    defined(STM32F10X_HD_VL) || defined(STM32F10X_HD) || defined(STM32F10X_XL)
	void DMA2_Channel4_5_IRQHandler(void);
#endif
#if   defined(STM32F10X_CL)
	void DMA2_Channel4_IRQHandler(void);
#endif
#if   defined(STM32F10X_HD_VL) || defined(STM32F10X_CL)
	void DMA2_Channel5_IRQHandler(void);
#endif

#if   defined(STM32F10X_CL)
	void ETH_IRQHandler(void);
	void ETH_WKUP_IRQHandler(void);
	void CAN2_TX_IRQHandler(void);
	void CAN2_RX0_IRQHandler(void);
	void CAN2_RX1_IRQHandler(void);
	void CAN2_SCE_IRQHandler(void);
	void OTG_FS_IRQHandler(void);
#endif



/******************************************************************************
*
* Vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
typedef void(*const intfunc)(void);

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
	0,
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
	WWDG_IRQHandler,
	PVD_IRQHandler,
	TAMPER_IRQHandler,
	RTC_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA1_Channel1_IRQHandler,
	DMA1_Channel2_IRQHandler,
	DMA1_Channel3_IRQHandler,
	DMA1_Channel4_IRQHandler,
	DMA1_Channel5_IRQHandler,
	DMA1_Channel6_IRQHandler,
	DMA1_Channel7_IRQHandler,

#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
	ADC1_IRQHandler,
#else
	/* STM32F10X_LD, STM32F10X_MD, STM32F10X_HD, STM32F10X_XL, STM32F10X_CL */
	ADC1_2_IRQHandler,
#endif

	/* 0x8C */
#if   defined(STM32F10X_CL)
	CAN1_TX_IRQHandler,
	CAN1_RX0_IRQHandler,
	CAN1_RX1_IRQHandler,
	CAN1_SCE_IRQHandler,
#elif defined(STM32F10X_LD) || defined(STM32F10X_MD) || defined(STM32F10X_HD) || defined(STM32F10X_XL)
	USB_HP_CAN1_TX_IRQHandler,
	USB_LP_CAN1_RX0_IRQHandler,
	CAN1_RX1_IRQHandler,
	CAN1_SCE_IRQHandler,
#else
	/* STM32F10X_LD_VL, STM32F10X_MD_VL, STM32F10X_HD_VL */
	0,0,0,0,
#endif
	/* 0x9C */
	EXTI9_5_IRQHandler,
	TIM1_BRK_IRQHandler,
	TIM1_UP_IRQHandler,
	TIM1_TRG_COM_IRQHandler,
	TIM1_CC_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,

#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_LD)
	0,
#else
	/* STM32F10X_MD_VL, STM32F10X_HD_VL, STM32F10X_MD, STM32F10X_HD, STM32F10X_XL, STM32F10X_CL */
	TIM4_IRQHandler,
#endif

	/* 0xBC */
	I2C1_EV_IRQHandler,
	I2C1_ER_IRQHandler,

#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_LD)
	0,
	0,
	SPI1_IRQHandler,
	0,
#else
	/* STM32F10X_MD_VL, STM32F10X_HD_VL, STM32F10X_MD, STM32F10X_HD, STM32F10X_XL, STM32F10X_CL */
	I2C2_EV_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
#endif

	/* 0xD4 */
	USART1_IRQHandler,
	USART2_IRQHandler,

#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_LD)
	0,
#else
	/* STM32F10X_MD_VL, STM32F10X_HD_VL, STM32F10X_MD, STM32F10X_HD, STM32F10X_XL, STM32F10X_CL */
	USART3_IRQHandler,
#endif

	EXTI15_10_IRQHandler,
	RTCAlarm_IRQHandler,

#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
	CEC_IRQHandler,
#elif defined(STM32F10X_CL)
	OTG_FS_WKUP_IRQHandler,
#else
	/* STM32F10X_LD, STM32F10X_MD, STM32F10X_HD, STM32F10X_XL */
	USBWakeUp_IRQHandler,
#endif

	/* 0xEC */
#if   defined(STM32F10X_HD_VL)
	TIM12_IRQHandler,
	TIM13_IRQHandler,
	TIM14_IRQHandler,
	0,
#elif defined(STM32F10X_HD)
	TIM8_BRK_IRQHandler,
	TIM8_UP_IRQHandler,
	TIM8_TRG_COM_IRQHandler,
	TIM8_CC_IRQHandler,
#elif defined(STM32F10X_XL)
	TIM8_BRK_TIM12_IRQHandler,
	TIM8_UP_TIM13_IRQHandler,
	TIM8_TRG_COM_TIM14_IRQHandler,
	TIM8_CC_IRQHandler,
#else
	/* STM32F10X_LD_VL, STM32F10X_MD_VL, STM32F10X_LD, STM32F10X_MD, STM32F10X_CL */
	0,0,0,0,
#endif

	/* 0xFC */
#if   defined(STM32F10X_HD) || defined(STM32F10X_XL)
	ADC3_IRQHandler,
#else
	/* STM32F10X_LD_VL, STM32F10X_MD_VL, STM32F10X_HD_VL, STM32F10X_LD, STM32F10X_MD, STM32F10X_CL */
	0,
#endif

#if   defined(STM32F10X_HD_VL)
	FSMC_IRQHandler,
	0,
#elif defined(STM32F10X_HD) || defined(STM32F10X_XL)
	FSMC_IRQHandler,
	SDIO_IRQHandler,
#else
	/* STM32F10X_LD_VL, STM32F10X_MD_VL, STM32F10X_LD, STM32F10X_MD, STM32F10X_CL */
	0,0,
#endif

	/* 0x108 ---------------------------------- end of interrupt table for LD, MD */
#if   defined(STM32F10X_LD) || defined(STM32F10X_MD)
	(intfunc)0xF108F85F  /* @0x108 */
#endif

#if   defined(STM32F10X_HD_VL) || defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	TIM5_IRQHandler,
	SPI3_IRQHandler,
	UART4_IRQHandler,
	UART5_IRQHandler,
#elif defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL)
	0,0,0,0,
#endif

	/* 0x118 */
#if   defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
	TIM6_DAC_IRQHandler,
	TIM7_IRQHandler,
#elif defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	TIM6_IRQHandler,
	TIM7_IRQHandler,
#endif

	/* 0x120 */
#if   defined(STM32F10X_HD_VL)
	DMA2_Channel1_IRQHandler,
	DMA2_Channel2_IRQHandler,
	DMA2_Channel3_IRQHandler,
	DMA2_Channel4_5_IRQHandler,
	DMA2_Channel5_IRQHandler,
#elif defined(STM32F10X_CL)
	DMA2_Channel1_IRQHandler,
	DMA2_Channel2_IRQHandler,
	DMA2_Channel3_IRQHandler,
	DMA2_Channel4_IRQHandler,
	DMA2_Channel5_IRQHandler,
#elif defined(STM32F10X_HD) || defined(STM32F10X_XL)
	DMA2_Channel1_IRQHandler,
	DMA2_Channel2_IRQHandler,
	DMA2_Channel3_IRQHandler,
	DMA2_Channel4_5_IRQHandler,
	0,
#endif

	/* 0x134 */
#if   defined(STM32F10X_CL)
	ETH_IRQHandler,
	ETH_WKUP_IRQHandler,
	CAN2_TX_IRQHandler,
	CAN2_RX0_IRQHandler,
	CAN2_RX1_IRQHandler,
	CAN2_SCE_IRQHandler,
	OTG_FS_IRQHandler,
	/* 0x150 */
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0,
	(intfunc)0xF1E0F85F /* @0x1E0 */
#elif defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL)
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,
	(intfunc)0xF1CCF85F /* @0x01CC */
#elif defined(STM32F10X_HD_VL)
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0
	(intfunc)0xF1E0F85F /* @0x1E0 */
#elif defined(STM32F10X_HD) || defined(STM32F10X_XL)
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0,
	0,0,0,0,
	(intfunc)0xF1E0F85F  /* @0x1E0 */
#endif
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

	for(pulDest = &_sdata; pulDest < &_edata; )
		*(pulDest++) = *(pulSrc++);

	for(pulDest = &_sbss; pulDest < &_ebss; )
		*(pulDest++) = 0;

	/* Init hardware before calling constructors */
	init_HW();

	/* External memory bus initialisation */
	// ?? SystemInit_ExtMemCtl();

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
#pragma weak WWDG_IRQHandler = Default_Handler
#pragma weak PVD_IRQHandler = Default_Handler
#pragma weak TAMPER_IRQHandler = Default_Handler
#pragma weak RTC_IRQHandler = Default_Handler
#pragma weak FLASH_IRQHandler = Default_Handler
#pragma weak RCC_IRQHandler = Default_Handler
#pragma weak EXTI0_IRQHandler = Default_Handler
#pragma weak EXTI1_IRQHandler = Default_Handler
#pragma weak EXTI2_IRQHandler = Default_Handler
#pragma weak EXTI3_IRQHandler = Default_Handler
#pragma weak EXTI4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel1_IRQHandler = Default_Handler
#pragma weak DMA1_Channel2_IRQHandler = Default_Handler
#pragma weak DMA1_Channel3_IRQHandler = Default_Handler
#pragma weak DMA1_Channel4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel5_IRQHandler = Default_Handler
#pragma weak DMA1_Channel6_IRQHandler = Default_Handler
#pragma weak DMA1_Channel7_IRQHandler = Default_Handler
#pragma weak ADC1_2_IRQHandler = Default_Handler
#pragma weak ADC1_IRQHandler = Default_Handler
#pragma weak USB_HP_CAN1_TX_IRQHandler = Default_Handler
#pragma weak USB_LP_CAN1_RX0_IRQHandler = Default_Handler
#pragma weak CAN1_TX_IRQHandler = Default_Handler
#pragma weak CAN1_RX0_IRQHandler = Default_Handler
#pragma weak CAN1_RX1_IRQHandler = Default_Handler
#pragma weak CAN1_SCE_IRQHandler = Default_Handler
#pragma weak EXTI9_5_IRQHandler = Default_Handler
#pragma weak TIM1_BRK_IRQHandler = Default_Handler
#pragma weak TIM1_UP_IRQHandler = Default_Handler
#pragma weak TIM1_TRG_COM_IRQHandler = Default_Handler
#pragma weak TIM1_CC_IRQHandler = Default_Handler
#pragma weak TIM2_IRQHandler = Default_Handler
#pragma weak TIM3_IRQHandler = Default_Handler
#pragma weak TIM4_IRQHandler = Default_Handler
#pragma weak I2C1_EV_IRQHandler = Default_Handler
#pragma weak I2C1_ER_IRQHandler = Default_Handler
#pragma weak I2C2_EV_IRQHandler = Default_Handler
#pragma weak I2C2_ER_IRQHandler = Default_Handler
#pragma weak SPI1_IRQHandler = Default_Handler
#pragma weak SPI2_IRQHandler = Default_Handler
#pragma weak USART1_IRQHandler = Default_Handler
#pragma weak USART2_IRQHandler = Default_Handler
#pragma weak USART3_IRQHandler = Default_Handler
#pragma weak EXTI15_10_IRQHandler = Default_Handler
#pragma weak RTCAlarm_IRQHandler = Default_Handler
#pragma weak USBWakeUp_IRQHandler = Default_Handler
#pragma weak CEC_IRQHandler = Default_Handler
#pragma weak OTG_FS_WKUP_IRQHandler = Default_Handler
#pragma weak TIM8_BRK_IRQHandler = Default_Handler
#pragma weak TIM8_UP_IRQHandler = Default_Handler
#pragma weak TIM8_TRG_COM_IRQHandler = Default_Handler
#pragma weak TIM8_CC_IRQHandler = Default_Handler
#pragma weak TIM8_BRK_TIM12_IRQHandler = Default_Handler
#pragma weak TIM8_UP_TIM13_IRQHandler = Default_Handler
#pragma weak TIM8_TRG_COM_TIM14_IRQHandler = Default_Handler
#pragma weak TIM12_IRQHandler = Default_Handler
#pragma weak TIM13_IRQHandler = Default_Handler
#pragma weak TIM14_IRQHandler = Default_Handler
#pragma weak ADC3_IRQHandler = Default_Handler
#pragma weak FSMC_IRQHandler = Default_Handler
#pragma weak SDIO_IRQHandler = Default_Handler
#pragma weak TIM5_IRQHandler = Default_Handler
#pragma weak SPI3_IRQHandler = Default_Handler
#pragma weak UART4_IRQHandler = Default_Handler
#pragma weak UART5_IRQHandler = Default_Handler
#pragma weak TIM6_IRQHandler = Default_Handler
#pragma weak TIM6_DAC_IRQHandler = Default_Handler
#pragma weak TIM7_IRQHandler = Default_Handler
#pragma weak DMA2_Channel1_IRQHandler = Default_Handler
#pragma weak DMA2_Channel2_IRQHandler = Default_Handler
#pragma weak DMA2_Channel3_IRQHandler = Default_Handler
#pragma weak DMA2_Channel4_IRQHandler = Default_Handler
#pragma weak DMA2_Channel4_5_IRQHandler = Default_Handler
#pragma weak DMA2_Channel5_IRQHandler = Default_Handler
#pragma weak ETH_IRQHandler = Default_Handler
#pragma weak ETH_WKUP_IRQHandler = Default_Handler
#pragma weak CAN2_TX_IRQHandler = Default_Handler
#pragma weak CAN2_RX0_IRQHandler = Default_Handler
#pragma weak CAN2_RX1_IRQHandler = Default_Handler
#pragma weak CAN2_SCE_IRQHandler = Default_Handler
#pragma weak OTG_FS_IRQHandler = Default_Handler

#pragma weak SystemInit_ExtMemCtl = SystemInit_ExtMemCtl_Dummy

void Default_Handler(void)
{
	for (;;);
}

void SystemInit_ExtMemCtl_Dummy(void) 
{
}
