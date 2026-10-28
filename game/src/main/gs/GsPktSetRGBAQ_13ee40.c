#include "types.h"

asm void GsPktSetRGBAQ_13ee40(void)
{
    .set noreorder;
    dsll32     $9, $5, 0;
    dsll32     $3, $7, 0;
    dsll32     $5, $6, 0;
    dsra32     $3, $3, 0;
    dsra32     $5, $5, 0;
    dsra32     $9, $9, 0;
    dsll       $6, $5, 8;
    lw         $7, 0xF4($4);
    dsll       $5, $3, 16;
    or         $6, $9, $6;
    dsll32     $3, $8, 0;
    or         $5, $5, $6;
    dsra32     $3, $3, 0;
    dsll       $3, $3, 24;
    or         $6, $3, $5;
    lwu        $5, 0x110($4);
    addiu      $3, $0, 0x1;
    dsll32     $5, $5, 0;
    or         $5, $5, $6;
    sd         $5, 0x0($7);
    sd         $3, 0x8($7);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    jr         $31;
    sw        $3, 0xF4($4);
}

