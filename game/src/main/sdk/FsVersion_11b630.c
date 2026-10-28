#include "types.h"

extern void memcmp(void);

asm void FsVersion_11b630(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    lui        $2, 0x44;
    sd         $19, 0x30($29);
    lui        $3, 0x49;
    sd         $17, 0x10($29);
    addiu      $19, $2, 0x61EC;
    sd         $18, 0x20($29);
    addiu      $17, $3, -0x6518;
    sd         $31, 0x40($29);
    daddu      $18, $0, $0;
    sd         $16, 0x0($29);
    daddu      $4, $17, $0;
    daddu      $5, $19, $0;
    jal        memcmp;
    addiu     $6, $0, 0x4;
    beqz       $2, L0011B69C;
    lui       $16, 0x44;
    daddu      $4, $17, $0;
    lw         $5, 0x62B0($16);
    jal        memcmp;
    addiu     $6, $0, 0x4;
    beqz       $2, L0011B69C;
    lw        $5, 0x62B0($16);
    daddu      $4, $19, $0;
    jal        memcmp;
    addiu     $6, $0, 0x4;
    sltu       $18, $0, $2;
  L0011B69C:
    daddu      $2, $18, $0;
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
