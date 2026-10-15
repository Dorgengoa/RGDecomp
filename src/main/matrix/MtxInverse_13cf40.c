#include "types.h"

asm void MtxInverse_13cf40(void)
{
    .set noreorder;
    lqc2       $vf1, 0x0($5);
    lqc2       $vf2, 0x10($5);
    lqc2       $vf3, 0x20($5);
    lqc2       $vf4, 0x30($5);
    vsub.xyzw  $vf5, $vf5, $vf5;
    vsub.xyzw  $vf6, $vf6, $vf6;
    vsub.xyzw  $vf7, $vf7, $vf7;
    vaddx.xyzw $vf8, $vf0, $vf0x;
    vopmula.xyz $ACC, $vf2, $vf3;
    vopmsub.xyz $vf10, $vf3, $vf2;
    vopmula.xyz $ACC, $vf3, $vf1;
    vopmsub.xyz $vf11, $vf1, $vf3;
    vopmula.xyz $ACC, $vf1, $vf2;
    vopmsub.xyz $vf12, $vf2, $vf1;
    vmul.xyz   $vf15, $vf10, $vf1;
    vaddx.x    $vf5, $vf0, $vf10x;
    vaddy.x    $vf6, $vf0, $vf10y;
    vaddz.x    $vf7, $vf0, $vf10z;
    vaddy.x    $vf15, $vf15, $vf15y;
    vaddx.y    $vf5, $vf0, $vf11x;
    vaddy.y    $vf6, $vf0, $vf11y;
    vaddz.y    $vf7, $vf0, $vf11z;
    vaddz.x    $vf15, $vf15, $vf15z;
    vaddx.z    $vf5, $vf0, $vf12x;
    vaddy.z    $vf6, $vf0, $vf12y;
    vaddz.z    $vf7, $vf0, $vf12z;
    vdiv       $Q, $vf0w, $vf15x;
    vwaitq;
    vmulq.xyz  $vf5, $vf5, $Q;
    vmulq.xyz  $vf6, $vf6, $Q;
    vmulq.xyz  $vf7, $vf7, $Q;
    vmulax.xyzw $ACC, $vf5, $vf4x;
    vmadday.xyzw $ACC, $vf6, $vf4y;
    vmaddz.xyzw $vf8, $vf7, $vf4z;
    vsub.xyz   $vf8, $vf0, $vf8;
    vaddx.w    $vf8, $vf0, $vf0x;
    sqc2       $vf5, 0x0($4);
    sqc2       $vf6, 0x10($4);
    sqc2       $vf7, 0x20($4);
    jr         $31;
    sqc2      $vf8, 0x30($4);
}

