//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M4(F)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version: 4.00
//*
//*     $Revision$
//*     $Date::             $
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
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
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//******************************************************************************
//*     Cortex-M4(F) GCC port by Anton B. Gusev aka AHTOXA, Copyright (c) 2012


#include <scmRTOS.h>

using namespace OS;

void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    // ARM Architecture Procedure Call Standard [AAPCS] requires 8-byte stack alignment:
    StackPointer = (stack_item_t*)((uintptr_t)Stack & 0xFFFFFFF8);

    *(--StackPointer)  = 0x01000000UL;      // xPSR
    *(--StackPointer)  = reinterpret_cast<uint32_t>(exec); // Entry Point
#if (defined __SOFTFP__)
    StackPointer -= 14;                     // emulate "push LR,R12,R3,R2,R1,R0,R11-R4"
#else
    StackPointer -= 6;                      // emulate "push LR,R12,R3,R2,R1,R0"
    *(--StackPointer)  = 0xFFFFFFFDUL;      // exc_return: Return to Thread mode, floating-point context inactive, execution uses PSP after return.
    StackPointer -= 8;                      // emulate "push R4-R11"
#endif

#if scmRTOS_DEBUG_ENABLE == 1
    for (stack_item_t* pDst = StackBegin; pDst < StackPointer; pDst++)
        *pDst = STACK_DEFAULT_PATTERN;
#endif // scmRTOS_DEBUG_ENABLE
}

/*
 * PendSV is used to perform a context switch. This is a recommended method for Cortex-M3/M4.
 * This is because the Cortex-M3/M4 automatically saves half of the processor context
 * on any exception, and restores same on return from exception.  So only saving of R4-R11
 * and fixing up the stack pointers is required.  Using the PendSV exception this way means
 * that context saving and restoring is identical whether it is initiated from a thread
 * or occurs due to an interrupt or exception.
 *
 * Since PendSV interrupt has the lowest priority in the system (set by os_start() below),
 * we can be sure that it will run only when no other exception or interrupt is active, and
 * therefore safe to assume that context being switched out was using the process stack (PSP).
 */

#if (defined __SOFTFP__)
// This function used for CPU without FPU (cortex-M3, cortex-M4)
extern "C" void PendSVC_ISR()
{
    asm volatile (
        "    CPSID   I                 \n" // Prevent interruption during context switch
        "    MRS     R0, PSP           \n" // PSP is process stack pointer
        "    STMDB   R0!, {R4-R11}     \n" // Save remaining regs r4-11 on process stack

        // At this point, entire context of process has been saved
        "    PUSH    {LR}              \n" // we must save LR (exc_return value) until exception return
        "    BL      os_context_switch_hook  \n" // call os_context_switch_hook();

        // R0 is new process SP;
        "    LDMIA   R0!, {R4-R11}     \n" // Restore r4-11 from new process stack
        "    MSR     PSP, R0           \n" // Load PSP with new process SP
        "    CPSIE   I                 \n"
        "    POP     {PC}              \n" // Return to saved exc_return. Exception return will restore remaining context
        : :
    );
}
#else // #if (defined __SOFTFP__)
// This function used for CPU with FPU (cortex-M4F)
extern "C" void PendSVC_ISR()
{
    asm volatile (
        "    CPSID     I                 \n" // Prevent interruption during context switch
        "    MRS       R0, PSP           \n" // PSP is process stack pointer
        "    TST       LR, #0x10         \n" // exc_return[4]=0? (it means that current process
        "    IT        EQ                \n" // has active floating point context)
        "    VSTMDBEQ  R0!, {S16-S31}    \n" // if so - save it.
        "    STMDB     R0!, {R4-R11, LR} \n" // save remaining regs r4-11 and LR on process stack

        // At this point, entire context of process has been saved
        "    BL        os_context_switch_hook  \n" // call os_context_switch_hook();

        // R0 is new process SP;
        "    LDMIA     R0!, {R4-R11, LR} \n" // Restore r4-11 and LR from new process stack
        "    TST       LR, #0x10         \n" // exc_return[4]=0? (it means that new process
        "    IT        EQ                \n" // has active floating point context)
        "    VLDMIAEQ  R0!, {S16-S31}    \n" // if so - restore it.
        "    MSR       PSP, R0           \n" // Load PSP with new process SP
        "    CPSIE     I                 \n"
        "    BX        LR                \n" // Return to saved exc_return. Exception return will restore remaining context
        : :
    );
}
#endif

