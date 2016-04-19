//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M0(+), Cortex-M1, Cortex-M3, Cortex-M4(F)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Target Dependent Stuff Source
//*
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
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
//*     Cortex-M3/M4(F) GCC port by Anton B. Gusev aka AHTOXA, Copyright (c) 2012-2016
//*     Cortex-M0 port by Sergey A. Borshch, Copyright (c) 2011-2016


#include <scmRTOS.h>

/*
 * M0(+) core : __ARM_ARCH_6M__ defined.
 * M3 core    : __SOFTFP__ defined, __ARM_ARCH_6M__ not defined.
 * M4F core   : __SOFTFP__ not defined.
 */

using namespace OS;

namespace OS
{

#if scmRTOS_DEBUG_ENABLE == 1

struct TDebugSupportInfo
{
    uint8_t PROCESS_COUNT;
    uint8_t TIMEOUT_SIZE;
    uint8_t NAME_OFFSET;
};


__attribute__((used))
extern const TDebugSupportInfo DebugInfo =
{
    PROCESS_COUNT,
    sizeof(timeout_t),
    sizeof(timeout_t) == 2 ? 20 : 24
};
#endif // scmRTOS_DEBUG_ENABLE

} // namespace OS

namespace{
enum {
#if (defined __SOFTFP__)
    CONTEXT_SIZE = 16 * sizeof(stack_item_t)   // Cortex-M0/M0+/M3/M4 context size
#else
    CONTEXT_SIZE = 17 * sizeof(stack_item_t)   // Cortex-M4F initial context size (without FPU context)
#endif
};
}

void TBaseProcess::init_stack_frame( stack_item_t * Stack
                                   , void (*exec)()
                                #if scmRTOS_DEBUG_ENABLE == 1
                                   , stack_item_t * StackBegin
                                #endif
                                   )
{
    /*
     * ARM Architecture Procedure Call Standard [AAPCS] requires 8-byte stack alignment.
     * This means that we must get top of stack aligned _after_ context "pushing", at
     * interrupt entry.
     */
    uintptr_t sptr = (((uintptr_t)Stack - CONTEXT_SIZE) & 0xFFFFFFF8UL) + CONTEXT_SIZE;
    StackPointer = (stack_item_t*)sptr;

    *(--StackPointer)  = 0x01000000UL;      // xPSR
    *(--StackPointer)  = reinterpret_cast<stack_item_t>(exec); // Entry Point
#if (defined __SOFTFP__)    // core without FPU
    StackPointer -= 14;                     // emulate "push LR,R12,R3,R2,R1,R0,R11-R4"
#else                       // core with FPU
    StackPointer -= 6;                      // emulate "push LR,R12,R3,R2,R1,R0"
    *(--StackPointer)  = 0xFFFFFFFDUL;      // exc_return: Return to Thread mode, floating-point context inactive, execution uses PSP after return.
    StackPointer -= 8;                      // emulate "push R4-R11"
#endif
#if scmRTOS_DEBUG_ENABLE == 1
    *(StackPointer)  = reinterpret_cast<stack_item_t>(&DebugInfo); // dummy load to keep 'DebugInfo' in output binary

    for (stack_item_t *pDst = StackBegin; pDst < StackPointer; pDst++)
        *pDst = STACK_DEFAULT_PATTERN;
#endif // scmRTOS_DEBUG_ENABLE
}

/*
 * PendSV is used to perform a context switch. This is a recommended method for Cortex-M.
 * This is because the Cortex-M automatically saves half of the processor context
 * on any exception, and restores same on return from exception.  So only saving of R4-R11
 * and fixing up the stack pointers is required.  Using the PendSV exception this way means
 * that context saving and restoring is identical whether it is initiated from a thread
 * or occurs due to an interrupt or exception.
 *
 * Since PendSV interrupt has the lowest priority in the system (set by os_start() below),
 * we can be sure that it will run only when no other exception or interrupt is active, and
 * therefore safe to assume that context being switched out was using the process stack (PSP).
 */
