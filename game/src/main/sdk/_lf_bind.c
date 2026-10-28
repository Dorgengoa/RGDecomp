#include "types.h"

extern void sceSifBindRpc(void);
extern void sceSifCallRpc(void);

asm void _lf_bind(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $18, 0x30($29);
    lui        $18, 0x44;
    sd         $31, 0x40($29);
    lw         $2, 0x62C0($18);
    sd         $17, 0x20($29);
    bgez       $2, L0011EE84;
    sd        $16, 0x10($29);
    lui        $17, 0x49;
    addiu      $16, $17, -0x6080;
  L0011EDC8:
    lui        $5, (0x80000006 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000006 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgezl      $2, L0011EDEC;
    lw        $2, 0x24($16);
    b          L0011EE88;
    addiu     $2, $0, -0x1;
  L0011EDEC:
    beqz       $2, L0011EE54;
    daddu     $4, $16, $0;
    lui        $17, 0x49;
    sw         $0, 0x62C0($18);
    sw         $0, 0x0($29);
    addiu      $5, $0, 0xFF;
    daddu      $6, $0, $0;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    addiu      $9, $17, -0x6280;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0011EE34;
    lui       $3, 0x49;
    lui        $2, (0xFFFEFFFF >> 16);
    b          L0011EE88;
    ori       $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011EE34:
    addiu      $7, $17, -0x6280;
    addiu      $6, $3, -0x6058;
    lwl        $4, 0x3($7);
    lwr        $4, 0x0($7);
    swl        $4, 0x3($6);
    swr        $4, 0x0($6);
    b          L0011EE88;
    daddu     $2, $0, $0;
  L0011EE54:
    lui        $2, 0x10;
    addiu      $3, $0, -0x1;
    nop;
  L0011EE60:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L0011EE60;
    nop;
    b          L0011EDC8;
    addiu     $16, $17, -0x6080;
  L0011EE84:
    daddu      $2, $0, $0;
  L0011EE88:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
