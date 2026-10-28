#include "types.h"

extern void Deci2Call(void);

asm void sceDeci2ExUnLock_117a68(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sw         $4, 0x0($29);
    daddu      $5, $29, $0;
    sd         $31, 0x10($29);
    jal        Deci2Call;
    addiu     $4, $0, -0x9;
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
