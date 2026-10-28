#include "types.h"

asm void sceGsResetPath(void)
{
    .set noreorder;
    lui        $2, (0x10003C10 >> 16);
    addiu      $7, $0, 0x1;
    ori        $2, $2, (0x10003C10 & 0xFFFF);
    lui        $3, (0x10003C20 >> 16);
    sw         $7, 0x0($2);
    ori        $3, $3, (0x10003C20 & 0xFFFF);
    addiu      $2, $0, 0x2;
    daddu      $4, $0, $0;
    sw         $2, 0x0($3);
    sync;
    cfc2.ni    $4, $vi28;
    ori        $4, $4, 0x200;
    ctc2.ni    $4, $vi28;
    sync.p;
    lui        $5, 0x44;
    lui        $6, (0x10005000 >> 16);
    addiu      $5, $5, 0x5EE0;
    ori        $6, $6, (0x10005000 & 0xFFFF);
    lq         $4, 0x0($5);
    lui        $3, (0x10003000 >> 16);
    ori        $3, $3, (0x10003000 & 0xFFFF);
    sq         $4, 0x0($6);
    lq         $2, 0x10($5);
    sq         $2, 0x0($6);
    jr         $31;
    sw        $7, 0x0($3);
}

