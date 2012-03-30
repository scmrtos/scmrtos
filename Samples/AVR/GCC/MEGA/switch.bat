@echo off

rem default place is current_access_scheme_and_root_url/trunk
rem switch http://bla-bla-bla or switch ^/branches/pre-v400 for specifc place

IF "%1" == "" ( 
    SET REP=^/trunk
) ELSE ( 
    SET REP=%1
)

SET TARGET=AVR
SET FAMILY=MEGA
SET TOOL=GCC
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Extensions/               %DST_DIR%/scmRTOS/Extensions
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

