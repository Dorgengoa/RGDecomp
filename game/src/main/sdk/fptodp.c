#include "types.h"

extern void UnpackF_13aed8(void);
extern void MakeDp_13baf0(void);

asm void fptodp(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $4, $29, 0x10;
    daddu      $5, $29, $0;
    sd         $31, 0x20($29);
    jal        UnpackF_13aed8;
    swc1      $f12, 0x10($29);
    lwu        $7, 0xC($29);
    lw         $4, 0x0($29);
    lw         $5, 0x4($29);
    dsll       $7, $7, 30;
    jal        MakeDp_13baf0;
    lw        $6, 0x8($29);
    ld         $31, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

