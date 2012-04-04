//******************************************************************************
//*
//*      Project:   TBx
//*
//*      File:      Terminal stuff
//*
//*      Version 1.0
//*
//*      Copyright (c) 2009-2012, Harry E. Zhurov
//*
//*      $Revision$
//*      $Date::             $
//*
//------------------------------------------------------------------------------

#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <stdarg.h>
#include <scmRTOS.h>
#include "macro.h"
#include "uart_dev.h"

int print(char *format, ...);

#endif // TERMINAL_H

