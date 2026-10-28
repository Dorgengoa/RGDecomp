#include "types.h"

asm void sceVu0TransposeMatrix(void)
{
    .set noreorder;
    lq         $8, 0x0($5);
    lq         $9, 0x10($5);
    lq         $10, 0x20($5);
    lq         $11, 0x30($5);
    pextlw     $12, $9, $8;
    pextuw     $13, $9, $8;
    pextlw     $14, $11, $10;
    pextuw     $15, $11, $10;
    pcpyld     $8, $14, $12;
    pcpyud     $9, $12, $14;
    pcpyld     $10, $15, $13;
    pcpyud     $11, $13, $15;
    sq         $8, 0x0($4);
    sq         $9, 0x10($4);
    sq         $10, 0x20($4);
    jr         $31;
    sq        $11, 0x30($4);
}

