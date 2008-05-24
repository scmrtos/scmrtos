#-----------------------------------------------------------------------
# ReAl common makefile for avreal
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# Externally (in project makefile or in environment) defined variables:
#
#  AVREAL_PORT = LPT port number for adapter (1 if not defined externally)
#  AVREAL_ADAPTER = adapter used for programming (b if not defined)
# 	b - Altera byte blaster
#	s - STK200/STK300
#
#  AVREAL_OPT = project-dependent avreal switches ( -n, -2, etc.)
#
#  MCU		- target processor name
#  TRGPGM	- programming file[s]
#  F_CPU	- AVR clock frequency in hertz
#  FUSES	- fuses switches, for example
#                  FUSES := m103c=1,cksel=f,sut=1,ckopt=0,boden=0,blev=0
#
#

ifndef AVREAL_PORT
AVREAL_PORT := 1
endif

ifndef AVREAL_ADAPTER
AVREAL_ADAPTER = b
endif

AVREAL := avreal32.exe -a$(AVREAL_ADAPTER) -p$(AVREAL_PORT) +$(MCU)

ifdef F_CPU
AVREAL_FREQ  := -o$(F_CPU)hz
endif

# programming without locking (developer makefile :-)
.PHONY : run program fuses verify lock erase reset
run : $(TRGPGM)
	$(AVREAL) $(AVREAL_OPT) $(AVREAL_FREQ) -e -wp $^

#
prg_final : erase fuses run lock

#
fuses:
	$(AVREAL) -o50 -wp -v -f$(FUSES)

## verify
ifdef FUSES
verify: $(TRGPGM)
	$(AVREAL) $(AVREAL_FREQ) -v $^ -f$(FUSES)
else
verify: $(TRGPGM)
	$(AVREAL) $(AVREAL_FREQ) -v $^
endif

## lock
lock:  $(TRGPGM)
	$(AVREAL) $(AVREAL_FREQ) -v -l2 $^

## erase chip
erase:
	$(AVREAL) $(AVREAL_FREQ) -e

# software reset button
reset:
	$(AVREAL)  $(AVREAL_FREQ)

####	end of avreal.make

