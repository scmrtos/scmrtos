@echo off

IF "%1" == "" ( 
    SET REP=^/trunk
) ELSE ( 
    SET REP=%1
)

SET TARGET=CortexM3
SET TOOL=GCC
SET FAMILY=STM32F1XX
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

svn switch %REP%/Samples/%TARGET%/%TOOL%/%FAMILY%/1-EventFlag/prj %DST_DIR%/2-Message/prj
svn switch %REP%/Samples/%TARGET%/%TOOL%/%FAMILY%/1-EventFlag/prj %DST_DIR%/3-Channel/prj
svn switch %REP%/Samples/%TARGET%/%TOOL%/%FAMILY%/1-EventFlag/prj %DST_DIR%/4-Debug/prj
