#include "types.h"

asm void VecMax4_13dfb0(void)
{
    .set noreorder;
    lqc2       $vf15, 0x0($5);
    lqc2       $vf16, 0x0($6);
    lqc2       $vf17, 0x0($7);
    lqc2       $vf18, 0x0($8);
    vmax.xyzw  $vf20, $vf15, $vf16;
    vmax.xyzw  $vf20, $vf20, $vf17;
    vmax.xyzw  $vf20, $vf20, $vf18;
    jr         $31;
    sqc2      $vf20, 0x0($4);
}

