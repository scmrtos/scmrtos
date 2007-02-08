#*******************************************************************************
# -*- coding: cp1251 -*-
#*
#*    VisualDSP/Blackfin output summary generator
#*
#*    Version 1.0
#*
#*    Copyright (c) 2006, Harry E. Zhurov
#*
#*******************************************************************************

import sys
import re

#-------------------------------------------------------------------------------
#
#   Get size
#
def GetSize(FieldName, s):
    Result = None
    res = re.search(FieldName, s)
    if res:
        istr = s.split(' ')
        for j in istr:
            res = re.match('([a-fA-F0-9]+):B', j)
            if res:
                 return int(res.group(1), 16)

#-------------------------------------------------------------------------------
def get_info(fn):

    dump = open(fn, 'r').readlines()
    
    code       = 0
    data_a     = 0
    data_b     = 0
    bsz_data_a = 0
    bsz_data_b = 0

    for i in dump:
        size = GetSize('l1_code', i)
        if size: code = size
    
        size = GetSize('l1_data_a', i)
        if size: data_a = size
    
        size = GetSize('l1_data_b', i)
        if size: data_b = size
    
        size = GetSize('bsz_L1_data_a', i)
        if size: bsz_data_a = size
    
        size = GetSize('bsz_L1_data_b', i)
        if size: bsz_data_b = size
    
    
    Data = data_a + data_b + bsz_data_a + bsz_data_b
    
    codeLen       = len( str(code) )
    data_aLen     = len( str(data_a ) )
    data_bLen     = len( str(data_b ) )
    bsz_data_aLen = len( str(bsz_data_a ) )
    bsz_data_bLen = len( str(bsz_data_b ) )
    dataLen       = len( str(Data) )
    
    lengths = [codeLen, data_aLen, data_bLen, bsz_data_aLen, bsz_data_bLen, dataLen]
    maxlen = max(lengths)
    
    StrCode  = str(code).rjust(maxlen)
    StrDA    = str(data_a).rjust(maxlen) 
    StrDB    = str(data_b).rjust(maxlen)
    StrBDA   = str(bsz_data_a).rjust(maxlen)
    StrBDB   = str(bsz_data_b).rjust(maxlen)
    StrData  = str(Data).rjust(maxlen)
    
    
    print 
    print 'Total :  Code: ' + StrCode + ' bytes'
    print '         Data: ' + StrData + ' bytes' + ' (Segment A: ' + str(data_a + bsz_data_a) + ' bytes. ' + 'Segment B: '  + str(data_b + bsz_data_b) + ' bytes.)' 
    print ''
    
    print '----------------------------' + '-'*maxlen + '--'
    print 'Details | Section     | Size'
    print '----------------------------' + '-'*maxlen + '--'
    print '        |  code       | ' + StrCode + ' bytes'
    print '        |  data_a     | ' + StrDA   + ' bytes'
    print '        |  data_b     | ' + StrDB   + ' bytes'
    print '        |  bsz_data_a | ' + StrBDA  + ' bytes'
    print '        |  bsz_data_b | ' + StrBDB  + ' bytes'
    print '----------------------------' + '-'*maxlen + '--'
#-------------------------------------------------------------------------------
def main():
    
    get_info(sys.argv[1])
#-------------------------------------------------------------------------------
if __name__ == '__main__': 
    main()
#-------------------------------------------------------------------------------

