#include "types.h"

/* Massive-frame context-save prologue (9 GPRs + 12 FPRs) into EhThrowHandler_101050 --
   looks like a signal/exception-context saver, hand-written (paddub as a
   register move) rather than compiler output. Naked `asm void` transcription
   of asm/matchings/main/ThrowException_1025c0.s (scripts/naked_asm_gen.py). Session
   43: the generator's trailing-nop stripper used to assume any `nop` not in
   a branch delay slot was spimdisasm's synthesized post-function padding and
   discarded it -- true for the sceMcMkdir precedent, false here, where the
   final `nop` is real content needed to reach the declared 0x80-byte size.
   Fixed by capping the strip at the symbol's own `size:` from
   config/main.symbols.txt. */

extern void EhThrowHandler_101050(void);

asm void ThrowException_1025c0(void)
{
    .set noreorder;
    paddub     $2, $29, $0;
    addiu      $29, $29, -0x2C0;
    sq         $16, 0x120($29);
    sq         $17, 0x130($29);
    sq         $18, 0x140($29);
    sq         $19, 0x150($29);
    sq         $20, 0x160($29);
    sq         $21, 0x170($29);
    sq         $22, 0x180($29);
    sq         $23, 0x190($29);
    sq         $30, 0x200($29);
    swc1       $f20, 0x288($29);
    swc1       $f21, 0x28C($29);
    swc1       $f22, 0x290($29);
    swc1       $f23, 0x294($29);
    swc1       $f24, 0x298($29);
    swc1       $f25, 0x29C($29);
    swc1       $f26, 0x2A0($29);
    swc1       $f27, 0x2A4($29);
    swc1       $f28, 0x2A8($29);
    swc1       $f29, 0x2AC($29);
    swc1       $f30, 0x2B0($29);
    swc1       $f31, 0x2B4($29);
    sw         $2, 0x14($29);
    sw         $2, 0x1C($29);
    sw         $31, 0x10($29);
    sw         $4, 0x0($29);
    sw         $5, 0x4($29);
    paddub     $4, $29, $0;
    jal        EhThrowHandler_101050;
    sw        $6, 0x8($29);
    nop;
}

