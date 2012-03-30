@echo off

IF "%1" == "" ( 
    SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/branches/pre-v400
) ELSE ( 
    SET REP=%1/trunk
)

SET TARGET=MSP430
SET TOOL=IAR
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%
svn switch  %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions

