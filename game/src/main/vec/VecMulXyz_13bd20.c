#include "types.h"

asm void VecMulXyz_13bd20(void)
{
    .set noreorder;
    lqc2       $vf4, 0x0($5);
    lqc2       $vf5, 0x0($6);
    vmul.xyz   $vf4, $vf4, $vf5;
    jr         $31;
    sqc2      $vf4, 0x0($4);
}

