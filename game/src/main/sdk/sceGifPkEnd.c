#include "types.h"

extern void sceGifPkTerminate_10a420(void);

asm void sceGifPkEnd(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $17, 0x10($29);
    daddu      $17, $4, $0;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    daddu      $19, $6, $0;
    sd         $16, 0x0($29);
    daddu      $18, $5, $0;
    sd         $31, 0x40($29);
    jal        sceGifPkTerminate_10a420;
    daddu     $16, $7, $0;
    lw         $3, 0x0($17);
    lui        $4, (0x70000000 >> 16);
    or         $16, $16, $4;
    sw         $2, 0x8($17);
    sw         $16, 0x0($3);
    addiu      $3, $3, 0x4;
    ld         $31, 0x40($29);
    addiu      $2, $3, 0xC;
    sw         $18, 0x4($3);
    sw         $2, 0x0($17);
    sw         $19, 0x8($3);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    sw         $0, 0x0($3);
    jr         $31;
    addiu     $29, $29, 0x50;
}

