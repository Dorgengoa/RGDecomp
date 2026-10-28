#include "types.h"

asm void VecMin_13df90(void)
{
    .set noreorder;
    lqc2       $vf15, 0x0($5);
    lqc2       $vf16, 0x0($6);
    vmini.xyzw $vf18, $vf15, $vf16;
    jr         $31;
    sqc2      $vf18, 0x0($4);
}

