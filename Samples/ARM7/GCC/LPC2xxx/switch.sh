#!/bin/sh

if [ -z "$1" ] ; then
	REP=^/trunk
else
	REP=$1
fi

TARGET=ARM7
TOOL=GCC
FAMILY=LPC2xxx
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

$SWITCH $REP/Samples/$TARGET/$TOOL/$FAMILY/1-EventFlag/prj $DST_DIR/2-Message/prj
$SWITCH $REP/Samples/$TARGET/$TOOL/$FAMILY/1-EventFlag/prj $DST_DIR/3-Channel/prj
