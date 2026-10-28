#include "types.h"

extern void MallocLock_131c20(void);
extern void MallocR_1310d0(void);
extern void MallocUnlock_131ca0(void);

asm void Malloc_130dd8(void)
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
    jal        MallocR_1310d0;
    daddu     $5, $17, $0;
    lw         $4, 0x0($16);
    jal        MallocUnlock_131ca0;
    daddu     $17, $2, $0;
    daddu      $2, $17, $0;
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
