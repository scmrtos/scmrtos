/**
*  @file ftoa.h
*
*  Created on: 18.02.2009
*  Copyright (c) 2009-2012by Anton Gusev aka AHTOXA
**/
#ifndef FTOA_H_INCLUDED
#define FTOA_H_INCLUDED

#define PRECISION_TABLE

#ifdef __cplusplus
extern "C" {
#endif

char * ftoa(double f, char * buf, int precision);

#ifdef __cplusplus
}
#endif

#endif // FTOA_H_INCLUDED

