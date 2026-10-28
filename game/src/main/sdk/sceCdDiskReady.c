#include "types.h"

extern void scePrintf_119288(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void CdInitSemas_129508(void);
extern void PollSema(void);
extern void sceCdSyncS_129d90(void);
extern void sceSifInitRpc_119b60(void);
extern void sceSifBindRpc(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdDiskReady(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    sd         $22, 0x70($29);
    lui        $22, 0x44;
    sd         $18, 0x30($29);
    lw         $2, 0x7950($22);
    daddu      $18, $4, $0;
    sd         $31, 0x90($29);
    sd         $23, 0x80($29);
    sd         $21, 0x60($29);
    sd         $20, 0x50($29);
    sd         $19, 0x40($29);
    sd         $17, 0x20($29);
    blez       $2, L0012A334;
    sd        $16, 0x10($29);
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7BA0;
  L0012A334:
    jal        DisableIntr_120660;
    nop;
    lui        $4, 0x44;
    addiu      $3, $0, 0x1;
    beqz       $2, L0012A354;
    sw        $3, 0x7980($4);
    jal        EnableIntr_1206b0;
    nop;
  L0012A354:
    jal        CdInitSemas_129508;
    lui       $19, 0x44;
    lw         $4, 0x796C($19);
    jal        PollSema;
    nop;
    lw         $3, 0x796C($19);
    bne        $3, $2, L0012A4DC;
    addiu     $2, $0, 0x6;
    jal        sceCdSyncS_129d90;
    addiu     $4, $0, 0x1;
    bnez       $2, L0012A494;
    daddu     $4, $0, $0;
    jal        sceSifInitRpc_119b60;
    lui       $17, 0x44;
    lw         $2, 0x7990($17);
    bgez       $2, L0012A444;
    lui       $21, 0x49;
    lui        $20, 0x49;
    b          L0012A3CC;
    lui       $23, 0x45;
    nop;
  L0012A3A8:
    addiu      $3, $0, -0x1;
    nop;
  L0012A3B0:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L0012A3B0;
    nop;
  L0012A3CC:
    addiu      $16, $21, -0x1370;
  L0012A3D0:
    lui        $5, (0x8000059A >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x8000059A & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgezl      $2, L0012A434;
    lw        $2, 0x24($16);
    lw         $2, 0x7950($22);
    blez       $2, L0012A408;
    lui       $2, 0x10;
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7BB8;
    lui        $2, (0x100000 >> 16);
  L0012A408:
    addiu      $3, $0, -0x1;
    nop;
  L0012A410:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L0012A410;
    nop;
    b          L0012A3D0;
    addiu     $16, $21, -0x1370;
  L0012A434:
    beqz       $2, L0012A3A8;
    lui       $2, 0x10;
    b          L0012A44C;
    sw        $0, 0x7990($17);
  L0012A444:
    lui        $20, 0x49;
    lui        $23, 0x45;
  L0012A44C:
    addiu      $16, $20, -0x1330;
    sw         $18, -0x1330($20);
    daddu      $4, $16, $0;
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x4;
    addiu      $17, $23, -0x74C0;
    addiu      $4, $21, -0x1370;
    daddu      $7, $16, $0;
    sw         $0, 0x0($29);
    daddu      $5, $0, $0;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x4;
    daddu      $9, $17, $0;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0012A4B4;
    lw        $2, 0x7950($22);
  L0012A494:
    lw         $4, 0x796C($19);
    jal        SignalSema;
    nop;
    xori       $4, $18, 0x8;
    addiu      $3, $0, -0x1;
    addiu      $2, $0, 0x6;
    b          L0012A4DC;
    movz      $2, $3, $4;
  L0012A4B4:
    blez       $2, L0012A4C4;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7BD8;
  L0012A4C4:
    lui        $2, (0x20000000 >> 16);
    lw         $4, 0x796C($19);
    or         $2, $17, $2;
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0012A4DC:
    ld         $31, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}
