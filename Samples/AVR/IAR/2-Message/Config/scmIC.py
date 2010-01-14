#*******************************************************************************
#
#             scmRTOS Integrity Checker Script
#
#                   Version 2.0
#
#       Copyright (c) 2006-2007, Harry E. Zhurov
#
#
#    DESCRIPTION:
#
#
#    FUNCTIONALITY:
#
#
#*******************************************************************************
# -*- coding: cp-1251 -*-

import sys
import os
import getopt
import glob
import re

#-------------------------------------------------------------------------------
class TProcess:
    def __init__(self, pr, name):
        self.pr    = pr
        self.name  = name
        self.procs = []
        self.execs = []

#-------------------------------------------------------------------------------
def rip_comments(f):
    s = re.sub('\/\/.*\n', ' ', f)
    s = re.sub('\n', ' ', s)
    s = re.sub('\/\*.*?\*\/', ' ', s)

    return s
#-------------------------------------------------------------------------------
def scan_file_pass1(fname):
    f = open(fname, 'rt').read()
    f = rip_comments(f)

    def_list        = re.findall('#\s*define\s+(\w+)\s+(\d+)', f)
    proc_types_list = re.findall('typedef\s+OS::process\s*<\s*[\w:]*pr(\d)\s*,.+?>\s+(\w+)\s*;', f)

    return f, def_list, proc_types_list
#-------------------------------------------------------------------------------
def scan_file_pass2(file, proc_list):
    file_name     = file[0]
    file_contents = file[1]

    for i in proc_list:
        proc_type_name = i.name
        procs = re.findall('(?<!extern)\s+' + proc_type_name + '\s+(\w+)\s*;', file_contents)
        i.procs += procs

        execs = re.findall('template<>\s+void\s+' + proc_type_name + '::Exec\s*\(\s*\)\s*\{', file_contents)
        i.execs += execs

#-------------------------------------------------------------------------------
def show_summary(proc_list):
    typename_maxlen = 0
    objname_maxlen  = 0
    for i in proc_list:
        cur_typename_len = len(i.name)
        if i.procs:
            cur_objname_len  = len(i.procs[0])
        else:
            i.procs.append('None')

        if cur_typename_len > typename_maxlen:
            typename_maxlen = cur_typename_len

        if cur_objname_len > objname_maxlen:
            objname_maxlen = cur_objname_len

    typename_header = 'Process type name'
    objname_header  = 'Process object name'

    if typename_maxlen > len(typename_header):
        typename_len = typename_maxlen
    else:
        typename_len = len(typename_header)

    if objname_maxlen > len(objname_header):
        objname_len = objname_maxlen
    else:
        objname_len = len(objname_header)

    str_len = 1 + 8 + 3 + typename_len + 3 + objname_len + 1

    print ''
    print '='*str_len
    print ' '*( (str_len - len('*** Summary ***'))/2 ) +  '*** Summary ***'
    print '-'*str_len
    print ' Priority | ' + typename_header + ' '*(typename_len-len(typename_header)) + ' | ' + objname_header
    print '-'*str_len
    for i in proc_list:
        print ' pr' + i.pr + ' '*( len('Priority ')-len('pr'+i.pr) ) + '| ' + i.name + ' '*(typename_len-len(i.name)) + ' | ' + i.procs[0]

    print '-'*str_len


