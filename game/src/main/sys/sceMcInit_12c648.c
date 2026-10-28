#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcInit`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcInit_12c648` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   MEDIUM-HIGH: RG may do slightly more than kh1's shown body
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcInit_12c648.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void CreateSema(void);
extern void DeleteSema(void);
extern void sceMcSync_12d098(void);
extern void WaitSema(void);
extern void sceSifInitRpc_119b60(void);
extern void sceSifBindRpc(void);
extern void scePrintf_119288(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceMcInit_12c648(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    sd         $20, 0x70($29);
    lui        $20, 0x45;
    sd         $17, 0x40($29);
    lw         $2, -0x6AA4($20);
    daddu      $17, $0, $0;
    sd         $31, 0x90($29);
    sd         $21, 0x80($29);
    sd         $19, 0x60($29);
    sd         $18, 0x50($29);
    bgez       $2, L0012C6EC;
    sd        $16, 0x30($29);
    lui        $2, 0x45;
    addiu      $16, $0, 0x1;
    addiu      $2, $2, 0x7DB0;
    sw         $16, 0x18($29);
    sw         $2, 0x24($29);
    addiu      $4, $29, 0x10;
    sw         $16, 0x14($29);
    jal        CreateSema;
    addiu     $18, $0, -0x1;
    bne        $2, $18, L0012C6AC;
    sw        $2, -0x6AA4($20);
    b          L0012C84C;
    addiu     $2, $0, -0x65;
  L0012C6AC:
    lui        $2, 0x45;
    sw         $16, 0x14($29);
    addiu      $2, $2, 0x7DC0;
    sw         $0, 0x18($29);
    sw         $2, 0x24($29);
    jal        CreateSema;
    addiu     $4, $29, 0x10;
    daddu      $16, $2, $0;
    lui        $2, 0x45;
    bne        $16, $18, L0012C6EC;
    sw        $16, -0x6AA0($2);
    jal        DeleteSema;
    lw        $4, -0x6AA4($20);
    sw         $16, -0x6AA4($20);
    b          L0012C84C;
    addiu     $2, $0, -0x65;
  L0012C6EC:
    daddu      $4, $0, $0;
    daddu      $5, $0, $0;
    jal        sceMcSync_12d098;
    daddu     $6, $0, $0;
    jal        WaitSema;
    lw        $4, -0x6AA4($20);
    jal        sceSifInitRpc_119b60;
    daddu     $4, $0, $0;
    b          L0012C74C;
    lui       $16, 0x49;
    nop;
  L0012C718:
    addiu      $2, $17, 0x1;
    lui        $3, 0x10;
  L0012C720:
    addiu      $3, $3, -0x1;
    nop;
    nop;
    nop;
    nop;
    bnez       $3, L0012C720;
    nop;
    daddu      $17, $2, $0;
    slti       $2, $17, 0x200;
    beqz       $2, L0012C838;
    lui       $4, 0x45;
  L0012C74C:
    lui        $5, (0x80000400 >> 16);
    addiu      $4, $16, -0x1000;
    ori        $5, $5, (0x80000400 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgez       $2, L0012C794;
    addiu     $18, $16, -0x1000;
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7DD8;
    nop;
  L0012C778:
    nop;
    nop;
    nop;
    nop;
    nop;
    b          L0012C778;
    nop;
  L0012C794:
    lw         $2, 0x24($18);
    beqz       $2, L0012C718;
    lui       $21, 0x49;
    daddu      $19, $18, $0;
    addiu      $17, $21, 0x5C0;
    lui        $7, 0x49;
    daddu      $9, $17, $0;
    addiu      $7, $7, -0xF80;
    sw         $0, 0x0($29);
    daddu      $4, $19, $0;
    addiu      $5, $0, 0xFE;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x30;
    addiu      $10, $0, 0xC;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    lw         $4, -0x6AA4($20);
    jal        SignalSema;
    daddu     $16, $2, $0;
    bgezl      $16, L0012C7F4;
    lw        $2, 0x4($17);
    sw         $0, 0x24($19);
    b          L0012C84C;
    addiu     $2, $0, -0x5B;
  L0012C7F4:
    slti       $2, $2, 0x20A;
    beqz       $2, L0012C814;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7DF0;
    sw         $0, 0x24($19);
    b          L0012C84C;
    addiu     $2, $0, -0x78;
  L0012C814:
    lw         $2, 0x8($17);
    slti       $2, $2, 0x20E;
    beqz       $2, L0012C848;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7E18;
    sw         $0, 0x24($18);
    b          L0012C84C;
    addiu     $2, $0, -0x79;
  L0012C838:
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7DD8;
    b          L0012C84C;
    addiu     $2, $0, -0x5B;
  L0012C848:
    lw         $2, 0x5C0($21);
  L0012C84C:
    ld         $31, 0x90($29);
    ld         $21, 0x80($29);
    ld         $20, 0x70($29);
    ld         $19, 0x60($29);
    ld         $18, 0x50($29);
    ld         $17, 0x40($29);
    ld         $16, 0x30($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}
