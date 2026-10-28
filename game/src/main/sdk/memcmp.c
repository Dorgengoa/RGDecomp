#include "types.h"

asm void memcmp(void)
{
    .set noreorder;
    sltiu      $2, $6, 0x10;
    bnez       $2, L0013195C;
    or        $2, $4, $5;
    andi       $2, $2, 0xF;
    bnez       $2, L0013195C;
    nop;
  L00131928:
    lq         $3, 0x0($4);
    sltiu      $7, $6, 0x20;
    lq         $2, 0x0($5);
    addiu      $4, $4, 0x10;
    pxor       $8, $2, $3;
    addiu      $2, $5, 0x10;
    pcpyud     $10, $8, $7;
    or         $9, $10, $8;
    movz       $5, $2, $9;
    bnel       $9, $0, L0013195C;
    addiu     $4, $4, -0x10;
    beqz       $7, L00131928;
    addiu     $6, $6, -0x10;
  L0013195C:
    lui        $2, (0xFFFFFFFF >> 16);
    addiu      $6, $6, -0x1;
    ori        $2, $2, (0xFFFFFFFF & 0xFFFF);
    beq        $6, $2, L0013199C;
    nop;
    lui        $7, (0xFFFFFFFF >> 16);
    ori        $7, $7, (0xFFFFFFFF & 0xFFFF);
  L00131978:
    lbu        $3, 0x0($4);
    lbu        $2, 0x0($5);
    beq        $3, $2, L00131990;
    addiu     $4, $4, 0x1;
    jr         $31;
    subu      $2, $3, $2;
  L00131990:
    addiu      $6, $6, -0x1;
    bne        $6, $7, L00131978;
    addiu     $5, $5, 0x1;
  L0013199C:
    jr         $31;
    daddu     $2, $0, $0;
}
