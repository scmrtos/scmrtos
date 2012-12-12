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

SVN_VER="`svn --version --quiet  | sed 's/\([0-9.]*\)\.\([0-9.]*\)\.\(.*\)/\1.\2/'`"
if [ $SVN_VER = "1.6" ]; then
    SWITCH="svn switch"
else
    SWITCH="svn switch --ignore-ancestry"
fi

$SWITCH $REP/Common/                $DST_DIR/scmRTOS/Common
$SWITCH $REP/Extensions/            $DST_DIR/scmRTOS/Extensions
$SWITCH $REP/Ports/$TARGET/$TOOL/   $DST_DIR/scmRTOS/$TARGET

$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Config $DST_DIR/2-Message/Config
$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Config $DST_DIR/3-Channel/Config
$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Config $DST_DIR/4-Profiler/Config

$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/device.h $DST_DIR/2-Message/Src/device.h
$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/device.h $DST_DIR/3-Channel/Src/device.h
$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/device.h $DST_DIR/4-Profiler/Src/device.h

$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/AT91SAM7S64.h $DST_DIR/2-Message/Src/AT91SAM7S64.h
$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/AT91SAM7S64.h $DST_DIR/3-Channel/Src/AT91SAM7S64.h
$SWITCH $REP/Samples/$TARGET/$TOOL/$CHIP_FAMILY/1-EventFlag/Src/AT91SAM7S64.h $DST_DIR/4-Profiler/Src/AT91SAM7S64.h
