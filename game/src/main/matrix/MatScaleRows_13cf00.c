#include "types.h"

asm void MatScaleRows_13cf00(void)
{
    .set noreorder;
    lqc2       $vf10, 0x0($6);
    lqc2       $vf1, 0x0($5);
    lqc2       $vf2, 0x10($5);
    lqc2       $vf3, 0x20($5);
    lqc2       $vf4, 0x30($5);
    vmulx.xyzw $vf1, $vf1, $vf10x;
    vmuly.xyzw $vf2, $vf2, $vf10y;
    vmulz.xyzw $vf3, $vf3, $vf10z;
    sqc2       $vf1, 0x0($4);
    sqc2       $vf2, 0x10($4);
    sqc2       $vf3, 0x20($4);
    jr         $31;
    sqc2      $vf4, 0x30($4);
}

