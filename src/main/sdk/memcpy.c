#include "types.h"

asm void memcpy(void)
{
    .set noreorder;
    daddu      $8, $4, $0;
    sltiu      $2, $6, 0x20;
    bnez       $2, L00131A24;
    daddu     $3, $8, $0;
    or         $2, $5, $8;
    andi       $2, $2, 0xF;
    bnel       $2, $0, L00131A28;
    addiu     $6, $6, -0x1;
    daddu      $7, $8, $0;
  L001319CC:
    lq         $3, 0x0($5);
    addiu      $6, $6, -0x20;
    addiu      $5, $5, 0x10;
    sltiu      $4, $6, 0x20;
    sq         $3, 0x0($7);
    addiu      $7, $7, 0x10;
    lq         $2, 0x0($5);
    addiu      $5, $5, 0x10;
    sq         $2, 0x0($7);
    beqz       $4, L001319CC;
    addiu     $7, $7, 0x10;
    sltiu      $2, $6, 0x8;
    bnez       $2, L00131A24;
    daddu     $3, $7, $0;
  L00131A04:
    ld         $3, 0x0($5);
    addiu      $6, $6, -0x8;
    addiu      $5, $5, 0x8;
    sltiu      $2, $6, 0x8;
    sd         $3, 0x0($7);
    beqz       $2, L00131A04;
    addiu     $7, $7, 0x8;
    daddu      $3, $7, $0;
  L00131A24:
    addiu      $6, $6, -0x1;
  L00131A28:
    addiu      $2, $0, -0x1;
    beq        $6, $2, L00131A50;
    daddu     $4, $2, $0;
  L00131A34:
    lbu        $2, 0x0($5);
    addiu      $6, $6, -0x1;
    addiu      $5, $5, 0x1;
    sb         $2, 0x0($3);
    addiu      $3, $3, 0x1;
    bne        $6, $4, L00131A34;
    nop;
  L00131A50:
    jr         $31;
    daddu     $2, $8, $0;
}
