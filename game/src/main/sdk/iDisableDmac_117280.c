#include "types.h"

extern void _iDisableDmac(void);

asm void iDisableDmac_117280(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        _iDisableDmac;
    nop;
    sync;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
