@echo off

IF "%1" == "" ( 
    SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk
) ELSE ( 
    SET REP=%1
)

SET TARGET=Blackfin
SET TOOL=VDSP
SET DST_DIR=.

for /F "usebackq tokens=1,2 delims=." %%f in (`svn --version --quiet`) do set SVNVERSION=%%f.%%g
if "%SVNVERSION%" == "1.6" (set SWITCH=svn switch) else (set SWITCH=svn switch --ignore-ancestry)

%SWITCH% %REP%/Common/                   %DST_DIR%/scmRTOS/Common
%SWITCH% %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%
%SWITCH% %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions

