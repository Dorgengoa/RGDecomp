#include "types.h"

extern void sceSifCallRpc(void);

asm void scePadGetPortMax(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    lui        $2, 0x49;
    sd         $16, 0x10($29);
    addiu      $3, $0, 0xC;
    addiu      $16, $2, -0x10C0;
    lui        $4, 0x49;
    sd         $31, 0x20($29);
    addiu      $4, $4, -0x1300;
    sw         $3, -0x10C0($2);
    addiu      $5, $0, 0x1;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x80;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0012C3C4;
    lw        $2, 0xC($16);
    daddu      $2, $0, $0;
  L0012C3C4:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
