#+---------------------------------------------------------------------------
#
#  Copyright (c) 2010 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  File:       makefile
#
#  Contents:   makefile to build ADuc7061 ARM software with gcc
#
#----------------------------------------------------------------------------

#############  program name
	TARGET	= 1-EventFlag

	TOOL	= arm-none-eabi-
#	TOOL	= arm-kgp-eabi-

# compile options 
	MCU			= arm7tdmi
	CHIP		= ADUC7061
	OPTIMIZE	= -O2
	USE_LTO		= NO

###########################################################
#  common part for all my ADUC7061 projects
###########################################################

	BASE		= .
	CC			= $(TOOL)gcc
	CXX			= $(TOOL)g++
	LD			= $(TOOL)g++
	AS			= $(CC) -x assembler-with-cpp
	OBJCOPY		= $(TOOL)objcopy
	OBJDUMP		= $(TOOL)objdump
	SIZE		= $(TOOL)size -d
	RAR			= Rar.exe
	RM			= rm -f
	CP			= cp
	MD			= mkdir
	FLASHER		= ARMWSD.exe


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
	LD_SCRIPT	= $(PRJDIR)/ADUC7061-ROM.ld

# scmRTOS dir
	SCMDIR		= ../scmRTOS
	COMMON		= ../SamplesCommon

# files
	DIRS	:= $(SRCDIR)
	DIRS	+= $(COMMON)
	DIRS	+= $(SCMDIR)/Common $(SCMDIR)/ARM7

	INCS	:= $(patsubst %, -I "%", $(DIRS))
	SRCS	:= $(wildcard $(addsuffix /*.cpp, $(DIRS))) $(wildcard $(addsuffix /*.c, $(DIRS))) $(wildcard $(addsuffix /*.S, $(DIRS)))
	OBJS	:= $(notdir $(SRCS) )
	OBJS	:= $(OBJS:.cpp=.o)
	OBJS	:= $(OBJS:.c=.o)
	OBJS	:= $(OBJS:.S=.o)
	OBJS	:= $(OBJS:.s=.o)
	OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

#files to archive
	ARCFILES	= \
		$(SRCDIR) \
		$(PRJDIR) \
		$(SCMDIR) \
		$(LIBDIR) \
		$(BASE)/makefile \
		$(BASE)/.cproject \
		$(BASE)/.project

# flags
	FLAGS	= -mcpu=$(MCU)
#	FLAGS	+= -mthumb-interwork
	FLAGS	+= -g -gdwarf-2
	FLAGS	+= $(INCS)
	FLAGS	+= -MD
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
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -funsigned-bitfields -fshort-enums
	CXXFLAGS	+= -Wall -Wextra
	CXXFLAGS	+= -Winline
	CXXFLAGS	+= -Wcast-align -Wpointer-arith
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic

	LD_FLAGS	= -mcpu=$(MCU)
	LD_FLAGS	+= -nostartfiles 
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref
	LD_FLAGS	+= -fno-exceptions -fno-rtti	
	LD_FLAGS	+= -Wl,--gc-sections
	LD_FLAGS	+= -T$(LD_SCRIPT)

ifeq ($(USE_LTO),YES)
	CFLAGS		+= -flto
	CXXFLAGS	+= -flto
	LD_FLAGS	+= -flto $(OPTIMIZE)
endif

# ARMWSD serial downloader command-line
	FLASHER_INI	:= ARMWSD-$(CHIP).ini

	F_FLAGS		+= af=$(HEX)	# file
	F_FLAGS		+= aa=y			# ?
#	F_FLAGS		+= ap=$(CHIP)	# chip
	F_FLAGS		+= ap=ADuC7061	# chip
	F_FLAGS		+= cp=COM1		# com-port
	F_FLAGS		+= cb=38400		# baudrate (max 38400)
	F_FLAGS		+= fe=n			# mass erase = NO
	F_FLAGS		+= fp=y			# program = YES
	F_FLAGS		+= fv=y			# verify = YES
	F_FLAGS		+= fh=n			# protect = NO

.SILENT :

.PHONY: all dirs build clean program reset archive info

############# targets

all : dirs $(ELF) $(HEX) $(LSS) $(OK)

build: clean all


$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
	$(OBJDUMP) -dC $(ELF) > $(LSS)

info:
	$(CC) -E -P -v -dD $(CFLAGS) ./src/sys.c

$(OK): $(ELF)
	$(SIZE) $(ELF)
	@echo "Errors: none"

$(ELF):	$(OBJS) makefile
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o $(ELF)

$(HEX): $(ELF)
	@echo --- make hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)
#	$(OBJCOPY) -O binary $(ELF) $(BIN)

program: $(HEX)
	@echo "Programming..."
	$(FLASHER) $(F_FLAGS)

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
