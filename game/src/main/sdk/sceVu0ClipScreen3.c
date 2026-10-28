#include "types.h"

asm void sceVu0ClipScreen3(void)
{
    .set noreorder;
    vsub.xyzw  $vf4, $vf0, $vf0;
    lui        $2, (0x45800000 >> 16);
    dsll       $2, $2, 16;
    ori        $2, $2, 0x4580;
    dsll       $2, $2, 16;
    lqc2       $vf6, 0x0($4);
    lqc2       $vf8, 0x0($5);
    lqc2       $vf9, 0x0($6);
    qmtc2.ni   $2, $vf7;
    ctc2.ni    $0, $vi16;
    vsub.xyw   $vf5, $vf6, $vf4;
    vsub.xy    $vf5, $vf7, $vf6;
    vsub.xyw   $vf5, $vf8, $vf4;
    vsub.xy    $vf5, $vf7, $vf8;
    vsub.xyw   $vf5, $vf9, $vf4;
    vsub.xy    $vf5, $vf7, $vf9;
    vnop;
    vnop;
    vnop;
    vnop;
    vnop;
    cfc2.ni    $2, $vi16;
    jr         $31;
    andi      $2, $2, 0xC0;
}

