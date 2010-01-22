#
#  scmRTOS avr-gcc port
#
#  project-dependent makefile for samples
#

# can change WinAVR version by setting AVRGCC variable here (override environment)
#AVRGCC :=c:/kgp-avr/20071102
#AVRGCC :=c:/kgp-avr/20070928
#AVRGCC :=d:/mingw/local
AVRGCC :=c:/WinAVR-20071221
#AVRGCC :=c:/WinAVR-20070525
#AVRGCC :=c:/WinAVR-20060421

# Y/N - !!! N for gcc < 4.x
MAKE_SMALLEST_HEX = Y

# point to start of project sources subtree,
PROJ_SRCTOP := .

#put the name of the target file here (without extension)
TRG	= event_flag

# project modules (directories with source files)
# "current" directory (.) included automatically in gcc-avr.make
MODULES := ./src ../scmRTOS/Common ../scmRTOS/AVR
# needed for includes below
COMMON_MAKEFILES := ./makefiles

###########
# used in gcc-avr.make and avreal.make
MCU := atmega168
#MCU := atmega48
TRGPGMEXT := hex
#eep

# used in avreal.make and transferred to source files as '#define'
F_CPU=8000000

# additional options for avreal (like -n)
# put -l2 here for lock chip after programming by 'make run'
#AVREAL_OPT= -n
FUSES = bodlevel=5,cksel=2,ckdiv8=off,sut=0


# additional libraries and object files to link
LIB	=

# assembler flags
ASFLAGS =

#OPT = -Os  -mcall-prologues
OPT = -Os

# compiler flags
CSTD = # -std=c++98 --pedantic

CWARN = -Wextra -Wall #-Wstrict-prototypes -Wno-main
CFLAGS	= -g $(OPT) $(CSTD) $(CWARN) \
 -DF_CPU=$(F_CPU)UL \
 -fno-exceptions -fno-rtti \
 -funsigned-bitfields -fshort-enums

# -fpack-struct не йде для scmRTOS для avr-gcc 3.4.6
# OS_Kernel.h:167: error: cannot bind packed field `((OS::TKernel*)this)->OS::TKernel::ReadyProcessMap' to `OS::TProcessMap&'

# linker flags
#---------------- Library Options ----------------
LDFLAGS =

ifeq "$(MAKE_SMALLEST_HEX)" "Y"
	CFLAGS += -ffunction-sections -fdata-sections
	LDFLAGS += -Wl,--gc-sections
	LDFLAGS += -Wl,--relax
endif

########### you should not need to change the following lines #############
# keep order!
# avreal.make must be included after gcc-avr because of TRGPGM definition
include $(COMMON_MAKEFILES)/gcc-avr.mak
include $(COMMON_MAKEFILES)/avreal.mak

## end
