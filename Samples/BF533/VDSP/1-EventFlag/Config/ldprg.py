#*******************************************************************************
#*
#*              ADSP-BF Load Program Script
#*          (client for VisualDSP++ 4.0 COM server)
#*
#*                    Version 1.0
#*
#*          Copyright (c) 2006-2007, Harry E. Zhurov
#*
#*
#*    DESCRIPTION:
#*
#*
#*    FUNCTIONALITY:
#*
#*
#* coding: CP1251
#*******************************************************************************

import win32com.client
import vdsp_tl
from vdsp_tl import constants as VDSP

import  sys
import  getopt
import  os
import  re
import  winsound
import  string
import  struct

#-------------------------------------------------------------------------------
#
#
#
class TProcessor:
    ''' ADSP Processor '''

    def __init__(self, p):
        self.p = p
        self.Memory = p.MemoryTypeList.Item("BLACKFIN Memory")
        self.Symbols = {}

#-------------------------------------------------------------------------------
#
#   Usage
#
def UsageInfo():
    print '*'*(101-12)
    print '* usage: ldprg -p <ProcessorName> -i <Initializer FileName> -e <Executable FileName> -s <Session Name>'
    print '*'
    print '*     Available Processors are: ADSP-BF531, ADSP-BF532, ADSP-BF533'
    print '*'*(101-12)
#-------------------------------------------------------------------------------
#
#   Process command line options
#
def ProcessOptions(olst):
    optlist, infiles = getopt.gnu_getopt(olst, 'i:e:p:s:')

    Options = {}

    Options['Result'    ] = False
    if olst == '':
        UsageInfo()
        return Options

    for i in optlist:
        if i[0] == '-i':
            Options['InitializerFileName'] = i[1]

        elif i[0] == '-e':
            Options['ExecutableFileName']  = i[1]

        elif i[0] == '-p':
            Options['ProcessorName']       = i[1]

        elif i[0] == '-s':
            Options['SessionName']         = i[1]


    if not Options.has_key('InitializerFileName'):
        print 'Error > Initializer file name does not specified'
        UsageInfo()
        return Options

    if not os.path.exists(Options['InitializerFileName']) :
        print 'Error > Initializer file \"' + Options['InitializerFileName'] + '\" does not exist'
        return Options

    if not Options.has_key('ExecutableFileName'):
        print 'Error > Executable file name does not specified'
        UsageInfo()
        return Options

    if not os.path.exists(Options['ExecutableFileName']) :
        print 'Error > Executable file \"' + Options['ExecutableFileName'] + '\" does not exist'
        return Options

    if not Options.has_key('ProcessorName'):
        print 'Error > Target processor does not specified'
        UsageInfo()
        return Options

    if not Options.has_key('SessionName'):
        print 'Error > Session name does not specified'
        UsageInfo()
        return Options


    Options['Result'] = True

    return Options

#-------------------------------------------------------------------------------
#
#   Check session for validity: session must be an Emulator Session and
#   must correspond to specified processor
#
def CheckSession(s, p, SessionName):
    if hasattr(s, 'DebugTargetName'):
        TargetName = s.DebugTargetName
        TargetProc = s.ProcessorList.Item(0)
    else:
        TargetName = s.TargetName
        TargetProc = s.ProcessorList.Item(0).Name

    search_object = re.search(SessionName, s.PlatformName)                   # check if Debug Target
    if search_object:                                                        # is emulator
        if s.ProcessorList.Count != 1:                                       # check if only one processor
            Message = 'Currently only one processor for session supported.'  # in session (JTAG chain)
            return ('Miss', Message)

        if TargetProc == p.upper():                                          # check if Debug Target Processor
            return ('Success', 'Success')                                    # is the same as specified in command
        else:                                                                # line options
            Message = 'Processor ' + p + ' does not mutch'
            return ('Miss', Message)                                         # valid Debug Session is found
    else:
        Message = 'This Session is not Emulator Session'
        return ('Miss', Message)



#-------------------------------------------------------------------------------
#
#
#
def process_symbols(p):
    SymbStrList = p.Memory.SymbolList.ArrayOfSymbols
    Symbols = []
    for i in SymbStrList:
        l = string.split(i, ',')
        addr = int(l[2], 16)
        a = struct.pack('I', addr)
        b = struct.unpack('i', a)
        Symbols.append( [str(l[0]), b[0]] )

    return Symbols

#-------------------------------------------------------------------------------
#
#   Run to main: goes to main and stopped
#
def RunToMain(ADSP):
    #-----------------------------------------------------
    #
    #   Process symbols
    #
    SymbList = process_symbols(ADSP)
    for i in SymbList:
        if i[0] == 'main':
            ADSP.Symbols['main'] = i[1]

    #-----------------------------------------------------
    #
    #   Manage Breakpoints and set
    #   processor to waiting for jobs
    #
    BPList = ADSP.p.BreakpointList
   # BPCount = BPList.Count
   # if BPCount:
   #     for i in xrange(BPCount):
   #         BPList.RemoveBreakpointByIndex(i)
    #                                                                         Skip  Expr   Temp   Enabled  Reserved
    BPList.SetBreakpointAtAddress( VDSP.breakpointPublic, ADSP.Symbols['main'], 0,   '',   True,  True,     0 )
    ADSP.p.Run(True)

