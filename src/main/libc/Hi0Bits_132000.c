#include "types.h"

asm void Hi0Bits_132000(void)
{
    .set noreorder;
    lui        $2, (0xFFFF0000 >> 16);
    and        $2, $4, $2;
    bnez       $2, L00132018;
    daddu     $5, $0, $0;
    addiu      $5, $0, 0x10;
    sll        $4, $4, 16;
  L00132018:
    lui        $2, (0xFF000000 >> 16);
    and        $2, $4, $2;
    bnez       $2, L00132030;
    lui       $2, (0xF0000000 >> 16);
    addiu      $5, $5, 0x8;
    sll        $4, $4, 8;
  L00132030:
    and        $2, $4, $2;
    bnez       $2, L00132044;
    lui       $2, (0xC0000000 >> 16);
    addiu      $5, $5, 0x4;
    sll        $4, $4, 4;
  L00132044:
    and        $2, $4, $2;
    bnez       $2, L00132058;
    nop;
    addiu      $5, $5, 0x2;
    sll        $4, $4, 2;
  L00132058:
    bltz       $4, L00132078;
    daddu     $2, $5, $0;
    lui        $3, (0x40000000 >> 16);
    addiu      $5, $5, 0x1;
    and        $3, $4, $3;
    beqz       $3, L00132078;
    addiu     $2, $0, 0x20;
    daddu      $2, $5, $0;
  L00132078:
    jr         $31;
    nop;
}
