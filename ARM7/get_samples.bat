@echo off
rem *************************************************************
rem **                                                         **
rem **     scmRTOS ARM7 example checkout & switch file         **
rem **                                                         **
rem **   usage: get_samples.bat chip toolset [dir]             **
rem **   where:                                                **
rem **      chip - AT91SAM7 | LPC2xxx | ADuC70xx               **
rem **      toolset - GCC | IAR_v4.30 | IAR                    **
rem **      dir - relative path to destination dir             **
rem **                                                         **
rem *************************************************************


SET REP=http://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk
::SET REP=http://scmrtos.svn.sourceforge.net/svnroot/scmrtos/branches/pre-v400

SET TARGET=ARM7
SET CHIP_FAMILY=%1
SET TOOL=%2

SET DST_DIR=./%3

echo %DST_DIR%
pause
svn co %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY% %DST_DIR%

svn switch %REP%/Common                 %DST_DIR%/scmRTOS/Common
svn switch %REP%/Ports/%TARGET%/%TOOL%  %DST_DIR%/scmRTOS/%TARGET%
svn switch %REP%/Extensions             %DST_DIR%/scmRTOS/Extensions


svn switch %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Config %DST_DIR%/2-Message/Config
svn switch %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Config %DST_DIR%/3-Channel/Config

svn switch %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/device.h %DST_DIR%/2-Message/Src/device.h
svn switch %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/device.h %DST_DIR%/3-Channel/Src/device.h

IF %TOOL% == GCC (
    IF %CHIP_FAMILY% == AT91SAM7 (
        svn switch %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/AT91SAM7S64.h %DST_DIR%/2-Message/Src/AT91SAM7S64.h
        svn switch %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/AT91SAM7S64.h %DST_DIR%/3-Channel/Src/AT91SAM7S64.h
    )
)
