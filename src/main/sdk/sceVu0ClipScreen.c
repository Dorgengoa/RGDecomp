#include "types.h"

asm void sceVu0ClipScreen(void)
{
    .set noreorder;
    vsub.xyzw  $vf4, $vf0, $vf0;
    lui        $2, (0x45800000 >> 16);
    dsll       $2, $2, 16;
    ori        $2, $2, 0x4580;
    dsll       $2, $2, 16;
    lqc2       $vf7, 0x0($4);
    qmtc2.ni   $2, $vf6;
    ctc2.ni    $0, $vi16;
    vsub.xyw   $vf5, $vf7, $vf4;
    vsub.xy    $vf5, $vf6, $vf7;
    vnop;
    vnop;
    vnop;
    vnop;
    vnop;
    cfc2.ni    $2, $vi16;
    jr         $31;
    andi      $2, $2, 0xC0;
}

