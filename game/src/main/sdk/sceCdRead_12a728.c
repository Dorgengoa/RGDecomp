#include "types.h"

extern void sceCdNcmdDiskReady_129c58(void);
extern void CdCheckNCmd_129b00(void);
extern void sceSifWriteBackDCache(void);
extern void scePrintf_119288(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdRead_12a728(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    lui        $3, 0x44;
    sd         $21, 0x60($29);
    lui        $21, 0x44;
    sd         $20, 0x50($29);
    lw         $2, 0x7978($21);
    daddu      $20, $6, $0;
    sd         $19, 0x40($29);
    sd         $18, 0x30($29);
    daddu      $19, $4, $0;
    sd         $17, 0x20($29);
    addiu      $18, $3, 0x7A40;
    sd         $16, 0x10($29);
    daddu      $17, $5, $0;
    sd         $31, 0x70($29);
    andi       $2, $2, 0x1;
    bnez       $2, L0012A784;
    daddu     $16, $7, $0;
    jal        sceCdNcmdDiskReady_129c58;
    nop;
    addiu      $3, $0, 0x6;
    beq        $2, $3, L0012A8E4;
    daddu     $2, $0, $0;
  L0012A784:
    jal        CdCheckNCmd_129b00;
    addiu     $4, $0, 0x4;
    beqz       $2, L0012A8C4;
    lui       $8, 0x45;
    sw         $19, 0x0($18);
    sw         $17, 0x4($18);
    lui        $19, 0x45;
    sw         $20, 0x8($18);
    addiu      $4, $19, -0x75C0;
    addiu      $5, $8, -0x7500;
    addiu      $6, $0, 0x1;
    lbu        $2, 0x0($16);
    sb         $2, 0xC($18);
    lbu        $3, 0x1($16);
    sb         $3, 0xD($18);
    lbu        $2, 0x2($16);
    sw         $4, 0x10($18);
    sb         $2, 0xE($18);
    sw         $5, 0x14($18);
    lbu        $7, 0x2($16);
    beq        $7, $6, L0012A7F8;
    slti      $2, $7, 0x2;
    bnez       $2, L0012A808;
    sll       $5, $17, 11;
    addiu      $2, $0, 0x2;
    beq        $7, $2, L0012A804;
    addiu     $2, $0, 0x924;
    b          L0012A808;
    nop;
  L0012A7F8:
    addiu      $2, $0, 0x918;
    b          L0012A808;
    mult      $5, $17, $2;
  L0012A804:
    mult       $5, $17, $2;
  L0012A808:
    lw         $2, 0x7978($21);
    addiu      $16, $8, -0x7500;
    andi       $2, $2, 0x2;
    bnez       $2, L0012A824;
    sw        $0, -0x7500($8);
    jal        sceSifWriteBackDCache;
    daddu     $4, $20, $0;
  L0012A824:
    addiu      $19, $19, -0x75C0;
    addiu      $5, $0, 0x90;
    daddu      $4, $19, $0;
    jal        sceSifWriteBackDCache;
    lui       $20, 0x44;
    daddu      $4, $18, $0;
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x18;
    daddu      $4, $16, $0;
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x4;
    lw         $2, 0x7950($20);
    blez       $2, L0012A864;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7C08;
  L0012A864:
    addiu      $2, $0, 0x1;
    lui        $16, 0x44;
    sw         $2, 0x79A0($16);
    lui        $17, 0x44;
    lui        $4, 0x45;
    lui        $11, 0x13;
    sw         $2, 0x7974($17);
    addiu      $4, $4, -0x74F0;
    sw         $19, 0x0($29);
    daddu      $7, $18, $0;
    addiu      $11, $11, -0x6BB0;
    addiu      $5, $0, 0x1;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x18;
    daddu      $9, $0, $0;
    jal        sceSifCallRpc;
    daddu     $10, $0, $0;
    bgezl      $2, L0012A8CC;
    lw        $2, 0x7950($20);
    sw         $0, 0x79A0($16);
    lui        $2, 0x44;
    sw         $0, 0x7974($17);
    jal        SignalSema;
    lw        $4, 0x7968($2);
  L0012A8C4:
    b          L0012A8E4;
    daddu     $2, $0, $0;
  L0012A8CC:
    blez       $2, L0012A8E4;
    addiu     $2, $0, 0x1;
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7C20;
    addiu      $2, $0, 0x1;
  L0012A8E4:
    ld         $31, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
