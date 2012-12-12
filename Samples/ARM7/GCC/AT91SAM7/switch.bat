@echo off

IF "%1" == "" ( 
    SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk
) ELSE ( 
    SET REP=%1
)

SET TARGET=ARM7
SET TOOL=GCC
SET CHIP_FAMILY=AT91SAM7
SET DST_DIR=.

for /F "usebackq tokens=1,2 delims=." %%f in (`svn --version --quiet`) do set SVNVERSION=%%f.%%g
if "%SVNVERSION%" == "1.6" (set SWITCH=svn switch) else (set SWITCH=svn switch --ignore-ancestry)

%SWITCH%  %REP%/Common                    %DST_DIR%/scmRTOS/Common
%SWITCH%  %REP%/Ports/%TARGET%/%TOOL%     %DST_DIR%/scmRTOS/%TARGET%
%SWITCH%  %REP%/Extensions                %DST_DIR%/scmRTOS/Extensions

%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Config %DST_DIR%/2-Message/Config
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Config %DST_DIR%/3-Channel/Config
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Config %DST_DIR%/4-Profiler/Config

%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/device.h %DST_DIR%/2-Message/Src/device.h
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/device.h %DST_DIR%/3-Channel/Src/device.h
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/device.h %DST_DIR%/4-Profiler/Src/device.h

%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/AT91SAM7S64.h %DST_DIR%/2-Message/Src/AT91SAM7S64.h
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/AT91SAM7S64.h %DST_DIR%/3-Channel/Src/AT91SAM7S64.h
%SWITCH% %REP%/Samples/%TARGET%/%TOOL%/%CHIP_FAMILY%/1-EventFlag/Src/AT91SAM7S64.h %DST_DIR%/4-Profiler/Src/AT91SAM7S64.h
