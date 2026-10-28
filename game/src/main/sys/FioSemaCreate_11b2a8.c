#include "types.h"

extern void CreateSema(void);

asm void FioSemaCreate_11b2a8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    addiu      $3, $0, -0x1;
    sd         $16, 0x20($29);
    lui        $16, 0x44;
    sd         $31, 0x30($29);
    lw         $2, 0x62A4($16);
    bne        $2, $3, L0011B2F0;
    ld        $31, 0x30($29);
    lui        $2, 0x45;
    addiu      $3, $0, 0x1;
    addiu      $2, $2, 0x69C8;
    sw         $3, 0x4($29);
    sw         $2, 0x14($29);
    daddu      $4, $29, $0;
    jal        CreateSema;
    sw        $3, 0x8($29);
    sw         $2, 0x62A4($16);
    ld         $31, 0x30($29);
  L0011B2F0:
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
