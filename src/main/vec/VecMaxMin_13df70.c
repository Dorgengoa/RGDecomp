#include "types.h"

asm void VecMaxMin_13df70(void)
{
    .set noreorder;
    lqc2       $vf15, 0x0($6);
    lqc2       $vf16, 0x0($7);
    vmax.xyzw  $vf18, $vf15, $vf16;
    vmini.xyzw $vf20, $vf15, $vf16;
    sqc2       $vf18, 0x0($4);
    jr         $31;
    sqc2      $vf20, 0x0($5);
}