#-------------------------------------------------------------------------------
def checker(fld, Quiet = False, Summary = False, Recursive = False):
    #-------------------------------------------------
    #
    #    Prepare folder list and check the existence
    #    of the folders
    #
    folders = []
    for i in fld:
        if i[-1] == '\\': i = i[:-1]   # ripping trailing slash if exists
        cwd = os.getcwd()
        folder = os.path.abspath(i)
        if not os.path.exists(folder):
            print 'Error: specified folder "' + folder + '" does not exist.'
            return 2

        if Recursive == False:
            folders.append(folder)
        else:
            tree = os.walk(i)
            for root, dirs, files in tree:
                for d in dirs:
                    folder = os.path.join(root, d)
                    folders.append(folder)

    #-------------------------------------------------
    #
    #    Remove duplicates in folder list
    #
    tmp_fl = []
    for i in folders:
        if tmp_fl.count(i) == 0:
            tmp_fl.append(i)

    folders = tmp_fl
    #-------------------------------------------------
    #
    #    Create source files list (filenames)
    #
    src_files = []
    for i in folders:
        src_files += glob.glob(i + '/*.h')
        src_files += glob.glob(i + '/*.cpp')
        src_files += glob.glob(i + '/*.c')

    #-------------------------------------------------
    #
    #    Pass 1: rip comments,
    #            find defines,
    #            find process types
    #
    src_files_list  = []
    defines_list    = []
    proc_types_list = []
    for i in src_files:
        f, d, pt = scan_file_pass1(i)
        src_files_list.append((i,f))
        defines_list += d
        proc_types_list += pt
    #-------------------------------------------------
    #
    #    Analyze the result of the first pass
    #
    process_count = None
    for i in defines_list:
        if i[0] == 'scmRTOS_PROCESS_COUNT':
            if process_count == None:
                process_count = int(i[1])
            else:
                print 'Error: Process count specified more than once.'
                return 2

    proc_types_list.sort()
    #print proc_types_list
    if proc_types_list == []:
        print 'Error: Process types not found. Please check src dirs specified.'
        return 2
    prN        = proc_types_list[0][0]
    ptype_name = proc_types_list[0][1]
    if prN != '0':
        print 'Error: the most priority process must have "pr0" priority, but currently'
        print '       the most priority process "' + ptype_name + '" has priority "pr' + prN + '".'
        return 2

    for i in proc_types_list[1:]:
        if i[0] == prN:
            print 'Error: equal priorities for different processes are not allowed, but'
            print '       process type "' + ptype_name + '" and process type "' + i[1] + '"'
            print '       has the same priority value "pr' + i[0] + '".'
            return 2

        if int(i[0]) - int(prN) != 1:
            print 'Error: priorities of the processes must be in successive order (without "holes"'
            print '       in priority numbering), but process "' + ptype_name + '" has priority "pr' + prN + '"'
            print '       and the next priority process "' + i[1] + '" has priority "pr' + i[0] + '".'
            return 2

        prN        = i[0]
        ptype_name = i[1]

    if process_count != len(proc_types_list):
        print 'Error: specified process count does not match defined process types count.'
        print '       scmRTOS_PROCESS_COUNT specified as: ' + str(process_count) + ','
        print '       but defined process types are: ' + str(len(proc_types_list)) + '.'
        print ''
        print 'Defined process types are:'

        maxlen = 0
        for i in proc_types_list:
            cur_maxlen = len(i[1])
            if cur_maxlen > maxlen:
                maxlen = cur_maxlen

        if maxlen < len('Process type name'):
            maxlen = len('Process type name')

        print '-'*(maxlen + 22)
        print ' Process type name' + ' '*(maxlen-len('Process type name')) + ' | Process Priority'
        print '-'*(maxlen + 22)
        for i in proc_types_list:
            print ' ' + i[1] + ' '*(maxlen - len(i[1])) + ' |   pr' + i[0]

        print '-'*(maxlen + 22)
        return 2


    #-------------------------------------------------
    #
    #    Create Process list
    #
    proc_list = []
    for i in proc_types_list:
        proc = TProcess(i[0], i[1])
        proc_list.append(proc)

    #-------------------------------------------------
    #
    #    Pass 2: find process objects
    #            find process root functions
    #
    for i in src_files_list:
        scan_file_pass2(i, proc_list)

    #-------------------------------------------------
    #
    #    Analyze the result of the second pass
    #
    for i in proc_list:
        #print vars(i)
        if len(i.procs) == 0:
            print 'Error: process type "' + i.name + '" has no process object declared.'
            return 2

        if len(i.procs) > 1:
            print 'Error: process must have only one process-object, but process "' + i.name + '"'
            print '       has ' + str(len(i.procs)) + ' objects:',
            for j in i.procs:
                if j != i.procs[-1]:
                    print '"' + j + '",',
                else:
                    print '"' + j + '"'

            return 2

        if len(i.procs) and len(i.execs) != 1:
            if len(i.execs) == 0:
                print 'Error: process object must have root function defined, but process object'
                print '       of process type "' + i.name + '" has no root function "Exec" defined.'

                return 2

            if len(i.execs) > 1:
                print 'Error: process object must have only one root function, but process object'
                print '       of process type "' + i.name + '" has ' + str(len(i.execs)) + ' root functions "Exec" defined.'

                return 2


    if Quiet == False:
        print 'scmRTOS configuration is Ok!'

    if Summary:
        show_summary(proc_list)

    return 0

#-------------------------------------------------------------------------------
def main():

    #-------------------------------------------------
    #
    #    Process options
    #
    optlist, fld = getopt.gnu_getopt(sys.argv[1:], 'qsr')

    if fld == []:
        print 'scmRTOS Integrity Checker utility, (c) 2006-2007, Harry E. Zhurov'
        print '\n Usage: scmic src_folder1 [src_folder2...src_folderN] [options]'
        print '     where options:'
        print '        -q - suppress output'
        print '        -s - show summary'
        print '        -r - recursive folder processing'
        sys.exit(0)


    Quiet     = False
    Summary   = False
    Recursive = False
    for i in optlist:
        if i[0] == '-q':
            Quiet = True
        elif i[0] == '-s':
            Summary = True
        elif i[0] == '-r':
            Recursive = True


    ErrorCode = checker(fld, Quiet, Summary, Recursive)
    if ErrorCode != 0:
        sys.exit(ErrorCode)

#-------------------------------------------------------------------------------
if __name__ == '__main__':
    main()
#-------------------------------------------------------------------------------

