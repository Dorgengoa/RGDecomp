#include "types.h"

asm void sceSifSetSysCmdBuffer(void)
{
    .set noreorder;
    lui        $3, 0x48;
    addiu      $3, $3, 0x6918;
    lw         $2, 0xC($3);
    sw         $5, 0x10($3);
    jr         $31;
    sw        $4, 0xC($3);
}
