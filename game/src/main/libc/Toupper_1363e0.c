#include "types.h"

asm void Toupper_1363e0(void)
{
    .set noreorder;
    daddu      $2, $4, $0;
    lui        $3, 0x45;
    addu       $3, $3, $2;
    lbu        $3, 0x7E91($3);
    addiu      $4, $2, -0x20;
    andi       $3, $3, 0x2;
    jr         $31;
    movn      $2, $4, $3;
}

