/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2009 IAR Systems. All rights reserved.
 *
 * $Revision: 33389 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c

        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     __iar_program_start         ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler
        DCD     WDT_IRQHandler              ; Watchdog Handler
        DCD     TMR0_IRQHandler             ; TIMER0 Handler
        DCD     TMR1_IRQHandler             ; TIMER1 Handler
        DCD     TMR2_IRQHandler             ; TIMER2 Handler
        DCD     TMR3_IRQHandler             ; TIMER3 Handler
        DCD     UART0_IRQHandler            ; UART0 Handler
        DCD     UART1_IRQHandler            ; UART1 Handler
        DCD     UART2_IRQHandler            ; UART2 Handler
        DCD     UART3_IRQHandler            ; UART3 Handler
        DCD     PWM1_IRQHandler             ; PWM1 Handler
        DCD     I2C0_IRQHandler             ; I2C0 Handler
        DCD     I2C1_IRQHandler             ; I2C1 Handler
        DCD     I2C2_IRQHandler             ; I2C2 Handler
        DCD     SPI_IRQHandler              ; SPI Handler
        DCD     SSP0_IRQHandler             ; SSP0 Handler
        DCD     SSP1_IRQHandler             ; SSP1 Handler
        DCD     PLL0_IRQHandler             ; PLL0 Handler
        DCD     RTC_IRQHandler              ; RTC Handler
        DCD     EINT0_IRQHandler            ; EXT Interupt 0 Handler
        DCD     EINT1_IRQHandler            ; EXT Interupt 1 Handler
        DCD     EINT2_IRQHandler            ; EXT Interupt 2 Handler
        DCD     EINT3_IRQHandler            ; EXT Interupt 3 Handler
        DCD     ADC_IRQHandler              ; ADC Handler
        DCD     BOD_IRQHandler              ; BOD Handler
        DCD     USB_IRQHandler              ; USB Handler
        DCD     CAN_IRQHandler              ; CAN Handler
        DCD     GPDMA_IRQHandler            ; General Purpose DMA Handler
        DCD     I2S_IRQHandler              ; I2S Handler
        DCD     Ethernet_IRQHandler         ; Ethernet Handler
        DCD     RIT_IRQHandler              ; Repetitive Interrupt Timer Handler
        DCD     MotorControlPWM_IRQHandler  ; Motor Control PWM Handler
        DCD     QE_IRQHandler               ; Quadrature Encoder Handler
        DCD     PLL1_IRQHandler             ; PLL1 Handler

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

      PUBWEAK NMI_Handler       
      PUBWEAK HardFault_Handler 
      PUBWEAK MemManage_Handler 
      PUBWEAK BusFault_Handler  
      PUBWEAK UsageFault_Handler
      PUBWEAK SVC_Handler       
      PUBWEAK DebugMon_Handler  
      PUBWEAK PendSV_Handler    
      PUBWEAK SysTick_Handler   
      PUBWEAK WDT_IRQHandler    
      PUBWEAK TMR0_IRQHandler   
      PUBWEAK TMR1_IRQHandler   
      PUBWEAK TMR2_IRQHandler   
      PUBWEAK TMR3_IRQHandler   
      PUBWEAK UART0_IRQHandler  
      PUBWEAK UART1_IRQHandler  
      PUBWEAK UART2_IRQHandler  
      PUBWEAK UART3_IRQHandler  
      PUBWEAK PWM1_IRQHandler   
      PUBWEAK I2C0_IRQHandler   
      PUBWEAK I2C1_IRQHandler   
      PUBWEAK I2C2_IRQHandler   
      PUBWEAK SPI_IRQHandler    
      PUBWEAK SSP0_IRQHandler   
      PUBWEAK SSP1_IRQHandler   
      PUBWEAK PLL0_IRQHandler   
      PUBWEAK RTC_IRQHandler    
      PUBWEAK EINT0_IRQHandler  
      PUBWEAK EINT1_IRQHandler  
      PUBWEAK EINT2_IRQHandler  
      PUBWEAK EINT3_IRQHandler  
      PUBWEAK ADC_IRQHandler    
      PUBWEAK BOD_IRQHandler    
      PUBWEAK USB_IRQHandler    
      PUBWEAK CAN_IRQHandler    
      PUBWEAK GPDMA_IRQHandler  
      PUBWEAK I2S_IRQHandler    
      PUBWEAK Ethernet_IRQHandler         
      PUBWEAK RIT_IRQHandler              
      PUBWEAK MotorControlPWM_IRQHandler  
      PUBWEAK QE_IRQHandler               
      PUBWEAK PLL1_IRQHandler             

        SECTION .text:CODE:REORDER(1)
        THUMB
NMI_Handler       
HardFault_Handler 
MemManage_Handler 
BusFault_Handler  
UsageFault_Handler
SVC_Handler       
DebugMon_Handler  
PendSV_Handler    
SysTick_Handler   
WDT_IRQHandler    
TMR0_IRQHandler   
TMR1_IRQHandler   
TMR2_IRQHandler   
TMR3_IRQHandler   
UART0_IRQHandler  
UART1_IRQHandler  
UART2_IRQHandler  
UART3_IRQHandler  
PWM1_IRQHandler   
I2C0_IRQHandler   
I2C1_IRQHandler   
I2C2_IRQHandler   
SPI_IRQHandler    
SSP0_IRQHandler   
SSP1_IRQHandler   
PLL0_IRQHandler   
RTC_IRQHandler    
EINT0_IRQHandler  
EINT1_IRQHandler  
EINT2_IRQHandler  
EINT3_IRQHandler  
ADC_IRQHandler    
BOD_IRQHandler    
USB_IRQHandler    
CAN_IRQHandler    
GPDMA_IRQHandler  
I2S_IRQHandler    
Ethernet_IRQHandler         
RIT_IRQHandler              
MotorControlPWM_IRQHandler  
QE_IRQHandler               
PLL1_IRQHandler             
Default_Handler          
        B Default_Handler 
        END
