#*******************************************************************************
# -*- coding: cp1251 -*-
#*
#*    VisualDSP/Blackfin compiler messages unwrapper
#*
#*    Version 1.0
#*
#*    Copyright (c) 2006-2007, Harry E. Zhurov
#*
#*******************************************************************************

import sys
import getopt
import re

#-------------------------------------------------------------------------------
# 
#    Examples of error message
#
# 
# "Src\flash.cpp", line 26: cc0020:  error: identifier "FLASH_ADDR_555" is
#           undefined
#       FLASH_ADDR_555() = 0xaa;   // 1

#"scmRTOS\Common\scmRTOS.h", line 211 (col. 40): cc1746: {D} warning:
#          Externally defined variable Kernel, possibly used in constructor
#          before it has been constructed


def handle_err(err):
    #pattern = '(\"[^\n]+\", *line [0-9]+ \(col. [0-9]+\): +[\w\d]+:.* +?(error|warning): +.+?\^)'
    pattern = '(\"[^\n]+\", *line [0-9]+.*? +?(error|warning):.+?\n\n)'
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

        out_list.append(err_rec)

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
def main():
    #-----------------------------------------------------
    #
    #   Process options
    #
    optlist, infiles = getopt.gnu_getopt(sys.argv[1:], '')

    if not infiles:  
        print 'No input file.'
        return
    InFileName = infiles[0]
    err = open(InFileName, 'rb').read()
    err = re.sub('\r', '', err)
    out_err = handle_err(err)
    print out_err
    
#-------------------------------------------------------------------------------
if __name__ == '__main__': 
    main()
#-------------------------------------------------------------------------------

