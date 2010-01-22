#+---------------------------------------------------------------------------
#
#  Copyright (c) 2009 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  File:       makefile
#
#  Contents:   makefile to build arm Cortex-M3 software with gcc
#
#----------------------------------------------------------------------------

#############  program name
	TARGET	= 1-EventFlag

############# toolset:
	TOOL	= arm-none-eabi-
#	TOOL	= arm-kgp-elf-

	MCU			= cortex-m3
	OPTIMIZE	= -O2

###########################################################
#  common part for all my cortex-m3 projects
###########################################################

	BASE		= .
	CC			= $(TOOL)gcc
	CXX			= $(TOOL)g++
	LD			= $(TOOL)g++
	AS			= $(CC) -x assembler-with-cpp
	OBJCOPY		= $(TOOL)objcopy
	OBJDUMP		= $(TOOL)objdump
	SIZE		= $(TOOL)size -d
	FLASHER		= openocd
	RM			= rm -f
	CP			= cp
	MD			= mkdir


#  dirs
	SRCDIR		= $(BASE)/src
	OBJDIR		= $(BASE)/obj
	EXEDIR		= $(BASE)/exe
	LSTDIR		= $(BASE)/lst
	PRJDIR		= $(BASE)/prj
	SCMDIR		= ../scmRTOS

#files
	HEX		= $(EXEDIR)/$(TARGET).hex
	ELF		= $(EXEDIR)/$(TARGET).elf
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

# linker script
ifeq ($(TOOL), arm-kgp-elf-)
	LD_SCRIPT	= $(PRJDIR)/stm32f10x_flash_md_kgp.ld
else
	LD_SCRIPT	= $(PRJDIR)/stm32f10x_flash_md.ld 
endif

# files
	DIRS	:= $(SRCDIR) $(SCMDIR)/Common $(SCMDIR)/CortexM3
	INCS	:= $(patsubst %, -I "%", $(DIRS))
	SRCS	:= $(wildcard $(addsuffix /*.cpp, $(DIRS))) $(wildcard $(addsuffix /*.c, $(DIRS))) $(wildcard $(addsuffix /*.S, $(DIRS)))
	OBJS	:= $(notdir $(SRCS) )
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

# flags
	FLAGS	= -mcpu=$(MCU) -mthumb
	FLAGS	+= -Wa,-gdwarf-2
	FLAGS	+= $(INCS)
	FLAGS	+= -MD 

	AFLAGS	= $(FLAGS)
	AFLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	CFLAGS	= $(FLAGS)
	CFLAGS	+= $(OPTIMIZE)
	CFLAGS	+= -std=gnu99
	CFLAGS	+= -g
	CFLAGS	+= -ffunction-sections -fdata-sections
	CFLAGS	+= -Wall -Wextra
	CFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -Wnested-externs -pedantic
	CFLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	CXXFLAGS	= $(FLAGS)
	CXXFLAGS	+= $(OPTIMIZE)
	CXXFLAGS	+= -g
	CXXFLAGS	+= -fomit-frame-pointer
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -fno-elide-constructors
	CXXFLAGS	+= -funsigned-bitfields -fshort-enums
	CXXFLAGS	+= -Wall -Wextra
	CXXFLAGS	+= -Winline -finline-limit=40
#	CXXFLAGS	+= -Weffc++ -Wctor-dtor-privacy
	CXXFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic
	CXXFLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	LD_FLAGS	= -mcpu=$(MCU)
	LD_FLAGS	+= -mthumb
	LD_FLAGS	+= -nostartfiles 
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -fno-exceptions -fno-rtti	
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -T$(LD_SCRIPT)


#openocd command-line

# debug level (d0..d3)
	oocd_params		= -d0
# interface and board/target settings (using the OOCD target-library here)
#	oocd_params		+= -c "fast enable"
	oocd_params		+= -f interface/arm-usb-ocd.cfg -f board/stm32f10x_128k_eval.cfg
	oocd_params		+= -c init -c targets
	oocd_params_program	= $(oocd_params)
# commands to prepare flash-write
	oocd_params_program	+= -c "halt"
# flash-write and -verify
	oocd_params_program	+= -c "flash write_image erase $(ELF)" -c "verify_image $(ELF)"
# reset target
	oocd_params_program	+= -c "reset run"
# terminate OOCD after programming
	oocd_params_program	+= -c shutdown

	oocd_params_reset	= $(oocd_params)
	oocd_params_reset	+= -c "reset run"
	oocd_params_reset	+= -c shutdown

.SILENT :

.PHONY: all dirs build clean program reset archive

############# targets

all : dirs $(ELF) $(LSS) $(OK)

build: clean all


$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
#	@$(OBJDUMP) -dStC $(ELF) > $(LSS)
	@$(OBJDUMP) -dC $(ELF) > $(LSS)

$(OK): $(ELF)
	@$(SIZE) $(ELF)
	@echo "Errors: none"

$(ELF):	$(OBJS) makefile
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o "$(ELF)"

program: $(ELF)
	@echo "Programming with OPENOCD"
	$(FLASHER) $(oocd_params_program)

reset:
	@echo Resetting device
	$(FLASHER) $(oocd_params_reset)

VPATH := $(DIRS)

$(OBJDIR)/%.o: %.cpp
	@echo --- compiling $(*F).cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.c
	@echo --- compiling $(*F).c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.S
	@echo --- assembling $(*F).s
	$(AS) -c $(AFLAGS) -o $@ $<

dirs: $(OBJDIR) $(EXEDIR) $(LSTDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(EXEDIR):
	-@$(MD) $(EXEDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)

clean:
	-@$(RM) $(OBJDIR)/*.d 2>nul
	-@$(RM) $(OBJDIR)/*.o 2>nul
	-@$(RM) $(EXEDIR)/*.hex 2>nul
	-@$(RM) $(EXEDIR)/*.bin 2>nul
	-@$(RM) $(EXEDIR)/*.elf 2>nul
	-@$(RM) $(LSTDIR)/*.lst 2>nul
	-@$(RM) $(LSTDIR)/*.lss 2>nul
	-@$(RM) $(LSTDIR)/*.map 2>nul

# dependencies
include $(wildcard $(OBJDIR)/*.d) 
