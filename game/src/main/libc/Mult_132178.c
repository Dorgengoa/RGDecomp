#include "types.h"

extern void Balloc_131cf0(void);

asm void Mult_132178(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $18, 0x10($29);
    daddu      $18, $6, $0;
    sd         $17, 0x8($29);
    sd         $19, 0x18($29);
    sd         $20, 0x20($29);
    sd         $31, 0x28($29);
    lw         $19, 0x10($16);
    lw         $17, 0x10($18);
    slt        $2, $19, $17;
    beql       $2, $0, L001321C8;
    lw        $5, 0x8($16);
    daddu      $24, $16, $0;
    daddu      $16, $18, $0;
    daddu      $18, $24, $0;
    daddu      $19, $17, $0;
    lw         $17, 0x10($18);
    lw         $5, 0x8($16);
  L001321C8:
    addu       $20, $19, $17;
    lw         $2, 0x4($16);
    slt        $5, $5, $20;
    jal        Balloc_131cf0;
    addu      $5, $2, $5;
    sll        $25, $20, 2;
    daddu      $24, $2, $0;
    addiu      $15, $24, 0x14;
    addu       $13, $15, $25;
    sltu       $2, $15, $13;
    beqz       $2, L0013221C;
    daddu     $8, $15, $0;
    sw         $0, 0x0($8);
    nop;
  L00132200:
    addiu      $8, $8, 0x4;
    sltu       $2, $8, $13;
    nop;
    nop;
    nop;
    bnel       $2, $0, L00132200;
    sw        $0, 0x0($8);
  L0013221C:
    addiu      $11, $18, 0x14;
    sll        $2, $17, 2;
    addu       $17, $11, $2;
    sll        $2, $19, 2;
    addiu      $13, $16, 0x14;
    sltu       $3, $11, $17;
    addu       $14, $13, $2;
    beqz       $3, L00132334;
    daddu     $12, $15, $0;
  L00132240:
    lw         $2, 0x0($11);
    andi       $9, $2, 0xFFFF;
    beqz       $9, L001322B0;
    daddu     $7, $12, $0;
    daddu      $8, $13, $0;
    daddu      $10, $0, $0;
  L00132258:
    lw         $3, 0x0($8);
    addiu      $8, $8, 0x4;
    lw         $5, 0x0($7);
    sltu       $6, $8, $14;
    andi       $2, $3, 0xFFFF;
    srl        $3, $3, 16;
    mult       $2, $2, $9;
    mult1      $3, $3, $9;
    andi       $4, $5, 0xFFFF;
    srl        $5, $5, 16;
    addu       $2, $2, $4;
    addu       $3, $3, $5;
    addu       $2, $2, $10;
    srl        $10, $2, 16;
    sh         $2, 0x0($7);
    addu       $2, $3, $10;
    sh         $2, 0x2($7);
    addiu      $7, $7, 0x4;
    bnez       $6, L00132258;
    srl       $10, $2, 16;
    sw         $10, 0x0($7);
    lw         $2, 0x0($11);
  L001322B0:
    srl        $9, $2, 16;
    beqz       $9, L00132324;
    daddu     $7, $12, $0;
    daddu      $8, $13, $0;
    lw         $2, 0x0($7);
    daddu      $10, $0, $0;
    daddu      $4, $2, $0;
    nop;
  L001322D0:
    lw         $3, 0x0($8);
    addiu      $8, $8, 0x4;
    sh         $2, 0x0($7);
    srl        $4, $4, 16;
    andi       $2, $3, 0xFFFF;
    srl        $3, $3, 16;
    mult       $2, $2, $9;
    mult1      $3, $3, $9;
    sltu       $5, $8, $14;
    addu       $2, $2, $4;
    addu       $2, $2, $10;
    sh         $2, 0x2($7);
    addiu      $7, $7, 0x4;
    lw         $4, 0x0($7);
    srl        $10, $2, 16;
    andi       $2, $4, 0xFFFF;
    addu       $3, $3, $2;
    addu       $2, $3, $10;
    bnez       $5, L001322D0;
    srl       $10, $2, 16;
    sw         $2, 0x0($7);
  L00132324:
    addiu      $11, $11, 0x4;
    sltu       $2, $11, $17;
    bnez       $2, L00132240;
    addiu     $12, $12, 0x4;
  L00132334:
    addu       $7, $15, $25;
  L00132338:
    blezl      $20, L00132360;
    sw        $20, 0x10($24);
    addiu      $7, $7, -0x4;
    lw         $2, 0x0($7);
    nop;
    nop;
    nop;
    beql       $2, $0, L00132338;
    addiu     $20, $20, -0x1;
    sw         $20, 0x10($24);
  L00132360:
    daddu      $2, $24, $0;
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
