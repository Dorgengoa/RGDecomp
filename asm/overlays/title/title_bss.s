.include "macro.inc"

# TITLE.BIN reserves 0x280 of bss. Like the main image it has to come from a
# real NOBITS input section: a `. = <addr>` in the lcf pads the FILE out to
# that address instead of reserving memory.

.section .bss

glabel title_bss
.space 0x280
