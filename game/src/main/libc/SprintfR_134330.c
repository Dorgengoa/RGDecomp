#include "types.h"

extern void VfprintfR_1374e0(void);

asm void SprintfR_134330(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    lui        $2, (0x7FFFFFFF >> 16);
    daddu      $3, $5, $0;
    daddu      $5, $6, $0;
    sw         $4, 0x54($29);
    daddu      $4, $29, $0;
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    addiu      $12, $0, 0x208;
    addiu      $6, $29, 0x98;
    sd         $31, 0x60($29);
    sw         $3, 0x10($29);
    sw         $3, 0x0($29);
    sd         $7, 0x98($29);
    sd         $8, 0xA0($29);
    sd         $9, 0xA8($29);
    sd         $10, 0xB0($29);
    sd         $11, 0xB8($29);
    swc1       $f12, 0x78($29);
    swc1       $f13, 0x7C($29);
    swc1       $f14, 0x80($29);
    swc1       $f15, 0x84($29);
    swc1       $f16, 0x88($29);
    swc1       $f17, 0x8C($29);
    swc1       $f18, 0x90($29);
    swc1       $f19, 0x94($29);
    sh         $12, 0xC($29);
    sw         $2, 0x14($29);
    jal        VfprintfR_1374e0;
    sw        $2, 0x8($29);
    lw         $3, 0x0($29);
    ld         $31, 0x60($29);
    sb         $0, 0x0($3);
    jr         $31;
    addiu     $29, $29, 0xC0;
}

