#include "types.h"

asm void sceGifPkReserve(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    sll        $5, $5, 2;
    addu       $5, $2, $5;
    jr         $31;
    sw        $5, 0x0($4);
}

