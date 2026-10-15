#include "types.h"

asm void VecMinMax3_13df40(void)
{
    .set noreorder;
    lqc2       $vf15, 0x0($6);
    lqc2       $vf16, 0x0($7);
    lqc2       $vf17, 0x0($8);
    vmax.xyzw  $vf18, $vf15, $vf16;
    vmini.xyzw $vf20, $vf15, $vf16;
    vmax.xyzw  $vf19, $vf18, $vf17;
    vmini.xyzw $vf21, $vf20, $vf17;
    sqc2       $vf19, 0x0($4);
    jr         $31;
    sqc2      $vf21, 0x0($5);
}

