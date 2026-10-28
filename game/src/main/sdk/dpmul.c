#include "types.h"

extern void UnpackD_13b080(void);
extern void MulDi3_139110(void);
extern void PackD_13afa8(void);

asm void dpmul(void)
{
    .set noreorder;
    addiu      $29, $29, -0xB0;
    sd         $4, 0x60($29);
    addiu      $4, $29, 0x60;
    sd         $5, 0x68($29);
    sd         $16, 0x70($29);
    sd         $17, 0x78($29);
    sd         $18, 0x80($29);
    sd         $19, 0x88($29);
    sd         $20, 0x90($29);
    sd         $21, 0x98($29);
    sd         $22, 0xA0($29);
    sd         $31, 0xA8($29);
    jal        UnpackD_13b080;
    daddu     $5, $29, $0;
    addiu      $16, $29, 0x20;
    addiu      $4, $29, 0x68;
    jal        UnpackD_13b080;
    daddu     $5, $16, $0;
    lw         $4, 0x0($29);
    sltiu      $2, $4, 0x2;
    bnez       $2, L0013B514;
    lw        $2, 0x4($29);
    lw         $3, 0x20($29);
    sltiu      $2, $3, 0x2;
    bnel       $2, $0, L0013B53C;
    lw        $3, 0x24($29);
    xori       $2, $4, 0x4;
    bnez       $2, L0013B4E8;
    xori      $2, $3, 0x4;
    xori       $2, $3, 0x2;
    bnel       $2, $0, L0013B514;
    lw        $2, 0x4($29);
    b          L0013B4FC;
    lui       $2, 0x46;
  L0013B4E8:
    bnez       $2, L0013B508;
    xori      $2, $4, 0x2;
    bnel       $2, $0, L0013B53C;
    lw        $3, 0x24($29);
    lui        $2, 0x46;
  L0013B4FC:
    b          L0013B6B4;
    addiu     $4, $2, -0x75C8;
    nop;
  L0013B508:
    bnez       $2, L0013B530;
    xori      $2, $3, 0x2;
    lw         $2, 0x4($29);
  L0013B514:
    daddu      $4, $29, $0;
    lw         $3, 0x24($29);
    xor        $2, $2, $3;
    sltu       $2, $0, $2;
    b          L0013B6B4;
    sw        $2, 0x4($29);
    nop;
  L0013B530:
    bnez       $2, L0013B558;
    ld        $19, 0x10($29);
    lw         $3, 0x24($29);
  L0013B53C:
    daddu      $4, $16, $0;
    lw         $2, 0x4($29);
    xor        $2, $2, $3;
    sltu       $2, $0, $2;
    b          L0013B6B4;
    sw        $2, 0x24($29);
    nop;
  L0013B558:
    lui        $21, (0xFFFF0000 >> 16);
    dsrl32     $21, $21, 0;
    ld         $18, 0x30($29);
    and        $16, $19, $21;
    dsrl32     $19, $19, 0;
    and        $22, $18, $21;
    dsrl32     $18, $18, 0;
    daddu      $5, $16, $0;
    jal        MulDi3_139110;
    daddu     $4, $22, $0;
    daddu      $4, $18, $0;
    daddu      $5, $16, $0;
    jal        MulDi3_139110;
    daddu     $20, $2, $0;
    daddu      $4, $22, $0;
    daddu      $5, $19, $0;
    jal        MulDi3_139110;
    daddu     $17, $2, $0;
    daddu      $4, $18, $0;
    daddu      $16, $2, $0;
    daddu      $5, $19, $0;
    jal        MulDi3_139110;
    daddu     $16, $17, $16;
    sltu       $17, $16, $17;
    dsll32     $6, $16, 0;
    dsrl32     $16, $16, 0;
    daddu      $6, $20, $6;
    and        $16, $16, $21;
    dsll32     $17, $17, 0;
    daddu      $16, $16, $2;
    lw         $2, 0x4($29);
    sltu       $20, $6, $20;
    lw         $4, 0x8($29);
    lw         $7, 0x28($29);
    daddu      $17, $17, $20;
    lw         $5, 0x24($29);
    daddu      $17, $17, $16;
    addu       $4, $4, $7;
    addiu      $3, $0, -0x1;
    dsrl       $3, $3, 3;
    xor        $2, $2, $5;
    addiu      $4, $4, 0x4;
    sltu       $2, $0, $2;
    sltu       $3, $3, $17;
    sw         $2, 0x44($29);
    beqz       $3, L0013B654;
    sw        $4, 0x48($29);
    ori        $7, $0, 0x8000;
    dsll32     $7, $7, 16;
    addiu      $5, $0, -0x1;
    dsrl       $5, $5, 3;
    andi       $2, $17, 0x1;
  L0013B628:
    dsrl       $17, $17, 1;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    sltu       $3, $5, $17;
    beqz       $2, L0013B648;
    addiu     $4, $4, 0x1;
    dsrl       $6, $6, 1;
    or         $6, $6, $7;
  L0013B648:
    bnez       $3, L0013B628;
    andi      $2, $17, 0x1;
    sw         $4, 0x48($29);
  L0013B654:
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 4;
    sltu       $2, $2, $17;
    bnez       $2, L0013B6A8;
    addiu     $2, $0, 0x3;
    lw         $4, 0x48($29);
    ori        $8, $0, 0x8000;
    dsll32     $8, $8, 16;
    addiu      $7, $0, 0x1;
    addiu      $5, $0, -0x1;
    dsrl       $5, $5, 4;
  L0013B680:
    dsll       $17, $17, 1;
    and        $3, $6, $8;
    or         $2, $17, $7;
    addiu      $4, $4, -0x1;
    movn       $17, $2, $3;
    sltu       $2, $5, $17;
    beqz       $2, L0013B680;
    dsll      $6, $6, 1;
    sw         $4, 0x48($29);
    addiu      $2, $0, 0x3;
  L0013B6A8:
    sd         $17, 0x50($29);
    sw         $2, 0x40($29);
    addiu      $4, $29, 0x40;
  L0013B6B4:
    jal        PackD_13afa8;
    nop;
    ld         $16, 0x70($29);
    ld         $17, 0x78($29);
    ld         $18, 0x80($29);
    ld         $19, 0x88($29);
    ld         $20, 0x90($29);
    ld         $21, 0x98($29);
    ld         $22, 0xA0($29);
    ld         $31, 0xA8($29);
    jr         $31;
    addiu     $29, $29, 0xB0;
}

