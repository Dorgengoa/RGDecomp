#include "types.h"

asm void BoundsAddPoint_13dee0(void)
{
    .set noreorder;
    lqc2       $vf15, 0x0($4);
    lqc2       $vf16, 0x0($5);
    lqc2       $vf17, 0x0($6);
    vmax.xyzw  $vf15, $vf15, $vf17;
    vmini.xyzw $vf16, $vf16, $vf17;
    sqc2       $vf15, 0x0($4);
    jr         $31;
    sqc2      $vf16, 0x0($5);
}

