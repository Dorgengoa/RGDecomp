#include "types.h"

extern void MallocLock_131c20(void);
extern void FreeR_12f9f8(void);
extern void MallocUnlock_131ca0(void);

asm void Free_130e30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    lui        $16, 0x45;
    sd         $17, 0x8($29);
    daddu      $17, $4, $0;
    sd         $31, 0x10($29);
    addiu      $16, $16, -0x67A8;
    jal        MallocLock_131c20;
    lw        $4, 0x0($16);
    lw         $4, 0x0($16);
    jal        FreeR_12f9f8;
    daddu     $5, $17, $0;
    lw         $4, 0x0($16);
    ld         $17, 0x8($29);
    ld         $16, 0x0($29);
    ld         $31, 0x10($29);
    j          MallocUnlock_131ca0;
    addiu     $29, $29, 0x20;
}
