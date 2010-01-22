@echo off

IF "%1" == "" ( 
    SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk
) ELSE ( 
    SET REP=%1/trunk
)

SET TARGET=FR
SET TOOL=Softune_V6
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

