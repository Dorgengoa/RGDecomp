#include "types.h"

extern void CdCheckNCmd_129b00(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdNcmdDiskReady_129c58(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $4, $0, 0x2;
    sd         $31, 0x20($29);
    jal        CdCheckNCmd_129b00;
    sd        $16, 0x10($29);
    bnez       $2, L00129C7C;
    lui       $2, 0x44;
    b          L00129CE0;
    daddu     $2, $0, $0;
  L00129C7C:
    lui        $4, 0x45;
    addiu      $16, $2, 0x79C0;
    addiu      $4, $4, -0x74F0;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0xE;
    daddu      $6, $0, $0;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L00129CC8;
    lui       $3, 0x44;
    lui        $2, 0x44;
    jal        SignalSema;
    lw        $4, 0x7968($2);
    b          L00129CE0;
    daddu     $2, $0, $0;
  L00129CC8:
    lui        $2, (0x20000000 >> 16);
    or         $2, $16, $2;
    lw         $4, 0x7968($3);
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L00129CE0:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
