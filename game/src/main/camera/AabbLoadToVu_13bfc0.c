#include "types.h"

asm void AabbLoadToVu_13bfc0(void)
{
    .set noreorder;
    addiu      $3, $28, -0x7350;
    lqc2       $vf3, 0x0($3);
    lqc2       $vf1, 0x0($4);
    lqc2       $vf2, 0x10($4);
    vmulax.xyzw $ACC, $vf1, $vf3x;
    vmsubx.xyzw $vf5, $vf2, $vf3x;
    vadd.xyzw  $vf6, $vf5, $vf2;
    lqc2       $vf10, 0x0($5);
    lqc2       $vf11, 0x10($5);
    lqc2       $vf12, 0x20($5);
    lqc2       $vf13, 0x30($5);
    vmulax.xyzw $ACC, $vf10, $vf6x;
    vmadday.xyzw $ACC, $vf11, $vf6y;
    vmaddaz.xyzw $ACC, $vf12, $vf6z;
    vmaddw.xyzw $vf7, $vf13, $vf0w;
    vmulx.xyzw $vf10, $vf10, $vf5x;
    vmuly.xyzw $vf11, $vf11, $vf5y;
    jr         $31;
    vmulz.xyzw $vf12, $vf12, $vf5z;
}

