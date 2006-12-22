@echo off
rem *************************************************************
rem **                                                         **
rem **     scmRTOS ARM7 example checkout & switch file         **
rem **                                                         **
rem **   usage: get_samples.bat chip [dir]                     **
rem **   where:                                                **
rem **      chip - AT91SAM7 | LPC2xxx | ADuC70xx               **
rem **      dir - relative path to destination dir             **
rem **                                                         **
rem *************************************************************


SET REP=http://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk

SET TARGET=ARM7
SET CHIP_FAMILY=%1
SET TOOL=IAR_v4.30

SET DST_DIR=./%2

echo %DST_DIR%
pause
svn co %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL% %DST_DIR%/
svn switch %REP%/Common/ %DST_DIR%/scmRTOS/Common
svn switch %REP%/Ports/%TARGET%/%TOOL%/ %DST_DIR%/scmRTOS/%TARGET%
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Config %DST_DIR%/2-Message/Config
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Config %DST_DIR%/3-Channel/Config

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Src/device.h %DST_DIR%/2-Message/Src/device.h

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Src/device.h %DST_DIR%/3-Channel/Src/device.h
