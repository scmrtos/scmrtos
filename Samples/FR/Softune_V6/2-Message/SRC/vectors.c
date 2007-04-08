/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES.                                             */
/*                 (C) Fujitsu Microelectronics Europe GmbH                  */
/*------------------------------------------------------------------------
  VECTORS.C
  - Interrupt level (priority) setting
  - Interrupt vector definition

 08.04.05  1.00   UMa    Initial Version
-------------------------------------------------------------------------*/

#include "MB91270.h"


/*------------------------------------------------------------------------
   InitIrqLevels()

   This function  pre-sets all interrupt control registers. It can be used
   to set all interrupt priorities in static applications. If this file
   contains assignments to dedicated resources, verify  that the
   appropriate controller is used.

   NOTE: value 31 disables the interrupt and value 0 sets highest priority.
-------------------------------------------------------------------------*/
void InitIrqLevels(void)
{
    /*  ICRxx */ 
    ICR00 = 31;    /* External Interrupt 0         */
    ICR01 = 31;    /* External Interrupt 1         */
    ICR02 = 31;    /* External Interrupt 2         */
    ICR03 = 31;    /* External Interrupt 3         */
    ICR04 = 31;    /* External Interrupt 4         */ 
    ICR05 = 31;    /* External Interrupt 5         */
    ICR06 = 31;    /* External Interrupt 6         */
    ICR07 = 31;    /* External Interrupt 7         */
    ICR08 = 31;    /* Reload Timer 0               */
    ICR09 = 31;    /* Reload Timer 1               */
    ICR10 = 31;    /* Reload Timer 2               */
    ICR11 = 31;    /* LIN-UART 0 RX                */
    ICR12 = 31;    /* LIN-UART 0 TX                */
    ICR13 = 31;    /* LIN-UART 1 RX                */
    ICR14 = 31;    /* LIN-UART 1 TX                */
    ICR15 = 31;    /* LIN-UART 2 RX                */
    ICR16 = 31;    /* LIN-UART 2 TX                */
    ICR17 = 31;    /* CAN 0                        */ 
    ICR18 = 31;    /* CAN 1/ICU 6/7                */
    ICR19 = 31;    /* CAN 1                        */
    ICR20 = 31;    /* LIN-UART 3/5 RX              */
    ICR21 = 31;    /* LIN-UART 3/5 TX              */
    ICR22 = 31;    /* LIN-UART 4/6 RX              */
    ICR23 = 31;    /* LIN-UART 4/6 TX              */
    ICR24 = 31;    /* I2C 0                        */
    ICR25 = 31;    /* I2C 1 / UDC 3                */
    ICR26 = 31;    /* I2C 2                        */
    ICR27 = 31;    /* A/D Converter 0              */
    ICR28 = 31;    /* RTC                          */
    ICR29 = 31;    /* UDC 1                        */
    ICR30 = 31;    /* Main osc. stabil. wait timer */
    ICR31 = 31;    /* TBT overflow                 */
    ICR32 = 31;    /* Prog. Pulse Gen. 0/1/4/5     */
    ICR33 = 31;    /* Prog. Pulse Gen. 2/3/6/7     */
    ICR34 = 31;    /* Prog. Pulse Gen. 8/9/C/D     */
    ICR35 = 31;    /* Prog. Pulse Gen. A/B/E/F     */
    ICR36 = 31;    /* FRT 0/1                      */
    ICR37 = 31;    /* FRT 2/3                      */
    ICR38 = 31;    /* ICU 0/1/2/3                  */
    ICR39 = 31;    /* ICU 4/5                      */
    ICR40 = 31;    /* OCU 0/1/2/3 UDC 3            */
    ICR41 = 31;    /* OCU 4/5/6/7                  */
    ICR42 = 31;    /* UDC 0                        */
    ICR43 = 31;    /* Ext. Int. 8/9/10/11          */
    ICR44 = 31;    /* Ext. Int. 12 to 39           */
    ICR45 = 31;    /* ROM collection Interrupt     */
    ICR46 = 31;    /* DMA                          */
    ICR47 = 31;    /* Delayed Interrupt            */
}

/*------------------------------------------------------------------------
   Prototypes
   
   Add your own prototypes here. Each vector definition needs its proto-
   type. Either do it here or include a header file containing them.

-------------------------------------------------------------------------*/

__interrupt void DefaultIRQHandler (void);
__interrupt void _start (void);               /* reset Vector definition, 
                                                start symbol is defined in startup.asm */


//*************************************************************************
__interrupt void ih_Timer2 (void);


//*************************************************************************
// scmRTOS System interrupts
__interrupt void SystemTimer_ISR (void);
__interrupt void ContextSwitcher_ISR (void);


/*------------------------------------------------------------------------
   Vector definiton

   Use following statements to define vectors. All resource related
   vectors are predefined. Remaining software interrupts can be added here
   as well.
------------------------------------------------------------------------*/
#pragma intvect _start            0     /* reset vector                 */
/*                                                                      */
/* Mode vector                                                          */
#pragma intvect 0x07000000        1     /* Mode Byte                    */
/* please refer to the hardware manual to set the mode vector           */

