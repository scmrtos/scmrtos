#+---------------------------------------------------------------------------
#
#  Copyright (c) 2012 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  File:       makefile
#
#  Contents:   makefile to build arm Cortex-M3 software with gcc
#
#----------------------------------------------------------------------------

# program name
	TARGET	= 3-Channel

	TOOL	= arm-none-eabi-
#	TOOL	= LC_MESSAGES=C arm-kgp-eabi-

# program version
    VER_MAJOR   = 0
    VER_MINOR   = 1

# compile options
	OPTIMIZE		= -O3
	USE_LTO			= NO

# Select chip: 
# STM32F10X_LD    : STM32 Low density devices
# STM32F10X_LD_VL : STM32 Low density Value Line devices
# STM32F10X_MD    : STM32 Medium density devices
# STM32F10X_MD_VL : STM32 Medium density Value Line devices
# STM32F10X_HD    : STM32 High density devices
# STM32F10X_HD_VL : STM32 XL-density devices
# STM32F10X_CL    : STM32 Connectivity line devices
# STM32F10X_XL    : STM32 XL-density devices
# STM32F2XX       : STM32F2XX devices
# STM32F4XX       : STM32F4XX devices
	CHIP		= STM32F4XX
	HSE_VALUE	= 8000000

ifeq ($(CHIP),STM32F4XX)
	MCU			= cortex-m4
	FPU			= -mfpu=fpv4-sp-d16 -mfloat-abi=hard
else
	MCU			= cortex-m3
endif

# compiler defines
    DEFS        = -D$(CHIP)
    DEFS        += -DVER_MAJOR=$(VER_MAJOR)
    DEFS        += -DVER_MINOR=$(VER_MINOR)
    DEFS        += -DHSE_VALUE=$(HSE_VALUE)

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
#	FLASHER		= openocd
#	FLASHER		= stm32flash
ifeq ($(OS),Windows_NT)
	FLASHER		= ST-LINK_CLI
else
	FLASHER		= st-flash
endif
	DOXYGEN		= doxygen
	RM			= rm -f
	CP			= cp
	MD			= mkdir


# dirs
	SRCDIR		= $(BASE)/src
	OBJDIR		= $(BASE)/obj
	EXEDIR		= $(BASE)/exe
	LSTDIR		= $(BASE)/lst
	PRJDIR		= $(BASE)/prj
	BAKDIR		= $(BASE)/bak

# files
	HEX		= $(EXEDIR)/$(TARGET).hex
	BIN		= $(EXEDIR)/$(TARGET).bin
	ELF		= $(EXEDIR)/$(TARGET).elf
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

# linker script (chip dependent)
	LD_SCRIPT	= $(PRJDIR)/$(CHIP).ld

# scmRTOS dir
	SCMDIR		= ../scmRTOS
# lib dir
	COMMON		= ../SamplesCommon
 

# source directories (all *.c, *.cpp and *.S files included)
	DIRS	:= $(SRCDIR)
	DIRS	+= $(COMMON)
	DIRS	+= $(SCMDIR)/Common $(SCMDIR)/CortexM4F
	DIRS	+= $(SCMDIR)/Extensions
# includes
	INCS	:= $(patsubst %, -I "%", $(DIRS))

# individual source files
	SRCS	:= 

