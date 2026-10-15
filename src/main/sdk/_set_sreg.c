#include "types.h"

asm void _set_sreg(void)
{
    .set noreorder;
    lw         $2, 0x10($4);
    lw         $6, 0x1C($5);
    lw         $3, 0x14($4);
    sll        $2, $2, 2;
    addu       $2, $2, $6;
    jr         $31;
    sw        $3, 0x0($2);
}
