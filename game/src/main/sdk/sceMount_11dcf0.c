#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMount`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceMount_11dcf0` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMount_11dcf0.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void FileIoUnlock_11b330(void);
extern void CreateSema(void);
extern void sceSifWriteBackDCache(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void WaitSema(void);

asm void sceMount_11dcf0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xE0;
    sd         $16, 0x40($29);
    sd         $23, 0xB0($29);
    daddu      $16, $4, $0;
    sd         $22, 0xA0($29);
    daddu      $23, $6, $0;
    sd         $19, 0x70($29);
    daddu      $22, $7, $0;
    sd         $17, 0x50($29);
    daddu      $19, $5, $0;
    sd         $30, 0xC0($29);
    daddu      $17, $8, $0;
    sd         $18, 0x60($29);
    addiu      $4, $0, 0x14;
    sd         $31, 0xD0($29);
    lui        $30, 0x49;
    sd         $21, 0x90($29);
    addiu      $18, $30, -0x7C40;
    jal        FileIoLock_11b300;
    sd        $20, 0x80($29);
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    bnel       $2, $0, L0011DD5C;
    lbu       $2, 0x0($16);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($16);
  L0011DD5C:
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011DDA4;
    sb        $2, 0xC($18);
    slti       $7, $17, 0x401;
    addiu      $5, $5, 0x1;
    nop;
  L0011DD78:
    slti       $2, $5, 0x400;
    beqz       $2, L0011DDA8;
    addu      $2, $16, $5;
    addu       $4, $18, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0xC($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011DD78;
    addiu     $5, $5, 0x1;
    b          L0011DDAC;
    addiu     $2, $0, 0x400;
  L0011DDA4:
    slti       $7, $17, 0x401;
  L0011DDA8:
    addiu      $2, $0, 0x400;
  L0011DDAC:
    beql       $5, $2, L0011DDB4;
    sb        $0, 0x40B($18);
  L0011DDB4:
    lbu        $2, 0x0($19);
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011DDF4;
    sb        $2, 0x40C($18);
    addiu      $6, $18, 0x40C;
    addiu      $5, $5, 0x1;
  L0011DDD0:
    slti       $2, $5, 0x400;
    beqz       $2, L0011DDF4;
    addu      $2, $19, $5;
    addu       $4, $6, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0x0($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011DDD0;
    addiu     $5, $5, 0x1;
  L0011DDF4:
    addiu      $2, $0, 0x400;
    beql       $5, $2, L0011DE00;
    sb        $0, 0x80B($18);
  L0011DE00:
    bnez       $7, L0011DE18;
    nop;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011DF40;
    addiu     $2, $0, -0x7;
  L0011DE18:
    blez       $17, L0011DE60;
    daddu     $5, $0, $0;
    addiu      $6, $18, 0x80C;
    lui        $7, 0x45;
    addiu      $19, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
    nop;
  L0011DE38:
    addu       $2, $22, $5;
    addu       $4, $6, $5;
    lbu        $3, 0x0($2);
    addiu      $5, $5, 0x1;
    slt        $2, $5, $17;
    sb         $3, 0x0($4);
    bnez       $2, L0011DE38;
    nop;
    b          L0011DE74;
    sw        $17, 0xC10($18);
  L0011DE60:
    lui        $7, 0x45;
    addiu      $19, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
    sw         $17, 0xC10($18);
  L0011DE74:
    addiu      $3, $7, 0x6B78;
    sw         $23, 0xC0C($18);
    addiu      $2, $0, 0x1;
    addiu      $4, $29, 0x10;
    sw         $2, 0x14($29);
    sw         $3, 0x24($29);
    addiu      $16, $30, -0x7C40;
    sw         $0, 0x18($29);
    jal        CreateSema;
    addiu     $20, $20, -0x7000;
    daddu      $17, $2, $0;
    daddu      $4, $16, $0;
    addiu      $2, $0, 0x4;
    sw         $19, 0x4($18);
    sw         $2, 0x8($18);
    addiu      $5, $0, 0xC14;
    jal        sceSifWriteBackDCache;
    sw        $17, 0x0($18);
    addiu      $4, $21, -0x6540;
    daddu      $7, $16, $0;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x14;
    sw         $0, 0x8($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0xC14;
    daddu      $9, $20, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011DF08;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011DF40;
    addiu     $2, $0, -0xB;
  L0011DF08:
    or         $2, $20, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011DF2C;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011DF40;
    addiu     $2, $0, -0xB;
  L0011DF2C:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011DF40:
    ld         $31, 0xD0($29);
    ld         $30, 0xC0($29);
    ld         $23, 0xB0($29);
    ld         $22, 0xA0($29);
    ld         $21, 0x90($29);
    ld         $20, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0xE0;
}
