#include "types.h"

extern void _sceRpcGetPacket(void);
extern void CreateSema(void);
extern void _sceRpcFreePacket(void);
extern void sceSifSendCmd(void);
extern void DeleteSema(void);
extern void WaitSema(void);

asm void sceSifBindRpc(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $17, 0x30($29);
    sd         $19, 0x50($29);
    daddu      $17, $4, $0;
    sd         $18, 0x40($29);
    lui        $4, 0x49;
    sd         $16, 0x20($29);
    daddu      $19, $5, $0;
    sd         $31, 0x60($29);
    daddu      $18, $6, $0;
    sw         $0, 0x10($17);
    addiu      $4, $4, -0x7CC0;
    jal        _sceRpcGetPacket;
    sw        $0, 0x24($17);
    daddu      $16, $2, $0;
    beqz       $16, L0011A438;
    addiu     $2, $0, -0x1;
    lw         $2, 0x18($16);
    andi       $3, $18, 0x1;
    sw         $16, 0x0($17);
    sw         $2, 0x4($17);
    sw         $19, 0x20($16);
    sw         $16, 0x14($16);
    bnez       $3, L0011A3FC;
    sw        $17, 0x1C($16);
    lui        $2, 0x45;
    addiu      $3, $0, 0x1;
    addiu      $2, $2, 0x6918;
    sw         $3, 0x4($29);
    sw         $2, 0x14($29);
    daddu      $4, $29, $0;
    jal        CreateSema;
    sw        $0, 0x8($29);
    bgez       $2, L0011A3A4;
    sw        $2, 0x8($17);
    jal        _sceRpcFreePacket;
    daddu     $4, $16, $0;
    b          L0011A438;
    addiu     $2, $0, -0x3;
  L0011A3A4:
    lui        $4, (0x80000009 >> 16);
    daddu      $5, $16, $0;
    ori        $4, $4, (0x80000009 & 0xFFFF);
    addiu      $6, $0, 0x40;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    jal        sceSifSendCmd;
    daddu     $9, $0, $0;
    bnez       $2, L0011A3E4;
    nop;
    jal        _sceRpcFreePacket;
    daddu     $4, $16, $0;
    jal        DeleteSema;
    lw        $4, 0x8($17);
    b          L0011A438;
    addiu     $2, $0, -0x2;
  L0011A3E4:
    jal        WaitSema;
    lw        $4, 0x8($17);
    jal        DeleteSema;
    lw        $4, 0x8($17);
    b          L0011A438;
    daddu     $2, $0, $0;
  L0011A3FC:
    addiu      $2, $0, -0x1;
    lui        $4, (0x80000009 >> 16);
    sw         $2, 0x8($17);
    ori        $4, $4, (0x80000009 & 0xFFFF);
    daddu      $5, $16, $0;
    addiu      $6, $0, 0x40;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    jal        sceSifSendCmd;
    daddu     $9, $0, $0;
    bnez       $2, L0011A438;
    daddu     $2, $0, $0;
    jal        _sceRpcFreePacket;
    daddu     $4, $16, $0;
    addiu      $2, $0, -0x2;
  L0011A438:
    ld         $31, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}
