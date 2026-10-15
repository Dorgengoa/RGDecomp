.include "macro.inc"

# FACTORY.BIN reserves 0xF00 of bss. Like the main image it has to
# come from a real NOBITS input section: a `. = <addr>` in the lcf pads the
# FILE out to that address instead of reserving memory.

.section .bss

glabel factory_bss
.space 0xF00
