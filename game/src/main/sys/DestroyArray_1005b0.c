#include "types.h"

asm void DestroyArray_1005b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x40($29);
    sq         $19, 0x30($29);
    sq         $18, 0x20($29);
    daddu      $19, $5, $0;
    sq         $17, 0x10($29);
    daddu      $18, $6, $0;
    daddu      $17, $7, $0;
    sq         $16, 0x0($29);
    mult       $3, $18, $17;
    beqz       $17, L00100600;
    addu      $16, $4, $3;
  L001005E0:
    subu       $16, $16, $18;
    addiu      $5, $0, -0x1;
    jalr $31, $19;
    daddu     $4, $16, $0;
    addiu      $17, $17, -0x1;
    bnez       $17, L001005E0;
    nop;
    nop;
  L00100600:
    ld         $31, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

