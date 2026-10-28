#include "types.h"

extern void PackF_13ae20(void);

asm void MakeFp_13af38(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sw         $4, 0x0($29);
    daddu      $4, $29, $0;
    sd         $31, 0x10($29);
    sw         $5, 0x4($29);
    sw         $6, 0x8($29);
    jal        PackF_13ae20;
    sw        $7, 0xC($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