#pragma intvect DefaultIRQHandler 15    /* Non Maskable Interrupt       */
#pragma intvect DefaultIRQHandler 16    /* External Interrupt 0         */
#pragma intvect DefaultIRQHandler 17    /* External Interrupt 1         */
#pragma intvect DefaultIRQHandler 18    /* External Interrupt 2         */
#pragma intvect DefaultIRQHandler 19    /* External Interrupt 3         */
#pragma intvect DefaultIRQHandler 20    /* External Interrupt 4         */
#pragma intvect DefaultIRQHandler 21    /* External Interrupt 5         */
#pragma intvect DefaultIRQHandler 22    /* External Interrupt 6         */
#pragma intvect DefaultIRQHandler 23    /* External Interrupt 7         */
#pragma intvect DefaultIRQHandler 24    /* Reload Timer 0               */
#pragma intvect DefaultIRQHandler 25    /* Reload Timer 1               */
#pragma intvect ih_Timer2         26    /* Reload Timer 2               */
#pragma intvect DefaultIRQHandler 27    /* LIN-UART 0 RX                */
#pragma intvect DefaultIRQHandler 28    /* LIN-UART 0 TX                */
#pragma intvect DefaultIRQHandler 29    /* LIN-UART 1 RX                */
#pragma intvect DefaultIRQHandler 30    /* LIN-UART 1 TX                */
#pragma intvect DefaultIRQHandler 31    /* LIN-UART 2 RX                */
#pragma intvect DefaultIRQHandler 32    /* LIN-UART 2 TX                */
#pragma intvect DefaultIRQHandler 33    /* CAN 0                        */
#pragma intvect DefaultIRQHandler 34    /* CAN 1/ICU 6/7                */
#pragma intvect DefaultIRQHandler 35    /* CAN 2                        */
#pragma intvect DefaultIRQHandler 36    /* LIN-UART 3/5 RX              */
#pragma intvect DefaultIRQHandler 37    /* LIN-UART 3/5 TX              */
#pragma intvect DefaultIRQHandler 38    /* LIN-UART 4/6 RX              */
#pragma intvect DefaultIRQHandler 39    /* LIN-UART 4/6 TX              */
#pragma intvect DefaultIRQHandler 40    /* I2C 0                        */
#pragma intvect DefaultIRQHandler 41    /* I2C 1 / UDC 3                */
#pragma intvect DefaultIRQHandler 42    /* I2C 2                        */
#pragma intvect DefaultIRQHandler 43    /* A/D Converter 0              */
#pragma intvect DefaultIRQHandler 44    /* RTC                          */
#pragma intvect DefaultIRQHandler 45    /* UDC 1                        */
#pragma intvect DefaultIRQHandler 46    /* Main osc. stabil. wait timer */
#pragma intvect SystemTimer_ISR   47    /* TBT overflow                 */
#pragma intvect DefaultIRQHandler 48    /* Prog. Pulse Gen. 0/1/4/5     */
#pragma intvect DefaultIRQHandler 49    /* Prog. Pulse Gen. 2/3/6/7     */
#pragma intvect DefaultIRQHandler 50    /* Prog. Pulse Gen. 8/9/C/D     */
#pragma intvect DefaultIRQHandler 51    /* Prog. Pulse Gen. A/B/E/F     */
#pragma intvect DefaultIRQHandler 52    /* FRT 0/1                      */
#pragma intvect DefaultIRQHandler 53    /* FRT 2/3                      */
#pragma intvect DefaultIRQHandler 54    /* ICU 0/1/2/3                  */
#pragma intvect DefaultIRQHandler 55    /* ICU 4/5                      */
#pragma intvect DefaultIRQHandler 56    /* OCU 0/1/2/3 UDC 3            */
#pragma intvect DefaultIRQHandler 57    /* OCU 4/5/6/7                  */
#pragma intvect DefaultIRQHandler 58    /* UDC 0                        */
#pragma intvect DefaultIRQHandler 59    /* Ext. Int. 8/9/10/11          */
#pragma intvect DefaultIRQHandler 60    /* Ext. Int. 12 to 39           */
#pragma intvect DefaultIRQHandler 61    /* ROM collection Interrupt     */
#pragma intvect DefaultIRQHandler 62    /* DMA                          */
#pragma intvect ContextSwitcher_ISR 63    /* Delayed Interrupt            */



/*------------------------------------------------------------------------
   DefaultIRQHandler()

   This function is a placeholder for all vector definitions. Either use
   your own placeholder or add necessary code here. 
-------------------------------------------------------------------------*/
__interrupt 
void DefaultIRQHandler (void)
{
  __DI();                               /* disable interrupts */
  while(1)
    __wait_nop();                       /* halt system */
}
