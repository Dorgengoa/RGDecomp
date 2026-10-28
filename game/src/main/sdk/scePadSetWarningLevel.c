#include "types.h"

extern void sceSifCallRpc(void);

asm void scePadSetWarningLevel(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    lui        $2, 0x49;
    sd         $16, 0x10($29);
    addiu      $6, $0, 0x14;
    addiu      $16, $2, -0x10C0;
    sd         $31, 0x20($29);
    sw         $4, 0x4($16);
    lui        $3, 0x49;
    sw         $6, -0x10C0($2);
    addiu      $5, $0, 0x1;
    addiu      $4, $3, -0x1300;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x80;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0012C500;
    lw        $2, 0x8($16);
    daddu      $2, $0, $0;
  L0012C500:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
