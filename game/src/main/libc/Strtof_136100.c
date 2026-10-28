#include "types.h"

extern void Strtod_1360d8(void);
extern void dptofp(void);

asm void Strtof_136100(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        Strtod_1360d8;
    nop;
    daddu      $4, $2, $0;
    jal        dptofp;
    nop;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

