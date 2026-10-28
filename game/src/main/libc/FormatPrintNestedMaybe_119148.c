#include "types.h"

extern void printf_118388(void);

asm void FormatPrintNestedMaybe_119148(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $16, 0x0($29);
    sd         $8, 0x60($29);
    daddu      $16, $6, $0;
    sd         $31, 0x10($29);
    addiu      $8, $29, 0x60;
    lw         $6, 0x0($16);
    sd         $9, 0x68($29);
    sd         $10, 0x70($29);
    jal        printf_118388;
    sd        $11, 0x78($29);
    lw         $3, 0x0($16);
    daddu      $4, $2, $0;
    ld         $31, 0x10($29);
    subu       $3, $3, $4;
    sw         $3, 0x0($16);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
