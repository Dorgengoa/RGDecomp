#include "types.h"

asm void GsPktSetTexa_13eca0(void)
{
    .set noreorder;
    lw         $6, 0xF4($4);
    addiu      $3, $0, 0x3B;
    sd         $5, 0x0($6);
    sd         $3, 0x8($6);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

