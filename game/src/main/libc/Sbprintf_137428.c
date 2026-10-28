#include "types.h"

extern void VfprintfR_1374e0(void);
extern void Fflush_12f590(void);

asm void Sbprintf_137428(void)
{
    .set noreorder;
    addiu      $29, $29, -0x480;
    addiu      $10, $0, 0x400;
    sd         $16, 0x460($29);
    daddu      $16, $4, $0;
    sd         $17, 0x468($29);
    addiu      $11, $29, 0x60;
    sd         $31, 0x470($29);
    daddu      $4, $29, $0;
    sw         $11, 0x10($29);
    lhu        $2, 0xC($16);
    lhu        $9, 0xE($16);
    lw         $8, 0x54($16);
    andi       $2, $2, 0xFFFD;
    lw         $3, 0x1C($16);
    lw         $7, 0x24($16);
    sw         $8, 0x54($29);
    sh         $2, 0xC($29);
    sh         $9, 0xE($29);
    sw         $3, 0x1C($29);
    sw         $7, 0x24($29);
    sw         $10, 0x14($29);
    sw         $11, 0x0($29);
    sw         $10, 0x8($29);
    jal        VfprintfR_1374e0;
    sw        $0, 0x18($29);
    daddu      $17, $2, $0;
    bltz       $17, L001374A8;
    daddu     $4, $29, $0;
    jal        Fflush_12f590;
    nop;
    addiu      $3, $0, -0x1;
    movn       $17, $3, $2;
  L001374A8:
    lhu        $2, 0xC($29);
    andi       $2, $2, 0x40;
    beqz       $2, L001374C8;
    daddu     $2, $17, $0;
    lhu        $2, 0xC($16);
    ori        $2, $2, 0x40;
    sh         $2, 0xC($16);
    daddu      $2, $17, $0;
  L001374C8:
    ld         $16, 0x460($29);
    ld         $17, 0x468($29);
    ld         $31, 0x470($29);
    jr         $31;
    addiu     $29, $29, 0x480;
}

