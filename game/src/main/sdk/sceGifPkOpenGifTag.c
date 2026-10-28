#include "types.h"

asm void sceGifPkOpenGifTag(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    addiu      $3, $2, 0x10;
    sq         $5, 0x0($2);
    sw         $3, 0x0($4);
    jr         $31;
    sw        $2, 0xC($4);
}

