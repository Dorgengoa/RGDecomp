#include "types.h"

asm void AabbPlaneDistances_13bf50(void)
{
    .set noreorder;
    lqc2       $vf1, 0x0($6);
    lqc2       $vf2, 0x10($6);
    lqc2       $vf3, 0x20($6);
    lqc2       $vf4, 0x30($6);
    vmulax.xyzw $ACC, $vf1, $vf10x;
    vmadday.xyzw $ACC, $vf2, $vf10y;
    vmaddz.xyzw $vf20, $vf3, $vf10z;
    vmulax.xyzw $ACC, $vf1, $vf11x;
    vmadday.xyzw $ACC, $vf2, $vf11y;
    vmaddz.xyzw $vf21, $vf3, $vf11z;
    vmulax.xyzw $ACC, $vf1, $vf12x;
    vmadday.xyzw $ACC, $vf2, $vf12y;
    vmaddz.xyzw $vf22, $vf3, $vf12z;
    vabs.xyzw  $vf20, $vf20;
    vabs.xyzw  $vf21, $vf21;
    vabs.xyzw  $vf22, $vf22;
    vadda.xyzw $ACC, $vf20, $vf21;
    vmaddw.xyzw $vf25, $vf22, $vf0w;
    vmulax.xyzw $ACC, $vf1, $vf7x;
    vmadday.xyzw $ACC, $vf2, $vf7y;
    vmaddaz.xyzw $ACC, $vf3, $vf7z;
    vmaddw.xyzw $vf26, $vf4, $vf0w;
    sqc2       $vf26, 0x0($5);
    jr         $31;
    sqc2      $vf25, 0x0($4);
}

