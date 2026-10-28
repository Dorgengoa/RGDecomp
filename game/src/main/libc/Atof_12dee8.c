#include "types.h"

extern void Strtod_1360d8(void);

asm void Atof_12dee8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $5, $0, $0;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          Strtod_1360d8;
    addiu     $29, $29, 0x10;
}
