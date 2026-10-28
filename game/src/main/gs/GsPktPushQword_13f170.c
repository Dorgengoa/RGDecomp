#include "types.h"

asm void GsPktPushQword_13f170(void)
{
    .set noreorder;
    lq         $6, 0x0($5);
    lw         $5, 0xF4($4);
    addiu      $3, $5, 0x10;
    sw         $3, 0xF4($4);
    jr         $31;
    sq        $6, 0x0($5);
}

