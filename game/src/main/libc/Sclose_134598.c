#include "types.h"

extern void CloseR_12dfe0(void);

asm void Sclose_134598(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    lh         $5, 0xE($4);
    ld         $31, 0x0($29);
    lw         $4, 0x54($4);
    j          CloseR_12dfe0;
    addiu     $29, $29, 0x10;
}

