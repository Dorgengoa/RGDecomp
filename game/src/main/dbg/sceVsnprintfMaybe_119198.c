#include "types.h"

extern void printf_118388(void);

asm void sceVsnprintfMaybe_119198(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $2, $6, $0;
    sw         $4, 0x0($29);
    daddu      $8, $7, $0;
    daddu      $6, $5, $0;
    lui        $4, 0x12;
    sd         $31, 0x10($29);
    addiu      $4, $4, -0x6F60;
    daddu      $7, $2, $0;
    jal        printf_118388;
    daddu     $5, $29, $0;
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
