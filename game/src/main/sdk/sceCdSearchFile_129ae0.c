#include "types.h"

extern void sceCdLayerSearchFile_1297e0(void);

asm void sceCdSearchFile_129ae0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        sceCdLayerSearchFile_1297e0;
    daddu     $6, $0, $0;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
