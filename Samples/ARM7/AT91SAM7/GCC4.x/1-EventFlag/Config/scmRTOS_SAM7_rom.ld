/*
//*****************************************************************
//  Command file for GNU linker
//
//  Generates appropriate mappings for objects in memory
//
//  Target mcu: AT91SAM7 (Atmel)
//  Code location: Internal flash 
//
//
//  $Revision$
//  $Date::             $
//
//*****************************************************************
*/

ENTRY(_start)
IRQ_STACK_SIZE = 0x400;
SYS_STACK_SIZE = 0x0;    /* actualy not used after OS:Start() */

/* memory layout */
MEMORY
{
  REMAP (rx)   : ORIGIN = 0x00000000, LENGTH = 0x00004000   /* the same size ar RAM */
  ROM (rx)     : ORIGIN = 0x00100000, LENGTH = 0x00008000   /* any SAM7 has at least 32K ROM */
  RAM (rw)     : ORIGIN = 0x00200000, LENGTH = 0x00004000   /* any SAM7 has at least 4K RAM */
}

SECTIONS
{
  .vectors :
  {
    KEEP(*(.vectors))
  } > REMAP AT > ROM    /* link vectors to remapped area, but place to ROM area */

  /* first section is .text which is used for code */
  .text :
  {
    __ctors_start = .;
    *(.ctors)
     __ctors_end = .;
     __dtors_start = .;
     *(.dtors)
     __dtors_end = .;
    KEEP(SORT(*)(.ctors))
    KEEP(SORT(*)(.dtors))

    . = ALIGN(4);

    *(.text*)           /* code */

    *(.rodata*)         /* read-only data (constants) */

    *(.glue_7)
    *(.glue_7t)
  } > ROM

  . = ALIGN(4);
  _etext = .;

  /* .data section which is used for initialized data */
  .data :
  {
    _data = .;
    *(.ramfunc*)
    *(.data*)

    _edata = . ;
    _data_image = LOADADDR(.data) ;
    PROVIDE (edata = .);
  } > RAM AT > ROM

  . = ALIGN(4);

  /* .bss section which is used for uninitialized data */
  .bss: (NOLOAD) :
  {
    __bss_start = . ;
    __bss_start__ = . ;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
	__bss_end__ = . ;
  } > RAM

  . = ALIGN(4);
  PROVIDE (__bss_end = .);

  .noinit (NOLOAD) :
  {
     PROVIDE (__noinit_start = .) ;
    *(.noinit*)
     PROVIDE (__noinit_end = .) ;
     _end = . ;
     PROVIDE (__heap_start = .) ;
  } > RAM

  .stack :
  {
    . = ALIGN(4);
    . += IRQ_STACK_SIZE;
    PROVIDE (__stack_irq = .);
    . += SYS_STACK_SIZE;
    PROVIDE (__stack_sys = .);
    /*  allocate stacks if needed */
    PROVIDE (__stack_fiq = .);
    PROVIDE (__stack_und = .);
    PROVIDE (__stack_abort = .);
    PROVIDE (__stack_svc = .);
    
  } > RAM

  _end = . ;
  PROVIDE (end = .);


  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}
