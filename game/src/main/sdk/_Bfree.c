#include "types.h"

asm void _Bfree(void)
{
    .set noreorder;
    beqz       $5, L00131DBC;
    nop;
    lw         $2, 0x4($5);
    lw         $4, 0x4C($4);
    sll        $2, $2, 2;
    addu       $2, $2, $4;
    lw         $3, 0x0($2);
    sw         $3, 0x0($5);
    sw         $5, 0x0($2);
  L00131DBC:
    jr         $31;
    nop;
}
