@echo off

IF "%1" == "" ( 
    SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk
) ELSE ( 
    SET REP=%1/trunk
)

SET TARGET=ARM7
SET TOOL=GCC4.x
SET CHIP_FAMILY=LPC2xxx
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/prj %DST_DIR%/2-Message/prj
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/prj %DST_DIR%/3-Channel/prj

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/src/device.h %DST_DIR%/2-Message/src/device.h
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/src/device.h %DST_DIR%/3-Channel/src/device.h

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/src/LPC214x.h %DST_DIR%/2-Message/src/LPC214x.h
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/src/LPC214x.h %DST_DIR%/3-Channel/src/LPC214x.h
