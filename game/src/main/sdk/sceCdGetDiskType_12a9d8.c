#include "types.h"

extern void CdCheckSCmd_129e00(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdGetDiskType_12a9d8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $4, $0, 0x1;
    sd         $31, 0x20($29);
    jal        CdCheckSCmd_129e00;
    sd        $16, 0x10($29);
    bnez       $2, L0012A9FC;
    lui       $2, 0x45;
    b          L0012AA60;
    addiu     $2, $0, -0x1;
  L0012A9FC:
    lui        $4, 0x45;
    addiu      $16, $2, -0x74C0;
    addiu      $4, $4, -0x6B40;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x3;
    daddu      $6, $0, $0;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0012AA48;
    lui       $3, 0x44;
    lui        $2, 0x44;
    jal        SignalSema;
    lw        $4, 0x796C($2);
    b          L0012AA60;
    addiu     $2, $0, -0x1;
  L0012AA48:
    lui        $2, (0x20000000 >> 16);
    or         $2, $16, $2;
    lw         $4, 0x796C($3);
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0012AA60:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
