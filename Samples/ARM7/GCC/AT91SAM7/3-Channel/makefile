#*****************************************************************
#  makefile for scmRTOS GCC port building
#*****************************************************************

#select preffered toolset or leave commented to use default
TOOLSET = $(ARM_GCC)/yagarto/20111119

TARGET = arm-none-eabi-
CC   = $(TARGET)gcc
AS   = $(TARGET)gcc -x assembler-with-cpp
OBJCOPY = $(TARGET)objcopy
OBJDUMP = $(TARGET)objdump 
SIZE = $(TARGET)size 

CHIP = AT91SAM7S64

PROJECT = 3-Channel

OPTIMIZE = -Os

##############################################################################################
# OS sources directories
scmRTOS_DIRS = ../scmRTOS/Common ../scmRTOS/ARM7
# Application sources directories
SRC_DIRS = ./Src
# Directories to search includes
INC_DIRS = 
# Directories to search libraries
LIB_DIRS =
##############################################################################################
# THUMB sources
#
SRC_THUMB_CPP = 
SRC_THUMB_ASM = 
############################
#  ARM .cpp sources
#       OS sources
SRC_ARM_CPP = OS_Kernel.cpp
SRC_ARM_CPP += OS_Services.cpp
SRC_ARM_CPP += usrlib.cpp
SRC_ARM_CPP += OS_Target_cpp.cpp
#       Application sources
SRC_ARM_CPP += main.cpp
############################
#  ARM .S sources
#       OS sources
SRC_ARM_ASM = OS_Target_asm.S
#       Application sources
SRC_ARM_ASM += crt.S
############################
# libraries
LIBS =
##############################################################################################
#LD_SCRIPT= ./Config/scmRTOS_SAM7_ram.ld
LD_SCRIPT= ./Config/scmRTOS_SAM7_rom.ld
##############################################################################################
# predefined symbols for all sources
DEFS =
# predefined symbols for .cpp sources
CPP_DEFS = 
# predefined symbols for .S sources
ASM_DEFS = 
##############################################################################################
# Output files
ELF = $(EXEDIR)/$(PROJECT).elf
HEX = $(EXEDIR)/$(PROJECT).hex
BIN = $(EXEDIR)/$(PROJECT).bin
LSS = $(LSTDIR)/$(PROJECT).lss
##############################################################################################
##############################################################################################
MCU  = arm7tdmi

INC_DIRS += $(scmRTOS_DIRS)
INC_DIRS += $(SRC_DIRS)

OUTDIR := release
OBJDIR := $(OUTDIR)/obj
LSTDIR := $(OUTDIR)/lst
EXEDIR := $(OUTDIR)
DEPDIR := $(OUTDIR)/dep
#-----------------------------------------------
#    add surce files directories to search path
vpath
vpath % $(scmRTOS_DIRS)
vpath % $(SRC_DIRS)

OBJS_ARM_ASM  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_ARM_ASM:.S=.o) ))
OBJS_ARM_CPP  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_ARM_CPP:.cpp=.o) ))
OBJS_THUMB_ASM  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_THUMB_ASM:.S=.o) ))
OBJS_THUMB_CPP  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_THUMB_CPP:.cpp=.o) ))
OBJS = $(OBJS_ARM_CPP) $(OBJS_ARM_ASM) $(OBJS_THUMB_CPP) $(OBJS_THUMB_ASM)

# defines
DEFS += -D$(CHIP)=1
CPP_DEFS += $(DEFS)
ASM_DEFS += $(DEFS)
# Flags

FLAGS = -mcpu=$(MCU)
# generate debug info in dwarf-2 format
FLAGS += -g -gdwarf-2
# generate dependency info  
FLAGS += -MD -MP -MF $(DEPDIR)/$(@F).d
# include search path
FLAGS += $(addprefix -I,$(INC_DIRS))

