#include "types.h"
extern void IeeeAtan2f_124c18(void);

asm void Atan2f_1291a8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          IeeeAtan2f_124c18;
    addiu     $29, $29, 0x10;
}
