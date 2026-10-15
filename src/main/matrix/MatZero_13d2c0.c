#include "types.h"

asm void MatZero_13d2c0(void)
{
    .set noreorder;
    vsub.xyzw  $vf1, $vf1, $vf1;
    sqc2       $vf1, 0x30($4);
    sqc2       $vf1, 0x20($4);
    sqc2       $vf1, 0x10($4);
    jr         $31;
    sqc2      $vf1, 0x0($4);
}

