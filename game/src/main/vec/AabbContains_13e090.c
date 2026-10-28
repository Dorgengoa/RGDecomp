#include "types.h"

asm void AabbContains_13e090(void)
{
    .set noreorder;
    lqc2       $vf10, 0x0($4);
    lqc2       $vf11, 0x0($5);
    lqc2       $vf1, 0x0($6);
    lqc2       $vf2, 0x0($7);
    ctc2.ni    $0, $vi16;
    vsub.xyz   $vf25, $vf1, $vf10;
    vsub.xyz   $vf25, $vf11, $vf2;
    vnop;
    vnop;
    vnop;
    vnop;
    vnop;
    cfc2.ni    $2, $vi16;
    andi       $2, $2, 0x80;
    xor        $2, $2, $0;
    jr         $31;
    sltiu     $2, $2, 0x1;
}

