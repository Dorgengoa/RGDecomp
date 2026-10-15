#include "types.h"

asm void GsPktOpenGifTag_13f3b0(void)
{
    .set noreorder;
    addiu      $3, $0, 0x1;
    andi       $10, $5, 0x7;
    sw         $3, 0x114($4);
    addiu      $9, $0, -0x8;
    lbu        $11, 0x70($4);
    lui        $3, (0x3F800000 >> 16);
    ori        $5, $0, 0x8000;
    and        $9, $11, $9;
    or         $9, $9, $10;
    sb         $9, 0x70($4);
    sw         $3, 0x110($4);
    lw         $3, 0xF4($4);
    sw         $3, 0xF8($4);
    sw         $3, 0xFC($4);
    lw         $9, 0xF4($4);
    sw         $0, 0x0($9);
    addiu      $3, $9, 0xC;
    sw         $0, 0x4($9);
    sw         $0, 0x8($9);
    sw         $0, 0xC($9);
    sw         $9, 0x104($4);
    sw         $3, 0x108($4);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    sw         $3, 0xF4($4);
    ld         $3, 0x70($4);
    sw         $8, 0x118($4);
    andi       $3, $3, 0x7FF;
    lw         $8, 0xF4($4);
    dsll32     $3, $3, 0;
    dsra32     $3, $3, 0;
    sll        $3, $3, 15;
    sw         $8, 0x100($4);
    sw         $5, 0x0($8);
    lw         $5, 0x118($4);
    sll        $5, $5, 28;
    or         $3, $5, $3;
    ori        $3, $3, 0x4000;
    sw         $3, 0x4($8);
    sw         $6, 0x8($8);
    sw         $7, 0xC($8);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

