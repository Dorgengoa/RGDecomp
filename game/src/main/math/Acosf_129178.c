#include "types.h"
extern void IeeeAcosf_124450(void);

asm void Acosf_129178(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          IeeeAcosf_124450;
    addiu     $29, $29, 0x10;
}
