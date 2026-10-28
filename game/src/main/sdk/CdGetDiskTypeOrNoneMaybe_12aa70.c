#include "types.h"

extern void sceCdGetDiskType_12a9d8(void);

asm void CdGetDiskTypeOrNoneMaybe_12aa70(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        sceCdGetDiskType_12a9d8;
    nop;
    nor        $3, $0, $2;
    ld         $31, 0x0($29);
    movz       $2, $0, $3;
    jr         $31;
    addiu     $29, $29, 0x10;
}
