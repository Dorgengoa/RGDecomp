#include "types.h"

extern void Balloc_131cf0(void);
extern void Lo0Bits_132080(void);
extern void Hi0Bits_132000(void);

asm void D2b_132a40(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $16, 0x10($29);
    daddu      $16, $5, $0;
    addiu      $5, $0, 0x1;
    sd         $17, 0x18($29);
    sd         $18, 0x20($29);
    sd         $19, 0x28($29);
    sd         $20, 0x30($29);
    daddu      $20, $6, $0;
    sd         $21, 0x38($29);
    sd         $31, 0x40($29);
    jal        Balloc_131cf0;
    daddu     $21, $7, $0;
    daddu      $19, $2, $0;
    lui        $2, (0x7FFFFFFF >> 16);
    dsra32     $4, $16, 0;
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    and        $2, $4, $2;
    and        $16, $16, $3;
    lui        $3, (0xFFFFF >> 16);
    dsll32     $2, $2, 0;
    ori        $3, $3, (0xFFFFF & 0xFFFF);
    or         $16, $16, $2;
    and        $4, $4, $3;
    dsrl32     $18, $16, 20;
    sw         $4, 0x4($29);
    beqz       $18, L00132AC4;
    addiu     $17, $19, 0x14;
    lui        $2, (0x100000 >> 16);
    or         $2, $4, $2;
    sw         $2, 0x4($29);
  L00132AC4:
    dsll32     $5, $16, 0;
    dsra32     $5, $5, 0;
    beqz       $5, L00132B38;
    daddu     $4, $29, $0;
    jal        Lo0Bits_132080;
    sw        $5, 0x0($29);
    daddu      $5, $2, $0;
    beqz       $5, L00132B10;
    lw        $2, 0x4($29);
    negu       $4, $5;
    lw         $3, 0x0($29);
    sllv       $2, $2, $4;
    or         $3, $3, $2;
    sw         $3, 0x0($17);
    lw         $2, 0x4($29);
    srlv       $2, $2, $5;
    b          L00132B18;
    sw        $2, 0x4($29);
    nop;
  L00132B10:
    lw         $2, 0x0($29);
    sw         $2, 0x0($17);
  L00132B18:
    lw         $4, 0x4($29);
    addiu      $3, $0, 0x1;
    addiu      $2, $0, 0x2;
    movz       $2, $3, $4;
    sw         $4, 0x4($17);
    daddu      $16, $2, $0;
    b          L00132B58;
    sw        $2, 0x10($19);
  L00132B38:
    addiu      $4, $29, 0x4;
    jal        Lo0Bits_132080;
    addiu     $16, $0, 0x1;
    addiu      $4, $0, 0x1;
    lw         $3, 0x4($29);
    addiu      $5, $2, 0x20;
    sw         $3, 0x0($17);
    sw         $4, 0x10($19);
  L00132B58:
    beqz       $18, L00132B78;
    addu      $2, $18, $5;
    addiu      $3, $0, 0x35;
    subu       $3, $3, $5;
    addiu      $2, $2, -0x433;
    b          L00132B98;
    sw        $2, 0x0($20);
    nop;
  L00132B78:
    addiu      $3, $5, -0x432;
    sll        $2, $16, 2;
    sw         $3, 0x0($20);
    addu       $2, $17, $2;
    jal        Hi0Bits_132000;
    lw        $4, -0x4($2);
    sll        $3, $16, 5;
    subu       $3, $3, $2;
  L00132B98:
    sw         $3, 0x0($21);
    daddu      $2, $19, $0;
    ld         $16, 0x10($29);
    ld         $17, 0x18($29);
    ld         $18, 0x20($29);
    ld         $19, 0x28($29);
    ld         $20, 0x30($29);
    ld         $21, 0x38($29);
    ld         $31, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