/*
 * Some Cortex-M3/M4(F) registers and constants.
 */
namespace
{

template<uint32_t addr, typename type = uint32_t>
struct ioregister_t
{
	type operator=(type value) { *(volatile type*)addr = value; return value; }
	void operator|=(type value) { *(volatile type*)addr |= value; }
	void operator&=(type value) { *(volatile type*)addr &= value; }
	operator type() { return *(volatile type*)addr; }
};

template<uint32_t addr, class T>
struct iostruct_t
{
	volatile T* operator->() { return (volatile T*)addr; }
};

// PendSV and SysTick priority registers
static ioregister_t<0xE000ED22UL, uint8_t> PendSvPriority;
static ioregister_t<0xE000ED23UL, uint8_t> SysTickPriority;

// SysTick stuff
struct systick_t
{
    uint32_t       CTRL;
	uint32_t       LOAD;
  	uint32_t       VAL;
  	uint32_t const CALIB;
};

enum
{
    NVIC_ST_CTRL_CLK_SRC = 0x00000004,       // Clock Source.
    NVIC_ST_CTRL_INTEN   = 0x00000002,       // Interrupt enable.
    NVIC_ST_CTRL_ENABLE  = 0x00000001        // Counter mode.
};

systick_t volatile * const SysTick = (systick_t volatile * const)0xE000E010UL;

// Floating point context control register stuff
static ioregister_t<0xE000EF34UL> FPCCR;
enum
{
	ASPEN =   (0x1UL << 31),  // always save enable
	LSPEN =   (0x1UL << 30)   // lazy save enable
};

}

/*
 * System timer stuff.
 * This is the default (weak) system timer ISR handler.
 * The user can redefine this handler if needed.
 */
#pragma weak SystemTimer_ISR = Default_SystemTimer_ISR
namespace OS
{
extern "C" OS_INTERRUPT void Default_SystemTimer_ISR()
{
    scmRTOS_ISRW_TYPE ISR;

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    system_timer_user_hook();
#endif

    Kernel.system_timer();

#if scmRTOS_SYSTIMER_NEST_INTS_ENABLE == 0
    DISABLE_NESTED_INTERRUPTS();
#endif
}
}

/*
 * Default system timer initialization.
 *
 * Sets SysTick timer interrupt priority to lowest.
 * Configures SysTick timer to interrupt with frequency SYSTICKINTRATE.
 */
#pragma weak __init_system_timer
extern "C" void __init_system_timer()
{
	SysTickPriority = 0xFF;
	SysTick->LOAD = SYSTICKFREQ/SYSTICKINTRATE-1;
	SysTick->CTRL = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE;
}


/*
 *   START MULTITASKING
 *
 * Note(s) : 1) os_start() MUST:
 *              a) Setup PendSV and SysTick exception priority to lowest;
 *              b) Call System timer initialization function;
 *              c) Enable interrupts (tasks will run with interrupts enabled);
 *              d) Jump to entry point of the highest priority process.
 */
extern "C" NORETURN void os_start(stack_item_t *sp)
{
	PendSvPriority = 0xFF;     // PendSV priority value (lowest)
#if (!defined __SOFTFP__)
    FPCCR |= ASPEN | LSPEN;    // move this to os_start
#endif

    asm volatile (
#if (defined __SOFTFP__)  // code without FPU
        "    LDR     R4, [%[stack], #(4 * 14)] \n" // Load process entry point into R4
        "    ADD     %[stack], #(4 * 16)       \n" // emulate context restore
#else
    	"    LDR     R4, [%[stack], #(4 * 15)] \n" // Load process entry point into R4
        "    ADD     %[stack], #(4 * 17)       \n" // emulate context restore
#endif
        "    MSR     PSP, %[stack]             \n" // store process SP to PSP
        "    MOV     R0, #2                    \n" // set up the current (thread) mode: use PSP as stack pointer, privileged level
        "    MSR     CONTROL, R0               \n"
        "    ISB                               \n" // Insert a barrier
   	    "    BL      __init_system_timer       \n" // run system timer
   	    "    CPSIE   I                         \n" // Enable interrupts at processor level
   	    "    BX      R4                        \n" // Jump to process exec() function
        : [stack]"+r" (sp)  // output
    );
    __builtin_unreachable(); // suppress compiler warning "'noreturn' func does return"
}
