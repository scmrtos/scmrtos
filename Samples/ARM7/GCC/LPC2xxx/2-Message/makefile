#+---------------------------------------------------------------------------
#
#  Copyright (c) 2010 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  File:       makefile
#
#  Contents:   makefile to build lpc2148 ARM software with gcc
#
#----------------------------------------------------------------------------

#############  program name
	TARGET	= 2-Message

	TOOL	= arm-none-eabi-
#	TOOL	= arm-kgp-eabi-

	MCU			= arm7tdmi
	CHIP		= LPC2148
	OPTIMIZE	= -O2

###########################################################
#  common part for all my lpc2148 projects
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
	BAKDIR		= $(BASE)/bak

#files
	HEX		= $(EXEDIR)/$(TARGET).hex
	ELF		= $(EXEDIR)/$(TARGET).elf
	BIN		= $(EXEDIR)/$(TARGET).bin
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

# linker script
	LD_SCRIPT	= $(PRJDIR)/$(CHIP)-ROM.ld

# dirs
    SCMDIR      = ../scmRTOS
    COMMON      = ../SamplesCommon

# files
	DIRS	:= $(SRCDIR)
	DIRS    += $(COMMON)
	DIRS    += $(SCMDIR)/Common $(SCMDIR)/ARM7
    
	INCS	:= $(patsubst %, -I "%", $(DIRS))
	SRCS	:= $(wildcard $(addsuffix /*.cpp, $(DIRS))) $(wildcard $(addsuffix /*.c, $(DIRS))) $(wildcard $(addsuffix /*.S, $(DIRS)))
	OBJS	:= $(notdir $(SRCS) )
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(OBJS:.s=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

#files to archive
    ARCFILES    = \
        $(SRCDIR) \
        $(PRJDIR) \
        $(SCMDIR) \
        $(LIBDIR) \
        $(BASE)/makefile \
        $(BASE)/.cproject \
        $(BASE)/.project

# flags
	FLAGS	= -mcpu=$(MCU) -mthumb-interwork
	FLAGS	+= -g -gdwarf-2
	FLAGS	+= $(INCS)
	FLAGS	+= -MD
	FLAGS	+= -DROM_RUN
	FLAGS	+= -D$(CHIP)
	FLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	AFLAGS	= $(FLAGS)

	CFLAGS	= $(FLAGS)
	CFLAGS	+= $(OPTIMIZE)
	CFLAGS	+= -std=gnu99
	CFLAGS	+= -ffunction-sections -fdata-sections
	CFLAGS	+= -Wall -Wextra
	CFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -Wnested-externs -pedantic

	CXXFLAGS	= $(FLAGS)
	CXXFLAGS	+= $(OPTIMIZE)
	CXXFLAGS	+= -fomit-frame-pointer
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -fno-elide-constructors
	CXXFLAGS	+= -funsigned-bitfields -fshort-enums
	CXXFLAGS	+= -Wall -Wextra
	CXXFLAGS	+= -Winline -finline-limit=40
#	CXXFLAGS	+= -fgraphite
#	CXXFLAGS	+= -funroll-loops 
#	CXXFLAGS	+= -Weffc++ -Wctor-dtor-privacy
	CXXFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith
#	CXXFLAGS	+= -Wredundant-decls
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic

	LD_FLAGS	= -mcpu=$(MCU)
	LD_FLAGS	+= -nostartfiles 
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -fno-exceptions -fno-rtti	
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -T$(LD_SCRIPT)


#openocd command-line

# debug level (d0..d3)
	oocd_params		= -d0
#	oocd_params		+= -c "fast enable"
	oocd_params		+= -f interface/arm-usb-ocd.cfg 
	oocd_params		+= -f $(PRJDIR)/$(CHIP).cfg
	oocd_params		+= -c init 
#	oocd_params		+= -c targets

	oocd_params_program	= $(oocd_params)

	oocd_params_program	+= -c "halt"
#	oocd_params_program	+= -c "sleep 10"
#	oocd_params_program	+= -c "poll"
#	oocd_params_program	+= -c "flash probe 0"

	oocd_params_program	+= -c "flash write_image erase $(ELF)"
	oocd_params_program	+= -c "verify_image $(ELF)"
	oocd_params_program	+= -c "reset run"
	oocd_params_program	+= -c shutdown

	oocd_params_reset	= $(oocd_params)
	oocd_params_reset	+= -c "reset run"
	oocd_params_reset	+= -c shutdown

.SILENT :

.PHONY: all dirs build clean program reset archive

############# targets

all : dirs $(ELF) $(HEX) $(LSS) $(OK)

build: clean all


$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
#	$(OBJDUMP) -dStC $(ELF) > $(LSS)
	$(OBJDUMP) -dC $(ELF) > $(LSS)

$(OK): $(ELF)
	$(SIZE) $(ELF)
	@echo "Errors: none"

$(ELF):	$(OBJS) makefile
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o $(ELF)

$(HEX): $(ELF)
	@echo --- make hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

program: $(ELF)
	@echo "Programming with OPENOCD"
	$(FLASHER) $(oocd_params_program)

oocd: $(ELF)
	@echo "starting openocd"
	START $(FLASHER) $(oocd_params)

reset:
	@echo Resetting device
	$(FLASHER) $(oocd_params_reset)

VPATH := $(DIRS)

$(OBJDIR)/%.o: %.cpp makefile
	@echo --- compiling $<...
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.c makefile
	@echo --- compiling $<...
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.S makefile
	@echo --- assembling $<...
	$(AS) -c $(AFLAGS) -o $@ $<

dirs: $(OBJDIR) $(EXEDIR) $(LSTDIR) $(BAKDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(EXEDIR):
	-@$(MD) $(EXEDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)

$(BAKDIR):
	-@$(MD) $(BAKDIR)

clean:
	-@$(RM) $(OBJDIR)/*.d 2>/dev/null
	-@$(RM) $(OBJDIR)/*.o 2>/dev/null
	-@$(RM) $(LSTDIR)/*.lst 2>/dev/null
	-@$(RM) $(ELF)
	-@$(RM) $(HEX)
	-@$(RM) $(LSS)
	-@$(RM) $(MAP)

archive:
	@echo --- archiving...
	7z a $(BAKDIR)/$(TARGET)_`date +%Y-%m-%d,%H-%M-%S` $(ARCFILES)
	@echo --- done!

ifeq (,$(findstring build,$(MAKECMDGOALS)))
 ifeq (,$(findstring clean,$(MAKECMDGOALS)))
  ifeq (,$(findstring dirs,$(MAKECMDGOALS)))
  -include $(wildcard $(OBJDIR)/*.d) 
  endif
 endif
endif
