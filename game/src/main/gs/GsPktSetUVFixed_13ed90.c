#include "types.h"

asm void GsPktSetUVFixed_13ed90(void)
{
    .set noreorder;
    dsll32     $3, $6, 0;
    dsll32     $7, $5, 0;
    dsra32     $3, $3, 0;
    lw         $6, 0xF4($4);
    dsll       $5, $3, 16;
    dsra32     $7, $7, 0;
    or         $5, $7, $5;
    addiu      $3, $0, 0x3;
    sd         $5, 0x0($6);
    sd         $3, 0x8($6);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

