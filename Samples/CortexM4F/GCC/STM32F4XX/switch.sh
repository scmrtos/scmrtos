#!/bin/sh

if [ -z "$1" ] ; then
	REP=^/trunk
else
	REP=$1
fi

TARGET=CortexM4F
TOOL=GCC
FAMILY=STM32F4XX
DST_DIR=.

svn switch $REP/Common/                $DST_DIR/scmRTOS/Common
svn switch $REP/Extensions/            $DST_DIR/scmRTOS/Extensions
svn switch $REP/Ports/$TARGET/$TOOL/   $DST_DIR/scmRTOS/$TARGET

svn switch $REP/Samples/$TARGET/$TOOL/$FAMILY/1-EventFlag/prj $DST_DIR/2-Message/prj
svn switch $REP/Samples/$TARGET/$TOOL/$FAMILY/1-EventFlag/prj $DST_DIR/3-Channel/prj
svn switch $REP/Samples/$TARGET/$TOOL/$FAMILY/1-EventFlag/prj $DST_DIR/4-Debug/prj
svn switch $REP/Samples/$TARGET/$TOOL/$FAMILY/1-EventFlag/prj $DST_DIR/5-FPU/prj
