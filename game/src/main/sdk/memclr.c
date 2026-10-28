#include "types.h"

asm void memclr(void)
{
    .set noreorder;
    beqz       $5, L00109D04;
    addiu     $2, $5, -0x1;
    addiu      $3, $0, -0x1;
    nop;
  L00109CE8:
    sb         $0, 0x0($4);
    addiu      $2, $2, -0x1;
    addiu      $4, $4, 0x1;
    nop;
    nop;
    bne        $2, $3, L00109CE8;
    nop;
  L00109D04:
    jr         $31;
    nop;
}

