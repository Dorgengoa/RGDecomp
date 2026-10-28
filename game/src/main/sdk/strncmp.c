#include "types.h"

asm void strncmp(void)
{
    .set noreorder;
    bnez       $6, L00134DD0;
    or        $3, $4, $5;
  L00134DC8:
    jr         $31;
    daddu     $2, $0, $0;
  L00134DD0:
    andi       $2, $3, 0x7;
    bnez       $2, L00134F2C;
    daddu     $2, $6, $0;
    andi       $2, $3, 0xF;
    sltiu      $7, $6, 0x10;
    lui        $9, (0x1010101 >> 16);
    ori        $9, $9, (0x1010101 & 0xFFFF);
    dsll       $9, $9, 16;
    ori        $9, $9, 0x101;
    dsll       $9, $9, 16;
    ori        $9, $9, 0x101;
    or         $2, $2, $7;
    bnez       $2, L00134EA8;
    daddu     $7, $4, $0;
    lq         $3, 0x0($4);
    pcpyld     $10, $9, $9;
    lq         $2, 0x0($5);
    lui        $8, (0x80808080 >> 16);
    ori        $8, $8, (0x80808080 & 0xFFFF);
    dsll       $8, $8, 16;
    ori        $8, $8, 0x8080;
    dsll       $8, $8, 16;
    ori        $8, $8, 0x8080;
    psubw      $3, $3, $2;
    pcpyld     $9, $8, $8;
    pcpyud     $2, $3, $4;
    daddu      $8, $5, $0;
    or         $3, $2, $3;
    bnez       $3, L00134F2C;
    daddu     $2, $6, $0;
    addiu      $6, $6, -0x10;
  L00134E4C:
    beqz       $6, L00134DC8;
    nop;
    lq         $2, 0x0($7);
    pnor       $3, $0, $2;
    psubb      $2, $2, $10;
    pand       $2, $2, $3;
    pand       $3, $2, $9;
    pcpyud     $2, $3, $4;
    or         $2, $2, $3;
    bnez       $2, L00134DC8;
    addiu     $7, $7, 0x10;
    sltiu      $2, $6, 0x10;
    lq         $3, 0x0($7);
    bnez       $2, L00134F20;
    addiu     $8, $8, 0x10;
    lq         $2, 0x0($8);
    psubw      $3, $3, $2;
    pcpyud     $2, $3, $4;
    or         $2, $2, $3;
    beql       $2, $0, L00134E4C;
    addiu     $6, $6, -0x10;
    b          L00134F24;
    daddu     $4, $7, $0;
  L00134EA8:
    sltiu      $2, $6, 0x8;
    bnez       $2, L00134F20;
    daddu     $8, $5, $0;
    ld         $3, 0x0($4);
    ld         $2, 0x0($5);
    bne        $3, $2, L00134F2C;
    daddu     $2, $6, $0;
    addiu      $6, $6, -0x8;
    lui        $10, (0x80808080 >> 16);
    ori        $10, $10, (0x80808080 & 0xFFFF);
    dsll       $10, $10, 16;
    ori        $10, $10, 0x8080;
    dsll       $10, $10, 16;
    ori        $10, $10, 0x8080;
  L00134EE0:
    beqz       $6, L00134DC8;
    nop;
    ld         $2, 0x0($7);
    nor        $3, $0, $2;
    dsubu      $2, $2, $9;
    and        $2, $2, $3;
    and        $2, $2, $10;
    bnez       $2, L00134DC8;
    addiu     $7, $7, 0x8;
    sltiu      $2, $6, 0x8;
    bnez       $2, L00134F20;
    addiu     $8, $8, 0x8;
    ld         $3, 0x0($7);
    ld         $2, 0x0($8);
    beql       $3, $2, L00134EE0;
    addiu     $6, $6, -0x8;
  L00134F20:
    daddu      $4, $7, $0;
  L00134F24:
    daddu      $5, $8, $0;
    daddu      $2, $6, $0;
  L00134F2C:
    beqz       $2, L00134F68;
    addiu     $6, $6, -0x1;
    b          L00134F5C;
    lb        $3, 0x0($4);
    nop;
  L00134F40:
    beqz       $6, L00134DC8;
    nop;
    beqz       $7, L00134DC8;
    addiu     $4, $4, 0x1;
    addiu      $5, $5, 0x1;
    lb         $3, 0x0($4);
    addiu      $6, $6, -0x1;
  L00134F5C:
    lb         $2, 0x0($5);
    beq        $3, $2, L00134F40;
    lbu       $7, 0x0($4);
  L00134F68:
    lbu        $2, 0x0($5);
    lbu        $3, 0x0($4);
    jr         $31;
    subu      $2, $3, $2;
}

