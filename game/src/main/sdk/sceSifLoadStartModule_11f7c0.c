#include "types.h"

extern void SifLoadModuleRpc_11f578(void);

asm void sceSifLoadStartModule_11f7c0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        SifLoadModuleRpc_11f578;
    daddu     $8, $0, $0;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
