#include "types.h"

extern void SifLoadModuleRpc_11f578(void);

asm void sceSifLoadModule_11f7a0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $8, $0, $0;
    sd         $31, 0x10($29);
    jal        SifLoadModuleRpc_11f578;
    daddu     $7, $29, $0;
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
