@echo off

IF "%1" == "" ( 
    SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk
) ELSE ( 
    SET REP=%1/trunk
)

SET TARGET=CortexM3
SET TOOL=GCC
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

svn switch %REP%/Samples/%TARGET%/%TOOL%/1-EventFlag/prj %DST_DIR%/2-Message/prj
svn switch %REP%/Samples/%TARGET%/%TOOL%/1-EventFlag/prj %DST_DIR%/3-Channel/prj
