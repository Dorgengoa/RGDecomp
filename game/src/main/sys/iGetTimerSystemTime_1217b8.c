#include "types.h"

asm void iGetTimerSystemTime_1217b8(void)
{
    .set noreorder;
    lui        $3, (0x10001000 >> 16);
    lui        $4, 0x44;
    ori        $3, $3, (0x10001000 & 0xFFFF);
    lwu        $2, 0x0($3);
    lw         $8, 0x10($3);
    ld         $10, 0x78A8($4);
    andi       $9, $8, 0x800;
    beqz       $9, L001217E4;
    addiu     $9, $0, 0x2;
    lwu        $2, 0x0($3);
    daddiu     $10, $10, 0x1;
  L001217E4:
    andi       $8, $8, 0x3;
    dsll       $10, $10, 16;
    movz       $9, $0, $8;
    or         $2, $2, $10;
    dsllv      $9, $9, $8;
    dsllv      $2, $2, $9;
    jr         $31;
    nop;
}
