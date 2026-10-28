#include "types.h"

extern void VfprintfR_1374e0(void);

asm void Vprintf_138e68(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $31, 0x0($29);
    daddu      $6, $5, $0;
    lw         $3, -0x67A8($2);
    daddu      $5, $4, $0;
    ld         $31, 0x0($29);
    lw         $4, 0x8($3);
    j          VfprintfR_1374e0;
    addiu     $29, $29, 0x10;
}

