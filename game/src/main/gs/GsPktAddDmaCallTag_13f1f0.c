#include "types.h"

asm void GsPktAddDmaCallTag_13f1f0(void)
{
    .set noreorder;
    lw         $3, 0xF4($4);
    dsll32     $5, $5, 4;
    lui        $6, (0x50000000 >> 16);
    dsrl32     $5, $5, 4;
    sq         $0, 0x0($3);
    lw         $3, 0xF4($4);
    sw         $6, 0x0($3);
    lw         $3, 0xF4($4);
    sw         $5, 0x4($3);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

