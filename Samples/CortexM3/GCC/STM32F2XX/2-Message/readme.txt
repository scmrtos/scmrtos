
 2-Message demo.

In addition to demonstration of message usage, this project demonstrates custom system timer usage.
Instead of Systick timer, which is used by default, the TIM4 timer is used as system timer.
To do this the folowing steps is performed:

1. Added void __init_system_timer() function (extern "C"). It initializes TIM4 (in custom-timer.cpp).
2. Added OS_INTERRUPT void OS::SystemTimer_ISR() interrupt handler (in custom-timer.cpp).
3. Placed SystemTimer_ISR at TIM4 interrupt entry into vector table (in startup-stm32f4xx.c).
