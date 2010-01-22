@echo off
rem *************************************************************
rem **                                                         **
rem **     scmRTOS Fujitsu FR example checkout & switch file   **
rem **                                                         **
rem **   usage: get_samples.bat [dir]                          **
rem **   where:                                                **
rem **      dir - relative path to destination dir             **
rem **                                                         **
rem *************************************************************


SET REP=http://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk

SET TARGET=FR

SET CHIP_FAMILY=FR

SET TOOL=Softune_V6

SET DST_DIR=./%1


echo %DST_DIR%

pause

svn co      %REP%/Samples/%TARGET%/%TOOL%   %DST_DIR%/

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

