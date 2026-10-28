#include "types.h"

/* Naked `asm void` transcription (scripts/naked_asm_gen.py). Session 43:
   the trailing `nop` (the tail `j`'s delay slot notwithstanding) is real
   content, not spimdisasm padding -- see ThrowException_1025c0.c's note for the
   generator fix this needed. A literal `j <extern>` reaches retail's byte
   here (frameless leaf), unlike __assert's framed `j Abort_12de80` tail
   call, which mwcc always expands to `jal`+full epilogue regardless of
   spelling -- worth revisiting whether "has a stack frame" is what decides
   it, next time a framed tail-call residue comes up. */

extern void _sceSDC(void);

asm void iSyncDCache(void)
{
    .set noreorder;
    lui        $2, (0xFFFFFFC0 >> 16);
    ori        $2, $2, (0xFFFFFFC0 & 0xFFFF);
    and        $5, $5, $2;
    j          _sceSDC;
    and       $4, $4, $2;
    nop;
}

