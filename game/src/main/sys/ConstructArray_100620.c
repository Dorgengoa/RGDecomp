#include "types.h"

asm void ConstructArray_100620(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $31, 0x40($29);
    sq         $19, 0x30($29);
    sq         $18, 0x20($29);
    daddu      $19, $5, $0;
    sq         $17, 0x10($29);
    daddu      $18, $7, $0;
    daddu      $17, $8, $0;
    daddu      $5, $0, $0;
    sq         $16, 0x0($29);
    sltu       $1, $5, $17;
    sw         $6, 0x5C($29);
    daddu      $16, $4, $0;
    sw         $4, 0x50($29);
    sw         $18, 0x54($29);
    sw         $17, 0x58($29);
    beqz       $1, L00100690;
    sw        $0, 0x60($29);
  L00100668:
    daddu      $4, $16, $0;
    jalr $31, $19;
    addiu     $5, $0, 0x1;
    lw         $3, 0x60($29);
    addu       $16, $16, $18;
    addiu      $5, $3, 0x1;
    sltu       $3, $5, $17;
    bnez       $3, L00100668;
    sw        $5, 0x60($29);
    nop;
  L00100690:
    lw         $3, 0x58($29);
    sltu       $1, $5, $3;
    beqz       $1, L001006E8;
    nop;
    lw         $3, 0x5C($29);
    beqz       $3, L001006E8;
    nop;
    lw         $4, 0x54($29);
    lw         $3, 0x50($29);
    mult       $4, $4, $5;
    beqz       $5, L001006E8;
    addu      $16, $3, $4;
  L001006C0:
    lw         $3, 0x54($29);
    addiu      $5, $0, -0x1;
    lw         $2, 0x5C($29);
    subu       $16, $16, $3;
    jalr $31, $2;
    daddu     $4, $16, $0;
    lw         $3, 0x60($29);
    addiu      $3, $3, -0x1;
    bnez       $3, L001006C0;
    sw        $3, 0x60($29);
  L001006E8:
    ld         $31, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

