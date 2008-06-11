@echo off

SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk

SET TARGET=AVR
SET TOOL=GCC
SET DST_DIR=.

svn switch  %REP%/Common/                   %DST_DIR%/scmRTOS/Common
svn switch  %REP%/Ports/%TARGET%/%TOOL%/    %DST_DIR%/scmRTOS/%TARGET%

