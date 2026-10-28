#include "types.h"

asm void iAllocTimerCounter_121888(void)
{
    .set noreorder;
    lui        $2, 0x44;
    addiu      $7, $2, 0x78A8;
    lw         $6, 0x14($7);
    bnez       $6, L001218A8;
    nop;
    lui        $2, (0x80008005 >> 16);
    jr         $31;
    ori       $2, $2, (0x80008005 & 0xFFFF);
  L001218A8:
    lw         $2, 0x10($7);
    sll        $5, $6, 4;
    lw         $4, 0x0($6);
    addiu      $2, $2, 0x1;
    sw         $0, 0x28($6);
    sw         $2, 0x10($7);
    sw         $0, 0xC($6);
    sw         $4, 0x14($7);
    lw         $3, 0xC($7);
    sd         $0, 0x18($6);
    addiu      $3, $3, 0x1;
    sw         $3, 0xC($7);
    lw         $2, 0xC($7);
    sll        $2, $2, 1;
    andi       $2, $2, 0x3FE;
    ori        $2, $2, 0x1;
    sw         $2, 0x8($6);
    lw         $2, 0x8($6);
    jr         $31;
    or        $2, $5, $2;
}
