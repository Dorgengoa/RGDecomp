#include "types.h"

extern void sceSifCallRpc(void);

asm void sceSifQueryMemSize_11eb50(void)
{
    .set noreorder;
    lui        $2, 0x44;
    addiu      $29, $29, -0x30;
    lw         $3, 0x62B8($2);
    sd         $31, 0x20($29);
    bgez       $3, L0011EB70;
    sd        $16, 0x10($29);
    b          L0011EBB0;
    daddu     $2, $0, $0;
  L0011EB70:
    lui        $4, 0x49;
    lui        $16, 0x49;
    addiu      $4, $4, -0x6440;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x5;
    daddu      $6, $0, $0;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    addiu      $9, $16, -0x6400;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0011EBB0;
    lw        $2, -0x6400($16);
    lui        $2, (0xFFFFFFFF >> 16);
    ori        $2, $2, (0xFFFFFFFF & 0xFFFF);
  L0011EBB0:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
