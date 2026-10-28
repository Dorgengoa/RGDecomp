#include "types.h"

extern void sceGsGetGParam_1082a0(void);

asm void sceGsPutDispEnv(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        sceGsGetGParam_1082a0;
    daddu     $16, $4, $0;
    lh         $3, 0x6($2);
    addiu      $2, $0, 0x1;
    bne        $3, $2, L001087A4;
    ld        $4, 0x0($16);
    lui        $2, (0x12000000 >> 16);
    lui        $3, (0x12000070 >> 16);
    lui        $6, (0x12000080 >> 16);
    sd         $4, (0x12000000 & 0xFFFF)($2);
    ori        $3, $3, (0x12000070 & 0xFFFF);
    ori        $6, $6, (0x12000080 & 0xFFFF);
    lui        $4, (0x120000C0 >> 16);
    ld         $5, 0x10($16);
    ori        $4, $4, (0x120000C0 & 0xFFFF);
    sd         $5, 0x0($3);
    ld         $2, 0x18($16);
    sd         $2, 0x0($6);
    ld         $3, 0x20($16);
    sd         $3, 0x0($4);
    b          L001087F0;
    ld        $31, 0x10($29);
  L001087A4:
    lui        $3, (0x12000000 >> 16);
    lui        $2, (0x12000020 >> 16);
    lui        $6, (0x12000090 >> 16);
    sd         $4, (0x12000000 & 0xFFFF)($3);
    ori        $2, $2, (0x12000020 & 0xFFFF);
    ori        $6, $6, (0x12000090 & 0xFFFF);
    lui        $5, (0x120000A0 >> 16);
    ld         $3, 0x8($16);
    ori        $5, $5, (0x120000A0 & 0xFFFF);
    lui        $4, (0x120000E0 >> 16);
    sd         $3, 0x0($2);
    ori        $4, $4, (0x120000E0 & 0xFFFF);
    ld         $2, 0x10($16);
    sd         $2, 0x0($6);
    ld         $3, 0x18($16);
    sd         $3, 0x0($5);
    ld         $2, 0x20($16);
    sd         $2, 0x0($4);
    ld         $31, 0x10($29);
  L001087F0:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

