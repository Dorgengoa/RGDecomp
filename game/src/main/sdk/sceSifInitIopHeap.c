#include "types.h"

extern void sceSifBindRpc(void);

asm void sceSifInitIopHeap(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    lui        $17, 0x49;
    b          L0011E88C;
    sd        $16, 0x0($29);
  L0011E868:
    lui        $2, 0x10;
    addiu      $3, $0, -0x1;
  L0011E870:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L0011E870;
    nop;
  L0011E88C:
    addiu      $16, $17, -0x6440;
    lui        $5, (0x80000003 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000003 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgezl      $2, L0011E8B4;
    lw        $2, 0x24($16);
    b          L0011E8C4;
    addiu     $2, $0, -0x1;
  L0011E8B4:
    beqz       $2, L0011E868;
    lui       $2, 0x44;
    sw         $0, 0x62B8($2);
    daddu      $2, $0, $0;
  L0011E8C4:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
