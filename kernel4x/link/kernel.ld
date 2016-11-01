OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(entry_from_boot)

SECTIONS {
    . = 0x40000;

    /* Text segment: instructions and read-only globals */
    .text : { *(.text .stub .text.* .gnu.linkonce.t.*) }
    PROVIDE(etext = .);    /* Define the `etext` symbol at this location */
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r.*) }

    /* Data segment: read/write and zero-initialized globals */
    . = ALIGN(4096);       /* Align to a page boundary */
    PROVIDE(start_data = .);
    .data : { *(.data) }
    PROVIDE(edata = .);
    .bss : { *(.bss) }
    PROVIDE(end = .);

    /DISCARD/ : { *(.eh_frame .note.GNU-stack) }
}
