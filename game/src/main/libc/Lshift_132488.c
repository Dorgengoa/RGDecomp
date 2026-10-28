#include "types.h"

extern void Balloc_131cf0(void);
extern void _Bfree(void);

asm void Lshift_132488(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $16, 0x0($29);
    daddu      $16, $6, $0;
    sd         $17, 0x8($29);
    sra        $17, $16, 5;
    sd         $18, 0x10($29);
    sd         $19, 0x18($29);
    daddu      $19, $5, $0;
    sd         $21, 0x28($29);
    daddu      $21, $4, $0;
    sd         $20, 0x20($29);
    sd         $31, 0x30($29);
    lw         $3, 0x10($19);
    lw         $6, 0x8($19);
    addu       $3, $17, $3;
    addiu      $18, $3, 0x1;
    slt        $2, $6, $18;
    beqz       $2, L001324F4;
    lw        $5, 0x4($19);
    nop;
  L001324D8:
    sll        $6, $6, 1;
    slt        $2, $6, $18;
    nop;
    nop;
    nop;
    bnez       $2, L001324D8;
    addiu     $5, $5, 0x1;
  L001324F4:
    jal        Balloc_131cf0;
    daddu     $4, $21, $0;
    daddu      $20, $2, $0;
    blez       $17, L0013252C;
    addiu     $7, $20, 0x14;
    daddu      $6, $17, $0;
    nop;
  L00132510:
    addiu      $6, $6, -0x1;
    sw         $0, 0x0($7);
    nop;
    nop;
    nop;
    bnez       $6, L00132510;
    addiu     $7, $7, 0x4;
  L0013252C:
    lw         $2, 0x10($19);
    addiu      $4, $19, 0x14;
    andi       $16, $16, 0x1F;
    sll        $2, $2, 2;
    beqz       $16, L00132588;
    addu      $6, $4, $2;
    addiu      $2, $0, 0x20;
    daddu      $3, $0, $0;
    subu       $5, $2, $16;
  L00132550:
    lw         $2, 0x0($4);
    sllv       $2, $2, $16;
    or         $2, $2, $3;
    sw         $2, 0x0($7);
    addiu      $7, $7, 0x4;
    lw         $3, 0x0($4);
    addiu      $4, $4, 0x4;
    sltu       $2, $4, $6;
    bnez       $2, L00132550;
    srlv      $3, $3, $5;
    beqz       $3, L001325A4;
    sw        $3, 0x0($7);
    b          L001325A4;
    addiu     $18, $18, 0x1;
  L00132588:
    lw         $2, 0x0($4);
    addiu      $4, $4, 0x4;
    sltu       $3, $4, $6;
    sw         $2, 0x0($7);
    nop;
    bnez       $3, L00132588;
    addiu     $7, $7, 0x4;
  L001325A4:
    addiu      $2, $18, -0x1;
    daddu      $4, $21, $0;
    sw         $2, 0x10($20);
    jal        _Bfree;
    daddu     $5, $19, $0;
    daddu      $2, $20, $0;
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $21, 0x28($29);
    ld         $31, 0x30($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
