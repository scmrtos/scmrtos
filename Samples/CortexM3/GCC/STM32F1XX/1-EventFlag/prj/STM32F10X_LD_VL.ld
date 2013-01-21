/*************************************************
* linker script for ST32F100 Low Density Value Line microcontroller
************************************************/ 

_Minimum_Stack_Size = 0x100 ;

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH =  4K
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 32K
}
/* higher address of the user mode stack */
PROVIDE ( _estack = ALIGN(ORIGIN(RAM) + LENGTH(RAM) - 8 ,8) );

SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} > FLASH

	.text :
	{
		__ctors_start__ = .;
		KEEP(SORT(*)(.init_array))  /* eabi uses .init_array for static constructor lists */
		__ctors_end__ = .;

		__dtors_start__ = .;
		__dtors_end__ = .;
        
		. = ALIGN(4);
		*(.text)                   /* remaining code */
		*(.text.*)
		*(.rodata)                 /* read-only data (constants) */
		*(.rodata*)

		*(.eh_frame_hdr)
		*(.eh_frame)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.gcc_except_table)
		*(.eh_frame_hdr)
		*(.eh_frame)

		*(.glue_7)
		*(.glue_7t)
		. = ALIGN(4);
	} > FLASH

	/* .ARM.exidx is sorted, so has to go in its own output section.  */
	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

	.text.align :
	{
		. = ALIGN(8);
		_etext = .;
		_sidata = _etext;		/* start of initialized data label */
	} > FLASH

	.data : AT ( _sidata )		/* AT makes the LMA follow on in the binary image */
	{
		. = ALIGN(4);
		_sdata = .;				/* start of .data label */
		KEEP( *(.data) )
		KEEP( *(.data.*) )
		. = ALIGN(4);
		_edata = .;				/* end of .data label */
	} > RAM

	/* .bss section - uninitialized data */
	.bss :
	{
		. = ALIGN(4);
		_sbss = .;				/* start of .bss label (for startup) */
		 *(.bss)
		 *(.bss.*)
		 *(COMMON)
		. = ALIGN(4);
		_ebss = .;				/* end of .bss label (for startup) */
		_end = .;				/* end of used ram (start of free memory, for malloc) */
		__end = .;				/* the same */
	} > RAM

/*
 * This is the user stack section
 * This is just to check that there is enough RAM left for the User mode stack
 * It should generate an error if it's full.
 */
    ._usrstack :
    {
	    . = ALIGN(4);
      _susrstack = . ;
      . = . + _Minimum_Stack_Size ;
      . = ALIGN(4);
      _eusrstack = . ;
    } >RAM


PROVIDE( _heap = _ebss );
PROVIDE ( _eheap = ALIGN(ORIGIN(RAM) + LENGTH(RAM) - 8 ,8) );

/*
 * after that it's only debugging information.
 */

/* remove the debugging information from the standard libraries */
DISCARD :
	{
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}

/* Stabs debugging sections.  */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
/*
 * DWARF debug sections.
 * Symbols in the DWARF debugging sections are relative to the beginning
 * of the section so we begin them at 0.
 */

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
