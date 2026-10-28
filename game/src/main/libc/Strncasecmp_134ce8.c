#include "types.h"

asm void Strncasecmp_134ce8(void)
{
    .set noreorder;
    daddu      $10, $6, $0;
    daddu      $11, $4, $0;
    daddu      $12, $5, $0;
    beqz       $10, L00134DB8;
    daddu     $2, $0, $0;
    addiu      $13, $0, -0x1;
    b          L00134D2C;
    addiu     $10, $10, -0x1;
  L00134D08:
    beql       $10, $0, L00134D80;
    lbu       $5, 0x0($11);
    beql       $9, $0, L00134D80;
    lbu       $5, 0x0($11);
    beql       $8, $0, L00134D80;
    lbu       $5, 0x0($11);
    addiu      $10, $10, -0x1;
    addiu      $11, $11, 0x1;
    addiu      $12, $12, 0x1;
  L00134D2C:
    beql       $10, $13, L00134D80;
    lbu       $5, 0x0($11);
    lb         $9, 0x0($11);
    lb         $8, 0x0($12);
    lui        $5, 0x45;
    addu       $5, $5, $9;
    lbu        $5, 0x7E91($5);
    addiu      $7, $9, 0x20;
    lui        $3, 0x45;
    addu       $3, $3, $8;
    lbu        $3, 0x7E91($3);
    daddu      $4, $9, $0;
    andi       $5, $5, 0x1;
    addiu      $6, $8, 0x20;
    andi       $3, $3, 0x1;
    daddu      $2, $8, $0;
    movn       $4, $7, $5;
    movn       $2, $6, $3;
    beq        $4, $2, L00134D08;
    nop;
    lbu        $5, 0x0($11);
  L00134D80:
    lbu        $2, 0x0($12);
    lui        $4, 0x45;
    addu       $4, $4, $5;
    lbu        $4, 0x7E91($4);
    addiu      $7, $5, 0x20;
    lui        $3, 0x45;
    addu       $3, $3, $2;
    lbu        $3, 0x7E91($3);
    addiu      $6, $2, 0x20;
    andi       $4, $4, 0x1;
    andi       $3, $3, 0x1;
    movn       $5, $7, $4;
    movn       $2, $6, $3;
    subu       $2, $5, $2;
  L00134DB8:
    jr         $31;
    nop;
}

