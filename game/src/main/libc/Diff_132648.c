#include "types.h"

extern void Mcmp_1325e0(void);
extern void Balloc_131cf0(void);

asm void Diff_132648(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sd         $18, 0x10($29);
    daddu      $18, $6, $0;
    sd         $19, 0x18($29);
    daddu      $19, $4, $0;
    daddu      $5, $18, $0;
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    jal        Mcmp_1325e0;
    daddu     $4, $17, $0;
    daddu      $16, $2, $0;
    bnez       $16, L001326A0;
    daddu     $4, $19, $0;
    jal        Balloc_131cf0;
    daddu     $5, $0, $0;
    addiu      $3, $0, 0x1;
    daddu      $11, $2, $0;
    sw         $3, 0x10($11);
    b          L001327BC;
    sw        $0, 0x14($11);
  L001326A0:
    bgezl      $16, L001326B8;
    daddu     $16, $0, $0;
    daddu      $11, $17, $0;
    daddu      $17, $18, $0;
    addiu      $16, $0, 0x1;
    daddu      $18, $11, $0;
  L001326B8:
    lw         $5, 0x4($17);
    jal        Balloc_131cf0;
    daddu     $4, $19, $0;
    addiu      $8, $17, 0x14;
    daddu      $11, $2, $0;
    addiu      $9, $18, 0x14;
    sw         $16, 0xC($11);
    addiu      $7, $11, 0x14;
    daddu      $10, $0, $0;
    lw         $12, 0x10($17);
    lw         $2, 0x10($18);
    sll        $3, $12, 2;
    sll        $2, $2, 2;
    addu       $13, $8, $3;
    addu       $6, $9, $2;
    nop;
  L001326F8:
    lw         $5, 0x0($8);
    addiu      $8, $8, 0x4;
    lw         $2, 0x0($9);
    addiu      $9, $9, 0x4;
    andi       $3, $5, 0xFFFF;
    srl        $5, $5, 16;
    andi       $4, $2, 0xFFFF;
    srl        $2, $2, 16;
    subu       $3, $3, $4;
    subu       $5, $5, $2;
    addu       $3, $3, $10;
    sltu       $2, $9, $6;
    sra        $10, $3, 16;
    sh         $3, 0x0($7);
    addu       $5, $5, $10;
    sh         $5, 0x2($7);
    addiu      $7, $7, 0x4;
    bnez       $2, L001326F8;
    sra       $10, $5, 16;
    sltu       $2, $8, $13;
    beql       $2, $0, L00132788;
    addiu     $7, $7, -0x4;
  L00132750:
    lw         $2, 0x0($8);
    addiu      $8, $8, 0x4;
    sltu       $4, $8, $13;
    andi       $3, $2, 0xFFFF;
    srl        $2, $2, 16;
    addu       $3, $3, $10;
    sra        $10, $3, 16;
    sh         $3, 0x0($7);
    addu       $5, $2, $10;
    sh         $5, 0x2($7);
    addiu      $7, $7, 0x4;
    bnez       $4, L00132750;
    sra       $10, $5, 16;
    addiu      $7, $7, -0x4;
  L00132788:
    lw         $2, 0x0($7);
    bnel       $2, $0, L001327B8;
    sw        $12, 0x10($11);
    nop;
  L00132798:
    addiu      $7, $7, -0x4;
    lw         $2, 0x0($7);
    nop;
    nop;
    nop;
    beqz       $2, L00132798;
    addiu     $12, $12, -0x1;
    sw         $12, 0x10($11);
  L001327B8:
    daddu      $2, $11, $0;
  L001327BC:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $31, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
