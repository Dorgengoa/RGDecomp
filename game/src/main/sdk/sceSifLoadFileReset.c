#include "types.h"

extern void memset(void);

asm void sceSifLoadFileReset(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x44;
    addiu      $3, $0, -0x1;
    lui        $4, 0x49;
    sd         $31, 0x0($29);
    addiu      $4, $4, -0x6058;
    sw         $3, 0x62C0($2);
    daddu      $5, $0, $0;
    jal        memset;
    addiu     $6, $0, 0x4;
    ld         $31, 0x0($29);
    daddu      $2, $0, $0;
    jr         $31;
    addiu     $29, $29, 0x10;
}
