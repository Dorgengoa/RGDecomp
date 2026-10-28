#include "types.h"

asm void IopResetCallbackUnregisterMaybe_122790(void)
{
    .set noreorder;
    bgezl      $4, L001227B4;
    lui       $2, 0x44;
    lui        $2, (0x7FFFFFFF >> 16);
    lui        $3, 0x49;
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    addiu      $5, $3, -0x2978;
    and        $4, $4, $2;
    b          L001227C0;
    addiu     $2, $0, 0x20;
  L001227B4:
    lui        $3, 0x44;
    lw         $5, 0x78C8($2);
    lw         $2, 0x78CC($3);
  L001227C0:
    sltu       $2, $4, $2;
    bnez       $2, L001227D4;
    sll       $3, $4, 4;
    jr         $31;
    addiu     $2, $0, -0x69;
  L001227D4:
    daddu      $2, $0, $0;
    addu       $3, $3, $5;
    jr         $31;
    sw        $0, 0x0($3);
}
