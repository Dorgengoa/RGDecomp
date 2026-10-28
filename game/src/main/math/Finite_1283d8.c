#include "types.h"

asm void Finite_1283d8(void)
{
    .set noreorder;
    dsra32     $2, $4, 0;
    lui        $3, (0x7FFFFFFF >> 16);
    lui        $4, (0x80100000 >> 16);
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    and        $2, $2, $3;
    addu       $2, $2, $4;
    jr         $31;
    srl       $2, $2, 31;
}
