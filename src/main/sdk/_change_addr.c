#include "types.h"

/* Naked `asm void` transcription (scripts/naked_asm_gen.py). Session 43:
   the trailing `nop` is real content, not spimdisasm padding -- see
   ThrowException_1025c0.c's note for the generator fix this needed. */

asm void _change_addr(void)
{
    .set noreorder;
    lw         $2, 0x10($4);
    jr         $31;
    sw        $2, 0x8($5);
    nop;
}

