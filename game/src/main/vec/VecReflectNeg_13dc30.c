#include "types.h"

asm void VecReflectNeg_13dc30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $2, $29, 0x0;
    lqc2       $vf4, 0x0($6);
    lqc2       $vf5, 0x0($5);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($2);
    lqc2       $vf4, 0x0($4);
    lqc2       $vf5, 0x0($2);
    vmul.xyz   $vf5, $vf4, $vf5;
    vaddy.x    $vf5, $vf5, $vf5y;
    vaddz.x    $vf5, $vf5, $vf5z;
    qmfc2.ni   $2, $vf5;
    mtc1       $2, $f1;
    lui        $2, (0x40000000 >> 16);
    mtc1       $2, $f0;
    nop;
    mul.s      $f0, $f0, $f1;
    addiu      $2, $29, 0x10;
    neg.s      $f1, $f0;
    lqc2       $vf4, 0x0($4);
    mfc1       $8, $f1;
    nop;
    qmtc2.ni   $8, $vf5;
    vmulx.xyzw $vf6, $vf4, $vf5x;
    sqc2       $vf6, 0x0($2);
    lqc2       $vf4, 0x0($5);
    lqc2       $vf5, 0x0($6);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($7);
    lqc2       $vf4, 0x0($7);
    lqc2       $vf5, 0x0($2);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($7);
    jr         $31;
    addiu     $29, $29, 0x20;
}

