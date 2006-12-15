#*******************************************************************************
#
#          List file generator for VisualDSP++ 4.0
#
#                    Version 1.0
#
#          Copyright (c) 2006, Harry E. Zhurov
#
#
#
#    DESCRIPTION:    
#                   
#
#    FUNCTIONALITY: 
#                       
#
#*******************************************************************************


# coding: CP1251

import  sys
import  string
import  getopt
import  os
import  time
import  re

#-------------------------------------------------------------------------------
#
#   Function opens and reads the file. Returns the list of strings 
#   without trailing '\n' character (actual for Windows)
#
#
def ReadSrcFile(f):
    srcfile_tmp  = open(f).readlines()
    srcfile = []
    for i in srcfile_tmp:
        s = i.rstrip()
        srcfile.append(s)

    return srcfile
#-------------------------------------------------------------------------------
#
#   Function checks the string and returns the label or None
#
#
def IsLabel(s):
    match_object = re.match('^([\.|\w]+:)', s)
    if match_object:
        return match_object.group(1)
    else:
        return None
#-------------------------------------------------------------------------------
#
#   Function checks the string and returns the tuple (src_file, line, col) 
#   or None
#
def IsReference(s):
    search_object = re.search('^//[ |\t]+"(.+)" line ([0-9]+) col ([0-9]+)', s)
    if search_object: 
        src_file = search_object.group(1)
        line     = search_object.group(2)
        col      = search_object.group(3)
        ref      = src_file, line, col
        return ref
    else:
        return None
#-------------------------------------------------------------------------------
#
#   Function checks the string and returns the code string or None
#
#
def IsCode(s):
    search_object = re.search('^[ |\t]+[\[\]\(\)_a-zA-Z][_a-zA-Z0-9]*', s)
    if search_object: 
        return s
    else:
        return None
#-------------------------------------------------------------------------------
#
#   Function handles the string and returns the list [Signature, Data] or None
#
#
def ProcessString(s):
    res = IsLabel(s)
    if res:
        return [ 'Label', res ]

    res = IsReference(s)
    if res:
        return [ 'Ref', res ]

    res = re.match('^//', s)
    if res:
        return None

    res = IsCode(s)
    if res:
        return [ 'Code', res ]
    else:
        return None
#-------------------------------------------------------------------------------
#
#   Functions creates title header
#
#
def CreateTitle(s):
    title  = '*'*80 + '\r\n'
    title += '*' + 78*' '  + '*\r\n' 
    title += '*' + 78*' '  + '*\r\n' 
    title += '*' + ' '*( (78-len(s))/2 ) + s +  ' '*( (78-len(s))/2 ) + '*\r\n'
    title += '*' + 78*' '  + '*\r\n' 
    title += '*' + 78*' '  + '*\r\n' 
    title += '*'*80 + '\r\n'
    return title
#-------------------------------------------------------------------------------
#
#   Functions prints contents of list record (for debug purposes).
#
#
def PrintRecords(r):
    for i in r:
        for j in i[2]:
            print j
        print i[0]
        for j in i[1]:
            print j

#-------------------------------------------------------------------------------
#
#    Main job
#
def create_lst(InFileName):

    idata = ReadSrcFile(InFileName)

    #-----------------------------------------------------
    #
    #   Collect Records
    #
    outfile   = []
    records   = []
    src_files = {}

    labels    = []
    ref       = ''
    code      = []
    state = 'Collect Labels'
    N = 0
    for i in idata:
        res = ProcessString(i)

        if not res: continue

        if res[0] == 'Label':
            if state == 'Ref has been found':
                labels = []
                labels.append(res[1])

            elif state == 'Collect code':
                rec = [ ref, code, labels ]
                records.append(rec)
                labels = []
                code = []
                ref  = ''
                labels.append(res[1])

            else:
                labels.append(res[1])

            state = 'Collect Labels'
            
        elif res[0] == 'Ref':
            ref   = res[1]
            state = 'Ref has been found'

        elif res[0] == 'Code':
            NumStr = (60-len(res[1]))*' ' + '(' +  str(N) + ')'
            res[1] += NumStr
            N += 1
            code.append(res[1]) 
            state = 'Collect code'

    #PrintRecords(records)

    #-----------------------------------------------------
    #
    #    Create Source Listing Section
    #
    out_str = CreateTitle('Source Listing Section')
    src_filename = re.search('"(.+)"', idata[0]).group(1)
    src_file = ReadSrcFile(src_filename)
    for i in range( 0, len(src_file)-1 ):
        out_str += src_file[i] + '\r\n'
        for j in records:
            if not j[0]: continue
            rec_src_file, rec_line, rec_col = j[0]  # unpack reference
            if rec_src_file != src_filename: continue
            if i == int(rec_line) - 1:
                for k in j[2]:          # print labels
                    out_str += k + '\r\n'
                for k in j[1]:          # print code
                    out_str += k + '\r\n'


    #----------------------------------------------------------------
    #
    #   Create Substituted References Section
    #
    title = CreateTitle('Substituted References Section')
    out_str += '\r\n\r\n' + title


    for i in idata:
        ref = IsReference(i)
        if ref:
            src_file, line, col = ref
            if not src_files.has_key(src_file):
                f = ReadSrcFile(src_file)
                src_files[src_file] = f

            if col == '1':
                line_num = int(line) - 1
            else:
                line_num = int(line)

            src_line = src_files[src_file][line_num-1]
            out_line = src_line + ' ' + i + '\r\n'
            out_str += out_line

        else:
            out_str += i + '\r\n'

    open(InFileName + '.lst', 'wb').write(out_str)

#-------------------------------------------------------------------------------
#
#    Main function: get options and arguments, run tasks
#
def main():
    #print os.listdir(os.getcwd())
    #-----------------------------------------------------
    #
    #   Process options
    #
    optlist, infiles = getopt.gnu_getopt(sys.argv[1:], '')

    if not infiles:  return
    InFileName = infiles[0]
    create_lst(InFileName)
#-------------------------------------------------------------------------------
if __name__ == '__main__': 
    main()
#-------------------------------------------------------------------------------

