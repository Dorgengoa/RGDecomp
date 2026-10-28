#include "types.h"

/* Registered name for stale lane-file func_0010B518. Naked asm void.
   Registered size 0x90 = 36 words, and here the LISTING's final `nop`
   (after `jr $31`'s delay slot) is genuinely IN RANGE (36th word) --
   unlike most other units in this vein, nothing here is out-of-range
   padding (lever 4 does not fire), so all three trailing words
   (jr/delay-nop/nop) are written explicitly. */

asm void sceVu0ClipAll(void)
{
    .set noreorder;
    lqc2  $vf8, 0x0($7);
    lqc2  $vf4, 0x0($6);
    lqc2  $vf5, 0x10($6);
    lqc2  $vf6, 0x20($6);
    lqc2  $vf7, 0x30($6);
    lqc2  $vf9, 0x0($4);
    lqc2  $vf10, 0x0($5);
    lqc2  $vf11, 0x0($4);
    lqc2  $vf12, 0x0($5);
L0010B53C:
    vmulax.xyzw  $ACC, $vf4, $vf8x;
    vmadday.xyzw $ACC, $vf5, $vf8y;
    vmaddaz.xyzw $ACC, $vf6, $vf8z;
    vmaddw.xyzw  $vf8, $vf7, $vf8w;
    vmulw.xyz $vf11, $vf9, $vf8w;
    vmulw.xyz $vf12, $vf10, $vf8w;
    vnop;
    vnop;
    ctc2.ni $0, $vi16;
    vsub.xyw $vf11, $vf8, $vf11;
    vsub.xyw $vf12, $vf12, $vf8;
    vmove.w $vf11, $vf9;
    vmove.w $vf12, $vf10;
    vnop;
    addi  $7, $7, 0x10;
    lqc2  $vf8, 0x0($7);
    addi  $8, $8, -0x1;
    cfc2.ni $2, $vi16;
    andi  $2, $2, 0xC0;
    beqz  $2, L0010B59C;
    nop;
    bne   $0, $8, L0010B53C;
    nop;
    addi  $2, $0, 0x1;
L0010B59C:
    jr    $31;
    nop;
    nop;
}