#calc obj files list
	OBJS	:= $(SRCS)
	OBJS	+= $(wildcard $(addsuffix /*.cpp, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.c, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.S, $(DIRS)))
	OBJS	:= $(notdir $(OBJS))
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

#files to archive
	ARCFILES	= \
		$(SRCDIR) \
		$(PRJDIR) \
		$(SCMDIR) \
		$(COMMON) \
		$(BASE)/makefile \
		$(BASE)/.cproject \
		$(BASE)/.project

# flags
	FLAGS	= -mcpu=$(MCU) -mthumb
	FLAGS	+= $(FPU)
	FLAGS	+= $(INCS)
	FLAGS	+= $(DEFS)
	FLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	AFLAGS	= $(FLAGS)

	CFLAGS	= $(FLAGS)
	CFLAGS	+= $(OPTIMIZE)
	ifneq (,$(filter-out discovery defines,$(MAKECMDGOALS)))
	CFLAGS	+= -MD 
    endif
	CFLAGS	+= -std=gnu99
	CFLAGS	+= -g
	CFLAGS	+= -pipe
	CFLAGS	+= -ffunction-sections -fdata-sections
	CFLAGS	+= -Wall -Wextra
	CFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CFLAGS	+= -Wshadow -Wcast-qual -Wnested-externs -pedantic

	CXXFLAGS	= $(FLAGS)
	CXXFLAGS	+= $(OPTIMIZE)
    ifeq (,$(findstring discovery,$(MAKECMDGOALS)))
	CXXFLAGS	+= -MD 
    endif
	CXXFLAGS	+= -g
	CXXFLAGS	+= -pipe
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -funsigned-bitfields -fshort-enums
	CXXFLAGS	+= -Wall -Wextra
	CXXFLAGS	+= -Winline
	CXXFLAGS	+= -Wpointer-arith -Wredundant-decls
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic

	LD_FLAGS	= -mcpu=$(MCU)
	LD_FLAGS	+= -mthumb
	LD_FLAGS	+= $(FPU)
	LD_FLAGS	+= -nostartfiles 
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -T$(LD_SCRIPT)

ifeq ($(USE_LTO),YES)
	CFLAGS		+= -flto
	CXXFLAGS	+= -flto
	LD_FLAGS	+= -flto $(OPTIMIZE)
endif

#openocd command-line

# debug level (d0..d3)
	OPENOCD_PARAMS		= -d0

# interface and board/target settings (using the OOCD target-library here)
	OPENOCD_PARAMS		+= -f board/stm32f4discovery.cfg
	OPENOCD_PARAMS		+= -c init
	OPENOCD_PARAMS		+= -c "sleep 200"

# commands to flash-write
	OPENOCD_PARAMS_LOAD	= $(OPENOCD_PARAMS)
	OPENOCD_PARAMS_LOAD	+= -c "reset halt"
	OPENOCD_PARAMS_LOAD	+= -c "wait_halt"
	OPENOCD_PARAMS_LOAD	+= -c "sleep 200"
	OPENOCD_PARAMS_LOAD	+= -c "flash write_image erase $(ELF)"
	OPENOCD_PARAMS_LOAD	+= -c "verify_image $(ELF)"
	OPENOCD_PARAMS_LOAD	+= -c "reset run"
	OPENOCD_PARAMS_LOAD	+= -c shutdown

# commands to just reset target
	OPENOCD_PARAMS_RESET	= $(OPENOCD_PARAMS)
	OPENOCD_PARAMS_RESET	+= -c "reset run"
	OPENOCD_PARAMS_RESET	+= -c shutdown


.SILENT :

.PHONY: all dirs build clean program reset archive docs discovery

############# targets

all : 
	@echo --- building $(TARGET). defines: $(DEFS)
	$(MAKE) dirs
	$(MAKE) $(ELF)
	$(MAKE) $(HEX)
	$(MAKE) $(LSS)
	$(SIZE) $(ELF)
	@echo "Errors: none"

build:
	$(MAKE) clean
	$(MAKE) all

$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
#	@$(OBJDUMP) -dStC $(ELF) > $(LSS)
	$(OBJDUMP) -dC $(ELF) > $(LSS)

$(ELF):	$(OBJS) $(LIBS) makefile
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o "$(ELF)"

$(HEX): $(ELF) makefile
	@echo --- make hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)

$(BIN): $(ELF) makefile
	@echo --- make bin...
	$(OBJCOPY) -O binary $(ELF) $(BIN)

program: $(HEX) $(BIN)
	@echo "Programming with $(FLASHER)"
ifeq ($(FLASHER),openocd)
	$(FLASHER) $(OPENOCD_PARAMS_LOAD)
endif
ifeq ($(FLASHER),st-flash)
	$(FLASHER) write $(BIN) 0x08000000
endif
ifeq ($(FLASHER),stm32flash)
	$(FLASHER) -b 115200 -w $(HEX) -v -g 0x0 /dev/ttyS0
#	$(FLASHER) -b 115200 -w $(HEX) -v -g 0x0 COM1
endif
ifeq ($(FLASHER),ST-LINK_CLI)
	$(FLASHER) -Q -P $(HEX) -V $(HEX) -Run
endif

reset:
	@echo Resetting device
ifeq ($(FLASHER),ST-LINK_CLI)
	$(FLASHER) -Q -Rst
endif
ifeq ($(FLASHER),openocd)
	$(FLASHER) $(OPENOCD_PARAMS_RESET)
endif

docs:
	@echo Creating doxygen docs...
	$(DOXYGEN) $(PRJDIR)/Doxyfile

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

#discovery target for Eclipse parser
discovery:
	$(CC) $(INCS) $(CFLAGS) -E -P -v -dD '$(specs_file)'
	
defines:
	$(CC) $(CFLAGS) -dM -E - < /dev/null | sort

#do not include dependency info on some targets:
ifneq (,$(filter-out docs build clean dirs discovery,$(MAKECMDGOALS)))
   -include $(wildcard $(OBJDIR)/*.d) 
endif
