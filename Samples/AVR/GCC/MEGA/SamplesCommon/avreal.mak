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

AVREAL := avreal32.exe "-a$(AVREAL_ADAPTER)" "-p$(AVREAL_PORT)" +$(MCU)

ifndef AVREAL_FREQ
ifdef F_CPU
AVREAL_FREQ  := $(F_CPU)
endif
endif

ifdef AVREAL_FREQ
AVREAL_FREQ_SW  := -o$(AVREAL_FREQ)hz
endif

# programming without locking (developer makefile :-)
.PHONY : program prg_final fuses verify lock erase reset
program : $(TRGPGM)
	$(AVREAL) $(AVREAL_OPT) $(AVREAL_FREQ_SW) -e -wp $^

#
prg_final : erase fuses program lock

#
fuses:
	$(AVREAL) -o50 -wp -v -f$(FUSES)

## verify
ifdef FUSES
verify: $(TRGPGM)
	$(AVREAL) $(AVREAL_FREQ_SW) -v $^ -f$(FUSES)
else
verify: $(TRGPGM)
	$(AVREAL) $(AVREAL_FREQ_SW) -v $^
endif

## lock
lock:  $(TRGPGM)
	$(AVREAL) $(AVREAL_FREQ_SW) -v -l2 $^

## erase chip
erase:
	$(AVREAL) $(AVREAL_FREQ_SW) -e

# software reset button
reset:
	$(AVREAL)  $(AVREAL_FREQ_SW)

####	end of avreal.make

