#include "types.h"

asm void ConstructNewArray_100710(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $31, 0x50($29);
    sq         $20, 0x40($29);
    sq         $19, 0x30($29);
    daddu      $20, $5, $0;
    sq         $18, 0x20($29);
    daddu      $19, $7, $0;
    sq         $17, 0x10($29);
    daddu      $18, $8, $0;
    sq         $16, 0x0($29);
    beqz       $4, L001007F8;
    daddu     $17, $4, $0;
    sw         $19, 0x0($17);
    sw         $18, 0x4($17);
    sw         $6, 0x8($17);
    beqz       $20, L001007F8;
    addiu     $17, $17, 0x10;
    daddu      $4, $0, $0;
    sw         $6, 0x6C($29);
    sltu       $1, $4, $18;
    daddu      $16, $17, $0;
    sw         $17, 0x60($29);
    sw         $19, 0x64($29);
    sw         $18, 0x68($29);
    beqz       $1, L001007A0;
    sw        $0, 0x70($29);
  L00100778:
    daddu      $4, $16, $0;
    jalr $31, $20;
    addiu     $5, $0, 0x1;
    lw         $2, 0x70($29);
    addu       $16, $16, $19;
    addiu      $4, $2, 0x1;
    sltu       $2, $4, $18;
    bnez       $2, L00100778;
    sw        $4, 0x70($29);
    nop;
  L001007A0:
    lw         $2, 0x68($29);
    sltu       $1, $4, $2;
    beqz       $1, L001007F8;
    nop;
    lw         $2, 0x6C($29);
    beqz       $2, L001007F8;
    nop;
    lw         $3, 0x64($29);
    lw         $2, 0x60($29);
    mult       $3, $3, $4;
    beqz       $4, L001007F8;
    addu      $16, $2, $3;
  L001007D0:
    lw         $3, 0x64($29);
    addiu      $5, $0, -0x1;
    lw         $2, 0x6C($29);
    subu       $16, $16, $3;
    jalr $31, $2;
    daddu     $4, $16, $0;
    lw         $2, 0x70($29);
    addiu      $2, $2, -0x1;
    bnez       $2, L001007D0;
    sw        $2, 0x70($29);
  L001007F8:
    daddu      $2, $17, $0;
    ld         $31, 0x50($29);
    lq         $20, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

