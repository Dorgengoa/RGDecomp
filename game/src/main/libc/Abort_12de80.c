#include "types.h"

extern void Raise_134230(void);
extern void KernelExitThunk_120d18(void);

asm void Abort_12de80(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        Raise_134230;
    addiu     $4, $0, 0x6;
    jal        KernelExitThunk_120d18;
    addiu     $4, $0, 0x1;
}