extern "C" __attribute__((naked)) void PendSV_Handler()
{
#if (defined __ARM_ARCH_6M__)   // Cortex-M0(+)/Cortex-M1
    asm volatile (
        "    CPSID   I                 \n"  // Prevent interruption during context switch
        "    MRS     R0, PSP           \n"  // Load process stack pointer to R0
        "    SUB     R0, R0, #32       \n"  // Adjust R0 to point to top of saved context in stack
        "    MOV     R1, R0            \n"  // Preserve R0 (needed for os_context_switch_hook() call)
        "    STMIA   R1!, {R4-R7}      \n"  // Save low portion of remaining registers (r4-7) on process stack
        "    MOV     R4, R8            \n"  // Move high portion of remaining registers (r8-11) to low registers
        "    MOV     R5, R9            \n"
        "    MOV     R6, R10           \n"
        "    MOV     R7, R11           \n"
        "    STMIA   R1!, {R4-R7}      \n"  // Save high portion of remaining registers (r8-11) on process stack

        // At this point, entire context of process has been saved
        "    PUSH    {LR}              \n" // we must save LR (exc_return value) until exception return
        "    LDR     R1, =os_context_switch_hook  \n"   // call os_context_switch_hook();
        "    BLX     R1                \n"

        // R0 is new process SP;
        "    ADD     R0, R0, #16       \n" // Adjust R0 to point to high registers (r8-11)
        "    LDMIA   R0!, {R4-R7}      \n" // Restore r8-11 from new process stack
        "    MOV     R8, R4            \n" // Move restored values to high registers (r8-11)
        "    MOV     R9, R5            \n"
        "    MOV     R10, R6           \n"
        "    MOV     R11, R7           \n"
        "    MSR     PSP, R0           \n" // R0 at this point is new process SP
        "    SUB     R0, R0, #32       \n" // Adjust R0 to point to low registers
        "    LDMIA   R0!, {R4-R7}      \n" // Restore r4-7
        "    CPSIE   I                 \n"
        "    POP     {PC}              \n" // Return to saved exc_return. Exception return will restore remaining context
        : :
    );
#else  // #if (defined __ARM_ARCH_6M__)

#if (defined __SOFTFP__)
    // M3/M4 cores without FPU
    asm volatile (
        "    CPSID   I                 \n" // Prevent interruption during context switch
        "    MRS     R0, PSP           \n" // PSP is process stack pointer
        "    STMDB   R0!, {R4-R11}     \n" // Save remaining regs r4-11 on process stack

        // At this point, entire context of process has been saved
        "    PUSH    {LR}              \n" // we must save LR (exc_return value) until exception return
        "    LDR     R1, =os_context_switch_hook  \n"   // call os_context_switch_hook();
        "    BLX     R1                \n"

        // R0 is new process SP;
        "    LDMIA   R0!, {R4-R11}     \n" // Restore r4-11 from new process stack
        "    MSR     PSP, R0           \n" // Load PSP with new process SP
        "    CPSIE   I                 \n"
        "    POP     {PC}              \n" // Return to saved exc_return. Exception return will restore remaining context
        : :
    );

#else // #if (defined __SOFTFP__)
    // Core with FPU (cortex-M4F)
    asm volatile (
        "    CPSID     I                 \n" // Prevent interruption during context switch
        "    MRS       R0, PSP           \n" // PSP is process stack pointer
        "    TST       LR, #0x10         \n" // exc_return[4]=0? (it means that current process
        "    IT        EQ                \n" // has active floating point context)
        "    VSTMDBEQ  R0!, {S16-S31}    \n" // if so - save it.
        "    STMDB     R0!, {R4-R11, LR} \n" // save remaining regs r4-11 and LR on process stack

        // At this point, entire context of process has been saved
        "    LDR     R1, =os_context_switch_hook  \n"   // call os_context_switch_hook();
        "    BLX     R1                \n"

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
#endif  // #if (defined __SOFTFP__)
#endif  // #if (defined __ARM_ARCH_6M__)
}

// weak alias to support old name of PendSV_Handler.
#pragma weak PendSVC_ISR = PendSV_Handler

/*
 * By default port uses SysTick timer as a system timer.
 */
#if (! defined SCMRTOS_USE_CUSTOM_TIMER)
#define SCMRTOS_USE_CUSTOM_TIMER 0
#endif

/*
 * Some Cortex-MX registers and constants.
 */
namespace
{

template<uintptr_t addr, typename type = uint32_t>
struct ioregister_t
{
    type operator=(type value) { *(volatile type*)addr = value; return value; }
    void operator|=(type value) { *(volatile type*)addr |= value; }
    void operator&=(type value) { *(volatile type*)addr &= value; }
    operator type() { return *(volatile type*)addr; }
};

template<uintptr_t addr, class T>
struct iostruct_t
{
    volatile T* operator->() { return (volatile T*)addr; }
};

// PendSV and SysTick priority registers

#if (defined __ARM_ARCH_6M__)
// Cortex-M0 system control registers are only accessible using word transfers.
static ioregister_t<0xE000ED20UL, uint32_t> SHPR3;
#define SHP3_WORD_ACCESS
#else
// Cortex-M3/M4 system control registers allows byte transfers.
static ioregister_t<0xE000ED22UL, uint8_t> PendSvPriority;
#if (SCMRTOS_USE_CUSTOM_TIMER == 0)
static ioregister_t<0xE000ED23UL, uint8_t> SysTickPriority;
#endif
#endif

#if (SCMRTOS_USE_CUSTOM_TIMER == 0)
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

static iostruct_t<0xE000E010UL, systick_t> SysTickRegisters;
#endif

#if (!defined __SOFTFP__)
// Floating point context control register stuff
static ioregister_t<0xE000EF34UL> FPCCR;
enum
{
    ASPEN =   (0x1UL << 31),  // always save enable
    LSPEN =   (0x1UL << 30)   // lazy save enable
};
#endif

}

/*
 * System timer stuff.
 */
#if (SCMRTOS_USE_CUSTOM_TIMER == 0)
OS_INTERRUPT void SysTick_Handler()
{
    system_timer_isr();
}
#endif

/*
 * Default system timer initialization.
 *
 * Sets SysTick timer interrupt priority a bit higher than lowest one.
 * Configures SysTick timer to interrupt with frequency SYSTICKINTRATE.
 */
#if (!defined CORE_PRIORITY_BITS)
#    define CORE_PRIORITY_BITS        8
#endif

namespace
{
enum { SYS_TIMER_PRIORITY = ((0xFEUL << (8-(CORE_PRIORITY_BITS))) & 0xFF) };
}

#if (SCMRTOS_USE_CUSTOM_TIMER == 0)
extern "C" void __init_system_timer()
{
#if (defined SHP3_WORD_ACCESS)   // word access
    SHPR3 = (SHPR3 & ~(0xFF << 24)) | (SYS_TIMER_PRIORITY << 24);
#else
    SysTickPriority = SYS_TIMER_PRIORITY;
#endif
    SysTickRegisters->LOAD = SYSTICKFREQ/SYSTICKINTRATE-1;
    SysTickRegisters->CTRL = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE;
}

/*
 * Default system timer lock/unlock functions.
 *
 */
void LOCK_SYSTEM_TIMER()   { SysTickRegisters->CTRL &= ~NVIC_ST_CTRL_INTEN; }
void UNLOCK_SYSTEM_TIMER() { SysTickRegisters->CTRL |= NVIC_ST_CTRL_INTEN; }

#endif  // #if (SCMRTOS_USE_CUSTOM_TIMER == 0)


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
    // Set PendSV lowest priority value
#if (defined SHP3_WORD_ACCESS)
    SHPR3 |= (0xFF << 16);
#else
    PendSvPriority = 0xFF;
#endif

#if (!defined __SOFTFP__)
    FPCCR |= ASPEN | LSPEN;
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
        "    LDR     R1, =__init_system_timer  \n" //
        "    BLX     R1                        \n" //
        "    CPSIE   I                         \n" // Enable interrupts at processor level
        "    BX      R4                        \n" // Jump to process exec() function
        : [stack]"+r" (sp)  // output
    );
    __builtin_unreachable(); // suppress compiler warning "'noreturn' func does return"
}

