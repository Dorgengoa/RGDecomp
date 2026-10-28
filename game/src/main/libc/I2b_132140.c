#include "types.h"

extern void Balloc_131cf0(void);

asm void I2b_132140(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $31, 0x8($29);
    jal        Balloc_131cf0;
    addiu     $5, $0, 0x1;
    addiu      $3, $0, 0x1;
    daddu      $4, $2, $0;
    ld         $31, 0x8($29);
    sw         $16, 0x14($4);
    ld         $16, 0x0($29);
    sw         $3, 0x10($4);
    jr         $31;
    addiu     $29, $29, 0x10;
}
