@echo off

IF "%1" == "" ( 
    SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk
) ELSE ( 
    SET REP=%1/trunk
)

svn switch %REP%/Common/ ./scmRTOS/Common
svn switch %REP%/Ports/MSP430/GCC ./scmRTOS/MSP430
