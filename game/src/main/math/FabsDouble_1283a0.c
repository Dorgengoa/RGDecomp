#include "types.h"

asm void FabsDouble_1283a0(void)
{
    .set noreorder;
    daddu      $2, $4, $0;
    dsra32     $2, $2, 0;
    lui        $3, (0x7FFFFFFF >> 16);
    lui        $5, (0xFFFF0000 >> 16);
    dsrl32     $5, $5, 0;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    and        $4, $4, $5;
    and        $2, $2, $3;
    dsll32     $2, $2, 0;
    or         $4, $4, $2;
    daddu      $2, $4, $0;
    jr         $31;
    nop;
}
