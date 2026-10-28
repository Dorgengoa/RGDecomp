#include "types.h"

extern void printf_118388(void);

asm void sceSnprintfMaybe_1191d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    sd         $7, 0x68($29);
    sw         $4, 0x0($29);
    daddu      $7, $6, $0;
    sd         $8, 0x70($29);
    daddu      $6, $5, $0;
    lui        $4, 0x12;
    sd         $31, 0x10($29);
    sd         $9, 0x78($29);
    addiu      $4, $4, -0x6F60;
    sd         $10, 0x80($29);
    daddu      $5, $29, $0;
    sd         $11, 0x88($29);
    jal        printf_118388;
    addiu     $8, $29, 0x68;
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
