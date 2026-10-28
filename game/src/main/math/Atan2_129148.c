#include "types.h"

extern void IeeeAtan2_123838(void);

asm void Atan2_129148(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          IeeeAtan2_123838;
    addiu     $29, $29, 0x10;
}
