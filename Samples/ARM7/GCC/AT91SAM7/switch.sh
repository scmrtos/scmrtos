#!/bin/sh

if [ -z "$1" ] ; then
	REP=^/trunk
else
	REP=$1
fi

TARGET=ARM7
TOOL=GCC
CHIP_FAMILY=AT91SAM7
DST_DIR=.

svn switch $REP/Common/                $DST_DIR/scmRTOS/Common
svn switch $REP/Extensions/            $DST_DIR/scmRTOS/Extensions
svn switch $REP/Ports/$TARGET/$TOOL/   $DST_DIR/scmRTOS/$TARGET

svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Config $DST_DIR/2-Message/Config
svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Config $DST_DIR/3-Channel/Config
svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Config $DST_DIR/4-Profiler/Config

svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/device.h $DST_DIR/2-Message/Src/device.h
svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/device.h $DST_DIR/3-Channel/Src/device.h
svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/device.h $DST_DIR/4-Profiler/Src/device.h

svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/AT91SAM7S64.h $DST_DIR/2-Message/Src/AT91SAM7S64.h
svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/AT91SAM7S64.h $DST_DIR/3-Channel/Src/AT91SAM7S64.h
svn switch $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/AT91SAM7S64.h $DST_DIR/4-Profiler/Src/AT91SAM7S64.h
