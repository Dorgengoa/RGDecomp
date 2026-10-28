#include "types.h"

extern void UnpackD_13b080(void);

asm void dptoli(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $4, 0x20($29);
    addiu      $4, $29, 0x20;
    sd         $31, 0x30($29);
    jal        UnpackD_13b080;
    daddu     $5, $29, $0;
    daddu      $2, $0, $0;
    lw         $4, 0x0($29);
    xori       $3, $4, 0x2;
    beqz       $3, L0013BAE0;
    sltiu     $5, $4, 0x2;
    bnez       $5, L0013BAE4;
    ld        $31, 0x30($29);
    xori       $2, $4, 0x4;
    beqz       $2, L0013BAAC;
    lw        $3, 0x4($29);
    lw         $5, 0x8($29);
    daddu      $2, $0, $0;
    bltz       $5, L0013BAE4;
    slti      $3, $5, 0x1F;
    bnez       $3, L0013BAC0;
    addiu     $3, $0, 0x3C;
    lw         $3, 0x4($29);
  L0013BAAC:
    lui        $2, (0x7FFFFFFF >> 16);
    lui        $4, (0x80000000 >> 16);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    b          L0013BAE0;
    movn      $2, $4, $3;
  L0013BAC0:
    ld         $2, 0x10($29);
    subu       $3, $3, $5;
    lw         $4, 0x4($29);
    dsrlv      $2, $2, $3;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    negu       $3, $2;
    movn       $2, $3, $4;
  L0013BAE0:
    ld         $31, 0x30($29);
  L0013BAE4:
    jr         $31;
    addiu     $29, $29, 0x40;
}

