#include "types.h"

extern void _iDisableIntc(void);

asm void iDisableIntc_117240(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        _iDisableIntc;
    nop;
    sync;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
