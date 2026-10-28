#include "types.h"

asm void sceSifSetCmdBuffer(void)
{
    .set noreorder;
    lui        $3, 0x48;
    addiu      $3, $3, 0x6918;
    lw         $2, 0x14($3);
    sw         $5, 0x18($3);
    jr         $31;
    sw        $4, 0x14($3);
}
