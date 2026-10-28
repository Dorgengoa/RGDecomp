#include "types.h"

extern void _sceRpcGetPacket(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifSendCmd(void);
extern void CreateSema(void);
extern void _sceRpcFreePacket(void);
extern void DeleteSema(void);
extern void WaitSema(void);

asm void sceSifCallRpc(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $17, 0x30($29);
    daddu      $17, $4, $0;
    sd         $30, 0xA0($29);
    sd         $23, 0x90($29);
    lui        $4, 0x49;
    sd         $22, 0x80($29);
    daddu      $30, $6, $0;
    sd         $21, 0x70($29);
    daddu      $22, $5, $0;
    sd         $20, 0x60($29);
    daddu      $21, $7, $0;
    sd         $19, 0x50($29);
    daddu      $20, $9, $0;
    sd         $18, 0x40($29);
    daddu      $19, $10, $0;
    sd         $16, 0x20($29);
    daddu      $18, $8, $0;
    sd         $31, 0xB0($29);
    daddu      $23, $11, $0;
    jal        _sceRpcGetPacket;
    addiu     $4, $4, -0x7CC0;
    daddu      $16, $2, $0;
    beqz       $16, L0011A6B8;
    addiu     $2, $0, -0x1;
    lw         $2, 0xC0($29);
    lw         $3, 0x18($16);
    sw         $2, 0x20($17);
    sw         $3, 0x4($17);
    sw         $16, 0x0($17);
    sw         $23, 0x1C($17);
    daddu      $2, $28, $0;
    sw         $2, 0x18($17);
    andi       $3, $30, 0x2;
    sw         $22, 0x20($16);
    sw         $18, 0x24($16);
    sw         $20, 0x28($16);
    sw         $19, 0x2C($16);
    sw         $16, 0x14($16);
    lw         $2, 0x24($17);
    sw         $17, 0x1C($16);
    bnez       $3, L0011A5D4;
    sw        $2, 0x34($16);
    bne        $21, $20, L0011A5B4;
    slt       $2, $18, $19;
    daddu      $5, $19, $0;
    daddu      $4, $21, $0;
    jal        sceSifWriteBackDCache;
    movz      $5, $18, $2;
    b          L0011A5D8;
    andi      $2, $30, 0x1;
  L0011A5B4:
    blez       $18, L0011A5C4;
    daddu     $4, $21, $0;
    jal        sceSifWriteBackDCache;
    daddu     $5, $18, $0;
  L0011A5C4:
    blez       $19, L0011A5D4;
    daddu     $4, $20, $0;
    jal        sceSifWriteBackDCache;
    daddu     $5, $19, $0;
  L0011A5D4:
    andi       $2, $30, 0x1;
  L0011A5D8:
    beqz       $2, L0011A62C;
    lui       $2, 0x45;
    bnez       $23, L0011A5F0;
    addiu     $2, $0, 0x1;
    b          L0011A5F4;
    sw        $0, 0x30($16);
  L0011A5F0:
    sw         $2, 0x30($16);
  L0011A5F4:
    addiu      $2, $0, -0x1;
    lui        $4, (0x8000000A >> 16);
    lw         $8, 0x14($17);
    daddu      $7, $21, $0;
    sw         $2, 0x8($17);
    daddu      $9, $18, $0;
    ori        $4, $4, (0x8000000A & 0xFFFF);
    daddu      $5, $16, $0;
    jal        sceSifSendCmd;
    addiu     $6, $0, 0x40;
    bnez       $2, L0011A6B8;
    daddu     $2, $0, $0;
    b          L0011A694;
    nop;
  L0011A62C:
    addiu      $19, $0, 0x1;
    addiu      $2, $2, 0x6928;
    sw         $0, 0x8($29);
    sw         $2, 0x14($29);
    daddu      $4, $29, $0;
    jal        CreateSema;
    sw        $19, 0x4($29);
    bgez       $2, L0011A660;
    sw        $2, 0x8($17);
    jal        _sceRpcFreePacket;
    daddu     $4, $16, $0;
    b          L0011A6B8;
    addiu     $2, $0, -0x3;
  L0011A660:
    sw         $19, 0x30($16);
    lui        $4, (0x8000000A >> 16);
    daddu      $7, $21, $0;
    daddu      $9, $18, $0;
    lw         $8, 0x14($17);
    ori        $4, $4, (0x8000000A & 0xFFFF);
    daddu      $5, $16, $0;
    jal        sceSifSendCmd;
    addiu     $6, $0, 0x40;
    bnez       $2, L0011A6A4;
    nop;
    jal        DeleteSema;
    lw        $4, 0x8($17);
  L0011A694:
    jal        _sceRpcFreePacket;
    daddu     $4, $16, $0;
    b          L0011A6B8;
    addiu     $2, $0, -0x2;
  L0011A6A4:
    jal        WaitSema;
    lw        $4, 0x8($17);
    jal        DeleteSema;
    lw        $4, 0x8($17);
    daddu      $2, $0, $0;
  L0011A6B8:
    ld         $31, 0xB0($29);
    ld         $30, 0xA0($29);
    ld         $23, 0x90($29);
    ld         $22, 0x80($29);
    ld         $21, 0x70($29);
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}
