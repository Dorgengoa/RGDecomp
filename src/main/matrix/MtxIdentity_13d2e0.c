#include "types.h"

asm void MtxIdentity_13d2e0(void)
{
    .set noreorder;
    vmr32.xyzw $vf1, $vf0;
    vmr32.xyzw $vf2, $vf1;
    vmr32.xyzw $vf3, $vf2;
    sqc2       $vf0, 0x30($4);
    sqc2       $vf1, 0x20($4);
    sqc2       $vf2, 0x10($4);
    jr         $31;
    sqc2      $vf3, 0x0($4);
}

