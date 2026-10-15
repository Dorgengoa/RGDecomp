#include "types.h"

asm void GsPktSetXYZ_13ef10(void)
{
    .set noreorder;
    lw         $9, 0x120($4);
    dsll32     $3, $7, 0;
    lw         $8, 0x124($4);
    dsra32     $3, $3, 0;
    dsll32     $7, $3, 0;
    lw         $10, 0xF4($4);
    addu       $9, $5, $9;
    addiu      $3, $0, 0x5;
    addu       $5, $6, $8;
    dsll32     $5, $5, 0;
    dsll32     $6, $9, 0;
    dsra32     $5, $5, 0;
    dsra32     $6, $6, 0;
    dsll       $5, $5, 16;
    or         $5, $6, $5;
    or         $5, $7, $5;
    sd         $5, 0x0($10);
    sd         $3, 0x8($10);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

