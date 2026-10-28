#include "types.h"

asm void MpegAddCallback_1112c0(void)
{
    .set noreorder;
    addiu      $2, $0, 0xC;
    lw         $8, 0x40($4);
    mult       $5, $5, $2;
    addiu      $3, $8, 0xC;
    addu       $3, $3, $5;
    addu       $4, $8, $5;
    lw         $2, 0x0($3);
    sw         $6, 0x0($3);
    sw         $7, 0x10($4);
    daddu      $3, $28, $0;
    daddu      $8, $4, $0;
    jr         $31;
    sw        $3, 0x14($8);
}
