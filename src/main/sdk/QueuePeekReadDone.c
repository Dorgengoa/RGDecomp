#include "types.h"

asm void QueuePeekReadDone(void)
{
    .set noreorder;
    daddu      $5, $4, $0;
    lw         $2, 0x4($5);
    lw         $4, 0x8($5);
    lw         $3, 0x0($5);
    addiu      $2, $2, -0x1;
    addiu      $4, $4, 0x1;
    sw         $2, 0x4($5);
    addiu      $3, $3, 0x10;
    addu       $3, $5, $3;
    bne        $4, $3, L00117B54;
    sw        $4, 0x8($5);
    addiu      $2, $5, 0x10;
    sw         $2, 0x8($5);
  L00117B54:
    jr         $31;
    nop;
}
