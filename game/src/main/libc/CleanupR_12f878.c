#include "types.h"

extern void Fwalk_130858(void);

asm void CleanupR_12f878(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $5, 0x13;
    sd         $31, 0x0($29);
    addiu      $5, $5, -0xA70;
    ld         $31, 0x0($29);
    j          Fwalk_130858;
    addiu     $29, $29, 0x10;
}
