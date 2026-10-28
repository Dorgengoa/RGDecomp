#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceFsInit`
   (ethteck/kh1 src/lib/filestub.c), kept as `SceFsInit_11b428` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/SceFsInit_11b428.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void sceSifInitRpc_119b60(void);
extern void DisableIntr_120660(void);
extern void sceSifAddCmdHandler(void);
extern void EnableIntr_1206b0(void);
extern void sceSifBindRpc(void);
extern void StdioInitSemas_11ac18(void);
extern void WaitSema(void);
extern void SignalSema(void);
extern void SifCallRpcRetry_11ad90(void);

asm void SceFsInit_11b428(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    daddu      $4, $0, $0;
    sd         $16, 0x20($29);
    lui        $16, 0x49;
    sd         $17, 0x30($29);
    sd         $31, 0x70($29);
    addiu      $17, $16, -0x64C0;
    sd         $20, 0x60($29);
    sd         $19, 0x50($29);
    jal        sceSifInitRpc_119b60;
    sd        $18, 0x40($29);
    sw         $0, -0x64C0($16);
    jal        DisableIntr_120660;
    sw        $0, 0x4($17);
    lui        $5, 0x12;
    lui        $6, 0x49;
    lui        $4, (0x80000011 >> 16);
    daddu      $16, $2, $0;
    addiu      $5, $5, -0x5110;
    addiu      $6, $6, -0x6500;
    jal        sceSifAddCmdHandler;
    ori       $4, $4, (0x80000011 & 0xFFFF);
    lui        $5, 0x12;
    lui        $4, (0x80000013 >> 16);
    addiu      $5, $5, -0x4C20;
    daddu      $6, $17, $0;
    jal        sceSifAddCmdHandler;
    ori       $4, $4, (0x80000013 & 0xFFFF);
    beqz       $16, L0011B4D4;
    lui       $19, 0x49;
    jal        EnableIntr_1206b0;
    addiu     $16, $19, -0x6540;
    b          L0011B4D8;
    nop;
  L0011B4B0:
    addiu      $3, $0, -0x1;
    nop;
  L0011B4B8:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L0011B4B8;
    nop;
  L0011B4D4:
    addiu      $16, $19, -0x6540;
  L0011B4D8:
    lui        $5, (0x80000001 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000001 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bltz       $2, L0011B610;
    addiu     $2, $0, -0x16;
    lw         $2, 0x24($16);
    beqz       $2, L0011B4B0;
    lui       $2, 0x10;
    jal        StdioInitSemas_11ac18;
    lui       $20, 0x44;
    jal        WaitSema;
    lw        $4, 0x62A8($20);
    lui        $3, 0x49;
    addiu      $3, $3, -0x6740;
    addiu      $4, $3, 0x200;
    sltu       $2, $3, $4;
    beqz       $2, L0011B554;
    lui       $18, 0x49;
    lui        $17, 0x49;
    lui        $16, 0x49;
  L0011B530:
    sw         $0, 0x4($3);
    addiu      $3, $3, 0x10;
    sltu       $2, $3, $4;
    nop;
    nop;
    bnez       $2, L0011B530;
    nop;
    b          L0011B560;
    lw        $4, 0x62A8($20);
  L0011B554:
    lui        $17, 0x49;
    lui        $16, 0x49;
    lw         $4, 0x62A8($20);
  L0011B560:
    jal        SignalSema;
    addiu     $16, $16, -0x7000;
    addiu      $3, $17, -0x6FC0;
    addiu      $7, $18, -0x7C80;
    sw         $3, -0x7C80($18);
    addiu      $4, $19, -0x6540;
    addiu      $3, $3, 0x440;
    addiu      $5, $0, 0xFF;
    sw         $3, 0x4($7);
    daddu      $6, $0, $0;
    sw         $0, 0x0($29);
    addiu      $8, $0, 0x8;
    sw         $0, 0x8($29);
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x8;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011B5B8;
    lui       $4, (0x20000000 >> 16);
    lui        $2, (0xFFFEFFFF >> 16);
    b          L0011B610;
    ori       $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011B5B8:
    addiu      $2, $16, 0x4;
    or         $3, $16, $4;
    or         $2, $2, $4;
    lui        $5, 0x49;
    addiu      $8, $5, -0x6518;
    lwl        $4, 0x3($3);
    lwr        $4, 0x0($3);
    swl        $4, 0x3($8);
    swr        $4, 0x0($8);
    lwl        $3, (0x20000003 & 0xFFFF)($2);
    lwr        $3, (0x20000000 & 0xFFFF)($2);
    swl        $3, 0x13($29);
    swr        $3, 0x10($29);
    lui        $6, 0x44;
    lui        $5, 0x44;
    lw         $3, 0x10($29);
    addiu      $4, $0, 0x1;
    sw         $4, 0x629C($5);
    daddu      $2, $0, $0;
    xori       $3, $3, 0x2;
    sltiu      $3, $3, 0x1;
    sw         $3, 0x62A0($6);
  L0011B610:
    ld         $31, 0x70($29);
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
