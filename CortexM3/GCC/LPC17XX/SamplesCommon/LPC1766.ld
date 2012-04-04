/*************************************************
* linker script for LPC176x Devices
************************************************/ 

/*
 *  Flash
 *	512 KB - LPC1769, 68, 67, LPC1759, 58
 *	256 KB - LPC1766, 65, 63, LPC1756
 *	128 KB - LPC1764,         LPC1754
 *	 64 KB -                  LPC1752
 *	 32 KB -                  LPC1751
 *  RAM
 *	 64 KB - LPC1769, 68, 67, 66, 65, 63, LPC1759, 58
 *	 32 KB - LPC1764, LPC1756, 54
 *	 16 KB - LPC1752
 *	  8 KB - LPC1751
 */

/* LPC17xx.h
 *	#ifdef __LPC17XX_REV00
 *	#define LPC_AHBRAM0_BASE      (0x20000000UL)
 *	#define LPC_AHBRAM1_BASE      (0x20004000UL)
 *	#else
 *	#define LPC_AHBRAM0_BASE      (0x2007C000UL)
 *	#define LPC_AHBRAM1_BASE      (0x20080000UL)
 *	#endif
 *
 * UM rev2, aug 2010
 *  On-chip SRAM	0x10000000 -- без BitBand !
 *	8, 16, 32 KB
 *
 * AHB SRAM BANK0	0x2007C000 - 16 K
 * AHB SRAM BANK1	0x20080000 - 16 K
 *
 */


ENTRY(Reset_Handler)

_Minimum_Stack_Size = 0x100 ;

MEMORY
{
	FLASH (rx)	: ORIGIN = 0x00000000, LENGTH = 256K
	RAM (xrw)	: ORIGIN = 0x10000000, LENGTH =  32K
	/*
	  RAM_AHB0 (rw)	: ORIGIN = 0x2007C000, LENGTH =  16K
	  RAM_AHB1 (rw)	: ORIGIN = 0x20080000, LENGTH =  16K
	*/
	RAM_AHB (rw)	: ORIGIN = 0x2007C000, LENGTH =  32K
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
/* Тут же не враховано мінімальний стек */
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

