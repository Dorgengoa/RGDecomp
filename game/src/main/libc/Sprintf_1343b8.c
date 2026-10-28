#include "types.h"

extern void VfprintfR_1374e0(void);

asm void Sprintf_1343b8(void)
{
    .set noreorder;
    lui        $2, 0x45;
    addiu      $29, $29, -0xC0;
    lw         $13, -0x67A8($2);
    addiu      $2, $0, 0x208;
    lui        $3, (0x7FFFFFFF >> 16);
    daddu      $12, $4, $0;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    sd         $6, 0x90($29);
    daddu      $4, $29, $0;
    addiu      $6, $29, 0x90;
    sd         $31, 0x60($29);
    sw         $3, 0x14($29);
    sw         $3, 0x8($29);
    sd         $7, 0x98($29);
    sd         $8, 0xA0($29);
    sd         $9, 0xA8($29);
    sd         $10, 0xB0($29);
    sd         $11, 0xB8($29);
    swc1       $f12, 0x70($29);
    swc1       $f13, 0x74($29);
    swc1       $f14, 0x78($29);
    swc1       $f15, 0x7C($29);
    swc1       $f16, 0x80($29);
    swc1       $f17, 0x84($29);
    swc1       $f18, 0x88($29);
    swc1       $f19, 0x8C($29);
    sh         $2, 0xC($29);
    sw         $12, 0x10($29);
    sw         $13, 0x54($29);
    jal        VfprintfR_1374e0;
    sw        $12, 0x0($29);
    lw         $3, 0x0($29);
    ld         $31, 0x60($29);
    sb         $0, 0x0($3);
    jr         $31;
    addiu     $29, $29, 0xC0;
}

