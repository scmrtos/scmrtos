/*
*******************************************************************************
*
* File:         pin_macros.h
*
* Author:       Sergey Pinigin
*
* Description:  Port bits access macros for Fujitsu MB91 uC family
*               (Softune C compiler)
*
* Based on macros by Ascold Volkov, Andy Mozzevilov, Aleksey Musin

*******************************************************************************
*/

#if 0 // Examples
//#############################################################################
#define Pin1 2,2,H
#define Pin2 8,3,L
//           ^ ^ ^
//          /  |  \
//      port  bit  active level

void main(void)
{
    direct(Pin1,O);         //as output
    direct(Pin2,I);         //as input
    driver(Pin2,PullUp);    //driver(Pin2,HiZ);

    on(Pin1);

    if (signal(Pin2))
        cpl(Pin1);

    if (latch(Pin1))
    {
        //if active level presents on Pin1 for drive something
        //do something
    }
}
//#############################################################################
#endif // Examples

#ifndef _PIN_MACROS_H_
#define _PIN_MACROS_H_

#ifndef __COMPILER_FCC911__
#error "This file should only be compiled with SOFTUNE Workbench Compiler"
#endif

#if defined(__CPU_MB91F272__) || defined (__CPU_MB91F273__)


#define pm_setL(port,bit,val)   PDR##port##_P##port##bit##=0
#define pm_setH(port,bit,val)   PDR##port##_P##port##bit##=1
#define set(port,bit,val)       pm_set##val(port,bit,val)
#define on(x)                   set(x)
#define SET                     setH

#define pm_clrL(port,bit,val)   PDR##port##_P##port##bit##=1
#define pm_clrH(port,bit,val)   PDR##port##_P##port##bit##=0
#define clr(port,bit,val)       pm_clr##val(port,bit,val)
#define off(x)                  clr(x)
#define CLR                     clrH

#define pm_bitL(port,bit)       (!(PDR##port##_P##port##bit))
#define pm_bitH(port,bit)       (PDR##port##_P##port##bit)
#define bit(port,bit,val)       pm_bit##val(port,bit)
#define latch(port,bit,val)     pm_bit##val(port,bit)
#define signal(x)               bit(x)
#define BIT                     bitH

#define cpl(port,bit,val)       PDR##port##_P##port##bit##=~(PDR##port##_P##port##bit##)
#define CPL                     cpl

#define BITNUM(port,bit,val)    bit


#define pm_setO(line) line=1
#define pm_setI(line) line=0

#define mode(port,bit,val,pin_mode) pm_set##pin_mode(DDR##port##_D##port##bit)

/* pin_mode = O or I */
#define direct(x,pin_mode)      mode(x,pin_mode)

#endif // __CPU_MB91F27x

#endif // _PIN_MACROS_H_

