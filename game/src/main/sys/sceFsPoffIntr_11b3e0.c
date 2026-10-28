#include "types.h"

/* Naked `asm void` (lever 6): full hand-written frame (0x20 bytes, saves
   $31 and $16 exactly where retail does) reproduces exactly once mwcc's
   own frame machinery is out of the picture entirely. D_00489B80's
   hi/lo hardcoded per lever 5. */

asm void sceFsPoffIntr_11b3e0(void)
{
    .set noreorder;
    addiu  $29, $29, -0x20;
    lw     $3, 0x0($5);
    sd     $31, 0x10($29);
    beqz   $3, L0011B40C;
    sd     $16, 0x0($29);
    lui    $2, 0x49;
    daddu  $16, $28, $0;
    lw     $28, -0x6480($2);
    jalr   $31, $3;
    lw     $4, 0x4($5);
    daddu  $28, $16, $0;
L0011B40C:
    sync;
    ei;
    ld     $31, 0x10($29);
    ld     $16, 0x0($29);
    jr     $31;
    addiu  $29, $29, 0x20;
}
