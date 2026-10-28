#include "types.h"

asm void VecAddScaled_13bdd0(void)
{
    .set noreorder;
    lqc2       $vf3, 0x0($4);
    lqc2       $vf4, 0x0($5);
    mfc1       $8, $f12;
    nop;
    qmtc2.ni   $8, $vf5;
    vmulaw.xyzw $ACC, $vf3, $vf0w;
    vmaddx.xyzw $vf6, $vf4, $vf5x;
    jr         $31;
    sqc2      $vf6, 0x0($4);
}

