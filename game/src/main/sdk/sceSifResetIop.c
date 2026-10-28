#include "types.h"

extern void IopResetCallbacksInvokeMaybe_1227e8(void);
extern void sceSifStopDma(void);
extern void sceSifGetReg(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifSetReg(void);
extern void sceSifSetDma(void);

asm void sceSifResetIop(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    daddu      $17, $4, $0;
    daddu      $16, $5, $0;
    sd         $31, 0x30($29);
    daddu      $4, $0, $0;
    jal        IopResetCallbacksInvokeMaybe_1227e8;
    daddu     $5, $0, $0;
    addiu      $4, $0, 0x1;
    jal        IopResetCallbacksInvokeMaybe_1227e8;
    daddu     $5, $0, $0;
    jal        sceSifStopDma;
    nop;
    jal        sceSifGetReg;
    lui       $4, (0x80000000 >> 16);
    lui        $10, 0x49;
    daddu      $11, $2, $0;
    addiu      $3, $10, -0x6040;
    sw         $16, 0x14($3);
    lb         $2, 0x0($17);
    beqz       $2, L0011FB88;
    daddu     $9, $0, $0;
    daddu      $2, $17, $0;
    lbu        $4, 0x0($2);
    nop;
  L0011FB68:
    addiu      $3, $10, -0x6040;
    addu       $3, $3, $9;
    addiu      $9, $9, 0x1;
    sb         $4, 0x18($3);
    addu       $2, $17, $9;
    lb         $3, 0x0($2);
    bnel       $3, $0, L0011FB68;
    lbu       $4, 0x0($2);
  L0011FB88:
    addiu      $6, $10, -0x6040;
    lui        $3, (0x80000003 >> 16);
    sw         $0, 0x4($6);
    addiu      $4, $0, -0x1;
    dsll32     $4, $4, 0;
    ori        $4, $4, 0xFF;
    ori        $3, $3, (0x80000003 & 0xFFFF);
    addiu      $5, $0, 0x68;
    ld         $2, -0x6040($10);
    addiu      $7, $0, 0x68;
    sw         $9, 0x10($6);
    addiu      $8, $0, 0x44;
    sw         $3, 0x8($6);
    and        $2, $2, $4;
    sd         $2, -0x6040($10);
    daddu      $4, $6, $0;
    sb         $5, -0x6040($10);
    addiu      $5, $0, 0x68;
    sw         $11, 0x4($29);
    sw         $7, 0x8($29);
    sw         $8, 0xC($29);
    jal        sceSifWriteBackDCache;
    sw        $6, 0x0($29);
    addiu      $4, $0, 0x4;
    jal        sceSifSetReg;
    lui       $5, (0x40000 >> 16);
    daddu      $4, $29, $0;
    jal        sceSifSetDma;
    addiu     $5, $0, 0x1;
    beqz       $2, L0011FC3C;
    addiu     $4, $0, 0x4;
    jal        sceSifSetReg;
    lui       $5, (0x10000 >> 16);
    addiu      $4, $0, 0x4;
    jal        sceSifSetReg;
    lui       $5, (0x20000 >> 16);
    lui        $4, (0x80000002 >> 16);
    daddu      $5, $0, $0;
    jal        sceSifSetReg;
    ori       $4, $4, (0x80000002 & 0xFFFF);
    lui        $4, (0x80000000 >> 16);
    jal        sceSifSetReg;
    daddu     $5, $0, $0;
    b          L0011FC40;
    addiu     $2, $0, 0x1;
  L0011FC3C:
    daddu      $2, $0, $0;
  L0011FC40:
    ld         $31, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
