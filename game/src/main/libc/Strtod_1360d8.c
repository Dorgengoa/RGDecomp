#include "types.h"

extern void StrtodR_1351c0(void);

asm void Strtod_1360d8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $31, 0x0($29);
    daddu      $6, $5, $0;
    daddu      $5, $4, $0;
    lw         $4, -0x67A8($2);
    ld         $31, 0x0($29);
    j          StrtodR_1351c0;
    addiu     $29, $29, 0x10;
}

