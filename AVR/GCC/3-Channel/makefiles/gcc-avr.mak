#-----------------------------------------------------------------------
# ReAl common makefile for avr-gcc
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#
#  This makefile add avr-gcc directory at start of PATH for easy changing
#  of avr-gcc version by changing (or overriding in project makefile)
#  only one variable AVRGCC.
#
#  avr-gcc.mak assume that directories organised as
#
#  proj/obj -.
#  proj/lst -+- working and output directories
#  proj/exe -'
#  proj/src - sources base directory
#
# Externally defined variables:
#
#  AVRGCC = Path to avr-gcc base directory (can contain spaces,
#       '/' must be used instead of '\', no slash at the end).
#
#  MCU = Target processor name
#  TRG = Target name (project name)
#  LIB = Additional libraries
#  CFLAGS  = C  project-dependent flags
#  ASFLAGS = AS project-dependent flags
#  LDFLAGS = LD project-dependent flags
#
#  PROJ_SRCTOP = Base directory of source files subtree. Must point to
#       proj/src and can be relative from makefile location.
#       For example, when main project makefile located at
#       proj/src/proj_main/  you can set PROJ_SRCTOP=..
#       For "simple" project with all sources and makefile placed to
#       proj/src you can set PROJ_SRCTOP=.
#
#  MODULES = Space separated source directories list (from PROJ_SRCTOP point)
#       All .c and .S files in this directories will be compiled and linked.
#

# do not print any commands
.SILENT :

#-----------------------------------------------------------------------
#   Prepare and export PATH
#
# Add WinAVR compiler directory and, if needed, utilites directory
# at start of PATH.
#
# AVRGCC variable can contain spaces, '/' must be used instead of '\',
#       no slash at the end.
#
# WinAVR distribution make.exe starts with PATH in windows-style ( c:\directory ).
# Shell and all utilites must be called from WinAVR\utils\bin directory for compatibility.
#
# MSYS (Minimal SYStem) make.exe starts with PATH converted to unix-like style  ( /c/directory ).
# If MSYS available in system and stay first in the PATH then we can use
# sh.exe and all utilites from MSYS distribution.
#
# We need different PATH processing for this two options.

ifeq (,$(findstring ;,$(PATH)))
  #  msys make
  GCCPATH := $(subst :,,/$(AVRGCC))
  PATH := $(GCCPATH)/bin:$(PATH)
else
  #  WinAVR make
  GCCPATH := $(subst /,\,$(AVRGCC))
  PATH := $(GCCPATH)\\bin;$(GCCPATH)\\utils\\bin;$(PATH)
endif

export PATH


#-----------------------------------------------------------------------
#
CC	:= avr-gcc
AS	:= avr-gcc -x assembler-with-cpp
OBJTOOL := objtool
BIN	:= avr-objcopy
OBJCOPY := avr-objcopy
OBJDUMP := avr-objdump
SIZE	:= avr-size

ELFSIZE = $(SIZE) --format=avr --mcu=$(MCU)
#ELFSIZE = $(SIZE) -A


#-----------------------------------------------------------------------
#
OBJDIR := ./obj
LSTDIR := ./lst
EXEDIR := ./exe

SRCDIRS := $(MODULES)
INCDIRS := $(SRCDIRS)

