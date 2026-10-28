#include "types.h"

extern void sceSifWriteBackDCache(void);
extern void DisableIntr_120660(void);
extern void _sceRpcGetFPacket2(void);
extern void _sceRpcGetFPacket(void);
extern void EnableIntr_1206b0(void);
extern void sceSifSendCmd(void);
extern void sceSifSetDma(void);

asm void sceSifExecRequest(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $20, 0x60($29);
    sd         $18, 0x40($29);
    daddu      $20, $0, $0;
    sd         $17, 0x30($29);
    sd         $31, 0x70($29);
    daddu      $17, $4, $0;
    sd         $19, 0x50($29);
    sd         $16, 0x20($29);
    lw         $2, 0x4($17);
    lw         $4, 0x24($17);
    lw         $5, 0x8($17);
    jalr $31, $2;
    lw        $6, 0xC($17);
    daddu      $18, $2, $0;
    bnel       $18, $0, L0011AA54;
    lw        $20, 0x2C($17);
  L0011AA54:
    lw         $5, 0xC($17);
    blez       $5, L0011AA68;
    nop;
    jal        sceSifWriteBackDCache;
    lw        $4, 0x8($17);
  L0011AA68:
    blez       $20, L0011AA78;
    daddu     $4, $18, $0;
    jal        sceSifWriteBackDCache;
    daddu     $5, $20, $0;
  L0011AA78:
    jal        DisableIntr_120660;
    nop;
    lw         $5, 0x34($17);
    andi       $2, $5, 0x4;
    beqz       $2, L0011AAA4;
    srl       $5, $5, 16;
    lui        $4, 0x49;
    jal        _sceRpcGetFPacket2;
    addiu     $4, $4, -0x7CC0;
    b          L0011AAB4;
    daddu     $16, $2, $0;
  L0011AAA4:
    lui        $4, 0x49;
    jal        _sceRpcGetFPacket;
    addiu     $4, $4, -0x7CC0;
    daddu      $16, $2, $0;
  L0011AAB4:
    jal        EnableIntr_1206b0;
    nop;
    lui        $3, (0x8000000A >> 16);
    lw         $4, 0x1C($17);
    ori        $3, $3, (0x8000000A & 0xFFFF);
    sw         $3, 0x20($16);
    sw         $4, 0x1C($16);
    lw         $2, 0x30($17);
    beql       $2, $0, L0011AB10;
    sw        $0, 0x18($16);
    nop;
  L0011AAE0:
    lui        $4, (0x80000008 >> 16);
    lw         $8, 0x28($17);
    ori        $4, $4, (0x80000008 & 0xFFFF);
    daddu      $5, $16, $0;
    addiu      $6, $0, 0x40;
    daddu      $7, $18, $0;
    jal        sceSifSendCmd;
    daddu     $9, $20, $0;
    beqz       $2, L0011AAE0;
    ld        $31, 0x70($29);
    b          L0011ABBC;
    ld        $20, 0x60($29);
  L0011AB10:
    daddu      $19, $0, $0;
    blez       $20, L0011AB34;
    sw        $0, 0x10($16);
    lw         $2, 0x28($17);
    addiu      $19, $0, 0x1;
    sw         $18, 0x0($29);
    sw         $2, 0x4($29);
    sw         $20, 0x8($29);
    sw         $0, 0xC($29);
  L0011AB34:
    sll        $5, $19, 4;
    lw         $4, 0x20($17);
    addu       $3, $29, $5;
    addiu      $2, $29, 0x4;
    sw         $16, 0x0($3);
    addu       $2, $2, $5;
    sw         $4, 0x0($2);
    addiu      $3, $29, 0x8;
    addu       $3, $3, $5;
    addiu      $4, $0, 0x40;
    addiu      $2, $29, 0xC;
    sw         $4, 0x0($3);
    addu       $2, $2, $5;
    addiu      $19, $19, 0x1;
    sw         $0, 0x0($2);
    daddu      $4, $29, $0;
    nop;
  L0011AB78:
    jal        sceSifSetDma;
    daddu     $5, $19, $0;
    bnez       $2, L0011ABB8;
    ld        $31, 0x70($29);
    lui        $3, 0x10;
    addiu      $4, $0, -0x1;
  L0011AB90:
    addiu      $3, $3, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $3, $4, L0011AB90;
    nop;
    beql       $2, $0, L0011AB78;
    daddu     $4, $29, $0;
    ld         $31, 0x70($29);
  L0011ABB8:
    ld         $20, 0x60($29);
  L0011ABBC:
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

