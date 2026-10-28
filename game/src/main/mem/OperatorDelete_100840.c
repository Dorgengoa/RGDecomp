#include "types.h"

extern void Free_130e30(s32);
extern void EhUnexpected_1014d0(void *);

/* Prologue/epilogue frame is real (0x40 bytes, saves $30/$31), but the
   body between the initial `jal Free_130e30` and the epilogue is a
   provably-unreachable dead block (a `jal EhUnexpected_1014d0` + an infinite
   spin loop) that mwcc's own -O4 CFG pass prunes on sight when written
   as plain C with a `goto` -- worse, once the dead block is gone the
   remaining `Free_130e30(param); return;` becomes tail-call-eligible
   and mwcc collapses the whole function to a bare `j Free_130e30`
   (measured: neither `#pragma opt_dead_code off` nor `#pragma tailcall
   off` nor `#pragma opt_optimizecontrolflow off` restores the dead
   block). Naked `asm void` verbatim transcription sidesteps the whole
   optimizer, matching retail exactly including the never-taken dead
   code and the spin loop's own dead `nop`s.

   NOTE: config/main.symbols.txt lists this symbol's size as 0x54 (21
   words), 0xC bytes SHORTER than the 24-word span the listing's own
   trailing 3 `nop`s would suggest -- those 3 trailing nops after the
   epilogue's `jr $31` delay slot are padding owned by whatever comes
   next, not part of this function; dropped here to match the declared
   size exactly. */

asm void OperatorDelete_100840(void)
{
    .set noreorder;
    addiu $29, $29, -0x40;
    sd    $31, 0x10($29);
    sq    $30, 0x0($29);
    jal   Free_130e30;
    addu  $30, $29, $0;
    b     L00100880;
    nop;
    jal   EhUnexpected_1014d0;
    addiu $4, $30, 0x20;
L00100864:
    nop;
    nop;
    nop;
    nop;
    nop;
    b     L00100864;
    nop;
L00100880:
    addu  $29, $30, $0;
    ld    $31, 0x10($29);
    lq    $30, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x40;
}
