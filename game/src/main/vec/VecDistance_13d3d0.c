#include "types.h"

asm void VecDistance_13d3d0(void)
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
    .word      0x4A0503BD;
    vwaitq;
    cfc2.ni    $2, $vi22;
    mtc1       $2, $f0;
    jr         $31;
    nop;
}

