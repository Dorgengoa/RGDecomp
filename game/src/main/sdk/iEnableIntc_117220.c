#include "types.h"

extern void _iEnableIntc(void);

asm void iEnableIntc_117220(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        _iEnableIntc;
    nop;
    sync;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
