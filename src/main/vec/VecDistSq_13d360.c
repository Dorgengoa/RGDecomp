#include "types.h"

asm void VecDistSq_13d360(void)
{
    .set noreorder;
    lqc2       $vf2, 0x0($4);
    lqc2       $vf3, 0x0($5);
    vsub.xyz   $vf4, $vf3, $vf2;
    vmul.xyz   $vf4, $vf4, $vf4;
    vmr32.xy   $vf5, $vf4;
    vmr32.x    $vf6, $vf5;
    vadd.x     $vf7, $vf4, $vf5;
    vadd.x     $vf5, $vf6, $vf7;
    qmfc2.ni   $2, $vf5;
    mtc1       $2, $f0;
    jr         $31;
    nop;
}

