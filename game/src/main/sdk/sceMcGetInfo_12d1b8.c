#include "types.h"

extern void PollSema(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceMcGetInfo_12d1b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    sd         $22, 0x70($29);
    sd         $21, 0x60($29);
    lui        $22, 0x49;
    sd         $20, 0x50($29);
    addiu      $2, $22, -0x1000;
    sd         $19, 0x40($29);
    daddu      $20, $7, $0;
    sd         $18, 0x30($29);
    daddu      $19, $6, $0;
    sd         $16, 0x10($29);
    daddu      $18, $4, $0;
    sd         $31, 0x90($29);
    daddu      $16, $5, $0;
    sd         $23, 0x80($29);
    sd         $17, 0x20($29);
    lw         $3, 0x24($2);
    bnez       $3, L0012D20C;
    daddu     $21, $8, $0;
    b          L0012D308;
    addiu     $2, $0, -0x64;
  L0012D20C:
    lui        $23, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($23);
    bgez       $2, L0012D228;
    lui       $17, 0x49;
    b          L0012D308;
    addiu     $2, $0, -0xC8;
  L0012D228:
    lui        $4, 0x49;
    addiu      $3, $17, -0xF80;
    addiu      $2, $4, -0xB00;
    sw         $18, 0x4($3);
    sw         $16, 0x8($3);
    beqz       $19, L0012D250;
    sw        $2, 0x1C($3);
    addiu      $2, $0, 0x1;
    b          L0012D254;
    sw        $2, 0x14($3);
  L0012D250:
    sw         $0, 0x14($3);
  L0012D254:
    beqz       $20, L0012D268;
    addiu     $3, $17, -0xF80;
    addiu      $2, $0, 0x1;
    b          L0012D270;
    sw        $2, 0x10($3);
  L0012D268:
    addiu      $2, $17, -0xF80;
    sw         $0, 0x10($2);
  L0012D270:
    beqz       $21, L0012D284;
    addiu     $3, $17, -0xF80;
    addiu      $2, $0, 0x1;
    b          L0012D28C;
    sw        $2, 0xC($3);
  L0012D284:
    addiu      $2, $17, -0xF80;
    sw         $0, 0xC($2);
  L0012D28C:
    addiu      $16, $4, -0xB00;
    lui        $2, 0x49;
    lui        $3, 0x49;
    lui        $6, 0x49;
    sw         $19, -0xFD8($2);
    daddu      $4, $16, $0;
    sw         $20, -0xFD4($3);
    addiu      $5, $0, 0xC0;
    jal        sceSifWriteBackDCache;
    sw        $21, -0xFD0($6);
    lui        $9, 0x49;
    lui        $11, 0x13;
    sw         $16, 0x0($29);
    addiu      $4, $22, -0x1000;
    addiu      $7, $17, -0xF80;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x2EA0;
    addiu      $5, $0, 0x1;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x30;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012D2FC;
    addiu     $2, $0, 0x1;
    jal        SignalSema;
    lw        $4, -0x6AA4($23);
    b          L0012D308;
    addiu     $2, $0, -0x5B;
  L0012D2FC:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012D308:
    ld         $31, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}
