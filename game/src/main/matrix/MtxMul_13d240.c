#include "types.h"

asm void MtxMul_13d240(void)
{
    .set noreorder;
    lqc2       $vf1, 0x0($5);
    lqc2       $vf2, 0x10($5);
    lqc2       $vf3, 0x20($5);
    lqc2       $vf4, 0x30($5);
    lqc2       $vf5, 0x0($6);
    lqc2       $vf6, 0x10($6);
    lqc2       $vf7, 0x20($6);
    lqc2       $vf8, 0x30($6);
    vmulax.xyzw $ACC, $vf1, $vf5x;
    vmadday.xyzw $ACC, $vf2, $vf5y;
    vmaddaz.xyzw $ACC, $vf3, $vf5z;
    vmaddw.xyzw $vf20, $vf4, $vf5w;
    vmulax.xyzw $ACC, $vf1, $vf6x;
    vmadday.xyzw $ACC, $vf2, $vf6y;
    vmaddaz.xyzw $ACC, $vf3, $vf6z;
    vmaddw.xyzw $vf21, $vf4, $vf6w;
    vmulax.xyzw $ACC, $vf1, $vf7x;
    vmadday.xyzw $ACC, $vf2, $vf7y;
    vmaddaz.xyzw $ACC, $vf3, $vf7z;
    vmaddw.xyzw $vf22, $vf4, $vf7w;
    vmulax.xyzw $ACC, $vf1, $vf8x;
    vmadday.xyzw $ACC, $vf2, $vf8y;
    vmaddaz.xyzw $ACC, $vf3, $vf8z;
    vmaddw.xyzw $vf23, $vf4, $vf8w;
    sqc2       $vf20, 0x0($4);
    sqc2       $vf21, 0x10($4);
    sqc2       $vf22, 0x20($4);
    jr         $31;
    sqc2      $vf23, 0x30($4);
}

