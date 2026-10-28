#include "types.h"

extern void _sceVu0ecossin(void);

/* Naked `asm void` (lever 6) -- no compiler frame at all, so the
   register-shuffle-around-the-call trick (`daddu $6,$31,$0` / jal /
   `daddu $31,$6,$0`, no stack touched) reproduces exactly instead of
   getting mwcc's own unwanted addiu-sp/sd-ra/ld-ra/jr frame. */

asm void sceVu0RotMatrixZ(void)
{
    .set noreorder;
    mtc1   $0, $f0;
    c.lt.s $f12, $f0;
    lui    $1, (0x3FC90FDB >> 16);
    ori    $1, $1, (0x3FC90FDB & 0xFFFF);
    mtc1   $1, $f0;
    bc1f   L0010ACB0;
    nop;
    add.s  $f12, $f0, $f12;
    j      func_0010ACB8;
    addiu  $7, $0, 0x1;
L0010ACB0:
    sub.s  $f12, $f0, $f12;
    daddu  $7, $0, $0;
func_0010ACB8:
    mfc1       $8, $f12;
    qmtc2.ni   $8, $vf6;
    daddu      $6, $31, $0;
    jal        _sceVu0ecossin;
    nop;
    daddu      $31, $6, $0;
    vmove.xyzw $vf6, $vf5;
    vmove.xyzw $vf7, $vf5;
    vmove.xyzw $vf9, $vf0;
    vsub.xyz   $vf9, $vf9, $vf9;
    vmr32.xyzw $vf8, $vf9;
    vsub.zw    $vf4, $vf4, $vf4;
    vaddx.y    $vf6, $vf5, $vf4x;
    vaddy.x    $vf6, $vf5, $vf4y;
    vsubx.x    $vf7, $vf5, $vf4x;
    vaddy.y    $vf7, $vf5, $vf4y;
    addiu $7, $0, 0x4;
L0010ACFC:
    lqc2  $vf4, 0x0($5);
    vmulax.xyzw  $ACC, $vf6, $vf4x;
    vmadday.xyzw $ACC, $vf7, $vf4y;
    vmaddaz.xyzw $ACC, $vf8, $vf4z;
    vmaddw.xyzw  $vf5, $vf9, $vf4w;
    sqc2  $vf5, 0x0($4);
    addi  $7, $7, -0x1;
    addi  $5, $5, 0x10;
    bne   $0, $7, L0010ACFC;
    addi  $4, $4, 0x10;
    jr    $31;
    nop;
}
