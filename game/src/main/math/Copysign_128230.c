#include "types.h"

asm void Copysign_128230(void)
{
    .set noreorder;
    daddu      $2, $4, $0;
    daddu      $3, $2, $0;
    dsra32     $3, $3, 0;
    dsra32     $5, $5, 0;
    daddu      $6, $2, $0;
    lui        $2, (0x7FFFFFFF >> 16);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    lui        $4, (0x80000000 >> 16);
    and        $3, $3, $2;
    lui        $2, (0xFFFF0000 >> 16);
    dsrl32     $2, $2, 0;
    and        $5, $5, $4;
    and        $6, $6, $2;
    or         $3, $3, $5;
    dsll32     $3, $3, 0;
    jr         $31;
    or        $2, $6, $3;
}
