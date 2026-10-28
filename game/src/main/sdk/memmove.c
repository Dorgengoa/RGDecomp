#include "types.h"

asm void memmove(void)
{
    .set noreorder;
    daddu      $8, $4, $0;
    sltu       $2, $5, $8;
    beqz       $2, L00131AB0;
    daddu     $3, $8, $0;
    addu       $7, $5, $6;
    sltu       $2, $8, $7;
    beqz       $2, L00131AB0;
    addiu     $2, $0, -0x1;
    addu       $3, $8, $6;
    addiu      $6, $6, -0x1;
    beq        $6, $2, L00131B54;
    daddu     $5, $7, $0;
    daddu      $4, $2, $0;
  L00131A8C:
    addiu      $5, $5, -0x1;
    addiu      $3, $3, -0x1;
    lbu        $2, 0x0($5);
    addiu      $6, $6, -0x1;
    sb         $2, 0x0($3);
    bne        $6, $4, L00131A8C;
    nop;
    jr         $31;
    daddu     $2, $8, $0;
  L00131AB0:
    sltiu      $2, $6, 0x20;
    bnel       $2, $0, L00131B2C;
    addiu     $6, $6, -0x1;
    or         $2, $5, $3;
    andi       $2, $2, 0xF;
    bnel       $2, $0, L00131B2C;
    addiu     $6, $6, -0x1;
    daddu      $7, $3, $0;
  L00131AD0:
    lq         $3, 0x0($5);
    addiu      $6, $6, -0x20;
    addiu      $5, $5, 0x10;
    sltiu      $4, $6, 0x20;
    sq         $3, 0x0($7);
    addiu      $7, $7, 0x10;
    lq         $2, 0x0($5);
    addiu      $5, $5, 0x10;
    sq         $2, 0x0($7);
    beqz       $4, L00131AD0;
    addiu     $7, $7, 0x10;
    sltiu      $2, $6, 0x8;
    bnez       $2, L00131B28;
    daddu     $3, $7, $0;
  L00131B08:
    ld         $3, 0x0($5);
    addiu      $6, $6, -0x8;
    addiu      $5, $5, 0x8;
    sltiu      $2, $6, 0x8;
    sd         $3, 0x0($7);
    beqz       $2, L00131B08;
    addiu     $7, $7, 0x8;
    daddu      $3, $7, $0;
  L00131B28:
    addiu      $6, $6, -0x1;
  L00131B2C:
    addiu      $2, $0, -0x1;
    beq        $6, $2, L00131B54;
    daddu     $4, $2, $0;
  L00131B38:
    lbu        $2, 0x0($5);
    addiu      $6, $6, -0x1;
    addiu      $5, $5, 0x1;
    sb         $2, 0x0($3);
    addiu      $3, $3, 0x1;
    bne        $6, $4, L00131B38;
    nop;
  L00131B54:
    jr         $31;
    daddu     $2, $8, $0;
}
