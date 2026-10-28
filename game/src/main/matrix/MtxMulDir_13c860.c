#include "types.h"

asm void MtxMulDir_13c860(void)
{
    .set noreorder;
    lqc2       $vf16, 0x0($6);
    lqc2       $vf10, 0x0($5);
    lqc2       $vf11, 0x10($5);
    lqc2       $vf12, 0x20($5);
    vmulax.xyzw $ACC, $vf10, $vf16x;
    vmadday.xyzw $ACC, $vf11, $vf16y;
    vmaddz.xyzw $vf17, $vf12, $vf16z;
    jr         $31;
    sqc2      $vf17, 0x0($4);
}

