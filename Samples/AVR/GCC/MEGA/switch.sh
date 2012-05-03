#!/bin/sh

# default place is current_access_scheme_and_root_url/trunk
# switch http://bla-bla-bla or switch ^/branches/pre-v400 for specifc place

if [ -z "$1" ] ; then
	REP=^/trunk
else
	REP=$1
fi


TARGET=AVR
FAMILY=MEGA
TOOL=GCC
DST_DIR=.

svn switch $REP/Common/                $DST_DIR/scmRTOS/Common
svn switch $REP/Extensions/            $DST_DIR/scmRTOS/Extensions
svn switch $REP/Ports/$TARGET/$TOOL/   $DST_DIR/scmRTOS/$TARGET

