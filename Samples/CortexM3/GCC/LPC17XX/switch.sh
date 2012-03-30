#!/bin/sh

if [ -z "$1" ] ; then
	REP=^/trunk
else
	REP=$1
fi

TARGET=CortexM3
TOOL=GCC
FAMILY=LPC17XX
DST_DIR=.

svn switch $REP/Common/                $DST_DIR/scmRTOS/Common
svn switch $REP/Extensions/            $DST_DIR/scmRTOS/Extensions
svn switch $REP/Ports/$TARGET/$TOOL/   $DST_DIR/scmRTOS/$TARGET

