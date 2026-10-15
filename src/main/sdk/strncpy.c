#include "types.h"

asm void strncpy(void)
{
    .set noreorder;
    daddu      $8, $4, $0;
    or         $7, $5, $4;
    addiu      $10, $0, 0x10;
    andi       $2, $7, 0x7;
    addiu      $9, $0, 0x8;
    bnez       $2, L001350E0;
    andi      $2, $7, 0xF;
    movz       $9, $10, $2;
    bnez       $2, L0013504C;
    sltu      $2, $6, $9;
    bnez       $2, L001350E0;
    nop;
    lui        $7, (0x1010101 >> 16);
    ori        $7, $7, (0x1010101 & 0xFFFF);
    dsll       $7, $7, 16;
    ori        $7, $7, 0x101;
    dsll       $7, $7, 16;
    ori        $7, $7, 0x101;
    lq         $3, 0x0($5);
    pcpyld     $9, $7, $7;
    pnor       $3, $0, $3;
    lui        $7, (0x80808080 >> 16);
    ori        $7, $7, (0x80808080 & 0xFFFF);
    dsll       $7, $7, 16;
    ori        $7, $7, 0x8080;
    dsll       $7, $7, 16;
    ori        $7, $7, 0x8080;
    psubb      $2, $3, $9;
    pcpyld     $10, $7, $7;
    pand       $2, $2, $3;
    pand       $2, $2, $10;
    pcpyud     $3, $2, $4;
    or         $3, $2, $3;
    bnez       $3, L001350DC;
    daddu     $7, $8, $0;
    lq         $3, 0x0($5);
    addiu      $6, $6, -0x10;
    addiu      $5, $5, 0x10;
    sltiu      $2, $6, 0x10;
    sq         $3, 0x0($7);
    bnez       $2, L001350DC;
    addiu     $7, $7, 0x10;
    lq         $2, 0x0($5);
    pnor       $3, $0, $2;
    psubb      $2, $2, $9;
    pand       $2, $2, $3;
    pand       $2, $2, $10;
    pcpyud     $3, $2, $4;
    or         $2, $2, $3;
    beql       $2, $0, L001350A8;
    lq        $3, 0x0($5);
    b          L001350E0;
    daddu     $4, $7, $0;
  L0013504C:
    bnez       $2, L001350E0;
    nop;
    ld         $3, 0x0($5);
    lui        $9, (0x1010101 >> 16);
    ori        $9, $9, (0x1010101 & 0xFFFF);
    dsll       $9, $9, 16;
    ori        $9, $9, 0x101;
    dsll       $9, $9, 16;
    ori        $9, $9, 0x101;
    lui        $10, (0x80808080 >> 16);
    ori        $10, $10, (0x80808080 & 0xFFFF);
    dsll       $10, $10, 16;
    ori        $10, $10, 0x8080;
    dsll       $10, $10, 16;
    ori        $10, $10, 0x8080;
    dsubu      $2, $3, $9;
    nor        $3, $0, $3;
    and        $2, $2, $3;
    and        $2, $2, $10;
    bnez       $2, L001350DC;
    daddu     $7, $8, $0;
    ld         $3, 0x0($5);
    nop;
  L001350A8:
    addiu      $6, $6, -0x8;
    addiu      $5, $5, 0x8;
    sltiu      $2, $6, 0x8;
    sd         $3, 0x0($7);
    bnez       $2, L001350DC;
    addiu     $7, $7, 0x8;
    ld         $2, 0x0($5);
    nor        $3, $0, $2;
    dsubu      $2, $2, $9;
    and        $2, $2, $3;
    and        $2, $2, $10;
    beql       $2, $0, L001350A8;
    ld        $3, 0x0($5);
  L001350DC:
    daddu      $4, $7, $0;
  L001350E0:
    beqz       $6, L0013512C;
    daddu     $2, $6, $0;
    lbu        $2, 0x0($5);
    addiu      $6, $6, -0x1;
    addiu      $5, $5, 0x1;
    sb         $2, 0x0($4);
    sll        $2, $2, 24;
    bnez       $2, L001350E0;
    addiu     $4, $4, 0x1;
    daddu      $2, $6, $0;
    beqz       $2, L0013512C;
    addiu     $6, $6, -0x1;
  L00135110:
    sb         $0, 0x0($4);
    daddu      $2, $6, $0;
    addiu      $4, $4, 0x1;
    addiu      $6, $6, -0x1;
    nop;
    bnez       $2, L00135110;
    nop;
  L0013512C:
    jr         $31;
    daddu     $2, $8, $0;
}

