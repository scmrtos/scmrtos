/**
*  @file test_context.cpp
*
*  Cortex-M4F context testing function.
*
*  Created on: 03.12.2012
*  Copyright (c) 2010 by Anton Gusev aka AHTOXA
**/
#include <scmRTOS.h>
#include "hw.h"

uint32_t loops1;
uint32_t loops2;

extern "C" void doSleep(uint32_t param)
{
	if(param == 0x87654321)
	{
		loops1++;
	}
	else
	{
		loops2++;
	}
	OS::sleep(1);
}

extern "C" void bailOut(uint32_t param)
{
	if(param == 0x87654321)
	{
		for(;;)
		{
			OrangeLED::On(); // indicate error
			OS::sleep(50);
			OrangeLED::Off();
			OS::sleep(450);
		}
	}
	else
	{
		for(;;)
		{
			RedLED::On(); // indicate error
			OS::sleep(50);
			RedLED::Off();
			OS::sleep(250);
		}
	}
}

/*
 * Test of context persistence.
 */
OS_PROCESS void test_context(uint32_t param)
{
	asm volatile (
			"	MOV		R0,%[param]		\n"
			"	ADD		R1, R0, R0		\n"
			"	ADD		R2, R1, R1		\n"
			"	ADD		R3, R2, R2		\n"
			"	ADD		R4, R3, R3		\n"
			"	ADD		R5, R4, R4		\n"
			"	ADD		R6, R5, R5		\n"
			"	ADD		R7, R6, R6		\n"
			"	ADD		R8, R7, R7		\n"
			"	ADD		R9, R8, R8		\n"
			"	ADD		R10, R9, R9		\n"
			"	ADD		R11, R10, R10	\n"
			"	ADD		R12, R11, R11	\n"

			"	VMOV	S0, R0			\n"
			"	VMOV	S1, R1			\n"
			"	VMOV	S2, R2			\n"
			"	VMOV	S3, R3			\n"
			"	VMOV	S4, R4			\n"
			"	VMOV	S5, R5			\n"
			"	VMOV	S6, R6			\n"
			"	VMOV	S7, R7			\n"
			"	VMOV	S8, R8			\n"
			"	VMOV	S9, R9			\n"
			"	VMOV	S10, R10		\n"
			"	VMOV	S11, R11		\n"
			"	VMOV	S12, R12		\n"
			"	VMOV	S13, R0			\n"
			"	VMOV	S14, R1			\n"
			"	VMOV	S15, R2			\n"
			"	VMOV	S16, R3			\n"
			"	VMOV	S17, R4			\n"
			"	VMOV	S18, R5			\n"
			"	VMOV	S19, R6			\n"
			"	VMOV	S20, R7			\n"
			"	VMOV	S21, R8			\n"
			"	VMOV	S22, R9			\n"
			"	VMOV	S23, R10		\n"
			"	VMOV	S24, R11		\n"
			"	VMOV	S25, R12		\n"
			"	VMOV	S26, R0			\n"
			"	VMOV	S27, R1			\n"
			"	VMOV	S28, R2			\n"
			"	VMOV	S29, R3			\n"
			"	VMOV	S30, R4			\n"
			"	VMOV	S31, R5			\n"

			"loop:						\n"
			"	PUSH	{R1}			\n"
			"	VMOV	R1, S0			\n"
			"	CMP		R1, R0			\n"
			"	BNE		error_r1		\n"
			"	VMOV	R1, S13			\n"
			"	CMP		R1, R0			\n"
			"	BNE		error_r1		\n"
			"	VMOV	R1, S26			\n"
			"	CMP		R1, R0			\n"
			"	BNE		error_r1		\n"
			"	POP		{R1}			\n"

			"	PUSH	{R0}			\n"
			"	VMOV	R0, S1			\n"
			"	CMP		R0, R1			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S2			\n"
			"	CMP		R0, R2			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S3			\n"
			"	CMP		R0, R3			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S4			\n"
			"	CMP		R0, R4			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S5			\n"
			"	CMP		R0, R5			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S6			\n"
			"	CMP		R0, R6			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S7			\n"
			"	CMP		R0, R7			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S8			\n"
			"	CMP		R0, R8			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S9			\n"
			"	CMP		R0, R9			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S10			\n"
			"	CMP		R0, R10			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S11			\n"
			"	CMP		R0, R11			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S12			\n"
			"	CMP		R0, R12			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S14			\n"
			"	CMP		R0, R1			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S15			\n"
			"	CMP		R0, R2			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S16			\n"
			"	CMP		R0, R3			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S17			\n"
			"	CMP		R0, R4			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S18			\n"
			"	CMP		R0, R5			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S19			\n"
			"	CMP		R0, R6			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S20			\n"
			"	CMP		R0, R7			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S21			\n"
			"	CMP		R0, R8			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S22			\n"
			"	CMP		R0, R9			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S23			\n"
			"	CMP		R0, R10			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S24			\n"
			"	CMP		R0, R11			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S25			\n"
			"	CMP		R0, R12			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S27			\n"
			"	CMP		R0, R1			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S28			\n"
			"	CMP		R0, R2			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S29			\n"
			"	CMP		R0, R3			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S30			\n"
			"	CMP		R0, R4			\n"
			"	BNE		error			\n"
			"	VMOV	R0, S31			\n"
			"	CMP		R0, R5			\n"
			"	BNE		error			\n"
			"	POP		{R0}			\n"

			"	PUSH	{R0-R3, LR}		\n"
			"	VPUSH	{S16-S31}		\n"
			"	BL		doSleep			\n"
			"	VPOP	{S16-S31}		\n"
			"	POP		{R0-R3, LR}		\n"
			"	B	loop				\n"
			"			\n"
			"error:						\n"
			"	POP		{R0}			\n"
			"	BL		bailOut			\n"
			"error_r1:					\n"
			"	POP		{R1}			\n"
			"	BL		bailOut			\n"
		:						// no output
		: [param]"r" (param)		// input
		:						// no clobbers
	);
    __builtin_unreachable(); // suppress compiler warning "'noreturn' func does return"
}

