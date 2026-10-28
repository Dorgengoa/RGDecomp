#include "types.h"

extern void CdInitSemas_129508(void);
extern void PollSema(void);
extern void scePrintf_119288(void);
extern void sceCdSync(void);
extern void SignalSema(void);
extern void sceSifInitRpc_119b60(void);
extern void sceSifBindRpc(void);

asm void CdCheckNCmd_129b00(void)
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
    lw         $4, 0x7968($16);
    jal        PollSema;
    nop;
    lw         $3, 0x7968($16);
    beq        $3, $2, L00129B60;
    lui       $2, 0x44;
    lw         $3, 0x7950($2);
    blez       $3, L00129B84;
    lui       $2, 0x44;
    lui        $4, 0x45;
    lw         $6, 0x795C($2);
    addiu      $4, $4, 0x7AD0;
    jal        scePrintf_119288;
    daddu     $5, $17, $0;
    b          L00129C40;
    daddu     $2, $0, $0;
  L00129B60:
    lui        $2, 0x44;
    addiu      $4, $0, 0x1;
    jal        sceCdSync;
    sw        $17, 0x795C($2);
    beqz       $2, L00129B8C;
    daddu     $4, $0, $0;
    lw         $4, 0x7968($16);
    jal        SignalSema;
    nop;
  L00129B84:
    b          L00129C40;
    daddu     $2, $0, $0;
  L00129B8C:
    jal        sceSifInitRpc_119b60;
    lui       $18, 0x44;
    lw         $2, 0x797C($18);
    bgez       $2, L00129C40;
    addiu     $2, $0, 0x1;
    b          L00129BCC;
    lui       $17, 0x45;
  L00129BA8:
    lui        $2, 0x10;
    addiu      $3, $0, -0x1;
  L00129BB0:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L00129BB0;
    nop;
  L00129BCC:
    addiu      $16, $17, -0x74F0;
  L00129BD0:
    lui        $5, (0x80000595 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000595 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgezl      $2, L00129C34;
    lw        $2, 0x24($16);
    lui        $2, 0x44;
    lw         $3, 0x7950($2);
    blez       $3, L00129C0C;
    lui       $2, 0x10;
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7AF8;
    lui        $2, (0x100000 >> 16);
  L00129C0C:
    addiu      $3, $0, -0x1;
  L00129C10:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L00129C10;
    nop;
    b          L00129BD0;
    addiu     $16, $17, -0x74F0;
  L00129C34:
    beqz       $2, L00129BA8;
    addiu     $2, $0, 0x1;
    sw         $0, 0x797C($18);
  L00129C40:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
