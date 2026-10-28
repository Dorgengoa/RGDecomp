#include "types.h"

asm void VecSetOnes4_13e170(void)
{
    .set noreorder;
    vmaxw.xyzw $vf1, $vf0, $vf0w;
    jr         $31;
    sqc2      $vf1, 0x0($4);
}

