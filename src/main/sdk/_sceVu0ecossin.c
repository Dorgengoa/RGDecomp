#include "types.h"

/* kh1 cross-reference, 2026-09-08: identity confirmed against
   ethteck/kh1 src/lib/libvu0.c.
   static helper, name already landed in main.symbols.txt
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/_sceVu0ecossin.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
asm void _sceVu0ecossin(void)
{
    .set noreorder;
    lui        $8, 0x44;
    addiu      $8, $8, 0x5F60;
    lqc2       $vf5, 0x0($8);
    vmr32.w    $vf6, $vf6;
    vaddx.x    $vf4, $vf0, $vf6x;
    vmul.x     $vf6, $vf6, $vf6;
    vmulx.yzw  $vf4, $vf4, $vf0x;
    vmulw.xyzw $vf8, $vf5, $vf6w;
    vsub.xyzw  $vf5, $vf0, $vf0;
    vmulx.xyzw $vf8, $vf8, $vf6x;
    vmulx.xyz  $vf8, $vf8, $vf6x;
    vaddw.x    $vf4, $vf4, $vf8w;
    vmulx.xy   $vf8, $vf8, $vf6x;
    vaddz.x    $vf4, $vf4, $vf8z;
    vmulx.x    $vf8, $vf8, $vf6x;
    vaddy.x    $vf4, $vf4, $vf8y;
    vaddx.x    $vf4, $vf4, $vf8x;
    vaddx.xy   $vf4, $vf5, $vf4x;
    vmul.x     $vf7, $vf4, $vf4;
    vsubx.w    $vf7, $vf0, $vf7x;
    .word      0x4B8703BD;
    vwaitq;
    bnez       $7, L0010AC78;
    vaddq.x   $vf7, $vf0, $Q;
    b          L0010AC7C;
    vaddx.x   $vf4, $vf5, $vf7x;
  L0010AC78:
    vsubx.x    $vf4, $vf5, $vf7x;
  L0010AC7C:
    jr         $31;
    nop;
}
