#include "types.h"

asm void MatRotateVu0_13bc20(void)
{
    .set noreorder;
    lqc2       $vf2, 0x0($5);
    vaddw.xyz  $vf1, $vf0, $vf0w;
    vmulx.xyzw $vf3, $vf0, $vf0x;
    vcallms    0x0;
    vnop;
    lqc2       $vf10, 0x0($4);
    lqc2       $vf11, 0x10($4);
    lqc2       $vf12, 0x20($4);
    lqc2       $vf13, 0x30($4);
    vmulax.xyzw $ACC, $vf4, $vf10x;
    vmadday.xyzw $ACC, $vf5, $vf10y;
    vmaddz.xyzw $vf20, $vf6, $vf10z;
    vmulax.xyzw $ACC, $vf4, $vf11x;
    vmadday.xyzw $ACC, $vf5, $vf11y;
    vmaddz.xyzw $vf21, $vf6, $vf11z;
    vmulax.xyzw $ACC, $vf4, $vf12x;
    vmadday.xyzw $ACC, $vf5, $vf12y;
    vmaddz.xyzw $vf22, $vf6, $vf12z;
    vmulax.xyzw $ACC, $vf4, $vf13x;
    vmadday.xyzw $ACC, $vf5, $vf13y;
    vmaddaz.xyzw $ACC, $vf6, $vf13z;
    vmaddw.xyzw $vf23, $vf7, $vf13w;
    sqc2       $vf20, 0x0($4);
    sqc2       $vf21, 0x10($4);
    sqc2       $vf22, 0x20($4);
    jr         $31;
    sqc2      $vf23, 0x30($4);
}

