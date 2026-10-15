#include "types.h"

asm void GsPktSetUV_13ed60(void)
{
    .set noreorder;
    sll        $3, $6, 4;
    sll        $7, $5, 4;
    lw         $6, 0xF4($4);
    dsll       $5, $3, 16;
    or         $5, $7, $5;
    addiu      $3, $0, 0x3;
    sd         $5, 0x0($6);
    sd         $3, 0x8($6);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

