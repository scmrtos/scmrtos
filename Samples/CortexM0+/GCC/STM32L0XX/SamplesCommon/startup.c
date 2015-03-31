/*******************************************************************************
*	Startup file for STM32L053 Cortex-M0+ MCU
*
* The file is prepared for:
*
*	STM32L051xx, STM32L052xx, STM32L053xx
*	STM32L062xx, STM32L063xx, STM32L061xx
*******************************************************************************/

#include <string.h>

extern unsigned char _sidata;
extern unsigned char _sdata;
extern unsigned char _edata;
extern unsigned char _sbss;
extern unsigned char _ebss;
extern unsigned long _estack;
extern unsigned long __ctors_start__;
extern unsigned long __ctors_end__;

extern unsigned long __dtors_start__;
extern unsigned long __dtors_end__;

void Reset_Handler(void) __attribute__((__interrupt__));

	/* Core interrupt vectors */
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

	/* Device interrupt vectors */
void WWDG_IRQHandler               (void);
void PVD_IRQHandler                (void);
void RTC_IRQHandler                (void);
void FLASH_IRQHandler              (void);
void RCC_IRQHandler                (void);
void RCC_CRS_IRQHandler            (void);
void EXTI0_1_IRQHandler            (void);
void EXTI2_3_IRQHandler            (void);
void EXTI4_15_IRQHandler           (void);
void TSC_IRQHandler                (void);
void DMA1_Channel1_IRQHandler      (void);
void DMA1_Channel2_3_IRQHandler    (void);
void DMA1_Channel4_5_6_7_IRQHandler(void);
void ADC1_COMP_IRQHandler          (void);
void LPTIM1_IRQHandler             (void);
void TIM2_IRQHandler               (void);
void TIM6_DAC_IRQHandler           (void);
void TIM21_IRQHandler              (void);
void TIM22_IRQHandler              (void);
void I2C1_IRQHandler               (void);
void I2C2_IRQHandler               (void);
void SPI1_IRQHandler               (void);
void SPI2_IRQHandler               (void);
void USART1_IRQHandler             (void);
void USART2_IRQHandler             (void);
void LPUART1_IRQHandler            (void);
void RNG_LPUART1_IRQHandler        (void);
void AES_LPUART1_IRQHandler        (void);
void AES_RNG_LPUART1_IRQHandler    (void);
void LCD_IRQHandler                (void);
void USB_IRQHandler                (void);


/******************************************************************************
*
* Vector table for a Cortex M0.
*
******************************************************************************/
typedef void( *const intfunc )( void );

__attribute__ ((used))
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
	(intfunc)((unsigned long)&_estack),

	/* Core interrupt vectors */
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,

	/* Device interrupt vectors */
	WWDG_IRQHandler,                   /* Window WatchDog              */
	PVD_IRQHandler,                    /* PVD through EXTI Line detection */
	RTC_IRQHandler,                    /* RTC through the EXTI line     */
	FLASH_IRQHandler,                  /* FLASH                        */
#if defined (STM32L051xx) || defined (STM32L061xx)
	RCC_IRQHandler,                    /* RCC                          */
#else
	RCC_CRS_IRQHandler,                /* RCC and CRS                  */
#endif
	EXTI0_1_IRQHandler,                /* EXTI Line 0 and 1            */
	EXTI2_3_IRQHandler,                /* EXTI Line 2 and 3            */
	EXTI4_15_IRQHandler,               /* EXTI Line 4 to 15            */
#if defined (STM32L051xx) || defined (STM32L061xx)
	0,
#else
	TSC_IRQHandler,                     /* TSC                           */
#endif
	DMA1_Channel1_IRQHandler,          // DMA1 Channel 1
	DMA1_Channel2_3_IRQHandler,        // DMA1 Channel 2 and Channel 3
	DMA1_Channel4_5_6_7_IRQHandler,    // DMA1 Channel 4, Channel 5, Channel 6 and Channel 7
	ADC1_COMP_IRQHandler,              // ADC1, COMP1 and COMP2
	LPTIM1_IRQHandler,                 // LPTIM1
	0,                                 // Reserved
	TIM2_IRQHandler,                   // TIM2
	0,                                 // Reserved
#if defined (STM32L051xx) || defined (STM32L061xx)
	TIM6_IRQHandler,                   // TIM6
#else
	TIM6_DAC_IRQHandler,               // TIM6 and DAC
