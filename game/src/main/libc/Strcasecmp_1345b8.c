#include "types.h"

asm void Strcasecmp_1345b8(void)
{
    .set noreorder;
    daddu      $8, $4, $0;
    lb         $7, 0x0($8);
    beqz       $7, L00134650;
    daddu     $9, $5, $0;
    lb         $5, 0x0($9);
    addiu      $6, $7, 0x20;
    lui        $2, 0x45;
    addu       $2, $2, $7;
    lbu        $2, 0x7E91($2);
    lui        $3, 0x45;
    addu       $3, $3, $5;
    lbu        $3, 0x7E91($3);
    addiu      $4, $5, 0x20;
    andi       $2, $2, 0x1;
    andi       $3, $3, 0x1;
    movz       $6, $7, $2;
    movz       $4, $5, $3;
    bnel       $6, $4, L00134654;
    lbu       $5, 0x0($8);
    addiu      $8, $8, 0x1;
  L00134608:
    addiu      $9, $9, 0x1;
    lb         $6, 0x0($8);
    beqz       $6, L00134650;
    addiu     $7, $6, 0x20;
    lb         $5, 0x0($9);
    lui        $2, 0x45;
    addu       $2, $2, $6;
    lbu        $2, 0x7E91($2);
    lui        $3, 0x45;
    addu       $3, $3, $5;
    lbu        $3, 0x7E91($3);
    addiu      $4, $5, 0x20;
    andi       $2, $2, 0x1;
    andi       $3, $3, 0x1;
    movn       $6, $7, $2;
    movz       $4, $5, $3;
    beql       $6, $4, L00134608;
    addiu     $8, $8, 0x1;
  L00134650:
    lbu        $5, 0x0($8);
  L00134654:
    lbu        $2, 0x0($9);
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
    jr         $31;
    subu      $2, $5, $2;
}

