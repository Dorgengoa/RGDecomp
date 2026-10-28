#include "types.h"

extern void sceSifInitRpc_119b60(void);
extern void sceSifBindRpc(void);
extern void scePrintf_119288(void);
extern void FlushCache(void);

asm void sceSdRemoteInit_122890(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    daddu      $4, $0, $0;
    sd         $16, 0x0($29);
    sd         $18, 0x20($29);
    lui        $16, 0x49;
    sd         $17, 0x10($29);
    addiu      $18, $16, -0x26C0;
    sd         $31, 0x30($29);
    jal        sceSifInitRpc_119b60;
    lui       $17, 0x45;
  L001228B8:
    lui        $5, (0x80000701 >> 16);
    addiu      $4, $16, -0x26C0;
    ori        $5, $5, (0x80000701 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgez       $2, L001228E4;
    addiu     $2, $0, 0x2710;
    jal        scePrintf_119288;
    addiu     $4, $17, 0x6CD8;
    b          L00122928;
    addiu     $2, $0, -0x1;
  L001228E4:
    addiu      $3, $0, -0x1;
  L001228E8:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L001228E8;
    nop;
    lw         $2, 0x24($18);
    beqz       $2, L001228B8;
    lui       $2, 0x44;
    lui        $3, 0x44;
    sw         $0, 0x78D0($2);
    daddu      $4, $0, $0;
    jal        FlushCache;
    sw        $0, 0x78D4($3);
    daddu      $2, $0, $0;
  L00122928:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
