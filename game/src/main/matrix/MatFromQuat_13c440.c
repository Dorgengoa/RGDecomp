#include "types.h"

asm void MatFromQuat_13c440(void)
{
    .set noreorder;
    addiu      $3, $28, -0x7360;
    lqc2       $vf10, 0x0($5);
    lqc2       $vf2, 0x0($3);
    vmula.xyz  $ACC, $vf10, $vf10;
    vmulx.xyzw $vf11, $vf10, $vf2x;
    vmr32.w    $vf15, $vf0;
    vmr32.w    $vf16, $vf0;
    vmr32.w    $vf17, $vf0;
    vmadd.xyz  $vf12, $vf10, $vf10;
    vaddw.xyz  $vf1, $vf0, $vf0w;
    vopmula.xyz $ACC, $vf11, $vf11;
    vmsubw.xyz $vf2, $vf11, $vf11w;
    vmaddw.xyz $vf3, $vf11, $vf11w;
    vaddaw.xyz $ACC, $vf0, $vf0w;
    vmsubax.yz $ACC, $vf1, $vf12x;
    vmsuby.z   $vf17, $vf1, $vf12y;
    vmsubay.x  $ACC, $vf1, $vf12y;
    vmsubz.y   $vf16, $vf1, $vf12z;
    vmr32.y    $vf15, $vf2;
    vmsubz.x   $vf15, $vf1, $vf12z;
    vmr32.x    $vf17, $vf2;
    vaddy.z    $vf15, $vf0, $vf3y;
    vmr32.w    $vf11, $vf2;
    vmr32.z    $vf16, $vf11;
    vaddx.y    $vf17, $vf0, $vf3x;
    vmr32.y    $vf3, $vf3;
    vmr32.x    $vf16, $vf3;
    sqc2       $vf15, 0x0($4);
    sqc2       $vf16, 0x10($4);
    jr         $31;
    sqc2      $vf17, 0x20($4);
}

