#include "types.h"

asm void Strupr_136390(void)
{
    .set noreorder;
    lb         $2, 0x0($4);
    daddu      $5, $4, $0;
    beqz       $2, L001363D4;
    lbu       $3, 0x0($4);
  L001363A0:
    sll        $2, $3, 24;
    sra        $2, $2, 24;
    lui        $3, 0x45;
    addu       $3, $3, $2;
    lbu        $3, 0x7E91($3);
    andi       $3, $3, 0x2;
    beqz       $3, L001363C4;
    addiu     $2, $2, -0x20;
    sb         $2, 0x0($5);
  L001363C4:
    addiu      $5, $5, 0x1;
    lbu        $2, 0x0($5);
    bnez       $2, L001363A0;
    daddu     $3, $2, $0;
  L001363D4:
    jr         $31;
    daddu     $2, $4, $0;
}

