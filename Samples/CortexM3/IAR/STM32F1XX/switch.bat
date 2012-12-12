@echo off

IF "%1" == "" ( 
    SET REP="^/trunk"
) ELSE ( 
    SET REP=%1
)

SET TARGET=CortexM3
SET TOOL=IAR
SET DST_DIR=.

for /F "usebackq tokens=1,2 delims=." %%f in (`svn --version --quiet`) do set SVNVERSION=%%f.%%g
if "%SVNVERSION%" == "1.6" (set SWITCH=svn switch) else (set SWITCH=svn switch --ignore-ancestry)

%SWITCH% %REP%/Common/                   %DST_DIR%/scmRTOS/Common
%SWITCH% %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions
%SWITCH% %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

