#include "types.h"

extern void CdCheckSCmd_129e00(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdSetTimeoutMaybe_12abf8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $19, 0x40($29);
    sd         $18, 0x30($29);
    lui        $19, 0x45;
    sd         $17, 0x20($29);
    daddu      $18, $4, $0;
    sd         $16, 0x10($29);
    addiu      $17, $19, -0x7080;
    sd         $31, 0x50($29);
    daddu      $16, $5, $0;
    jal        CdCheckSCmd_129e00;
    addiu     $4, $0, 0x25;
    bnel       $2, $0, L0012AC38;
    sw        $18, -0x7080($19);
    b          L0012ACB0;
    daddu     $2, $0, $0;
  L0012AC38:
    daddu      $4, $17, $0;
    sw         $16, 0x4($17);
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x8;
    lui        $2, 0x45;
    lui        $4, 0x45;
    addiu      $16, $2, -0x74C0;
    addiu      $4, $4, -0x6B40;
    daddu      $7, $17, $0;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x25;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x8;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0012AC98;
    lui       $3, 0x44;
    lui        $2, 0x44;
    jal        SignalSema;
    lw        $4, 0x796C($2);
    b          L0012ACB0;
    daddu     $2, $0, $0;
  L0012AC98:
    lui        $2, (0x20000000 >> 16);
    or         $2, $16, $2;
    lw         $4, 0x796C($3);
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0012ACB0:
    ld         $31, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
