#include "types.h"

asm void kputchar(void)
{
    .set noreorder;
    lui        $3, (0x1000F130 >> 16);
    ori        $3, $3, (0x1000F130 & 0xFFFF);
  L00118008:
    lw         $2, 0x0($3);
    andi       $2, $2, 0x8000;
    nop;
    nop;
    nop;
    bnez       $2, L00118008;
    nop;
    lui        $3, (0x1000F180 >> 16);
    daddu      $2, $4, $0;
    ori        $3, $3, (0x1000F180 & 0xFFFF);
    jr         $31;
    sb        $4, 0x0($3);
}
