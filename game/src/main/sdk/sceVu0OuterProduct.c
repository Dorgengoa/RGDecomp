#include "types.h"

asm void sceVu0OuterProduct(void)
{
    .set noreorder;
    lqc2       $vf4, 0x0($5);
    lqc2       $vf5, 0x0($6);
    vopmula.xyz $ACC, $vf4, $vf5;
    vopmsub.xyz $vf6, $vf5, $vf4;
    vsub.w     $vf6, $vf6, $vf6;
    jr         $31;
    sqc2      $vf6, 0x0($4);
}

