@echo off

IF "%1" == "" ( 
    SET REP=^/trunk
) ELSE ( 
    SET REP=%1
)

SET TARGET=MSP430
SET TOOL=GCC
SET FAMILY=430
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%
