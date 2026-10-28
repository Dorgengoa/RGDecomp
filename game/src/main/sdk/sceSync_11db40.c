#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceSync`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceSync_11db40` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceSync_11db40.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void CreateSema(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void FileIoUnlock_11b330(void);
extern void WaitSema(void);

asm void sceSync_11db40(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $17, 0x50($29);
    sd         $21, 0x90($29);
    daddu      $17, $4, $0;
    sd         $22, 0xA0($29);
    daddu      $21, $5, $0;
    sd         $16, 0x40($29);
    addiu      $4, $0, 0x13;
    sd         $31, 0xB0($29);
    lui        $22, 0x49;
    sd         $20, 0x80($29);
    addiu      $16, $22, -0x7C40;
    sd         $19, 0x70($29);
    jal        FileIoLock_11b300;
    sd        $18, 0x60($29);
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnel       $3, $0, L0011DB98;
    lbu       $2, 0x0($17);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($17);
  L0011DB98:
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011DBEC;
    sb        $2, 0x14($16);
    lui        $6, 0x45;
    addiu      $18, $29, 0x30;
    lui        $20, 0x49;
    lui        $19, 0x49;
    addiu      $5, $5, 0x1;
    nop;
  L0011DBC0:
    slti       $2, $5, 0x400;
    beqz       $2, L0011DBFC;
    addu      $2, $17, $5;
    addu       $4, $16, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0x14($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011DBC0;
    addiu     $5, $5, 0x1;
    b          L0011DC00;
    addiu     $2, $0, 0x400;
  L0011DBEC:
    lui        $6, 0x45;
    addiu      $18, $29, 0x30;
    lui        $20, 0x49;
    lui        $19, 0x49;
  L0011DBFC:
    addiu      $2, $0, 0x400;
  L0011DC00:
    beql       $5, $2, L0011DC08;
    sb        $0, 0x413($16);
  L0011DC08:
    sw         $21, 0x10($16);
    addiu      $3, $6, 0x6B60;
    addiu      $2, $0, 0x1;
    addiu      $4, $29, 0x10;
    sw         $2, 0x14($29);
    addiu      $19, $19, -0x7000;
    sw         $3, 0x24($29);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $17, $2, $0;
    sw         $18, 0x4($16);
    addiu      $2, $0, 0x4;
    sw         $17, 0x0($16);
    sw         $2, 0x8($16);
    addiu      $4, $20, -0x6540;
    addiu      $7, $22, -0x7C40;
    addiu      $5, $0, 0x13;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    sw         $0, 0x8($29);
    addiu      $8, $0, 0x414;
    daddu      $9, $19, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011DC8C;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011DCC4;
    addiu     $2, $0, -0xB;
  L0011DC8C:
    or         $2, $19, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011DCB0;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011DCC4;
    addiu     $2, $0, -0xB;
  L0011DCB0:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011DCC4:
    ld         $31, 0xB0($29);
    ld         $22, 0xA0($29);
    ld         $21, 0x90($29);
    ld         $20, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}
