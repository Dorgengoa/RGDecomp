#include "types.h"

extern void UnpackD_13b080(void);
extern void FpCmpPartsD_13b828(void);

asm void DoubleCmp_13b948(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $4, 0x40($29);
    addiu      $4, $29, 0x40;
    sd         $5, 0x48($29);
    sd         $16, 0x50($29);
    sd         $31, 0x58($29);
    jal        UnpackD_13b080;
    daddu     $5, $29, $0;
    addiu      $16, $29, 0x20;
    addiu      $4, $29, 0x48;
    jal        UnpackD_13b080;
    daddu     $5, $16, $0;
    daddu      $5, $16, $0;
    jal        FpCmpPartsD_13b828;
    daddu     $4, $29, $0;
    ld         $16, 0x50($29);
    ld         $31, 0x58($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

