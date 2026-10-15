#include "types.h"

asm void AabbCorners_13e190(void)
{
    .set noreorder;
    lqc2       $vf1, 0x0($5);
    lqc2       $vf2, 0x0($6);
    vaddx.xyzw $vf3, $vf2, $vf0x;
    vaddx.xyzw $vf4, $vf2, $vf0x;
    vaddx.xyzw $vf5, $vf2, $vf0x;
    vaddx.xyzw $vf6, $vf1, $vf0x;
    vaddx.xyzw $vf7, $vf1, $vf0x;
    vaddx.xyzw $vf8, $vf1, $vf0x;
    sqc2       $vf2, 0x0($4);
    sqc2       $vf1, 0x70($4);
    vaddx.x    $vf3, $vf1, $vf0x;
    vaddx.y    $vf4, $vf1, $vf0x;
    vaddx.z    $vf5, $vf1, $vf0x;
    vaddx.x    $vf6, $vf2, $vf0x;
    vaddx.y    $vf7, $vf2, $vf0x;
    vaddx.z    $vf8, $vf2, $vf0x;
    sqc2       $vf3, 0x10($4);
    sqc2       $vf4, 0x20($4);
    sqc2       $vf5, 0x40($4);
    sqc2       $vf6, 0x60($4);
    sqc2       $vf7, 0x50($4);
    jr         $31;
    sqc2      $vf8, 0x30($4);
}

