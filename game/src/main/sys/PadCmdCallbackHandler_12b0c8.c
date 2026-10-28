#include "types.h"

/* Sibling of sceFsPoffIntr_11b3e0 (naked `asm void`, lever 6). D_00449510 and
   D_0048EFC0 hardcoded per lever 5. */

asm void PadCmdCallbackHandler_12b0c8(void)
{
    .set noreorder;
    lui    $2, 0x45;
    addiu  $29, $29, -0x20;
    lw     $3, -0x6AF0($2);
    sd     $31, 0x10($29);
    beqz   $3, L0012B0F8;
    sd     $16, 0x0($29);
    lui    $2, 0x49;
    daddu  $16, $28, $0;
    lw     $28, -0x1040($2);
    jalr   $31, $3;
    lw     $4, 0xC($4);
    daddu  $28, $16, $0;
L0012B0F8:
    sync;
    ei;
    ld     $31, 0x10($29);
    ld     $16, 0x0($29);
    jr     $31;
    addiu  $29, $29, 0x20;
}
