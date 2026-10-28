#include "types.h"

extern void sceSifCallRpc(void);

asm void sceSifAllocSysMemory_11e948(void)
{
    .set noreorder;
    lui        $2, 0x44;
    addiu      $29, $29, -0x30;
    lw         $3, 0x62B8($2);
    daddu      $7, $4, $0;
    sd         $31, 0x20($29);
    sd         $16, 0x10($29);
    bltz       $3, L0011E9B8;
    daddu     $2, $0, $0;
    lui        $2, 0x49;
    lui        $4, 0x49;
    addiu      $3, $2, -0x63C0;
    sw         $5, -0x63C0($2);
    sw         $7, 0x4($3);
    lui        $16, 0x49;
    sw         $6, 0x8($3);
    addiu      $4, $4, -0x6440;
    daddu      $7, $3, $0;
    addiu      $5, $0, 0x4;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0xC;
    addiu      $9, $16, -0x6400;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0011E9B8;
    lw        $2, -0x6400($16);
    daddu      $2, $0, $0;
  L0011E9B8:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
