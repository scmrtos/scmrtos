@echo off

rem default place is current_access_scheme_and_root_url/trunk
rem switch http://bla-bla-bla or switch ^/branches/pre-v400 for specifc place

IF "%1" == "" ( 
    SET REP="^/trunk"
) ELSE ( 
    SET REP=%1
)

SET TARGET=AVR
SET FAMILY=MEGA
SET TOOL=GCC
SET DST_DIR=.

for /F "usebackq tokens=1,2 delims=." %%f in (`svn --version --quiet`) do set SVNVERSION=%%f.%%g
if "%SVNVERSION%" == "1.6" (set SWITCH=svn switch) else (set SWITCH=svn switch --ignore-ancestry)

%SWITCH%  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
%SWITCH%  %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions
%SWITCH%  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

