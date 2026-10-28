#include "types.h"

asm void sceVpu0Reset(void)
{
    .set noreorder;
    lui        $2, (0x10003830 >> 16);
    lui        $4, (0x10003820 >> 16);
    ori        $2, $2, (0x10003830 & 0xFFFF);
    ori        $4, $4, (0x10003820 & 0xFFFF);
    sw         $0, 0x0($2);
    lui        $3, (0x10003810 >> 16);
    sw         $0, 0x0($4);
    ori        $3, $3, (0x10003810 & 0xFFFF);
    addiu      $2, $0, 0x1;
    sw         $2, 0x0($3);
    cfc2.ni    $8, $vi28;
    ori        $8, $8, 0x2;
    ctc2.ni    $8, $vi28;
    sync.p;
    lui        $4, 0x44;
    lui        $5, (0x10004000 >> 16);
    addiu      $4, $4, 0x5F70;
    ori        $5, $5, (0x10004000 & 0xFFFF);
    lq         $2, 0x0($4);
    sq         $2, 0x0($5);
    lq         $3, 0x10($4);
    jr         $31;
    sq        $3, 0x0($5);
}

