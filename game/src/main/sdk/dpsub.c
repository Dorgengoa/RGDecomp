#include "types.h"

extern void UnpackD_13b080(void);
extern void FpaddParts_13b140(void);
extern void PackD_13afa8(void);

asm void dpsub(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $4, 0x60($29);
    addiu      $4, $29, 0x60;
    sd         $5, 0x68($29);
    sd         $16, 0x70($29);
    sd         $31, 0x78($29);
    jal        UnpackD_13b080;
    daddu     $5, $29, $0;
    addiu      $16, $29, 0x20;
    addiu      $4, $29, 0x68;
    jal        UnpackD_13b080;
    daddu     $5, $16, $0;
    daddu      $5, $16, $0;
    lw         $2, 0x24($29);
    daddu      $4, $29, $0;
    addiu      $6, $29, 0x40;
    xori       $2, $2, 0x1;
    jal        FpaddParts_13b140;
    sw        $2, 0x24($29);
    jal        PackD_13afa8;
    daddu     $4, $2, $0;
    ld         $16, 0x70($29);
    ld         $31, 0x78($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

