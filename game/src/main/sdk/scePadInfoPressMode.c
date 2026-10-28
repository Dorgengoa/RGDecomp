#include "types.h"

extern void scePadGetButtonMask(void);

asm void scePadInfoPressMode(void)
{
    .set noreorder;
    daddu      $6, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $6, $3;
    mult       $4, $5, $4;
    addiu      $29, $29, -0x10;
    lui        $2, 0x49;
    sd         $31, 0x0($29);
    addiu      $2, $2, -0x12B0;
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    beqz       $3, L0012C1E0;
    daddu     $2, $0, $0;
    jal        scePadGetButtonMask;
    daddu     $4, $6, $0;
    lui        $3, (0x3FFFF >> 16);
    ori        $3, $3, (0x3FFFF & 0xFFFF);
    xor        $2, $2, $3;
    sltiu      $2, $2, 0x1;
  L0012C1E0:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
