/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_it.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains the headers of the interrupt handlers.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_lib.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif

void NMIException(void);
void HardFaultException(void);
void MemManageException(void);
void BusFaultException(void);
void UsageFaultException(void);
void DebugMonitor(void);
void SVCHandler(void);
void PendSV_Handler();
void SysTick_Handler();
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
void DMAChannel1_IRQHandler(void);
void DMAChannel2_IRQHandler(void);
void DMAChannel3_IRQHandler(void);
void DMAChannel4_IRQHandler(void);
void DMAChannel5_IRQHandler(void);
void DMAChannel6_IRQHandler(void);
void DMAChannel7_IRQHandler(void);
void ADC_IRQHandler(void);
void USB_HP_CAN_TX_IRQHandler(void);
void USB_LP_CAN_RX0_IRQHandler(void);
void CAN_RX1_IRQHandler(void);
void CAN_SCE_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void TIM1_BRK_IRQHandler(void);
void TIM1_UP_IRQHandler(void);
void TIM1_TRG_COM_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void RTCAlarm_IRQHandler(void);
void USBWakeUp_IRQHandler(void);

#ifdef __cplusplus
}
#endif
					 
#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
