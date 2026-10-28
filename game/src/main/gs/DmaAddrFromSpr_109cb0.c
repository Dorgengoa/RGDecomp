#include "types.h"

asm void DmaAddrFromSpr_109cb0(void)
{
    .set noreorder;
    addiu      $3, $0, 0x7;
    srl        $2, $4, 28;
    bne        $2, $3, L00109CD0;
    lui       $2, (0xFFFFFFF >> 16);
    lui        $3, (0x80000000 >> 16);
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    and        $4, $4, $2;
    or         $4, $4, $3;
  L00109CD0:
    jr         $31;
    daddu     $2, $4, $0;
}

