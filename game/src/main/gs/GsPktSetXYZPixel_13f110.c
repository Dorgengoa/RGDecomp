#include "types.h"

asm void GsPktSetXYZPixel_13f110(void)
{
    .set noreorder;
    sll        $8, $6, 4;
    dsll32     $3, $7, 0;
    lw         $6, 0x124($4);
    sll        $9, $5, 4;
    lw         $7, 0x120($4);
    dsra32     $3, $3, 0;
    dsll32     $5, $3, 0;
    lw         $10, 0xF4($4);
    addu       $6, $8, $6;
    addiu      $3, $0, 0x5;
    addu       $7, $9, $7;
    dsll32     $6, $6, 0;
    dsll32     $7, $7, 0;
    dsra32     $6, $6, 0;
    dsra32     $7, $7, 0;
    dsll       $6, $6, 16;
    or         $6, $7, $6;
    or         $5, $5, $6;
    sd         $5, 0x0($10);
    sd         $3, 0x8($10);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

