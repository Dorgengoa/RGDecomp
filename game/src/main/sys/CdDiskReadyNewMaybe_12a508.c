#include "types.h"

extern void scePrintf_119288(void);
extern void CdInitSemas_129508(void);
extern void PollSema(void);
extern void sceSifInitRpc_119b60(void);
extern void sceSifBindRpc(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);
extern void sceCdDiskReady(void);

asm void CdDiskReadyNewMaybe_12a508(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    sd         $22, 0x70($29);
    lui        $22, 0x44;
    sd         $18, 0x30($29);
    lw         $2, 0x7950($22);
    daddu      $18, $4, $0;
    sd         $31, 0x80($29);
    sd         $21, 0x60($29);
    sd         $20, 0x50($29);
    sd         $19, 0x40($29);
    sd         $17, 0x20($29);
    blez       $2, L0012A548;
    sd        $16, 0x10($29);
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7BF0;
  L0012A548:
    jal        CdInitSemas_129508;
    lui       $20, 0x44;
    lw         $4, 0x7970($20);
    jal        PollSema;
    nop;
    lw         $3, 0x7970($20);
    bne        $3, $2, L0012A6AC;
    xori      $4, $18, 0x8;
    daddu      $4, $0, $0;
    jal        sceSifInitRpc_119b60;
    lui       $19, 0x44;
    lw         $2, 0x7990($19);
    bgez       $2, L0012A62C;
    daddu     $17, $0, $0;
    b          L0012A5B8;
    lui       $21, 0x49;
  L0012A588:
    beqz       $2, L0012A6BC;
    addiu     $2, $17, 0x1;
    lui        $3, 0x10;
    addiu      $4, $0, -0x1;
  L0012A598:
    addiu      $3, $3, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $3, $4, L0012A598;
    nop;
    daddu      $17, $2, $0;
  L0012A5B8:
    addiu      $16, $21, -0x1370;
  L0012A5BC:
    lui        $5, (0x8000059C >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x8000059C & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgezl      $2, L0012A61C;
    lw        $2, 0x24($16);
    lw         $2, 0x7950($22);
    blez       $2, L0012A5F4;
    lui       $3, 0x10;
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7BB8;
    lui        $3, (0x100000 >> 16);
  L0012A5F4:
    addiu      $2, $0, -0x1;
  L0012A5F8:
    addiu      $3, $3, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $3, $2, L0012A5F8;
    nop;
    b          L0012A5BC;
    addiu     $16, $21, -0x1370;
  L0012A61C:
    beqz       $2, L0012A588;
    slti      $2, $17, 0x11;
    b          L0012A630;
    sw        $0, 0x7990($19);
  L0012A62C:
    lui        $21, 0x49;
  L0012A630:
    jal        DisableIntr_120660;
    nop;
    lui        $3, 0x44;
    beqz       $2, L0012A64C;
    sw        $0, 0x7980($3);
    jal        EnableIntr_1206b0;
    nop;
  L0012A64C:
    lui        $2, 0x49;
    addiu      $5, $0, 0x4;
    addiu      $16, $2, -0x1330;
    sw         $18, -0x1330($2);
    jal        sceSifWriteBackDCache;
    daddu     $4, $16, $0;
    lui        $2, 0x45;
    addiu      $4, $21, -0x1370;
    addiu      $17, $2, -0x6C40;
    daddu      $7, $16, $0;
    sw         $0, 0x0($29);
    daddu      $5, $0, $0;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x4;
    daddu      $9, $17, $0;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0012A6D8;
    lw        $2, 0x7950($22);
    lw         $4, 0x7970($20);
    jal        SignalSema;
    nop;
    xori       $4, $18, 0x8;
  L0012A6AC:
    addiu      $3, $0, -0x1;
    addiu      $2, $0, 0x6;
    b          L0012A700;
    movz      $2, $3, $4;
  L0012A6BC:
    lw         $4, 0x7970($20);
    jal        SignalSema;
    nop;
    jal        sceCdDiskReady;
    daddu     $4, $18, $0;
    b          L0012A704;
    ld        $31, 0x80($29);
  L0012A6D8:
    blez       $2, L0012A6E8;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7BD8;
  L0012A6E8:
    lui        $2, (0x20000000 >> 16);
    lw         $4, 0x7970($20);
    or         $2, $17, $2;
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0012A700:
    ld         $31, 0x80($29);
  L0012A704:
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
