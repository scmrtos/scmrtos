@echo off

IF "%1" == "" ( 
    SET REP="^/trunk"
) ELSE ( 
    SET REP=%1
)

SET TARGET=CortexM3
SET TOOL=GCC
SET FAMILY=STM32F2XX
SET DST_DIR=.

for /F "usebackq tokens=1,2 delims=." %%f in (`svn --version --quiet`) do set SVNVERSION=%%f.%%g
if "%SVNVERSION%" == "1.6" (set SWITCH=svn switch) else (set SWITCH=svn switch --ignore-ancestry)

%SWITCH% %REP%/Common/                   %DST_DIR%/scmRTOS/Common
%SWITCH% %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions
%SWITCH% %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%FAMILY%/1-EventFlag/prj %DST_DIR%/2-Message/prj
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%FAMILY%/1-EventFlag/prj %DST_DIR%/3-Channel/prj
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%FAMILY%/1-EventFlag/prj %DST_DIR%/4-Debug/prj
