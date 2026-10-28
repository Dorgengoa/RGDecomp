#include "types.h"

extern void RaiseR_1340c0(void);

asm void Raise_134230(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $31, 0x0($29);
    daddu      $5, $4, $0;
    lw         $4, -0x67A8($2);
    ld         $31, 0x0($29);
    j          RaiseR_1340c0;
    addiu     $29, $29, 0x10;
}

