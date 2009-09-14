SET REP=https://scmrtos.svn.sourceforge.net/svnroot/scmrtos/trunk

svn switch %REP%/Common/ ./scmRTOS/Common
svn switch %REP%/Ports/CortexM3/GCC ./scmRTOS/CortexM3
