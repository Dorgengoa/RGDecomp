#include "types.h"

asm void GsPktBeginPrimAD_13f6b0(void)
{
    .set noreorder;
    lw         $7, 0xF4($4);
    ori        $6, $0, 0x8000;
    lui        $5, (0x10000000 >> 16);
    addiu      $3, $0, 0xE;
    sw         $7, 0xF8($4);
    sw         $7, 0xFC($4);
    lw         $8, 0xF4($4);
    sw         $0, 0x0($8);
    addiu      $7, $8, 0xC;
    sw         $0, 0x4($8);
    sw         $0, 0x8($8);
    sw         $0, 0xC($8);
    sw         $8, 0x104($4);
    sw         $7, 0x108($4);
    lw         $8, 0xF4($4);
    addiu      $7, $8, 0x10;
    sw         $7, 0xF4($4);
    sw         $7, 0x100($4);
    sw         $6, 0x10($8);
    sw         $5, 0x14($8);
    sw         $3, 0x18($8);
    sw         $0, 0x1C($8);
    lw         $6, 0xF4($4);
    addiu      $3, $6, 0x10;
    sw         $3, 0xF4($4);
    ld         $5, 0x70($4);
    addiu      $3, $3, 0x10;
    sd         $5, 0x10($6);
    sd         $0, 0x18($6);
    jr         $31;
    sw        $3, 0xF4($4);
}

