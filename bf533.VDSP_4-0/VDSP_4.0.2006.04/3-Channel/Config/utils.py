#*******************************************************************************
# -*- coding: cp1251 -*-
#*
#*    VisualDSP/Blackfin compiler messages unwrapper
#*
#*    Version 1.0
#*
#*    Copyright (c) 2006, Harry E. Zhurov
#*
#*******************************************************************************

import re

#-------------------------------------------------------------------------------
# 
#    Example of error message
#
# "Src\flash.cpp", line 26: cc0020:  error: identifier "FLASH_ADDR_555" is
#           undefined
#       FLASH_ADDR_555() = 0xaa;   // 1


def handle_err(err):
    pattern = '(\"[^\n]+\", *line [0-9]+: +[\w\d]+:.* +?(error|warning): +.+?\^)'
    err_list = re.findall(pattern, err, re.DOTALL + re.I)
    N = 0
    elist = []
    for i in err_list:
        elist.append(i[0])

    out_list = []
    for i in elist:
        # find newline positions
        nl_list = re.findall('\n *', i)
        pos_list = []
        p = 0
        for j in nl_list:
            p = i.find(j, p+1)
            pos_list.append(p)

        # create output record
        err_rec = ''
        if len(pos_list) < 3:
            err_rec = i
        else:
            err_rec = re.sub('\n *', ' ', i, len(pos_list)-2)

        out_list.append(err_rec  + '\n'*2)

    #print elist
    out_err = ''
    if elist == []:
        out_err = err
    else:
        begin_pos = err.find(elist[0])
        end_pos   = err.find(elist[-1]) + len(elist[-1])

        out_err  = ''.join([err[:begin_pos]] + out_list + [err[end_pos:]])

    return out_err
#-------------------------------------------------------------------------------

