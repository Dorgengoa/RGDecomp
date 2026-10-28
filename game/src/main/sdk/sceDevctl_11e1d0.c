#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceDevctl`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceDevctl_11e1d0` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceDevctl_11e1d0.s -- the SDK
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

asm void sceDevctl_11e1d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xE0;
    sd         $19, 0x70($29);
    sd         $30, 0xC0($29);
    daddu      $19, $4, $0;
    sd         $21, 0x90($29);
    daddu      $30, $9, $0;
    sd         $18, 0x60($29);
    daddu      $21, $5, $0;
    sd         $16, 0x40($29);
    daddu      $18, $6, $0;
    sd         $17, 0x50($29);
    daddu      $16, $7, $0;
    sd         $31, 0xD0($29);
    addiu      $4, $0, 0x17;
    sd         $23, 0xB0($29);
    sd         $22, 0xA0($29);
    sd         $20, 0x80($29);
    jal        FileIoLock_11b300;
    sw        $8, 0x34($29);
    lui        $2, 0x49;
    addiu      $17, $2, -0x7C40;
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnel       $3, $0, L0011E240;
    lbu       $2, 0x0($19);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($19);
  L0011E240:
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011E284;
    sb        $2, 0xC($17);
    sltiu      $6, $16, 0x401;
    addiu      $5, $5, 0x1;
  L0011E258:
    slti       $2, $5, 0x400;
    beqz       $2, L0011E288;
    addu      $2, $19, $5;
    addu       $4, $17, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0xC($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011E258;
    addiu     $5, $5, 0x1;
    b          L0011E28C;
    addiu     $2, $0, 0x400;
  L0011E284:
    sltiu      $6, $16, 0x401;
  L0011E288:
    addiu      $2, $0, 0x400;
  L0011E28C:
    beql       $5, $2, L0011E294;
    sb        $0, 0x40B($17);
  L0011E294:
    beqz       $6, L0011E2D0;
    sltiu     $2, $30, 0x401;
    beqz       $2, L0011E2D0;
    addiu     $2, $0, 0x4601;
    bne        $21, $2, L0011E2E0;
    nop;
    lw         $2, 0x4($18);
    bnel       $2, $0, L0011E2C8;
    lw        $2, 0xC($18);
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011E448;
    daddu     $2, $0, $0;
  L0011E2C8:
    bnez       $2, L0011E2E0;
    nop;
  L0011E2D0:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011E448;
    addiu     $2, $0, -0x16;
  L0011E2E0:
    beqz       $16, L0011E328;
    daddu     $5, $0, $0;
    addiu      $6, $17, 0x40C;
    lui        $7, 0x45;
    addiu      $19, $29, 0x30;
    lui        $23, (0x490000 >> 16);
    lui        $22, (0x490000 >> 16);
    nop;
  L0011E300:
    addu       $2, $18, $5;
    addu       $4, $6, $5;
    lbu        $3, 0x0($2);
    addiu      $5, $5, 0x1;
    sltu       $2, $5, $16;
    sb         $3, 0x0($4);
    bnez       $2, L0011E300;
    nop;
    b          L0011E33C;
    sw        $16, 0x810($17);
  L0011E328:
    lui        $7, 0x45;
    addiu      $19, $29, 0x30;
    lui        $23, 0x49;
    lui        $22, 0x49;
    sw         $16, 0x810($17);
  L0011E33C:
    addiu      $3, $7, 0x6BA8;
    addiu      $2, $0, 0x1;
    sw         $3, 0x24($29);
    sw         $2, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $21, 0x80C($17);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $20, $2, $0;
    sw         $30, 0x818($17);
    addiu      $2, $0, 0x4;
    sw         $19, 0x4($17);
    sw         $2, 0x8($17);
    addiu      $3, $0, 0x4601;
    lw         $2, 0x34($29);
    sw         $20, 0x0($17);
    bne        $21, $3, L0011E3A8;
    sw        $2, 0x814($17);
    lw         $5, 0xC($18);
    addiu      $17, $0, 0x1C;
    lw         $2, 0x4($18);
    mult       $0, $2, $5;
    mflo       $5;
    jal        sceSifWriteBackDCache;
    lw        $4, 0x8($18);
    b          L0011E3B0;
    lui       $2, 0x49;
  L0011E3A8:
    addiu      $17, $0, 0x17;
    lui        $2, 0x49;
  L0011E3B0:
    addiu      $5, $0, 0x81C;
    addiu      $16, $2, -0x7C40;
    addiu      $18, $22, -0x7000;
    jal        sceSifWriteBackDCache;
    daddu     $4, $16, $0;
    addiu      $4, $23, -0x6540;
    daddu      $5, $17, $0;
    daddu      $7, $16, $0;
    sw         $0, 0x0($29);
    sw         $0, 0x8($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x81C;
    daddu      $9, $18, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011E410;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $20, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011E448;
    addiu     $2, $0, -0xB;
  L0011E410:
    or         $2, $18, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011E434;
    nop;
    jal        DeleteSema;
    daddu     $4, $20, $0;
    b          L0011E448;
    addiu     $2, $0, -0xB;
  L0011E434:
    jal        WaitSema;
    daddu     $4, $20, $0;
    jal        DeleteSema;
    daddu     $4, $20, $0;
    lw         $2, 0x30($29);
  L0011E448:
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
