#include "types.h"

asm void memchr(void)
{
    .set noreorder;
    sltiu      $2, $6, 0x10;
    bnez       $2, L001318D0;
    andi      $5, $5, 0xFF;
    andi       $2, $4, 0xF;
    bnez       $2, L001318D0;
    daddu     $7, $4, $0;
    dsll       $3, $5, 8;
    lui        $2, (0x1010101 >> 16);
    ori        $2, $2, (0x1010101 & 0xFFFF);
    dsll       $2, $2, 16;
    ori        $2, $2, 0x101;
    dsll       $2, $2, 16;
    ori        $2, $2, 0x101;
    daddu      $10, $3, $5;
    lui        $3, (0x80808080 >> 16);
    ori        $3, $3, (0x80808080 & 0xFFFF);
    dsll       $3, $3, 16;
    ori        $3, $3, 0x8080;
    dsll       $3, $3, 16;
    ori        $3, $3, 0x8080;
    pcpyh      $8, $10;
    pcpyld     $9, $8, $8;
    daddu      $4, $2, $0;
    pcpyld     $8, $3, $3;
  L00131890:
    lq         $2, 0x0($7);
    pxor       $2, $2, $9;
    pcpyld     $10, $4, $4;
    pnor       $3, $0, $2;
    psubb      $2, $2, $10;
    pand       $2, $2, $3;
    pand       $2, $2, $8;
    pcpyud     $3, $2, $9;
    or         $2, $2, $3;
    bnel       $2, $0, L001318D0;
    daddu     $4, $7, $0;
    addiu      $6, $6, -0x10;
    sltiu      $2, $6, 0x10;
    beqz       $2, L00131890;
    addiu     $7, $7, 0x10;
    daddu      $4, $7, $0;
  L001318D0:
    lui        $2, (0xFFFFFFFF >> 16);
    addiu      $6, $6, -0x1;
    ori        $2, $2, (0xFFFFFFFF & 0xFFFF);
    beq        $6, $2, L00131900;
    nop;
    lui        $3, (0xFFFFFFFF >> 16);
    ori        $3, $3, (0xFFFFFFFF & 0xFFFF);
  L001318EC:
    lbu        $2, 0x0($4);
    beq        $2, $5, L00131908;
    addiu     $6, $6, -0x1;
    bne        $6, $3, L001318EC;
    addiu     $4, $4, 0x1;
  L00131900:
    jr         $31;
    daddu     $2, $0, $0;
  L00131908:
    jr         $31;
    daddu     $2, $4, $0;
}