#if any THUMB mode sources, generate interworking code
ifneq ($(strip $(SRC_THUMB_ASM) $(SRC_THUMB_CPP)),)
FLAGS += -mthumb-interwork
endif

ASM_FLAGS = $(FLAGS)
ASM_FLAGS += $(ASM_DEFS)
ASM_FLAGS += -Wa,-amhlds=$(LSTDIR)/$(notdir $(<:.S=.lst)) 

CPP_FLAGS = $(FLAGS)
CPP_FLAGS += $(OPTIMIZE)
CPP_FLAGS += $(CPP_DEFS)
CPP_FLAGS += -fomit-frame-pointer
CPP_FLAGS += -fno-exceptions -fno-rtti
CPP_FLAGS += -Wall -Wextra -Wundef -Wcast-align
CPP_FLAGS += -Wa,-ahlmsdc=$(LSTDIR)/$(notdir $(<:.cpp=.lst)) -fverbose-asm
CPP_FLAGS += -ffunction-sections -fdata-sections    # to remove dead code, if any, at link time
CPP_FLAGS += -Winline                               # generate warning if inlinign fails
CPP_FLAGS += -funsigned-bitfields -fshort-enums	    # actually not important for scmRTOS


LD_FLAGS = -mcpu=$(MCU)
LD_FLAGS += -nostartfiles
LD_FLAGS += -T$(LD_SCRIPT)
LD_FLAGS += -Wl,-Map=$(LSTDIR)/$(PROJECT).map,--cref,--no-warn-mismatch
LD_FLAGS += $(addprefix -L,$(LIB_DIRS))
LD_FLAGS += $(LIBDIR)
LD_FLAGS += -Wl,--gc-sections


#
# makefile rules
#
.SILENT :
.PHONY : all clean
all: directories $(OBJS) $(ELF)  $(LSS) size $(HEX) $(BIN)
#all: directories $(OBJS) $(ELF) $(LSS) size

#all objects depends on makefile
$(OBJS): makefile

$(OBJS_ARM_CPP) : $(OBJDIR)/%.o : %.cpp
	@echo Compiling: $<
	$(CC) -c $(CPP_FLAGS) $< -o $@

$(OBJS_ARM_ASM) : $(OBJDIR)/%.o : %.S
	@echo Assembling: $<
	$(AS) -c $(ASM_FLAGS) $< -o $@

$(OBJS_THUMB_CPP) : $(OBJDIR)/%.o : %.cpp
	@echo Compiling: $<
	$(CC) -c -mthumb $(CPP_FLAGS) $< -o $@

$(OBJS_THUMB_ASM) : $(OBJDIR)/%.o : %.S
	@echo Assembling: $<
	$(AS) -c  -mthumb $(ASM_FLAGS) $< -o $@

$(ELF): $(OBJS) $(LD_SCRIPT)
	@echo Linking: $@
	$(CC) $(OBJS) $(LD_FLAGS) $(LIBS) -o $@

$(LSS): $(ELF)
	$(OBJDUMP) -h -S -C $< > $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

size:
	$(SIZE) -B -t $(ELF)
	$(CC) --version

directories:
	mkdir -p $(EXEDIR) $(OBJDIR) $(DEPDIR) $(LSTDIR)
clean:
	rm -rf $(OUTDIR)

    
# if TOOLSET variable set,
# add TOOLSET bin directory first in PATH    
ifneq ($(strip $(TOOLSET)),)
ifeq (,$(findstring ;,$(PATH)))
  PATH := $(subst :,,/$(TOOLSET)/bin):$(PATH)
else
  PATH := $(subst /,\,$(TOOLSET)/bin);$(PATH)
endif
export PATH
endif

# dependencies inclusion
# if make target list not contain this targets - include dependencies
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
 ifeq (,$(findstring directories,$(MAKECMDGOALS)))
-include $(shell mkdir $(DEPDIR) 2>/dev/null) $(wildcard $(DEPDIR)/*.d)
 endif
endif
