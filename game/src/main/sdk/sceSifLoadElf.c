#include "types.h"

extern void _sceSifLoadElfPart(void);

asm void sceSifLoadElf(void)
{
    .set noreorder;
    daddu      $6, $5, $0;
    addiu      $29, $29, -0x10;
    lui        $5, 0x45;
    sd         $31, 0x0($29);
    addiu      $5, $5, 0x6BF8;
    jal        _sceSifLoadElfPart;
    addiu     $7, $0, 0x1;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
