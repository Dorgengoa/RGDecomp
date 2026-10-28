#include "types.h"

extern void CdCheckSCmd_129e00(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdReadDvdDualInfo_12acd0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $17, 0x20($29);
    sd         $18, 0x30($29);
    daddu      $17, $4, $0;
    sd         $31, 0x40($29);
    daddu      $18, $5, $0;
    sd         $16, 0x10($29);
    jal        CdCheckSCmd_129e00;
    addiu     $4, $0, 0x27;
    bnez       $2, L0012AD04;
    lui       $2, 0x45;
    b          L0012AD88;
    daddu     $2, $0, $0;
  L0012AD04:
    lui        $4, 0x45;
    addiu      $16, $2, -0x74C0;
    addiu      $4, $4, -0x6B40;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x27;
    daddu      $6, $0, $0;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0xC;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0012AD50;
    lui       $5, (0x20000000 >> 16);
    lui        $2, 0x44;
    jal        SignalSema;
    lw        $4, 0x796C($2);
    b          L0012AD88;
    daddu     $2, $0, $0;
  L0012AD50:
    addiu      $2, $16, 0x4;
    or         $2, $2, $5;
    addiu      $3, $16, 0x8;
    lw         $4, (0x20000000 & 0xFFFF)($2);
    or         $3, $3, $5;
    lui        $6, 0x44;
    or         $5, $16, $5;
    sw         $4, 0x0($17);
    lw         $2, (0x20000000 & 0xFFFF)($3);
    sw         $2, 0x0($18);
    lw         $4, 0x796C($6);
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($5);
    daddu      $2, $16, $0;
  L0012AD88:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
