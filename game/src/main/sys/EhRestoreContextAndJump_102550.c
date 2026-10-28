#include "types.h"

/* Register-restore trampoline: NAKED `asm` function (no compiler frame at
   all) instead of `asm volatile{}` inside a normal C function -- the
   normal-C-function form made mwcc auto-save EVERY raw callee-saved
   register/FPR ($16-$23,$30,f20-f31) it saw mentioned in the block (a
   huge, wrong, 70-word frame). `asm void f(void) { ...; }` emits every
   instruction VERBATIM with no compiler-generated prologue/epilogue at
   all (same construct the overlay entry stubs use), which is exactly
   what a real hand-written trampoline needs. */

asm void EhRestoreContextAndJump_102550(void)
{
    lq    $16, 0x120($4);
    lwc1  $f20, 0x288($4);
    lq    $17, 0x130($4);
    lwc1  $f21, 0x28C($4);
    lq    $18, 0x140($4);
    lwc1  $f22, 0x290($4);
    lq    $19, 0x150($4);
    lwc1  $f23, 0x294($4);
    lq    $20, 0x160($4);
    lwc1  $f24, 0x298($4);
    lq    $21, 0x170($4);
    lwc1  $f25, 0x29C($4);
    lq    $22, 0x180($4);
    lwc1  $f26, 0x2A0($4);
    lq    $23, 0x190($4);
    lwc1  $f27, 0x2A4($4);
    lq    $30, 0x200($4);
    lwc1  $f28, 0x2A8($4);
    lwc1  $f29, 0x2AC($4);
    lw    $29, 0x1C($4);
    lwc1  $f30, 0x2B0($4);
    lw    $2, 0x224($4);
    lwc1  $f31, 0x2B4($4);
    jr    $6;
    sub   $29, $29, $2;
}
