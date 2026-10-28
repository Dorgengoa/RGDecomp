#include "types.h"

asm void MatFromSRTVu0_13bc90(void)
{
    .set noreorder;
    lqc2       $vf1, 0x0($5);
    lqc2       $vf2, 0x0($6);
    lqc2       $vf3, 0x0($7);
    vcallms    0x0;
    vnop;
    sqc2       $vf4, 0x0($4);
    sqc2       $vf5, 0x10($4);
    sqc2       $vf6, 0x20($4);
    jr         $31;
    sqc2      $vf7, 0x30($4);
}

