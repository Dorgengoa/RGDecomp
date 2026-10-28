#include "types.h"

asm void MatMul33_13d180(void)
{
    .set noreorder;
    lqc2       $vf1, 0x0($5);
    lqc2       $vf2, 0x10($5);
    lqc2       $vf3, 0x20($5);
    lqc2       $vf5, 0x0($6);
    lqc2       $vf6, 0x10($6);
    lqc2       $vf7, 0x20($6);
    vmulax.xyzw $ACC, $vf1, $vf5x;
    vmadday.xyzw $ACC, $vf2, $vf5y;
    vmaddz.xyzw $vf20, $vf3, $vf5z;
    vmulax.xyzw $ACC, $vf1, $vf6x;
    vmadday.xyzw $ACC, $vf2, $vf6y;
    vmaddz.xyzw $vf21, $vf3, $vf6z;
    vmulax.xyzw $ACC, $vf1, $vf7x;
    vmadday.xyzw $ACC, $vf2, $vf7y;
    vmaddz.xyzw $vf22, $vf3, $vf7z;
    sqc2       $vf20, 0x0($4);
    sqc2       $vf21, 0x10($4);
    jr         $31;
    sqc2      $vf22, 0x20($4);
}

