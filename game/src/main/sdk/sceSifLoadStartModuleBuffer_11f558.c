#include "types.h"

extern void SifLoadModuleBufferRpc_11ef68(void);

asm void sceSifLoadStartModuleBuffer_11f558(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        SifLoadModuleBufferRpc_11ef68;
    nop;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
