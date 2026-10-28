#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceFormat`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceFormat_11cdb8` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceFormat_11cdb8.s -- the SDK
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

asm void sceFormat_11cdb8(void)
{
    .set noreorder;
    addiu      $29, $29, -0xD0;
    sd         $16, 0x40($29);
    sd         $22, 0xA0($29);
    daddu      $16, $4, $0;
    sd         $18, 0x60($29);
    daddu      $22, $6, $0;
    sd         $17, 0x50($29);
    daddu      $18, $5, $0;
    sd         $23, 0xB0($29);
    daddu      $17, $7, $0;
    sd         $19, 0x70($29);
    addiu      $4, $0, 0xE;
    sd         $31, 0xC0($29);
    lui        $23, 0x49;
    sd         $21, 0x90($29);
    addiu      $19, $23, -0x7C40;
    jal        FileIoLock_11b300;
    sd        $20, 0x80($29);
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnel       $3, $0, L0011CE1C;
    lbu       $2, 0x0($16);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($16);
  L0011CE1C:
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011CE64;
    sb        $2, 0xC($19);
    slti       $7, $17, 0x401;
    addiu      $5, $5, 0x1;
    nop;
  L0011CE38:
    slti       $2, $5, 0x400;
    beqz       $2, L0011CE68;
    addu      $2, $16, $5;
    addu       $4, $19, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0xC($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011CE38;
    addiu     $5, $5, 0x1;
    b          L0011CE6C;
    addiu     $2, $0, 0x400;
  L0011CE64:
    slti       $7, $17, 0x401;
  L0011CE68:
    addiu      $2, $0, 0x400;
  L0011CE6C:
    beql       $5, $2, L0011CE74;
    sb        $0, 0x40B($19);
  L0011CE74:
    bnel       $18, $0, L0011CE84;
    lbu       $2, 0x0($18);
    b          L0011CED0;
    sb        $0, 0x40C($19);
  L0011CE84:
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011CEC4;
    sb        $2, 0x40C($19);
    addiu      $6, $19, 0x40C;
    addiu      $5, $5, 0x1;
    nop;
  L0011CEA0:
    slti       $2, $5, 0x400;
    beqz       $2, L0011CEC4;
    addu      $2, $18, $5;
    addu       $4, $6, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0x0($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011CEA0;
    addiu     $5, $5, 0x1;
  L0011CEC4:
    addiu      $2, $0, 0x400;
    beql       $5, $2, L0011CED0;
    sb        $0, 0x80B($19);
  L0011CED0:
    bnez       $7, L0011CEE8;
    nop;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011D00C;
    addiu     $2, $0, -0x7;
  L0011CEE8:
    blez       $17, L0011CF30;
    daddu     $5, $0, $0;
    addiu      $6, $19, 0x80C;
    lui        $7, 0x45;
    addiu      $18, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
    nop;
  L0011CF08:
    addu       $2, $22, $5;
    addu       $4, $6, $5;
    lbu        $3, 0x0($2);
    addiu      $5, $5, 0x1;
    slt        $2, $5, $17;
    sb         $3, 0x0($4);
    bnez       $2, L0011CF08;
    nop;
    b          L0011CF44;
    sw        $17, 0xC0C($19);
  L0011CF30:
    lui        $7, 0x45;
    addiu      $18, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
    sw         $17, 0xC0C($19);
  L0011CF44:
    addiu      $3, $7, 0x6AB8;
    addiu      $2, $0, 0x1;
    addiu      $4, $29, 0x10;
    sw         $2, 0x14($29);
    addiu      $16, $23, -0x7C40;
    sw         $3, 0x24($29);
    addiu      $20, $20, -0x7000;
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $17, $2, $0;
    daddu      $4, $16, $0;
    addiu      $2, $0, 0x4;
    sw         $18, 0x4($19);
    sw         $2, 0x8($19);
    addiu      $5, $0, 0xC10;
    jal        sceSifWriteBackDCache;
    sw        $17, 0x0($19);
    addiu      $4, $21, -0x6540;
    daddu      $7, $16, $0;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0xE;
    sw         $0, 0x8($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0xC10;
    daddu      $9, $20, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011CFD4;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011D00C;
    addiu     $2, $0, -0xB;
  L0011CFD4:
    or         $2, $20, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011CFF8;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011D00C;
    addiu     $2, $0, -0xB;
  L0011CFF8:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011D00C:
    ld         $31, 0xC0($29);
    ld         $23, 0xB0($29);
    ld         $22, 0xA0($29);
    ld         $21, 0x90($29);
    ld         $20, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0xD0;
}
