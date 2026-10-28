#include "types.h"

extern void GetpidStub_116d70(void);

asm void GetpidR_134318(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          GetpidStub_116d70;
    addiu     $29, $29, 0x10;
}

