#include "types.h"

asm void VecSetOnes_13e180(void)
{
    .set noreorder;
    vmaxw.xyz  $vf1, $vf0, $vf0w;
    vmulx.w    $vf1, $vf0, $vf0x;
    jr         $31;
    sqc2      $vf1, 0x0($4);
}

