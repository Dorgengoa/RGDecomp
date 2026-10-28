#include "types.h"

extern void sceSifCallRpc(void);

asm void sceSifQueryBlockSize_11ed20(void)
{
    .set noreorder;
    lui        $3, 0x44;
    addiu      $29, $29, -0x30;
    lw         $2, 0x62B8($3);
    daddu      $5, $4, $0;
    sd         $31, 0x20($29);
    bgez       $2, L0011ED44;
    sd        $16, 0x10($29);
    b          L0011ED8C;
    daddu     $2, $0, $0;
  L0011ED44:
    lui        $7, 0x49;
    lui        $4, 0x49;
    sw         $5, -0x63C0($7);
    lui        $16, 0x49;
    addiu      $4, $4, -0x6440;
    addiu      $7, $7, -0x63C0;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x9;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x4;
    addiu      $9, $16, -0x6400;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0011ED8C;
    lw        $2, -0x6400($16);
    lui        $2, (0xFFFFFFFF >> 16);
    ori        $2, $2, (0xFFFFFFFF & 0xFFFF);
  L0011ED8C:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
