#
#  scmRTOS avr-gcc port
#
#  Project-dependent makefile for sample 2-Message
#
#     $Revision$
#     $Date::             $
#

########
# Change avr-gcc version by setting TOOL variable here.
# If TOOL not defined here it will be defined in avr-gcc.mak to default value "avr-"

#TOOL = avr-kgp-
#TOOL = c:/WinAVR/bin/avr-
#TOOL = c:/avr-gcc/WinAVR/20071221/bin/avr-
#TOOL = c:/avr-gcc/WinAVR/20100110/bin/avr-
#TOOL = c:/avr-gcc/kgp/20080530/bin/avr-
#TOOL = c:/avr-gcc/kgp/20100725/bin/avr-

# Y/N - !!! N for gcc < 4.x
MAKE_SMALLEST_HEX = Y

# point to start of project sources subtree,
PROJ_SRCTOP := .

#put the name of the target file here (without extension)
TRG	  := 2-Message
TRGPGMEXT := hex
#eep

# project modules (directories with source files)
# "current" directory (.) included automatically in gcc-avr.make
MODULES := ./src ../SamplesCommon
MODULES += ../scmRTOS/Common ../scmRTOS/AVR

# needed for includes below
COMMON_MAKEFILES := ../SamplesCommon

###########
# used in gcc-avr.make and avreal.make
#MCU := atmega48
#MCU := atmega88
MCU := atmega168
#MCU := atmega328p
#MCU := atmega64
#MCU := atmega640
#MCU := atmega2561

# used in avreal.make and transferred to source files as '#define'
F_CPU=8000000

# additional options for avreal (like -n)
# put -l2 here for lock chip after programming by 'make run'
#AVREAL_OPT= -n
# The same fuses can be used for atmega48..atmega328 and for atmega640..atmega2561
# if JTAGEN fuse need not to be erased (factory default state - programmed)
ifneq (,$(findstring $(MCU),atmega64 atmega128))
FUSES = boden=0,bodlevel=1,cksel=F,ckopt=on,sut=1
else
FUSES = bodlevel=5,cksel=7,ckdiv8=off,sut=1
endif


# additional libraries and object files to link
LIB	=

# assembler flags
ASFLAGS =

#OPT = -Os  -mcall-prologues
OPT = -Os

# compiler flags
#CSTD := -std=gnu99
#CXXSTD := -std=c++98 --pedantic

CWARN = -Wextra -Wall #-Wstrict-prototypes -Wno-main
CFLAGS	= -g $(OPT) $(CSTD) $(CWARN) -DF_CPU=$(F_CPU)UL
CFLAGS += -funsigned-bitfields -fshort-enums
CFLAGS += -frename-registers
CFLAGS += -Wredundant-decls

# Copy common part of flags into C++ flags variable
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -fno-exceptions -fno-rtti
CXXFLAGS += -fno-threadsafe-statics

# add standard flag to CFLAGS _after_ copying CFLAGS to CXXFLAGS
CFLAGS += $(CSTD)
CXXFLAGS += $(CXXSTD)


# linker flags
#---------------- Library Options ----------------
LDFLAGS =

ifeq ($(MAKE_SMALLEST_HEX),Y)
	CFLAGS += -ffunction-sections -fdata-sections
	CXXFLAGS += -ffunction-sections -fdata-sections
	LDFLAGS += -Wl,--gc-sections
#	LDFLAGS += -Wl,--print-gc-sections
	LDFLAGS += -Wl,--relax
endif

########### you should not need to change the following lines #############
# keep order!
# avreal.mak must be included after gcc-avr because of TRGPGM definition
include $(COMMON_MAKEFILES)/gcc-avr.mak
include $(COMMON_MAKEFILES)/avreal.mak

## end
