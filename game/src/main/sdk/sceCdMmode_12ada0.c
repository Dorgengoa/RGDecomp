#include "types.h"

extern void CdCheckSCmd_129e00(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdMmode_12ada0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    lui        $17, 0x45;
    sd         $18, 0x30($29);
    daddu      $16, $4, $0;
    sd         $31, 0x40($29);
    addiu      $18, $17, -0x7080;
    jal        CdCheckSCmd_129e00;
    addiu     $4, $0, 0x22;
    bnel       $2, $0, L0012ADD8;
    sw        $16, -0x7080($17);
    b          L0012AE58;
    daddu     $2, $0, $0;
  L0012ADD8:
    daddu      $4, $18, $0;
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x4;
    lui        $4, 0x45;
    lui        $6, 0x45;
    lui        $3, 0x45;
    lui        $2, 0x45;
    lw         $8, -0x6B14($4);
    addiu      $16, $2, -0x74C0;
    lui        $4, 0x45;
    lw         $10, -0x6B10($6);
    lw         $5, -0x6B18($3);
    addiu      $4, $4, -0x6B40;
    daddu      $7, $18, $0;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    daddu      $9, $16, $0;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0012AE40;
    lui       $3, 0x44;
    lui        $2, 0x44;
    jal        SignalSema;
    lw        $4, 0x796C($2);
    b          L0012AE58;
    daddu     $2, $0, $0;
  L0012AE40:
    lui        $2, (0x20000000 >> 16);
    or         $2, $16, $2;
    lw         $4, 0x796C($3);
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0012AE58:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
