#include "types.h"

asm void VecTriCross_13de70(void)
{
    .set noreorder;
    lqc2       $vf15, 0x0($5);
    lqc2       $vf16, 0x0($6);
    lqc2       $vf17, 0x0($7);
    vsub.xyzw  $vf10, $vf16, $vf15;
    vsub.xyzw  $vf11, $vf17, $vf15;
    vopmula.xyz $ACC, $vf10, $vf11;
    vopmsub.xyz $vf12, $vf11, $vf10;
    jr         $31;
    sqc2      $vf12, 0x0($4);
}

