#include "types.h"

/* Registered name for stale lane-file func_0010B368. Naked asm void. */

asm void sceVu0RotTransPersN(void)
{
    .set noreorder;
    lqc2  $vf4, 0x0($5);
    lqc2  $vf5, 0x10($5);
    lqc2  $vf6, 0x20($5);
    lqc2  $vf7, 0x30($5);
L0010B378:
    lqc2  $vf8, 0x0($6);
    vmulax.xyzw  $ACC, $vf4, $vf8x;
    vmadday.xyzw $ACC, $vf5, $vf8y;
    vmaddaz.xyzw $ACC, $vf6, $vf8z;
    vmaddw.xyzw  $vf9, $vf7, $vf8w;
    vdiv  $Q, $vf0w, $vf9w;
    vwaitq;
    vmulq.xyz $vf9, $vf9, $Q;
    beqz  $8, L0010B3A4;
    vftoi4.xyzw $vf10, $vf9;
    vftoi0.zw   $vf10, $vf9;
L0010B3A4:
    sqc2  $vf10, 0x0($4);
    addi  $7, $7, -0x1;
    addi  $6, $6, 0x10;
    bne   $0, $7, L0010B378;
    addi  $4, $4, 0x10;
    jr    $31;
    nop;
}
