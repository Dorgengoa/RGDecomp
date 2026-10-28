#include "types.h"

extern void MallocLock_131c20(void);
extern void MemalignR_130c10(void);
extern void MallocUnlock_131ca0(void);

asm void Memalign_130ba8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    lui        $16, 0x45;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sd         $18, 0x10($29);
    daddu      $18, $4, $0;
    sd         $31, 0x18($29);
    addiu      $16, $16, -0x67A8;
    jal        MallocLock_131c20;
    lw        $4, 0x0($16);
    lw         $4, 0x0($16);
    daddu      $5, $18, $0;
    jal        MemalignR_130c10;
    daddu     $6, $17, $0;
    lw         $4, 0x0($16);
    jal        MallocUnlock_131ca0;
    daddu     $17, $2, $0;
    daddu      $2, $17, $0;
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
