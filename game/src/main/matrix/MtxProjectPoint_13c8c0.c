#include "types.h"

asm void MtxProjectPoint_13c8c0(void)
{
    .set noreorder;
    lqc2       $vf4, 0x0($5);
    lqc2       $vf5, 0x10($5);
    lqc2       $vf6, 0x20($5);
    lqc2       $vf7, 0x30($5);
    lqc2       $vf8, 0x0($6);
    vmulax.xyzw $ACC, $vf4, $vf8x;
    vmadday.xyzw $ACC, $vf5, $vf8y;
    vmaddaz.xyzw $ACC, $vf6, $vf8z;
    vmaddw.xyzw $vf9, $vf7, $vf8w;
    vdiv       $Q, $vf0w, $vf9w;
    vwaitq;
    vmulq.xyz  $vf9, $vf9, $Q;
    jr         $31;
    sqc2      $vf9, 0x0($4);
}

