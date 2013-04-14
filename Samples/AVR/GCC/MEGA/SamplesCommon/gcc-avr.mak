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

# Set default toolchain prefix if it does not defind in environment or project makefile
TOOL ?= avr-

# Set tool names
CC	:= $(TOOL)gcc
AS	:= $(TOOL)gcc -x assembler-with-cpp
BIN	:= $(TOOL)objcopy
OBJCOPY := $(TOOL)objcopy
OBJDUMP := $(TOOL)objdump
SIZE	:= $(TOOL)size

#ELFSIZE := $(SIZE) --format=avr --mcu=$(MCU)
ELFSIZE := $(SIZE) -A


#-----------------------------------------------------------------------
#
OBJDIR := ./obj
LSTDIR := ./lst
EXEDIR := ./exe

SRCDIRS := $(MODULES)
INCDIRS := $(SRCDIRS)

CSRC	:= $(wildcard $(addsuffix /*.c,$(SRCDIRS)))
CXXSRC	:= $(wildcard $(addsuffix /*.cpp,$(SRCDIRS)))
ASRC    := $(wildcard $(addsuffix /*.S,$(SRCDIRS)))
BAK     := $(wildcard $(addsuffix /*.*~*,$(SRCDIRS)))
OBJ	:= $(addprefix $(OBJDIR)/,$(notdir $(CSRC:.c=.o) $(CXXSRC:.cpp=.o) $(ASRC:.S=.o) ))
LST	:= $(addprefix $(LSTDIR)/,$(notdir $(CSRC:.c=.lst) $(CXXSRC:.cpp=.o) $(ASRC:.S=.lst) ))

ifndef TRGPGMEXT
TRGPGMEXT = hex eep
endif

TRGELF := $(EXEDIR)/$(TRG).elf
TRGPGM := $(addprefix $(EXEDIR)/$(TRG).,$(TRGPGMEXT))
TRGCOF := $(EXEDIR)/$(TRG).cof

GENDEPFLAGS = -Wp,-MM,-MP,-MT,$@,-MF,$(@:.o=.d)
CFLAGS  += -mmcu=$(MCU)
CXXLAGS += -mmcu=$(MCU)
ASFLAGS += -mmcu=$(MCU)
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
.PHONY : all debug printok depends build

# default target - binaries for AVR programming
all:	begin $(TRGPGM) printok

build:
	$(MAKE) clean
	$(MAKE)

begin:
	echo ======== Beginning of project  \"$(TRG)\"  processing. MCU=$(MCU); $(CC) --version ;\
	mkdir -p $(OBJDIR) $(EXEDIR) $(LSTDIR)

#	which mkdir.exe ; which avr-gcc.exe ;\

printok:  $(TRGELF)
	echo ======== All OK,  project \"$(TRG)\" size for $(MCU): ; $(ELFSIZE) $<

#-----------------------------------------------------------------------
# compilation rules
#
$(OBJDIR)/%.o : %.c
	echo ====  Compiling $< ; \
	$(CC) -E $(CFLAGS)  $(addprefix -I,$(INCDIRS)) $(GENDEPFLAGS) $< ;\
	$(CC) -c $(CFLAGS)  $(addprefix -I,$(INCDIRS)) \
		-Wa,-ahlmsd=$(LSTDIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(OBJDIR)/%.o : %.cpp
	echo ====  Compiling $< ; \
	$(CC) -E $(CXXFLAGS)  $(addprefix -I,$(INCDIRS)) $(GENDEPFLAGS) $< ;\
	$(CC) -c $(CXXFLAGS)  $(addprefix -I,$(INCDIRS)) \
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
	$(CC) -S $(CXXFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.cpp=.s)

%.E : %.c # preprocess only
	echo ====  Generate PREPROCESSED file from $< ; \
	$(CC) -E $(CFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.c=.E)

%.E : %.cpp # preprocess only
	echo ====  Generate PREPROCESSED file from $< ; \
	$(CC) -E $(CXXFLAGS) $(addprefix -I,$(INCDIRS)) $< -o $(<:.cpp=.E)

#-----------------------------------------------------------------------
# elf post-processing rules
#

# hex-files for programmer
%.hex: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O ihex -R .eeprom -R .lock -R .fuse -R .signature $< $@

%.eep: %.elf
	echo ====  extract $(notdir $@) ; \
	$(BIN) -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 $< $@

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


#####	end of avr.mak
