@echo off

IF "%1" == "" ( 
    SET REP="^/branches/pre-v400"
) ELSE ( 
    SET REP=%1
)

SET TARGET=STM8
SET TOOL=IAR
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

