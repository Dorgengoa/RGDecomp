#include "types.h"

extern void UnpackD_13b080(void);

asm void DoubleToUInt_13bb78(void)
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
    beqz       $3, L0013BC0C;
    sltiu     $5, $4, 0x2;
    bnez       $5, L0013BC10;
    ld        $31, 0x30($29);
    lw         $3, 0x4($29);
    bnez       $3, L0013BC10;
    xori      $3, $4, 0x4;
    beqz       $3, L0013BC10;
    addiu     $2, $0, -0x1;
    lw         $4, 0x8($29);
    daddu      $2, $0, $0;
    bltz       $4, L0013BC10;
    slti      $3, $4, 0x20;
    beqz       $3, L0013BC10;
    addiu     $2, $0, -0x1;
    slti       $2, $4, 0x3D;
    bnez       $2, L0013BBF8;
    addiu     $3, $0, 0x3C;
    ld         $2, 0x10($29);
    addiu      $3, $4, -0x3C;
    b          L0013BC04;
    dsllv     $2, $2, $3;
    nop;
  L0013BBF8:
    ld         $2, 0x10($29);
    subu       $3, $3, $4;
    dsrlv      $2, $2, $3;
  L0013BC04:
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
  L0013BC0C:
    ld         $31, 0x30($29);
  L0013BC10:
    jr         $31;
    addiu     $29, $29, 0x40;
}

