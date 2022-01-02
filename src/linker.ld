SECTIONS
{
    /* From boot.s */
    .text.boot : { *(.text.boot) }
    .text : { *(.text) }
    /* Read-only data */
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    /* Byte padding for BSS section */
    . = ALIGN(0x8);
    /* Block starting symbol section (statically allocated variables) */
    bss_begin = .;
    .bss : { *(.bss*) }
    bss_end = .;
}