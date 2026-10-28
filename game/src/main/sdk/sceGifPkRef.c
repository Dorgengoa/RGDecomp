#include "types.h"

extern void sceGifPkTerminate_10a420(void);

asm void sceGifPkRef(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $19, 0x30($29);
    daddu      $19, $4, $0;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    daddu      $21, $8, $0;
    sd         $18, 0x20($29);
    daddu      $20, $7, $0;
    sd         $17, 0x10($29);
    daddu      $18, $5, $0;
    sd         $16, 0x0($29);
    daddu      $17, $6, $0;
    sd         $31, 0x60($29);
    jal        sceGifPkTerminate_10a420;
    daddu     $16, $9, $0;
    lui        $4, (0x30000000 >> 16);
    lw         $2, 0x0($19);
    or         $17, $17, $4;
    lui        $3, (0x9FFFFFFF >> 16);
    or         $16, $16, $17;
    ori        $3, $3, (0x9FFFFFFF & 0xFFFF);
    sw         $16, 0x0($2);
    and        $18, $18, $3;
    addiu      $2, $2, 0x4;
    ld         $31, 0x60($29);
    addiu      $3, $2, 0xC;
    sw         $18, 0x0($2);
    sw         $3, 0x0($19);
    sw         $20, 0x4($2);
    sw         $21, 0x8($2);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

