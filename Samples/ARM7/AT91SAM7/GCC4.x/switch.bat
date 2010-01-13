@echo off

SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk

SET TARGET=ARM7
SET TOOL=GCC4.x
SET CHIP_FAMILY=AT91SAM7
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Config %DST_DIR%/2-Message/Config
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Config %DST_DIR%/3-Channel/Config

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Src/device.h %DST_DIR%/2-Message/Src/device.h
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Src/device.h %DST_DIR%/3-Channel/Src/device.h

svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Src/AT91SAM7S64.h %DST_DIR%/2-Message/Src/AT91SAM7S64.h
svn switch %REP%/Samples/%TARGET%/%CHIP_FAMILY%/%TOOL%/1-EventFlag/Src/AT91SAM7S64.h %DST_DIR%/3-Channel/Src/AT91SAM7S64.h
