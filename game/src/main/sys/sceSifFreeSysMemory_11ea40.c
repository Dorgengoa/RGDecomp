#include "types.h"

extern void sceSifFreeIopHeap(void);

asm void sceSifFreeSysMemory_11ea40(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        sceSifFreeIopHeap;
    nop;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
