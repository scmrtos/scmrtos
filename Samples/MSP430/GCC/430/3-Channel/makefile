#+---------------------------------------------------------------------------
#
#  Copyright (c) 2011 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  File:       makefile
#
#  Contents:   makefile to build software with msp-gcc and gnu make
#
#----------------------------------------------------------------------------

#############  program name
	TARGET	= 3-Channel

	TOOL	= msp430-

	MCU			= msp430x149
	OPTIMIZE	= -Os
	USE_GC		= NO

###########################################################
#  common part for all my msp-gcc projects
###########################################################

	BASE		= .
	CC			= $(TOOL)gcc
	CXX			= $(TOOL)g++
	LD			= $(TOOL)gcc
	AS			= $(CC) -x assembler-with-cpp
	OBJCOPY		= $(TOOL)objcopy
	OBJDUMP		= $(TOOL)objdump
	SIZE		= $(TOOL)size -d
	JTAG		= $(TOOL)jtag
	RM			= rm -f
	CP			= cp
	MD			= mkdir


#  dirs
	SRCDIR		= $(BASE)/src
	OBJDIR		= $(BASE)/obj
	EXEDIR		= $(BASE)/exe
	LSTDIR		= $(BASE)/lst
	BAKDIR		= $(BASE)/bak

#files
	HEX		= $(EXEDIR)/$(TARGET).hex
	ELF		= $(EXEDIR)/$(TARGET).elf
	MAP		= $(LSTDIR)/$(TARGET).map
	LSS		= $(LSTDIR)/$(TARGET).lss
	OK		= $(EXEDIR)/$(TARGET).ok

# scmRTOS dir
	SCMDIR		= ../scmRTOS

# files
	DIRS	:= $(SRCDIR)
	DIRS	+= $(SCMDIR)/Common $(SCMDIR)/MSP430
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
		$(DIRS) \
		$(PRJDIR) \
		$(BASE)/makefile \
		$(BASE)/.cproject \
		$(BASE)/.project

# flags
	FLAGS	= -mmcu=$(MCU)
	FLAGS	+= $(INCS)
	FLAGS	+= -MD 
	FLAGS	+= -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

	AFLAGS	= $(FLAGS)

	CFLAGS	= $(FLAGS)
	CFLAGS	+= $(OPTIMIZE)
	CFLAGS	+= -std=gnu99
	CFLAGS	+= -g
	CFLAGS	+= -funsigned-char
	CFLAGS	+= -Wall
	CFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -Wnested-externs -pedantic

	CXXFLAGS	= $(FLAGS)
	CXXFLAGS	+= $(OPTIMIZE)
	CXXFLAGS	+= -g
	CXXFLAGS	+= -fno-exceptions -fno-rtti
	CXXFLAGS	+= -funsigned-char
	CXXFLAGS	+= -Wall
	CXXFLAGS	+= -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
	CXXFLAGS	+= -Wshadow -Wcast-qual -Wcast-align -pedantic

	LD_FLAGS	= -mmcu=$(MCU)
	LD_FLAGS	+= -Wl,-Map="$(MAP)",--cref

ifeq ($(USE_GC),YES)
	CFLAGS		+= -ffunction-sections -fdata-sections
	CXXFLAGS	+= -ffunction-sections -fdata-sections
	LD_FLAGS	+= -Wl,--gc-sections
endif


.SILENT :

.PHONY: all dirs build clean program reset archive

############# targets

all : dirs $(ELF) $(HEX) $(LSS) $(OK)

build: clean all


$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
	@$(OBJDUMP) -dtC $(ELF) > $(LSS)

$(OK): $(ELF)
	@$(SIZE) $(ELF)
	@echo "Errors: none"

$(ELF):	$(OBJS) makefile
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o "$(ELF)"

$(HEX):	$(ELF) makefile
	@echo --- making hex...
	@$(OBJCOPY) -O ihex $(ELF) $(HEX)

program: $(ELF)
	@echo --- programming...
	@$(JTAG) -e $(ELF)

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
	7z a -r $(BAKDIR)/$(TARGET)_`date +%Y-%m-%d,%H-%M-%S` $(ARCFILES)
	@echo --- done!

ifeq (,$(findstring build,$(MAKECMDGOALS)))
 ifeq (,$(findstring clean,$(MAKECMDGOALS)))
  ifeq (,$(findstring dirs,$(MAKECMDGOALS)))
  -include $(wildcard $(OBJDIR)/*.d) 
  endif
 endif
endif
