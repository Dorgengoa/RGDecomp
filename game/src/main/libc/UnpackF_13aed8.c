#include "types.h"

asm void UnpackF_13aed8(void)
{
    .set noreorder;
    lw         $3, 0x0($4);
    lui        $4, (0x7FFFFF >> 16);
    ori        $4, $4, (0x7FFFFF & 0xFFFF);
    daddu      $6, $5, $0;
    srl        $2, $3, 23;
    srl        $5, $3, 31;
    andi       $2, $2, 0xFF;
    and        $3, $3, $4;
    sw         $5, 0x4($6);
    addiu      $5, $2, -0x7F;
    bnez       $2, L0013AF18;
    sll       $4, $3, 7;
    addiu      $2, $0, 0x2;
    jr         $31;
    sw        $2, 0x0($6);
    nop;
  L0013AF18:
    lui        $2, (0x40000000 >> 16);
    addiu      $3, $0, 0x3;
    or         $2, $4, $2;
    sw         $5, 0x8($6);
    sw         $3, 0x0($6);
    jr         $31;
    sw        $2, 0xC($6);
}

