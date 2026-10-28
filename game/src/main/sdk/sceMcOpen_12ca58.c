#include "types.h"

extern void PollSema(void);
extern void SignalSema(void);
extern void strncpy(void);
extern void sceSifCallRpc(void);

asm void sceMcOpen_12ca58(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    lui        $2, 0x49;
    sd         $22, 0x70($29);
    sd         $21, 0x60($29);
    addiu      $22, $2, -0x1000;
    sd         $20, 0x50($29);
    daddu      $21, $5, $0;
    sd         $19, 0x40($29);
    daddu      $20, $4, $0;
    sd         $17, 0x20($29);
    daddu      $19, $7, $0;
    sd         $31, 0x80($29);
    sd         $18, 0x30($29);
    sd         $16, 0x10($29);
    lw         $2, 0x24($22);
    bnez       $2, L0012CAA4;
    daddu     $17, $6, $0;
    b          L0012CB58;
    addiu     $2, $0, -0x64;
  L0012CAA4:
    lui        $18, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($18);
    bltz       $2, L0012CB58;
    addiu     $2, $0, -0xC8;
    beqz       $17, L0012CACC;
    nop;
    lb         $2, 0x0($17);
    bnez       $2, L0012CADC;
    lui       $16, 0x49;
  L0012CACC:
    jal        SignalSema;
    lw        $4, -0x6AA4($18);
    b          L0012CB58;
    addiu     $2, $0, -0xD2;
  L0012CADC:
    daddu      $5, $17, $0;
    addiu      $16, $16, -0xF3C;
    addiu      $6, $0, 0x3FF;
    jal        strncpy;
    daddu     $4, $16, $0;
    addiu      $3, $16, -0x14;
    sw         $20, -0x14($16);
    lui        $9, 0x49;
    lui        $11, 0x13;
    sw         $19, 0x8($3);
    daddu      $4, $22, $0;
    sw         $21, 0x4($3);
    daddu      $7, $3, $0;
    sb         $0, 0x413($3);
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x3738;
    addiu      $5, $0, 0x2;
    sw         $0, 0x0($29);
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x414;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012CB4C;
    addiu     $2, $0, 0x2;
    jal        SignalSema;
    lw        $4, -0x6AA4($18);
    b          L0012CB58;
    addiu     $2, $0, -0x5B;
  L0012CB4C:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012CB58:
    ld         $31, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
