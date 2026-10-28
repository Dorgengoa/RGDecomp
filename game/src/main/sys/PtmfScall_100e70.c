#include "types.h"

asm void PtmfScall_100e70(void)
{
    .set noreorder;
    lw         $1, 0x0($25);
    lw         $24, 0x4($25);
    lw         $25, 0x8($25);
    bltz       $24, L00100E9C;
    addu      $4, $4, $1;
    addu       $25, $4, $25;
    lw         $25, 0x0($25);
    nop;
    addu       $25, $25, $24;
    lw         $25, 0x0($25);
    nop;
  L00100E9C:
    jr         $25;
    nop;
}

