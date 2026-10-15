#include "types.h"

/* Approved startup assembly exception (2026-10-14): retain the original eight-byte startup prefix as assembly.
 * Retail ELF e_entry is 0x00100008; PT_LOAD begins at 0x00100000.
 * This symbol is a registered prefix/padding fragment, not a returning C
 * function. If execution reaches it, the two nops fall through to entry.
 * Preserve symbol and bytes: generated data contains address-valued references.
 * Evidence: build/libdeasm/100000/NOTES.md. Not a pure-C decompilation.
 */
asm void EntryPad_100000(void)
{
    .set noreorder;
    nop;
    nop;
}