#if scmRTOS_PRIORITY_ORDER == 0
namespace OS
{
    extern TPriority const PriorityTable[] =
    {
        #if scmRTOS_PROCESS_COUNT == 1
            static_cast<TPriority>(0xFF),
            pr0,
            prIDLE, pr0
        #elif scmRTOS_PROCESS_COUNT == 2
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            prIDLE, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 3
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 4
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #elif scmRTOS_PROCESS_COUNT == 5
            static_cast<TPriority>(0xFF),
            pr0,
            pr1, pr0,
            pr2, pr0, pr1, pr0,
            pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0,
            prIDLE, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr4, pr0, pr1, pr0, pr2, pr0, pr1, pr0, pr3, pr0, pr1, pr0, pr2, pr0, pr1, pr0
        #else // scmRTOS_PROCESS_COUNT > 5
            static_cast<TPriority>(32),      static_cast<TPriority>(0),       static_cast<TPriority>(1),       static_cast<TPriority>(12),
            static_cast<TPriority>(2),       static_cast<TPriority>(6),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(13),
            static_cast<TPriority>(3),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(7),       static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(14),
            static_cast<TPriority>(10),      static_cast<TPriority>(4),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(8),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(25),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(21),      static_cast<TPriority>(27),      static_cast<TPriority>(15),
            static_cast<TPriority>(31),      static_cast<TPriority>(11),      static_cast<TPriority>(5),       static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(9),       static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(24),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(20),      static_cast<TPriority>(26),
            static_cast<TPriority>(30),      static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),    static_cast<TPriority>(0xFF),
            static_cast<TPriority>(0xFF),    static_cast<TPriority>(23),      static_cast<TPriority>(0xFF),    static_cast<TPriority>(19),
            static_cast<TPriority>(29),      static_cast<TPriority>(0xFF),    static_cast<TPriority>(22),      static_cast<TPriority>(18),
            static_cast<TPriority>(28),      static_cast<TPriority>(17),      static_cast<TPriority>(16),      static_cast<TPriority>(0xFF)
        #endif  // scmRTOS_PROCESS_COUNT
    };
}   //namespace
#endif

