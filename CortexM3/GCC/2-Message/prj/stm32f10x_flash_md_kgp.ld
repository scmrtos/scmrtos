/*************************************************
* linker script for ST32F103Vx  microcontroller
*
************************************************/ 

_Minimum_Stack_Size = 0x100 ;

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH =  20K
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 128K
}

/* higher address of the user mode stack */
_estack = 0x20005000;

SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))            /* Startup code */
		. = ALIGN(4);
	} >FLASH

/*
 * the program code is stored in the .text section, which goes to Flash
 */
	.text :
	{
        __ctors_start__ = .;
        KEEP(SORT(*)(.ctors))
        __ctors_end__ = .;
        __dtors_start__ = .;
        /* *(.dtors) */
        __dtors_end__ = .;
        /*
        KEEP(SORT(*)(.dtors))
        */
        /*
        KEEP(SORT(*)(.init_array))
        */
        
		. = ALIGN(4);
		*(.text)                   /* remaining code */
		*(.text.*)                   /* remaining code */
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
	} >FLASH

  /* .ARM.exidx is sorted, so has to go in its own output section.  */
	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} >FLASH
	__exidx_end = .;
	.text.align :
	{
		. = ALIGN(8);
		_etext = .;
		_sidata = _etext; /* Uused by the startup in order to initialize the .data secion */
	} >FLASH

/*
 * This is the initialized data section. It is stored in RAM but the initial values
 * are held in flash and copied to RAM by the startup code
 */
	.data  : AT ( _sidata )  /* AT makes the LMA follow on in the binary image */
	{
		. = ALIGN(4);
		_sdata = . ; /* Used by the startup in order to initialize the .data section */
		KEEP( *(.data) )
		KEEP( *(.data.*) )
		. = ALIGN(4);
		_edata = . ; /* Used by the startup in order to initialize the .data section */
	} >RAM



/*
 * This is the uninitialized data section. Date here is stored in RAM and will be
 * set to zero by the startup code.
 */
	.bss :
	{
		. = ALIGN(4);
		_sbss = .; /* Used by the startup in order to initialize the .bss section */
		 *(.bss)
		 *(.bss.*)
		 *(COMMON)
		. = ALIGN(4);
		_ebss = . ; /* Used by the startup in order to initialize the .bss section */
		_end = .;
		__end = .;
	} >RAM

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

