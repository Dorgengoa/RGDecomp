#include "types.h"

asm s32 abs(s32 i)
{
    .set noreorder;
    bgez       $4, L0012DEA4;
    daddu     $2, $4, $0;
    negu       $2, $2;
  L0012DEA4:
    jr         $31;
    nop;
}