#-------------------------------------------------------------------------------
#
#
#
def set_breakpoints(ADSP, bpl):
    BPList = ADSP.p.BreakpointList
    for i in bpl:
        if i[0]:
            #                                                                          Skip Expr   Temp   Enabled  Reserved
            BPList.SetBreakpointAtLine( VDSP.breakpointPublic, i[0], i[1], 0,   '',   False,  True,     0 )

#-------------------------------------------------------------------------------
#
#   Loader
#
def loader(InitializerFileName, ExecutableFileName, ProcessorName, SessionName):
    #-----------------------------------------------------
    #
    #   Conect to server
    #
    print ''
    print 'Info  > Connecting to VisualDSP++... ',
    vdsp = win32com.client.Dispatch("VisualDSP.ADspApplication")
    print 'Success'
    vdsp.CurrentDirectory = os.getcwd()
    print 'Info  > Current Session: \"' + vdsp.ActiveSession.SessionName + '\"',

    res = CheckSession(vdsp.ActiveSession, ProcessorName, SessionName)
    if res[0] == 'Success':
        print '... Ok!'
    else:
        print '... mismatch'
        #print 'Info  > ' + res[1]
        #-----------------------------------------------------
        #
        #   Find emulator session and set it avtive
        #
        Session = None
        for i in xrange(vdsp.SessionList.Count):
            res = CheckSession(vdsp.SessionList.Item(i), ProcessorName, SessionName)
            if res[0] == 'Success':
                Session = i
                break                                  # valid Debug Session is found

        if Session == None:
            print 'Error > There are no available emulator sessions for specified processor'
            print 'Info  > Specified processor: ' + ProcessorName
            print '        Available Sessions: ',
            for i in xrange(vdsp.SessionList.Count):
                if i == 0: indent = ''
                else:      indent = ' '*(45-16)
                print indent + vdsp.SessionList.Item(i).Name

            winsound.PlaySound('Utopia Critical Stop.WAV', winsound.SND_FILENAME)
            sys.exit(1)

        vdsp.SessionList.CreateSession(Session)
        print 'Info  > Changing current Simulator Session to Emulator ' + SessionName    + ' Session... ',
        print 'Done'
        print 'Info  > New Session: \"' + vdsp.ActiveSession.SessionName + '\"'

    ADSP = TProcessor(vdsp.ActiveSession.ProcessorList.Item(0))
    #-----------------------------------------------------
    #
    #   Load Initializer
    #
    vdsp.PrintText(VDSP.tabConsole, '')
    vdsp.PrintText(VDSP.tabConsole, 'Begin loading')
    bpl = ADSP.p.BreakpointList
    PrevBPL = []
    for i in bpl:
        PrevBPL.append( (i.FileName, i.LineNumber) )

    print 'Info  > Loading Hardware Initializer... ',
    if ADSP.p.State != VDSP.stateHalted:
        ADSP.p.Halt(True)

    ADSP.p.LoadProgram(InitializerFileName)
    ADSP.p.Restart(True)

    print 'Done'

    vdsp.PrintText(VDSP.tabConsole, 'Load Hardware Initializer')
    RunToMain(ADSP)
    vdsp.PrintText(VDSP.tabConsole, 'Initialize Hardware')

    #-----------------------------------------------------
    #
    #   Load Executable
    #
    print 'Info  > Loading Executable... ',
    if ADSP.p.State != VDSP.stateHalted:
        ADSP.p.Halt(True)

    ADSP.p.LoadProgram(ExecutableFileName)
    ADSP.p.Restart(True)

    print 'Done'
    vdsp.PrintText(VDSP.tabConsole, 'Load Program Executable')
    RunToMain(ADSP)
    set_breakpoints(ADSP, PrevBPL)
   # for i in BPList:
   #     print hex(i.Address + 0x100000000)

   # ADSP.p.StepAsm(True)
   # ADSP.Memory.GetMemory()
    winsound.PlaySound('chimes.wav', winsound.SND_FILENAME)


#-------------------------------------------------------------------------------
#
#   Main code
#
def main():
    #-----------------------------------------------------
    #
    #   Process options
    #
    Options = ProcessOptions(sys.argv[1:])
    if Options['Result'] == False:
        winsound.PlaySound('Utopia Critical Stop.WAV', winsound.SND_FILENAME)
        sys.exit(1)

    curdir = os.getcwd()
    InitializerFileName = curdir + '\\' + Options['InitializerFileName']
    ExecutableFileName  = curdir + '\\' + Options['ExecutableFileName']
    ProcessorName       = Options['ProcessorName']
    SessionName         = Options['SessionName']
    loader(InitializerFileName, ExecutableFileName, ProcessorName, SessionName)

#-------------------------------------------------------------------------------
if __name__ == '__main__':
    main()
#-------------------------------------------------------------------------------

