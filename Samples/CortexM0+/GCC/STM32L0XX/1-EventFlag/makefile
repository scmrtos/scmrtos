#+---------------------------------------------------------------------------
#
#  Copyright (c) 2015 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  File:       makefile
#
#  Contents:   makefile to build arm Cortex-M0+ software with gcc
#
#----------------------------------------------------------------------------

# program name
	TARGET	= 1-EventFlag

# toolchain
	TOOL	= arm-none-eabi-

# program version
	VER_MAJOR	= 0
	VER_MINOR	= 1

# compile options
	OPTIMIZE        = -O2
	USE_LTO         = NO
	USE_CPP11       = YES
	USE_NANO_LIB    = YES

# Select chip: 
#	STM32L051xx
#	STM32L052xx
#	STM32L053xx
#	STM32L062xx
#	STM32L063xx
#	STM32L061xx

	CHIP		= STM32L053xx
	HSE_VALUE	= 8000000
	USE_HSE		= NO

# compiler defines
	DEFS		= -D$(CHIP)
	DEFS		+= -DVER_MAJOR=$(VER_MAJOR)
	DEFS		+= -DVER_MINOR=$(VER_MINOR)
	DEFS		+= -DHSE_VALUE=$(HSE_VALUE)
	
ifeq ($(USE_HSE),YES)
	DEFS		+= -DUSE_HSE_CLOCK
endif

	MCU			= cortex-m0plus

############# common part for all my cortex-m projects #############
	BASE		= .
	CC			= $(TOOL)gcc
	CXX			= $(TOOL)g++
	LD			= $(TOOL)g++
	AS			= $(CC) -x assembler-with-cpp
	OBJCOPY		= $(TOOL)objcopy
	OBJDUMP		= $(TOOL)objdump
	SIZE		= $(TOOL)size -d
ifeq ($(OS),Windows_NT)
	FLASHER		= ST-LINK_CLI
else
#	FLASHER		= st-flash
	FLASHER		= mbed
endif
	RM			= rm -f
	CP			= cp
	MD			= mkdir


# dirs
	SRCDIR		= $(BASE)/src
	OBJDIR		= $(BASE)/obj
	EXEDIR		= $(BASE)/exe
	LSTDIR		= $(BASE)/lst
	PRJDIR		= $(BASE)/prj
	LD_SCRIPTS	= $(PRJDIR)

# files
	HEX		= $(EXEDIR)/$(TARGET).hex
	BIN		= $(EXEDIR)/$(TARGET).bin
	ELF		= $(EXEDIR)/$(TARGET).elf
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

# linker script (chip dependent)
	LD_SCRIPT	= $(CHIP).ld

# scmRTOS dir
	SCMDIR		= ../scmRTOS
# lib dir
	LIBDIR		= ../SamplesCommon


# source directories (all *.c, *.cpp and *.S files from this dirs are included in build)
	DIRS	:= $(SRCDIR)
	DIRS	+= $(LIBDIR)
	DIRS	+= $(LIBDIR)/CMSIS
	DIRS	+= $(SCMDIR)/Common $(SCMDIR)/CortexMx
	DIRS	+= $(SCMDIR)/Extensions

# includes
	INCS	:= $(patsubst %, -I "%", $(DIRS))

# individual source files
	SRCS	:= 

# generate list of obj files 
	OBJS	:= $(SRCS)
	OBJS	+= $(wildcard $(addsuffix /*.cpp, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.c, $(DIRS)))
	OBJS	+= $(wildcard $(addsuffix /*.S, $(DIRS)))
	OBJS	:= $(notdir $(OBJS))
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

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
ifneq (,$(filter-out discovery defines,$(MAKECMDGOALS)))
	CXXFLAGS	+= -MD 
endif
ifeq ($(USE_CPP11),YES)
	CXXFLAGS	+= -std=c++11
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
ifeq ($(USE_NANO_LIB),YES)
	LD_FLAGS	+= --specs=nano.specs
#	LD_FLAGS	+= -u _printf_float  
endif
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -L$(LD_SCRIPTS)
	LD_FLAGS	+= -T$(LD_SCRIPT)

ifeq ($(USE_LTO),YES)
	CFLAGS		+= -flto
	CXXFLAGS	+= -flto
	LD_FLAGS	+= -flto $(OPTIMIZE)
endif

.SILENT :

.PHONY: all dirs build clean program protect reset archive discovery defines

############# targets

all : 
	@echo --- building $(TARGET). defines: $(DEFS)
	$(MAKE) dirs
	$(MAKE) $(ELF)
	$(MAKE) $(HEX)
	$(MAKE) $(BIN)
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
	$(LD) $(OBJS) $(LIBS) $(LD_FLAGS) -o "$(ELF)"

$(HEX): $(ELF) makefile
	@echo --- make hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)

$(BIN): $(ELF) makefile
	@echo --- make bin...
	$(OBJCOPY) -O binary $(ELF) $(BIN)

program: $(HEX) $(BIN)
	@echo "Programming with $(FLASHER)"
ifeq ($(FLASHER),st-flash)
	$(FLASHER) write $(BIN) 0x08000000
endif
ifeq ($(FLASHER),mbed)
	$(CP) $(BIN) /media/NUCLEO/
endif
ifeq ($(FLASHER),ST-LINK_CLI)
	$(FLASHER)  -c SWD UR -Q -P $(HEX) -V "while_programming" -Run
endif

protect:
ifeq ($(FLASHER),ST-LINK_CLI)
	$(FLASHER)  -c SWD UR -Q -P $(HEX) -V $(HEX) -OB RDP=1
endif

reset:
	@echo Resetting device
ifeq ($(FLASHER),ST-LINK_CLI)
	$(FLASHER) -Q -Rst
endif

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

dirs: $(OBJDIR) $(EXEDIR) $(LSTDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(EXEDIR):
	-@$(MD) $(EXEDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)

clean:
	-@$(RM) $(OBJDIR)/*.d 2>/dev/null
	-@$(RM) $(OBJDIR)/*.o 2>/dev/null
	-@$(RM) $(LSTDIR)/*.lst 2>/dev/null
	-@$(RM) $(ELF)
	-@$(RM) $(HEX)
	-@$(RM) $(LSS)
	-@$(RM) $(MAP)

#discovery target for Eclipse parser.
discovery:
ifeq ($(extension),c)
	@echo -- discovery for $(CC)
	$(CC) $(INCS) $(CFLAGS) -E -P -v -dD '$(specs_file)'
else
	@echo -- discovery for $(CCX)
	$(CXX) $(INCS) $(CXXFLAGS) -E -P -v -dD '$(specs_file)'
endif
	$(RM) spec.d
	
defines:
	$(CC) $(CFLAGS) -dM -E - < /dev/null | sort

#do not include dependency info on some targets:
ifneq (,$(filter-out build clean dirs discovery,$(MAKECMDGOALS)))
  -include $(wildcard $(OBJDIR)/*.d) 
endif
