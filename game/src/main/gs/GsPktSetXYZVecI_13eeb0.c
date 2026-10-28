#include "types.h"

asm void GsPktSetXYZVecI_13eeb0(void)
{
    .set noreorder;
    lw         $8, 0x4($5);
    addiu      $3, $0, 0x5;
    lw         $6, 0x124($4);
    lw         $7, 0x0($5);
    lw         $9, 0xF4($4);
    addu       $8, $8, $6;
    lw         $6, 0x120($4);
    dsll32     $8, $8, 0;
    lw         $5, 0x8($5);
    dsra32     $8, $8, 0;
    dsll       $8, $8, 16;
    addu       $6, $7, $6;
    dsll32     $6, $6, 0;
    dsll32     $5, $5, 0;
    dsra32     $6, $6, 0;
    or         $6, $6, $8;
    or         $5, $5, $6;
    sd         $5, 0x0($9);
    sd         $3, 0x8($9);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

