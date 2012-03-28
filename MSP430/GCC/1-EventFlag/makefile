#+---------------------------------------------------------------------------
#
#  Copyright (c) AHTOXA
#
#  File:       makefile
#
#  Contents:   makefile to build software with msp-gcc and gnu make
#
#----------------------------------------------------------------------------

program_name	:= scmrtos-1-EventFlag

cpu             := msp430x149

base		:= .
obj_dir		:= $(base)/obj
exe_dir		:= $(base)/exe
lst_dir		:= $(base)/lst
bak_dir		:= $(base)/bak
cfg_dir		:= $(base)/cfg

source_dirs  := ./src ../scmRTOS/Common ../scmRTOS/MSP430
include_dirs := $(patsubst %, -I "%", $(source_dirs))
source_files := $(wildcard $(addsuffix /*.cpp, $(source_dirs)))
asource_files := $(wildcard $(addsuffix /*.S, $(source_dirs)))
obj_files	 := $(notdir $(source_files) )
aobj_files	 := $(notdir $(asource_files) )
obj_files	 := $(aobj_files:.S=.o) $(obj_files:.cpp=.o)
obj_files	 := $(patsubst %, $(obj_dir)/%, $(obj_files))


CC			:= msp430-gcc
CXX			:= msp430-c++
AS			:= msp430-gcc -x assembler-with-cpp
OBJCOPY		:= msp430-objcopy
OBJDUMP		:= msp430-objdump
JTAG		:= msp430-jtag
SIZE		:= msp430-size
GDB			:= msp430-gdb
LD			:= $(CC)
RM			:= rm -f
archiver	:= Rar.exe
cp			:= cp -p


hexfile		:= $(exe_dir)/$(program_name).a43
elffile		:= $(exe_dir)/$(program_name).elf
lstfile		:= $(lst_dir)/$(program_name).lst
mapfile		:= $(lst_dir)/$(program_name).map
okfile		:= $(exe_dir)/$(program_name).ok

cflags		:= -c -mmcu=$(cpu) $(include_dirs) -MD -funsigned-char -fno-exceptions -fno-rtti -O2 -Wall -Wno-reorder -g
aflags		:= -c -mmcu=$(cpu) $(include_dirs) -MD -O2 -Wall -g -D_GNU_ASSEMBLER_ 
aflags		+= -DL_reset_vector__ -DL_ctors 
ldflags		:= -mmcu=$(cpu) -Wl,-Map=$(mapfile),--cref


rars	=\
	src\*.S src\*.inc  src\*.c src\*.h $(base)\makefile $(base)\*.mpj

.PHONY: all clean program

all: $(elffile) $(hexfile) $(lstfile) $(okfile)

build: clean all

#additional rules for files
$(elffile): $(obj_files)
	@echo --- linking...
	@$(CC) $(ldflags) -o $@ $(obj_files)

$(hexfile): $(elffile)
	@echo --- making hex...
	@$(OBJCOPY) -O ihex $(elffile) $(hexfile)

$(lstfile): $(elffile)
	@echo --- generating listing...
	@$(OBJDUMP) -dStC $(elffile) >$(lstfile)

$(okfile): $(elffile)
	@$(SIZE) $(elffile)
	@echo "Errors: none" 

VPATH := $(source_dirs)

$(obj_dir)/%.o: %.cpp
	@echo --- compiling $<...
	@$(CXX) $(cflags) -o $@ $<

$(obj_dir)/%.o: %.S
	@echo --- assembling $<...
	@$(CC) $(aflags) -o $@ $<

program: all
	@$(JTAG) -e $(elffile)

debug: all
	@$(GDB) $(elffile)

clean:
	-@$(RM) $(elffile) $(hexfile) $(lstfile) $(obj_files) $(mapfile) $(wildcard $(obj_dir)/*.d) 2>nul

archive:
	@echo --- archiving...
	@$(archiver) a -r -inul -agyy-mm-dd,hh-nn-ss $(bak_dir)\$(program_name)_.rar $(rars)
	@echo --- done!

# dependencies
include $(wildcard $(obj_dir)/*.d) 
