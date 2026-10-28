#include "types.h"

extern void SifLoadModuleBufferRpc_11ef68(void);

asm void sceSifLoadModuleBuffer_11f538(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $31, 0x10($29);
    jal        SifLoadModuleBufferRpc_11ef68;
    daddu     $7, $29, $0;
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