CSRC	:= $(wildcard $(addsuffix /*.c,$(SRCDIRS)))
CPPSRC	:= $(wildcard $(addsuffix /*.cpp,$(SRCDIRS)))
ASRC    := $(wildcard $(addsuffix /*.S,$(SRCDIRS)))
BAK      = $(wildcard $(addsuffix /*.*~*,$(SRCDIRS)))
OBJ	:= $(addprefix $(OBJDIR)/,$(notdir $(CSRC:.c=.o) $(CPPSRC:.cpp=.o) $(ASRC:.S=.o) ))
LST	:= $(addprefix $(LSTDIR)/,$(notdir $(CSRC:.c=.lst) $(CPSRC:.cpp=.o) $(ASRC:.S=.lst) ))


TRGELF := $(EXEDIR)/$(TRG).elf
TRGPGM := $(addprefix $(EXEDIR)/$(TRG).,$(TRGPGMEXT))
TRGCOF := $(EXEDIR)/$(TRG).cof

#GENDEPFLAGS = -Wp,-MM,-MP,-MT,$(OBJDIR)/$(*F).o,-MF,$(OBJDIR)/$(@F).d
GENDEPFLAGS = -Wp,-MM,-MP,-MT,$@,-MF,$(@:.o=.d)
CFLAGS  += -mmcu=$(MCU) $(GENDEPFLAGS)
ASFLAGS += -mmcu=$(MCU) # $(GENDEPFLAGS)
LDFLAGS += -mmcu=$(MCU) -Wl,-Map=$(LSTDIR)/$(TRG).map,--cref

# search path for common sources and headers
vpath
vpath %.c $(SRCDIRS)
vpath %.cpp $(SRCDIRS)
vpath %.h $(SRCDIRS)
vpath %.S $(SRCDIRS)

#-----------------------------------------------------------------------
# targets of makefile
#
.PHONY : all debug printok depends

# default target - binaries for AVR programming
all:	begin $(TRGPGM) printok

begin:
	echo ======== Beginning of project  "$(TRG)"  processing ; $(CC) --version ;\
	mkdir -p $(OBJDIR) $(EXEDIR) $(LSTDIR)

#	which mkdir.exe ; which avr-gcc.exe ;\

printok:  $(TRGELF)
	echo ======== All OK,  project size: ; $(ELFSIZE) $<

#-----------------------------------------------------------------------
# compilation rules
#
$(OBJDIR)/%.o : %.c
	echo ====  Compiling $< ; \
	$(CC) -c $(CFLAGS) $(addprefix -I,$(INCDIRS)) \
	-Wa,-ahlmsd=$(LSTDIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(OBJDIR)/%.o : %.cpp
	echo ====  Compiling $< ; \
	$(CC) -c $(CFLAGS) $(addprefix -I,$(INCDIRS)) \
	-Wa,-ahlmsd=$(LSTDIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(OBJDIR)/%.o : %.S
	echo ====  Compiling $< ; \
	$(AS) -E $(ASFLAGS) $(addprefix -I,$(INCDIRS)) $(GENDEPFLAGS) $< ; \
	$(AS) -c $(ASFLAGS) $(addprefix -I,$(INCDIRS)) \
	-Wa,-alm=$(LSTDIR)/$(notdir $(<:.S=.lst)) $< -o $@

%.s : %.c
	echo ====  Generate assembly source from $< ; \
	$(CC) -S $(CFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.c=.s)

%.s : %.cpp
	echo ====  Generate assembly source from $< ; \
	$(CC) -S $(CFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.cpp=.s)

%.E : %.c # preprocess only
	echo ====  Generate PREPROCESSED file from $< ; \
	$(CC) -E $(CFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.c=.E)

#-----------------------------------------------------------------------
# elf post-processing rules
#

# hex-files for programmer
%.hex: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O ihex -R .eeprom $< $@

%.eep: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 $< $@

# files for simulator
%.obj: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O avrobj -R .eeprom $< $@

%.cof: %.elf
	echo ====  extract $(notdir $@) ; \
	$(OBJTOOL) loadelf $< mapfile $*.map writecof $@

#	$(OBJCOPY) --debugging \
#	--change-section-address .data-0x800000 \
#	--change-section-address .bss-0x800000 \
#	--change-section-address .noinit-0x800000 \
#	--change-section-address .eeprom-0x810000  \
#	-O coff-avr $< $@


# "dizassemble" elf file
dump: $(TRGELF)
	echo ====  disassemble $(notdir $<) ; \
	$(OBJDUMP) -d -S -C $< >$(LSTDIR)/$(TRG).dump

#-----------------------------------------------------------------------
# link: instructions to create elf output file from object files
#
.SECONDARY : $(TRG).elf
.PRECIOUS : $(OBJ)
$(TRGELF) : $(OBJ)
	echo ====  Link to $(notdir $@) ;\
	$(CC) $^ $(LIB) $(LDFLAGS) -o $@

#-----------------------------------------------------------------------
#  dependencies

# all obj files depend on makefile because of makefile contain
#  some compiler's switches (optimisation, debug options, etc..)
$(OBJ) : makefile

# dependencies inclusion
# if make target list not contain this targets - include dependencies
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
 ifeq (,$(findstring cleanall,$(MAKECMDGOALS)))
  ifeq (,$(findstring directories,$(MAKECMDGOALS)))
-include $(shell mkdir $(OBJDIR) 2>/dev/null) $(wildcard $(OBJDIR)/*.d)
  endif
 endif
endif

#-----------------------------------------------------------------------
#  create temporary and ouptut directories
#
.PHONY : directories
directories:
	echo ====  Create working directories ;\
	mkdir -p $(OBJDIR) $(LSTDIR) $(EXEDIR)

.PHONY : dummy
dummy:

#-----------------------------------------------------------------------
# clean project directories from working & backup ('~' suffix) files
#
.PHONY : clean cleanall
clean:
	echo ====  Erasing working directories and indent/editor backup files; \
	rm -f $(TRGCOF) $(EXEDIR)/$(TRG).obj $(EXEDIR)/$(TRG).sym ; \
	rm -f $(TRGELF) ; \
	rm -f $(LSTDIR)/* ; \
	rm -f $(OBJDIR)/* ; \
	rm -f $(CSRC:.c=.s) ; \
	rm -f $(BAK)

cleanall: clean
	echo ====  Remove target binaries and working directories ; \
	rm -f $(TRGPGM) ; \
	test -e $(EXEDIR) && rmdir $(EXEDIR) ; \
	test -e $(LSTDIR) && rmdir $(LSTDIR) ; \
	test -e $(OBJDIR) && rmdir $(OBJDIR)


#####	end of avr.make
