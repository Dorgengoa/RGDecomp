#include "types.h"

asm void BBoxUnion_13dea0(void)
{
    .set noreorder;
    lqc2       $vf15, 0x0($4);
    lqc2       $vf16, 0x10($4);
    lqc2       $vf17, 0x0($5);
    lqc2       $vf18, 0x10($5);
    vmax.xyzw  $vf20, $vf15, $vf16;
    vmini.xyzw $vf21, $vf15, $vf16;
    vmax.xyzw  $vf20, $vf20, $vf17;
    vmini.xyzw $vf21, $vf21, $vf17;
    vmax.xyzw  $vf20, $vf20, $vf18;
    vmini.xyzw $vf21, $vf21, $vf18;
    sqc2       $vf20, 0x0($4);
    jr         $31;
    sqc2      $vf21, 0x10($4);
}

