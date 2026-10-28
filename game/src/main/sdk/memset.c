#include "types.h"

asm void memset(void)
{
    .set noreorder;
    sltiu      $2, $6, 0x8;
    bnez       $2, L00131BE0;
    daddu     $3, $4, $0;
    andi       $2, $4, 0xF;
    bnez       $2, L00131BE0;
    daddu     $7, $4, $0;
    andi       $9, $5, 0xFF;
    sltiu      $10, $6, 0x20;
    daddu      $8, $9, $0;
    dsll       $3, $8, 8;
    or         $8, $3, $9;
    pcpyh      $3, $8;
    bnez       $10, L00131BCC;
    sltiu     $2, $6, 0x8;
    pcpyld     $8, $3, $3;
  L00131B9C:
    sq         $8, 0x0($7);
    addiu      $6, $6, -0x20;
    addiu      $7, $7, 0x10;
    sltiu      $2, $6, 0x20;
    sq         $8, 0x0($7);
    beqz       $2, L00131B9C;
    addiu     $7, $7, 0x10;
    b          L00131BCC;
    sltiu     $2, $6, 0x8;
  L00131BC0:
    addiu      $6, $6, -0x8;
    addiu      $7, $7, 0x8;
    sltiu      $2, $6, 0x8;
  L00131BCC:
    nop;
    nop;
    beql       $2, $0, L00131BC0;
    sd        $3, 0x0($7);
    daddu      $3, $7, $0;
  L00131BE0:
    lui        $2, (0xFFFFFFFF >> 16);
    addiu      $6, $6, -0x1;
    ori        $2, $2, (0xFFFFFFFF & 0xFFFF);
    beq        $6, $2, L00131C18;
    nop;
    lui        $2, (0xFFFFFFFF >> 16);
    ori        $2, $2, (0xFFFFFFFF & 0xFFFF);
  L00131BFC:
    sb         $5, 0x0($3);
    addiu      $6, $6, -0x1;
    addiu      $3, $3, 0x1;
    nop;
    nop;
    bne        $6, $2, L00131BFC;
    nop;
  L00131C18:
    jr         $31;
    daddu     $2, $4, $0;
}