#endif
	0,                                 // Reserved
	0,                                 // Reserved
	TIM21_IRQHandler,                  // TIM21
	0,                                 // Reserved
	TIM22_IRQHandler,                  // TIM22
	I2C1_IRQHandler,                   // I2C1
	I2C2_IRQHandler,                   // I2C2
	SPI1_IRQHandler,                   // SPI1
	SPI2_IRQHandler,                   // SPI2
	USART1_IRQHandler,                 // USART1
	USART2_IRQHandler,                 // USART2
#if defined (STM32L051xx)
	LPUART1_IRQHandler,                // LPUART1
#elif defined (STM32L052xx) || defined (STM32L053xx)
	RNG_LPUART1_IRQHandler,            // RNG and LPUART1
#elif defined (STM32L061xx)
	AES_LPUART1_IRQHandler,            // AES and LPUART1
#else
	AES_RNG_LPUART1_IRQHandler,        // AES, RNG and LPUART1
#endif

#if defined (STM32L053xx) || defined (STM32L063xx)
	LCD_IRQHandler,                    // LCD
#else
	0,
#endif

#if defined (STM32L052xx) || defined (STM32L053xx) || defined (STM32L062xx) || defined (STM32L063xx)
	USB_IRQHandler                     // USB
#else
	0
#endif
};

extern void init_HW(void);
extern int main(void);

void Reset_Handler(void)
{
	memcpy(&_sdata, &_sidata, &_edata - &_sdata); // copy initialized variables
	memset(&_sbss, 0, &_ebss - &_sbss);           // zero-fill uninitialized variables

	init_HW();  // initialize hardware before calling constructors

	// call constructors
	for(unsigned long *ctors = &__ctors_start__; ctors < &__ctors_end__; )
		((void(*)(void))(*ctors++))();

	main();
}

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/
#pragma weak NMI_Handler                     = Default_Handler
#pragma weak HardFault_Handler               = Default_Handler
#pragma weak SVC_Handler                     = Default_Handler
#pragma weak DebugMon_Handler                = Default_Handler
#pragma weak PendSV_Handler                  = Default_Handler
#pragma weak SysTick_Handler                 = Default_Handler

#pragma weak WWDG_IRQHandler                 = Default_Handler
#pragma weak PVD_IRQHandler                  = Default_Handler
#pragma weak RTC_IRQHandler                  = Default_Handler
#pragma weak FLASH_IRQHandler                = Default_Handler
#pragma weak RCC_IRQHandler                  = Default_Handler
#pragma weak RCC_CRS_IRQHandler              = Default_Handler
#pragma weak EXTI0_1_IRQHandler              = Default_Handler
#pragma weak EXTI2_3_IRQHandler              = Default_Handler
#pragma weak EXTI4_15_IRQHandler             = Default_Handler
#pragma weak TSC_IRQHandler                  = Default_Handler
#pragma weak DMA1_Channel1_IRQHandler        = Default_Handler
#pragma weak DMA1_Channel2_3_IRQHandler      = Default_Handler
#pragma weak DMA1_Channel4_5_6_7_IRQHandler  = Default_Handler
#pragma weak ADC1_COMP_IRQHandler            = Default_Handler
#pragma weak LPTIM1_IRQHandler               = Default_Handler
#pragma weak TIM2_IRQHandler                 = Default_Handler
#pragma weak TIM6_DAC_IRQHandler             = Default_Handler
#pragma weak TIM21_IRQHandler                = Default_Handler
#pragma weak TIM22_IRQHandler                = Default_Handler
#pragma weak I2C1_IRQHandler                 = Default_Handler
#pragma weak I2C2_IRQHandler                 = Default_Handler
#pragma weak SPI1_IRQHandler                 = Default_Handler
#pragma weak SPI2_IRQHandler                 = Default_Handler
#pragma weak USART1_IRQHandler               = Default_Handler
#pragma weak USART2_IRQHandler               = Default_Handler
#pragma weak LPUART1_IRQHandler              = Default_Handler
#pragma weak RNG_LPUART1_IRQHandler          = Default_Handler
#pragma weak AES_LPUART1_IRQHandler          = Default_Handler
#pragma weak AES_RNG_LPUART1_IRQHandler      = Default_Handler
#pragma weak LCD_IRQHandler                  = Default_Handler
#pragma weak USB_IRQHandler                  = Default_Handler

void Default_Handler(void)
{
	for (;;);
}
