#include "types.h"

extern void PackD_13afa8(void);

asm void MakeDp_13baf0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sw         $4, 0x0($29);
    daddu      $4, $29, $0;
    sd         $31, 0x20($29);
    sw         $5, 0x4($29);
    sw         $6, 0x8($29);
    jal        PackD_13afa8;
    sd        $7, 0x10($29);
    ld         $31, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

