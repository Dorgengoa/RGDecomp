#include "types.h"

asm void VecLengthSq_13d440(void)
{
    .set noreorder;
    lqc2       $vf4, 0x0($4);
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

