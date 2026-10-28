#include "types.h"

extern void CdInitSemas_129508(void);
extern void PollSema(void);
extern void scePrintf_119288(void);
extern void sceCdSyncS_129d90(void);
extern void SignalSema(void);
extern void sceSifInitRpc_119b60(void);
extern void sceSifBindRpc(void);

asm void CdCheckSCmd_129e00(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $31, 0x30($29);
    lui        $16, 0x44;
    jal        CdInitSemas_129508;
    sd        $18, 0x20($29);
    lw         $4, 0x796C($16);
    jal        PollSema;
    nop;
    lw         $3, 0x796C($16);
    beq        $3, $2, L00129E60;
    lui       $2, 0x44;
    lw         $3, 0x7950($2);
    blez       $3, L00129E84;
    lui       $2, 0x44;
    lui        $4, 0x45;
    lw         $6, 0x7958($2);
    addiu      $4, $4, 0x7B30;
    jal        scePrintf_119288;
    daddu     $5, $17, $0;
    b          L00129F40;
    daddu     $2, $0, $0;
  L00129E60:
    lui        $2, 0x44;
    addiu      $4, $0, 0x1;
    jal        sceCdSyncS_129d90;
    sw        $17, 0x7958($2);
    beqz       $2, L00129E8C;
    daddu     $4, $0, $0;
    lw         $4, 0x796C($16);
    jal        SignalSema;
    nop;
  L00129E84:
    b          L00129F40;
    daddu     $2, $0, $0;
  L00129E8C:
    jal        sceSifInitRpc_119b60;
    lui       $18, 0x44;
    lw         $2, 0x7994($18);
    bgez       $2, L00129F40;
    addiu     $2, $0, 0x1;
    b          L00129ECC;
    lui       $17, 0x45;
  L00129EA8:
    lui        $2, 0x10;
    addiu      $3, $0, -0x1;
  L00129EB0:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L00129EB0;
    nop;
  L00129ECC:
    addiu      $16, $17, -0x6B40;
  L00129ED0:
    lui        $5, (0x80000593 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000593 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgezl      $2, L00129F34;
    lw        $2, 0x24($16);
    lui        $2, 0x44;
    lw         $3, 0x7950($2);
    blez       $3, L00129F0C;
    lui       $2, 0x10;
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7B58;
    lui        $2, (0x100000 >> 16);
  L00129F0C:
    addiu      $3, $0, -0x1;
  L00129F10:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L00129F10;
    nop;
    b          L00129ED0;
    addiu     $16, $17, -0x6B40;
  L00129F34:
    beqz       $2, L00129EA8;
    addiu     $2, $0, 0x1;
    sw         $0, 0x7994($18);
  L00129F40:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
