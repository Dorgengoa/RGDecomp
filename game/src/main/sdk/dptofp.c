#include "types.h"

extern void UnpackD_13b080(void);
extern void MakeFp_13af38(void);

asm void dptofp(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $4, 0x20($29);
    addiu      $4, $29, 0x20;
    sd         $31, 0x30($29);
    jal        UnpackD_13b080;
    daddu     $5, $29, $0;
    lui        $5, (0x3FFFFFFF >> 16);
    ori        $5, $5, (0x3FFFFFFF & 0xFFFF);
    ld         $2, 0x10($29);
    lw         $4, 0x0($29);
    dsll       $3, $2, 2;
    dsra32     $3, $3, 0;
    and        $2, $2, $5;
    ori        $7, $3, 0x1;
    lw         $6, 0x8($29);
    lw         $5, 0x4($29);
    jal        MakeFp_13af38;
    movz      $7, $3, $2;
    ld         $31, 0x30($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

