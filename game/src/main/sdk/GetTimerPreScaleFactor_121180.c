#include "types.h"

asm void GetTimerPreScaleFactor_121180(void)
{
    .set noreorder;
    lui        $2, 0x44;
    lw         $3, 0x78B0($2);
    bgez       $3, L0012119C;
    lui       $3, (0x10001010 >> 16);
    lui        $2, (0x80008001 >> 16);
    jr         $31;
    ori       $2, $2, (0x80008001 & 0xFFFF);
  L0012119C:
    ori        $3, $3, (0x10001010 & 0xFFFF);
    lw         $2, 0x0($3);
    jr         $31;
    andi      $2, $2, 0x3;
}
