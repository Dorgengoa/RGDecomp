#include "types.h"

extern void IeeeAcos_123110(void);

asm void Acos_129130(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          IeeeAcos_123110;
    addiu     $29, $29, 0x10;
}
