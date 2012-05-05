/*******************************************************************************
*	Startup file for STM32F4xx Cortex-M4F MCU
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

void Reset_Handler(void) __attribute__((__interrupt__));
extern int main(void);
void __Init_Data(void);


/* Core interrupt vectors */
void NMI_Handler                  (void);
void HardFault_Handler            (void);
void MemManage_Handler            (void);
void BusFault_Handler             (void);
void UsageFault_Handler           (void);
void SVC_Handler                  (void);
void DebugMon_Handler             (void);
void PendSVC_ISR                  (void);
void SystemTimer_ISR              (void);

/* External Interrupts */
void WWDG_IRQHandler              (void);
void PVD_IRQHandler               (void);
void TAMP_STAMP_IRQHandler        (void);
void RTC_WKUP_IRQHandler          (void);
void FLASH_IRQHandler             (void);
void RCC_IRQHandler               (void);
void EXTI0_IRQHandler             (void);
void EXTI1_IRQHandler             (void);
void EXTI2_IRQHandler             (void);
void EXTI3_IRQHandler             (void);
void EXTI4_IRQHandler             (void);
void DMA1_Stream0_IRQHandler      (void);
void DMA1_Stream1_IRQHandler      (void);
void DMA1_Stream2_IRQHandler      (void);
void DMA1_Stream3_IRQHandler      (void);
void DMA1_Stream4_IRQHandler      (void);
void DMA1_Stream5_IRQHandler      (void);
void DMA1_Stream6_IRQHandler      (void);
void ADC_IRQHandler               (void);
void CAN1_TX_IRQHandler           (void);
void CAN1_RX0_IRQHandler          (void);
void CAN1_RX1_IRQHandler          (void);
void CAN1_SCE_IRQHandler          (void);
void EXTI9_5_IRQHandler           (void);
void TIM1_BRK_TIM9_IRQHandler     (void);
void TIM1_UP_TIM10_IRQHandler     (void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM1_CC_IRQHandler           (void);
void TIM2_IRQHandler              (void);
void TIM3_IRQHandler              (void);
void TIM4_IRQHandler              (void);
void I2C1_EV_IRQHandler           (void);
void I2C1_ER_IRQHandler           (void);
void I2C2_EV_IRQHandler           (void);
void I2C2_ER_IRQHandler           (void);
void SPI1_IRQHandler              (void);
void SPI2_IRQHandler              (void);
void USART1_IRQHandler            (void);
void USART2_IRQHandler            (void);
void USART3_IRQHandler            (void);
void EXTI15_10_IRQHandler         (void);
void RTC_Alarm_IRQHandler         (void);
void OTG_FS_WKUP_IRQHandler       (void);
void TIM8_BRK_TIM12_IRQHandler    (void);
void TIM8_UP_TIM13_IRQHandler     (void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);
void TIM8_CC_IRQHandler           (void);
void DMA1_Stream7_IRQHandler      (void);
void FSMC_IRQHandler              (void);
void SDIO_IRQHandler              (void);
void TIM5_IRQHandler              (void);
void SPI3_IRQHandler              (void);
void UART4_IRQHandler             (void);
void UART5_IRQHandler             (void);
void TIM6_DAC_IRQHandler          (void);
void TIM7_IRQHandler              (void);
void DMA2_Stream0_IRQHandler      (void);
void DMA2_Stream1_IRQHandler      (void);
void DMA2_Stream2_IRQHandler      (void);
void DMA2_Stream3_IRQHandler      (void);
void DMA2_Stream4_IRQHandler      (void);
void ETH_IRQHandler               (void);
void ETH_WKUP_IRQHandler          (void);
void CAN2_TX_IRQHandler           (void);
void CAN2_RX0_IRQHandler          (void);
void CAN2_RX1_IRQHandler          (void);
void CAN2_SCE_IRQHandler          (void);
void OTG_FS_IRQHandler            (void);
void DMA2_Stream5_IRQHandler      (void);
void DMA2_Stream6_IRQHandler      (void);
void DMA2_Stream7_IRQHandler      (void);
void USART6_IRQHandler            (void);
void I2C3_EV_IRQHandler           (void);
void I2C3_ER_IRQHandler           (void);
void OTG_HS_EP1_OUT_IRQHandler    (void);
void OTG_HS_EP1_IN_IRQHandler     (void);
void OTG_HS_WKUP_IRQHandler       (void);
void OTG_HS_IRQHandler            (void);
void DCMI_IRQHandler              (void);
void CRYP_IRQHandler              (void);
void HASH_RNG_IRQHandler          (void);
void FPU_IRQHandler               (void);

/******************************************************************************
* Vector table for a Cortex M4F.
******************************************************************************/
typedef void( *const intfunc )( void );

__attribute__ ((used))
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
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

	WWDG_IRQHandler,                   /* Window WatchDog              */
	PVD_IRQHandler,                    /* PVD through EXTI Line detection */
	TAMP_STAMP_IRQHandler,             /* Tamper and TimeStamps through the EXTI line */
	RTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line */
	FLASH_IRQHandler,                  /* FLASH                        */
	RCC_IRQHandler,                    /* RCC                          */
	EXTI0_IRQHandler,                  /* EXTI Line0                   */
	EXTI1_IRQHandler,                  /* EXTI Line1                   */
	EXTI2_IRQHandler,                  /* EXTI Line2                   */
	EXTI3_IRQHandler,                  /* EXTI Line3                   */
	EXTI4_IRQHandler,                  /* EXTI Line4                   */
	DMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                */
	DMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                */
	DMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                */
	DMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                */
	DMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                */
	DMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                */
	DMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                */
	ADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s         */
	CAN1_TX_IRQHandler,                /* CAN1 TX                      */
	CAN1_RX0_IRQHandler,               /* CAN1 RX0                     */
	CAN1_RX1_IRQHandler,               /* CAN1 RX1                     */
	CAN1_SCE_IRQHandler,               /* CAN1 SCE                     */
	EXTI9_5_IRQHandler,                /* External Line[9:5]s          */
	TIM1_BRK_TIM9_IRQHandler,          /* TIM1 Break and TIM9          */
	TIM1_UP_TIM10_IRQHandler,          /* TIM1 Update and TIM10        */
	TIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11 */
	TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
	TIM2_IRQHandler,                   /* TIM2                         */
	TIM3_IRQHandler,                   /* TIM3                         */
	TIM4_IRQHandler,                   /* TIM4                         */
	I2C1_EV_IRQHandler,                /* I2C1 Event                   */
	I2C1_ER_IRQHandler,                /* I2C1 Error                   */
	I2C2_EV_IRQHandler,                /* I2C2 Event                   */
	I2C2_ER_IRQHandler,                /* I2C2 Error                   */
	SPI1_IRQHandler,                   /* SPI1                         */
	SPI2_IRQHandler,                   /* SPI2                         */
	USART1_IRQHandler,                 /* USART1                       */
	USART2_IRQHandler,                 /* USART2                       */
	USART3_IRQHandler,                 /* USART3                       */
	EXTI15_10_IRQHandler,              /* External Line[15:10]s        */
	RTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line */
	OTG_FS_WKUP_IRQHandler,            /* USB OTG FS Wakeup through EXTI line */
	TIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12         */
	TIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13        */
	TIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14 */
	TIM8_CC_IRQHandler,                /* TIM8 Capture Compare         */
	DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                 */
	FSMC_IRQHandler,                   /* FSMC                         */
	SDIO_IRQHandler,                   /* SDIO                         */
	TIM5_IRQHandler,                   /* TIM5                         */
	SPI3_IRQHandler,                   /* SPI3                         */
	UART4_IRQHandler,                  /* UART4                        */
	UART5_IRQHandler,                  /* UART5                        */
	TIM6_DAC_IRQHandler,               /* TIM6 and DAC1&2 underrun errors */
	TIM7_IRQHandler,                   /* TIM7                         */
	DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                */
	DMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                */
	DMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                */
	DMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                */
	DMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                */
	ETH_IRQHandler,                    /* Ethernet                     */
	ETH_WKUP_IRQHandler,               /* Ethernet Wakeup through EXTI line */
	CAN2_TX_IRQHandler,                /* CAN2 TX                      */
	CAN2_RX0_IRQHandler,               /* CAN2 RX0                     */
	CAN2_RX1_IRQHandler,               /* CAN2 RX1                     */
	CAN2_SCE_IRQHandler,               /* CAN2 SCE                     */
	OTG_FS_IRQHandler,                 /* USB OTG FS                   */
	DMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                */
	DMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                */
	DMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                */
	USART6_IRQHandler,                 /* USART6                       */
	I2C3_EV_IRQHandler,                /* I2C3 event                   */
	I2C3_ER_IRQHandler,                /* I2C3 error                   */
	OTG_HS_EP1_OUT_IRQHandler,         /* USB OTG HS End Point 1 Out   */
	OTG_HS_EP1_IN_IRQHandler,          /* USB OTG HS End Point 1 In    */
	OTG_HS_WKUP_IRQHandler,            /* USB OTG HS Wakeup through EXTI */
	OTG_HS_IRQHandler,                 /* USB OTG HS                   */
	DCMI_IRQHandler,                   /* DCMI                         */
	CRYP_IRQHandler,                   /* CRYP crypto                  */
	HASH_RNG_IRQHandler,               /* Hash and Rng                 */
	FPU_IRQHandler                     /* FPU                          */
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
#pragma weak NMI_Handler                    = Default_Handler
#pragma weak HardFault_Handler              = Default_Handler
#pragma weak MemManage_Handler              = Default_Handler
#pragma weak BusFault_Handler               = Default_Handler
#pragma weak UsageFault_Handler             = Default_Handler
#pragma weak SVC_Handler                    = Default_Handler
#pragma weak DebugMon_Handler               = Default_Handler
#pragma weak PendSVC_ISR                    = Default_Handler
#pragma weak WWDG_IRQHandler                = Default_Handler
#pragma weak PVD_IRQHandler                 = Default_Handler
#pragma weak TAMP_STAMP_IRQHandler          = Default_Handler
#pragma weak RTC_WKUP_IRQHandler            = Default_Handler
#pragma weak FLASH_IRQHandler               = Default_Handler
#pragma weak RCC_IRQHandler                 = Default_Handler
#pragma weak EXTI0_IRQHandler               = Default_Handler
#pragma weak EXTI1_IRQHandler               = Default_Handler
#pragma weak EXTI2_IRQHandler               = Default_Handler
#pragma weak EXTI3_IRQHandler               = Default_Handler
#pragma weak EXTI4_IRQHandler               = Default_Handler
#pragma weak DMA1_Stream0_IRQHandler        = Default_Handler
#pragma weak DMA1_Stream1_IRQHandler        = Default_Handler
#pragma weak DMA1_Stream2_IRQHandler        = Default_Handler
#pragma weak DMA1_Stream3_IRQHandler        = Default_Handler
#pragma weak DMA1_Stream4_IRQHandler        = Default_Handler
#pragma weak DMA1_Stream5_IRQHandler        = Default_Handler
#pragma weak DMA1_Stream6_IRQHandler        = Default_Handler
#pragma weak ADC_IRQHandler                 = Default_Handler
#pragma weak CAN1_TX_IRQHandler             = Default_Handler
#pragma weak CAN1_RX0_IRQHandler            = Default_Handler
#pragma weak CAN1_RX1_IRQHandler            = Default_Handler
#pragma weak CAN1_SCE_IRQHandler            = Default_Handler
#pragma weak EXTI9_5_IRQHandler             = Default_Handler
#pragma weak TIM1_BRK_TIM9_IRQHandler       = Default_Handler
#pragma weak TIM1_UP_TIM10_IRQHandler       = Default_Handler
#pragma weak TIM1_TRG_COM_TIM11_IRQHandler  = Default_Handler
#pragma weak TIM1_CC_IRQHandler             = Default_Handler
#pragma weak TIM2_IRQHandler                = Default_Handler
#pragma weak TIM3_IRQHandler                = Default_Handler
#pragma weak TIM4_IRQHandler                = Default_Handler
#pragma weak I2C1_EV_IRQHandler             = Default_Handler
#pragma weak I2C1_ER_IRQHandler             = Default_Handler
#pragma weak I2C2_EV_IRQHandler             = Default_Handler
#pragma weak I2C2_ER_IRQHandler             = Default_Handler
#pragma weak SPI1_IRQHandler                = Default_Handler
#pragma weak SPI2_IRQHandler                = Default_Handler
#pragma weak USART1_IRQHandler              = Default_Handler
#pragma weak USART2_IRQHandler              = Default_Handler
#pragma weak USART3_IRQHandler              = Default_Handler
#pragma weak EXTI15_10_IRQHandler           = Default_Handler
#pragma weak RTC_Alarm_IRQHandler           = Default_Handler
#pragma weak OTG_FS_WKUP_IRQHandler         = Default_Handler
#pragma weak TIM8_BRK_TIM12_IRQHandler      = Default_Handler
#pragma weak TIM8_UP_TIM13_IRQHandler       = Default_Handler
#pragma weak TIM8_TRG_COM_TIM14_IRQHandler  = Default_Handler
#pragma weak TIM8_CC_IRQHandler             = Default_Handler
#pragma weak DMA1_Stream7_IRQHandler        = Default_Handler
#pragma weak FSMC_IRQHandler                = Default_Handler
#pragma weak SDIO_IRQHandler                = Default_Handler
#pragma weak TIM5_IRQHandler                = Default_Handler
#pragma weak SPI3_IRQHandler                = Default_Handler
#pragma weak UART4_IRQHandler               = Default_Handler
#pragma weak UART5_IRQHandler               = Default_Handler
#pragma weak TIM6_DAC_IRQHandler            = Default_Handler
#pragma weak TIM7_IRQHandler                = Default_Handler
#pragma weak DMA2_Stream0_IRQHandler        = Default_Handler
#pragma weak DMA2_Stream1_IRQHandler        = Default_Handler
#pragma weak DMA2_Stream2_IRQHandler        = Default_Handler
#pragma weak DMA2_Stream3_IRQHandler        = Default_Handler
#pragma weak DMA2_Stream4_IRQHandler        = Default_Handler
#pragma weak ETH_IRQHandler                 = Default_Handler
#pragma weak ETH_WKUP_IRQHandler            = Default_Handler
#pragma weak CAN2_TX_IRQHandler             = Default_Handler
#pragma weak CAN2_RX0_IRQHandler            = Default_Handler
#pragma weak CAN2_RX1_IRQHandler            = Default_Handler
#pragma weak CAN2_SCE_IRQHandler            = Default_Handler
#pragma weak OTG_FS_IRQHandler              = Default_Handler
#pragma weak DMA2_Stream5_IRQHandler        = Default_Handler
#pragma weak DMA2_Stream6_IRQHandler        = Default_Handler
#pragma weak DMA2_Stream7_IRQHandler        = Default_Handler
#pragma weak USART6_IRQHandler              = Default_Handler
#pragma weak I2C3_EV_IRQHandler             = Default_Handler
#pragma weak I2C3_ER_IRQHandler             = Default_Handler
#pragma weak OTG_HS_EP1_OUT_IRQHandler      = Default_Handler
#pragma weak OTG_HS_EP1_IN_IRQHandler       = Default_Handler
#pragma weak OTG_HS_WKUP_IRQHandler         = Default_Handler
#pragma weak OTG_HS_IRQHandler              = Default_Handler
#pragma weak DCMI_IRQHandler                = Default_Handler
#pragma weak CRYP_IRQHandler                = Default_Handler
#pragma weak HASH_RNG_IRQHandler            = Default_Handler
#pragma weak FPU_IRQHandler                 = Default_Handler

void Default_Handler(void)
{
	for (;;);
}
