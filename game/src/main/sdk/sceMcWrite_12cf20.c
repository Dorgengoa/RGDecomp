#include "types.h"

extern void PollSema(void);
extern void FlushCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceMcWrite_12cf20(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $20, 0x50($29);
    sd         $18, 0x30($29);
    lui        $20, 0x49;
    sd         $17, 0x20($29);
    addiu      $2, $20, -0x1000;
    sd         $16, 0x10($29);
    daddu      $18, $4, $0;
    sd         $31, 0x70($29);
    daddu      $17, $5, $0;
    sd         $21, 0x60($29);
    sd         $19, 0x40($29);
    lw         $3, 0x24($2);
    bnez       $3, L0012CF64;
    daddu     $16, $6, $0;
    b          L0012D074;
    addiu     $2, $0, -0x64;
  L0012CF64:
    lui        $21, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($21);
    bgez       $2, L0012CF80;
    lui       $19, 0x49;
    b          L0012D074;
    addiu     $2, $0, -0xC8;
  L0012CF80:
    slti       $2, $16, 0x11;
    addiu      $6, $19, -0xF80;
    beqz       $2, L0012CFA0;
    sw        $18, -0xF80($19);
    sw         $16, 0x14($6);
    sw         $0, 0x18($6);
    b          L0012CFCC;
    sw        $0, 0xC($6);
  L0012CFA0:
    lui        $3, (0xFFFFFFF0 >> 16);
    addiu      $2, $17, -0x1;
    ori        $3, $3, (0xFFFFFFF0 & 0xFFFF);
    addiu      $4, $17, -0x10;
    and        $2, $2, $3;
    subu       $2, $2, $4;
    subu       $5, $16, $2;
    addu       $3, $17, $2;
    sw         $3, 0x18($6);
    sw         $5, 0xC($6);
    sw         $2, 0x14($6);
  L0012CFCC:
    addiu      $2, $19, -0xF80;
    daddu      $7, $19, $0;
    lw         $3, 0x14($2);
    beqz       $3, L0012D018;
    daddu     $6, $0, $0;
    lui        $18, 0x49;
    lui        $16, 0x13;
    addu       $2, $17, $6;
    addiu      $4, $7, -0xF80;
  L0012CFF0:
    lbu        $5, 0x0($2);
    addu       $3, $4, $6;
    addiu      $6, $6, 0x1;
    sb         $5, 0x20($3);
    lw         $2, 0x14($4);
    sltu       $2, $6, $2;
    bnez       $2, L0012CFF0;
    addu      $2, $17, $6;
    b          L0012D020;
    nop;
  L0012D018:
    lui        $18, 0x49;
    lui        $16, 0x13;
  L0012D020:
    jal        FlushCache;
    daddu     $4, $0, $0;
    addiu      $4, $20, -0x1000;
    addiu      $7, $19, -0xF80;
    addiu      $9, $18, 0x5C0;
    addiu      $11, $16, -0x3738;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x6;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x30;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012D068;
    addiu     $2, $0, 0x6;
    jal        SignalSema;
    lw        $4, -0x6AA4($21);
    b          L0012D074;
    addiu     $2, $0, -0x5B;
  L0012D068:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012D074:
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
