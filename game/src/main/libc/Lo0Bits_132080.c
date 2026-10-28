#include "types.h"

asm void Lo0Bits_132080(void)
{
    .set noreorder;
    lw         $5, 0x0($4);
    andi       $2, $5, 0x7;
    beqz       $2, L001320C0;
    andi      $3, $5, 0x1;
    bnez       $3, L00132134;
    daddu     $2, $0, $0;
    andi       $2, $5, 0x2;
    beqz       $2, L001320B0;
    srl       $3, $5, 1;
    addiu      $2, $0, 0x1;
    jr         $31;
    sw        $3, 0x0($4);
  L001320B0:
    srl        $3, $5, 2;
    addiu      $2, $0, 0x2;
    jr         $31;
    sw        $3, 0x0($4);
  L001320C0:
    andi       $2, $5, 0xFFFF;
    bnez       $2, L001320D4;
    daddu     $3, $0, $0;
    addiu      $3, $0, 0x10;
    srl        $5, $5, 16;
  L001320D4:
    andi       $2, $5, 0xFF;
    bnez       $2, L001320EC;
    andi      $2, $5, 0xF;
    addiu      $3, $3, 0x8;
    srl        $5, $5, 8;
    andi       $2, $5, 0xF;
  L001320EC:
    bnez       $2, L00132100;
    andi      $2, $5, 0x3;
    addiu      $3, $3, 0x4;
    srl        $5, $5, 4;
    andi       $2, $5, 0x3;
  L00132100:
    bnez       $2, L00132114;
    andi      $2, $5, 0x1;
    addiu      $3, $3, 0x2;
    srl        $5, $5, 2;
    andi       $2, $5, 0x1;
  L00132114:
    bnel       $2, $0, L00132130;
    sw        $5, 0x0($4);
    srl        $5, $5, 1;
    addiu      $3, $3, 0x1;
    beqz       $5, L00132134;
    addiu     $2, $0, 0x20;
    sw         $5, 0x0($4);
  L00132130:
    daddu      $2, $3, $0;
  L00132134:
    jr         $31;
    nop;
}
