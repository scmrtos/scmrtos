//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADSP-BF533 (Analog Devices)
//*
//*     TOOLKIT:   VDSP (Analog Devices)
//*               
//*     PURPOSE:   Target Dependent Low-Level Stuff
//*               
//*     Version: v5.2.0
//*
//*
//*     Copyright (c) 2003-2021, scmRTOS Team
//*
//*     Permission is hereby granted, free of charge, to any person 
//*     obtaining  a copy of this software and associated documentation 
//*     files (the "Software"), to deal in the Software without restriction, 
//*     including without limitation the rights to use, copy, modify, merge, 
//*     publish, distribute, sublicense, and/or sell copies of the Software, 
//*     and to permit persons to whom the Software is furnished to do so, 
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included 
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*     Blackfin/CrossCore Embedded Studio port by Evgeny Nesterov, Copyright (c) 2012-2021

#include "scmRTOS_TARGET_CFG.h"

    .global _os_start
    .global _context_switcher_isr
    .global _caller
 
    .extern _os_context_switch_hook
    
    .extern ldf_stack_end;
          
    .extern  __cec_int_dispatcher
    
    .section program;
    .align 2;

//------------------------------------------------------------------------------
_os_start:
    sp   = r0;                              // load highest priority process stack pointer
    nop;  nop;                              //
    p0.l = lo(IMASK);                       //
    p0.h = hi(IMASK);                       //
    r1   = [sp++];                          // enable interrupts at CEC level
    [p0] = r1;                              //
     
   
    p0   = 43*4;                            // emulate 43 pops
    sp   = sp + p0;                         //
    
   
                                            //
    rets = [sp++];                          // load process's main function address
    
    p0   = 0x20;                             //
    sp   = sp + p0; 
    rts;                                    // go to the process's application code

_os_start.end:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
_context_switcher_isr:

    //--------------------------------------------------------------------------                                        
    //
    //   Save return address
    //
    [--sp] = reti;
         
    
    //--------------------------------------------------------------------------                                        
    //
    //   Save context
    //
    [--sp] = rets;           
    [--sp] = astat;
    [--sp] = fp;
    [--sp] = (r7:0,p5:0);
    [--sp] = i0;
    [--sp] = i1;
    [--sp] = i2;
    [--sp] = i3;
    [--sp] = b0;
    [--sp] = b1;
    [--sp] = b2;
    [--sp] = b3;
    [--sp] = l0;
    [--sp] = l1;
    [--sp] = l2;
    [--sp] = l3;
    [--sp] = m0;
    [--sp] = m1;
    [--sp] = m2;
    [--sp] = m3;
    [--sp] = a0.x;
    [--sp] = a0.w;
    [--sp] = a1.x;
    [--sp] = a1.w;
    [--sp] = lc0;
    [--sp] = lc1;
    [--sp] = lt0;
    [--sp] = lt1;
    [--sp] = lb0;
    [--sp] = lb1;

    //--------------------------------------------------------------------------                                        
    //
    //   Switch stack pointers and manage interrupt enable status
    //
    p5.l    = lo(IMASK);                      // save IMASK value
    p5.h    = hi(IMASK);                      // (global interrupts enable state)
    r7      = [p5];                           //
    [--sp]  = r7;  
     r0      = sp;
    
    sp += -12; // reserve space for calling function incoming parameters
    call    _os_context_switch_hook;                          
    sp +=  12;                                // restore space for calling function incoming parameters
    
    sp      = r0;
    nop; nop;  nop;  nop;

    r0      = [sp++];                         // load IMASK value 
    [p5]    = r0;                           // (global interrupts enable state)
    
    //--------------------------------------------------------------------------                                        
    //
    //   Restore context
    //
    lb1    = [sp++];                        
    lb0    = [sp++];
    lt1    = [sp++];
    lt0    = [sp++];
    lc1    = [sp++];
    lc0    = [sp++];
    a1.w   = [sp++];
    a1.x   = [sp++];
    a0.w   = [sp++];
    a0.x   = [sp++];
    m3     = [sp++];
    m2     = [sp++];
    m1     = [sp++];
    m0     = [sp++];
    l3     = [sp++];
    l2     = [sp++];
    l1     = [sp++];
    l0     = [sp++];
    b3     = [sp++];
    b2     = [sp++];
    b1     = [sp++];
    b0     = [sp++];
    i3     = [sp++];
    i2     = [sp++];
    i1     = [sp++];
    i0     = [sp++];
   (r7:0,
    p5:0)  = [sp++];
    fp     = [sp++];
    astat  = [sp++];
    rets   = [sp++];

    //--------------------------------------------------------------------------                                        
    //
    //   Restore return address and go to the process's application code
    //
  		
    reti   = [sp++];
    rts;//return subroutine
    
._context_switcher_isr.end:
//------------------------------------------------------------------------------

_caller:
      [--sp]=R1;
      R0.L = LO(__cec_int_dispatcher);
      R0.H = HI(__cec_int_dispatcher);
      R1 = 0x42;//offset return adrress
      R0 = R0+R1;
      R1 = [sp++];
      rts;
    
_caller.end:
