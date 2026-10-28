#include "types.h"

extern void IeeePowf_124df8(void);

asm void Powf_1291c0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          IeeePowf_124df8;
    addiu     $29, $29, 0x10;
}
