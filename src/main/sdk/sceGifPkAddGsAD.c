#include "types.h"

asm void sceGifPkAddGsAD(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    dsll32     $5, $5, 0;
    dsrl32     $5, $5, 0;
    sd         $6, 0x0($2);
    addiu      $2, $2, 0x8;
    sd         $5, 0x0($2);
    addiu      $2, $2, 0x8;
    jr         $31;
    sw        $2, 0x0($4);
}

