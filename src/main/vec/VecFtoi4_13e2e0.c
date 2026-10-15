#include "types.h"

asm void VecFtoi4_13e2e0(void)
{
    .set noreorder;
    lqc2       $vf1, 0x0($5);
    vftoi4.xyzw $vf1, $vf1;
    jr         $31;
    sqc2      $vf1, 0x0($4);
}

