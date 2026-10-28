#include "types.h"

asm void GsPktWriteAD_13ec80(void)
{
    .set noreorder;
    lw         $3, 0xF4($4);
    sd         $6, 0x0($3);
    sd         $5, 0x8($3);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

