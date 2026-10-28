#include "types.h"

extern void CdCheckSCmd_129e00(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdTrayReq_12ae98(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    lui        $17, 0x45;
    sd         $19, 0x40($29);
    daddu      $16, $4, $0;
    sd         $18, 0x30($29);
    addiu      $19, $17, -0x7080;
    sd         $31, 0x50($29);
    daddu      $18, $5, $0;
    jal        CdCheckSCmd_129e00;
    addiu     $4, $0, 0x1A;
    bnel       $2, $0, L0012AED8;
    sw        $16, -0x7080($17);
    b          L0012AF68;
    addiu     $2, $0, -0x1;
  L0012AED8:
    daddu      $4, $19, $0;
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x4;
    lui        $2, 0x45;
    lui        $4, 0x45;
    addiu      $16, $2, -0x74C0;
    addiu      $4, $4, -0x6B40;
    daddu      $7, $19, $0;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x5;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x4;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x8;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0012AF34;
    lui       $2, 0x44;
    lw         $4, 0x796C($2);
    jal        SignalSema;
    nop;
    b          L0012AF68;
    addiu     $2, $0, -0x1;
  L0012AF34:
    beqz       $18, L0012AF4C;
    addiu     $2, $16, 0x4;
    lui        $3, (0x20000000 >> 16);
    or         $2, $2, $3;
    lw         $4, (0x20000000 & 0xFFFF)($2);
    sw         $4, 0x0($18);
  L0012AF4C:
    lui        $3, 0x44;
    lui        $2, (0x20000000 >> 16);
    or         $2, $16, $2;
    lw         $4, 0x796C($3);
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0012AF68:
    ld         $31, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
