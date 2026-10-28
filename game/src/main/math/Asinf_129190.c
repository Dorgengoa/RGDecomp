#include "types.h"

extern void IeeeAsinf_124878(void);

asm void Asinf_129190(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          IeeeAsinf_124878;
    addiu     $29, $29, 0x10;
}
