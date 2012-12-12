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

SVN_VER="`svn --version --quiet  | sed 's/\([0-9.]*\)\.\([0-9.]*\)\.\(.*\)/\1.\2/'`"
if [ $SVN_VER = "1.6" ]; then
    SWITCH="svn switch"
else
    SWITCH="svn switch --ignore-ancestry"
fi

$SWITCH $REP/Common/                $DST_DIR/scmRTOS/Common
$SWITCH $REP/Extensions/            $DST_DIR/scmRTOS/Extensions
$SWITCH $REP/Ports/$TARGET/$TOOL/   $DST_DIR/scmRTOS/$TARGET

