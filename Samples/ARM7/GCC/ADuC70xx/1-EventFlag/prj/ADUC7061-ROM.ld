/*************************************************
* linker script for ADuC7061 microcontroller
*
************************************************/ 
ENTRY(_start)

IRQ_STACK_SIZE = 0x400;
SYS_STACK_SIZE = 0x0;
FIQ_STACK_SIZE = 0x0;
UND_STACK_SIZE = 0x0;
ABT_STACK_SIZE = 0x0;
SVC_STACK_SIZE = 0x0;

MEMORY
{
	REMAP (rx)	: ORIGIN = 0x00000000, LENGTH = 4k   /* the same size as RAM */
	RAM (rw)	: ORIGIN = 0x00040000, LENGTH = 4k
	FLASH (rx)	: ORIGIN = 0x00080000, LENGTH = 29k
	EEDATA (r)	: ORIGIN = 0x00087400, LENGTH = 1k
	BOOTROM (r)	: ORIGIN = 0x00087800, LENGTH = 2k
}

SECTIONS
{
	.vectors :
	{
		. = ALIGN(4);
		KEEP(*(.vectors))
		. = ALIGN(4);
	} > FLASH

	.flashdata :
	{
		KEEP(*(.flashdata))
	} > EEDATA

	.text :
	{
		__ctors_start = .;
        KEEP(SORT(*)(.init_array))  /* eabi uses .init_array for static constructor lists */
		__ctors_end = .;

		__dtors_start = .;
		__dtors_end = .;

		. = ALIGN(4);

		*(.text)                   /* remaining code */
		*(.text.*)                 /* remaining code */
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
	} >FLASH
	__exidx_end = .;

	.text.align :
	{
		. = ALIGN(8);
		_etext = .;
		_data_image = _etext; /* start of initialized data label */
	} >FLASH

	.data : AT ( _data_image )
	{
		. = ALIGN(4);
		_data = .;
		*(.ramfunc*)
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = . ;
	} >RAM

	/* .bss section which is used for uninitialized data */
	.bss: (NOLOAD) :
	{
		. = ALIGN(4);
		__bss_start = . ;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end = . ;
	} > RAM

	.noinit (NOLOAD) :
	{
		PROVIDE (__noinit_start = .) ;
		*(.noinit*)
		PROVIDE (__noinit_end = .) ;
	} > RAM

	stack ALIGN(256) :
	{
		. += IRQ_STACK_SIZE;
		PROVIDE (__stack_irq = .);
		. += FIQ_STACK_SIZE;
		PROVIDE (__stack_fiq = .);
		. += UND_STACK_SIZE;
		PROVIDE (__stack_und = .);
		. += ABT_STACK_SIZE;
		PROVIDE (__stack_abort = .);
		. += SVC_STACK_SIZE;
		PROVIDE (__stack_svc = .);
		. += SYS_STACK_SIZE;
		PROVIDE (__stack_sys = .);
	} > RAM

	_end = . ;
	PROVIDE (end = .);
	PROVIDE( _heap = _end );
	PROVIDE ( _eheap = ALIGN(ORIGIN(RAM) + LENGTH(RAM) - 8 ,8) );


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
