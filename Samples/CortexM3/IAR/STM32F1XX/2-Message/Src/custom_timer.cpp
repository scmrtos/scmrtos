
#include "stm32F10x.h"
#include <scmRTOS.h>

void init_custom_system_timer()
{
   RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

   NVIC_SetPriority(TIM4_IRQn, 255);
   NVIC_EnableIRQ(TIM4_IRQn);

   TIM4->PSC = 1;
   TIM4->ARR = 8000;           // 1KHz
   TIM4->EGR = TIM_EGR_UG;     // generate an update event to reload the prescaler value immediately
   TIM4->DIER = TIM_DIER_UIE;  // enable update interrupt
   TIM4->CR1 = TIM_CR1_CEN;    // run timer
}

OS_INTERRUPT void TIM4_IRQHandler()
{
   if (TIM4->SR & TIM_SR_UIF)
   {
       TIM4->SR = ~TIM_SR_UIF;
       OS::SystemTimer_Handler();
   }
}