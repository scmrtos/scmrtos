
/*
** app_handler_table.c generated on Èþëü 3, 2013 at 11:38:15.
**
** Copyright (C) 2000-2013 Analog Devices Inc., All Rights Reserved.
**
** This file is generated automatically based upon the options selected in the
** Startup Code/LDF Configuration Editor. Changes to the Interrupt Handler
** configuration should be made by changing the appropriate options rather than
** editing this file.
**
*/

#ifdef _MISRA_RULES
#pragma diag(suppress:misra_rule_5_1:\
             "Identifiers shall not rely on the significance of more than 31 characters")
#pragma diag(suppress:misra_rule_16_9:\
             "A function identifier shall only be used with either a preceding &,\
             or with a parenthesised parameter list, which may be empty")
#pragma diag(suppress:misra_rule_8_10:\
             "All declarations and definitions of objects or functions at file scope\
             shall have internal linkage unless external linkage is required")
#endif /* _MISRA_RULES */

/**
 * To place the interrupt handler table in a specific area of memory
 * set the macro in the C/C++ Compiler preprocessor tools settings.
 * All data used in interrupt and exception handling should be placed
 * in an area of memory covered by a locked CPLB and, if possible,
 * in L1 to achieve the best performance.
 */
#ifndef __INT_SECTION__
#define __INT_SECTION__ "L1_data"
#endif /* __INT_SECTION__ */

#include <sys/exception.h>
#include <stddef.h>
#include <stdint.h>
#include <adi_osal.h>

/* Maximum number of dispatchers available in the application */
#define INTERRUPT_TABLE_SIZE (96u)

#pragma section(__INT_SECTION__)
adi_dispatched_data_t adi_dispatched_int_vector_table[INTERRUPT_TABLE_SIZE] = {
	{ adi_no_dispatched_handler, NULL }
};

#pragma section(__INT_SECTION__)
ADI_OSAL_HANDLER_PTR _adi_osal_gHandlerTable[INTERRUPT_TABLE_SIZE];

extern const uint32_t _adi_osal_gHandlerTableSize = INTERRUPT_TABLE_SIZE;

extern const uint32_t adi_dispatched_int_vector_table_size = sizeof(adi_dispatched_int_vector_table) / sizeof(adi_dispatched_int_vector_table[0]);

