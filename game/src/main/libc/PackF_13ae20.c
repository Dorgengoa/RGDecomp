#include "types.h"

asm void PackF_13ae20(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    daddu      $7, $0, $0;
    lw         $5, 0xC($4);
    xori       $2, $2, 0x2;
    beqz       $2, L0013AE74;
    lw        $8, 0x4($4);
    beqz       $5, L0013AE88;
    lui       $2, (0x7FFFFF >> 16);
    lw         $4, 0x8($4);
    slti       $2, $4, -0x7E;
    bnel       $2, $0, L0013AE84;
    daddu     $5, $0, $0;
    slti       $2, $4, 0x81;
    beql       $2, $0, L0013AE74;
    addiu     $7, $0, 0xFF;
    addiu      $2, $0, 0x80;
    bne        $4, $2, L0013AE80;
    addiu     $7, $4, 0x7F;
    bgezl      $5, L0013AE84;
    srl       $5, $5, 7;
    addiu      $7, $0, 0xFF;
  L0013AE74:
    b          L0013AE84;
    daddu     $5, $0, $0;
    nop;
  L0013AE80:
    srl        $5, $5, 7;
  L0013AE84:
    lui        $2, (0x7FFFFF >> 16);
  L0013AE88:
    lui        $3, (0xFF800000 >> 16);
    ori        $2, $2, (0x7FFFFF & 0xFFFF);
    and        $6, $6, $3;
    and        $2, $5, $2;
    lui        $3, (0x807FFFFF >> 16);
    or         $6, $6, $2;
    lui        $2, (0x7FFFFFFF >> 16);
    ori        $3, $3, (0x807FFFFF & 0xFFFF);
    andi       $4, $7, 0xFF;
    and        $6, $6, $3;
    sll        $3, $8, 31;
    sll        $4, $4, 23;
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    or         $6, $6, $4;
    and        $6, $6, $2;
    or         $6, $6, $3;
    mtc1       $6, $f0;
    jr         $31;
    nop;
}

