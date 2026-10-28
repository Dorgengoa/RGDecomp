#include "types.h"

extern void _sceVu0ecossin(void);

asm void sceVu0RotMatrixY(void)
{
    .set noreorder;
    mtc1   $0, $f0;
    c.lt.s $f12, $f0;
    lui    $1, (0x3FC90FDB >> 16);
    ori    $1, $1, (0x3FC90FDB & 0xFFFF);
    mtc1   $1, $f0;
    bc1f   L0010AE00;
    nop;
    add.s  $f12, $f0, $f12;
    j      func_0010AE08;
    addiu  $7, $0, 0x1;
L0010AE00:
    sub.s  $f12, $f0, $f12;
    daddu  $7, $0, $0;
func_0010AE08:
    mfc1       $8, $f12;
    qmtc2.ni   $8, $vf6;
    daddu      $6, $31, $0;
    jal        _sceVu0ecossin;
    nop;
    daddu      $31, $6, $0;
    vmove.xyzw $vf6, $vf5;
    vmove.xyzw $vf7, $vf5;
    vmove.xyzw $vf8, $vf5;
    vmove.xyzw $vf9, $vf5;
    vaddw.y    $vf7, $vf5, $vf0w;
    vaddw.w    $vf9, $vf5, $vf0w;
    vsub.zw    $vf4, $vf4, $vf4;
    vsubx.z    $vf6, $vf5, $vf4x;
    vaddy.x    $vf6, $vf5, $vf4y;
    vaddx.x    $vf8, $vf5, $vf4x;
    vaddy.z    $vf8, $vf5, $vf4y;
    addiu $7, $0, 0x4;
L0010AE50:
    lqc2  $vf4, 0x0($5);
    vmulax.xyzw  $ACC, $vf6, $vf4x;
    vmadday.xyzw $ACC, $vf7, $vf4y;
    vmaddaz.xyzw $ACC, $vf8, $vf4z;
    vmaddw.xyzw  $vf5, $vf9, $vf4w;
    sqc2  $vf5, 0x0($4);
    addi  $7, $7, -0x1;
    addi  $5, $5, 0x10;
    bne   $0, $7, L0010AE50;
    addi  $4, $4, 0x10;
    jr    $31;
    nop;
}
