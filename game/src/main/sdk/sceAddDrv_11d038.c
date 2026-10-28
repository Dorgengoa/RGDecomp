#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceAddDrv`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceAddDrv_11d038` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceAddDrv_11d038.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void CreateSema(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void FileIoUnlock_11b330(void);
extern void WaitSema(void);

asm void sceAddDrv_11d038(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    sd         $17, 0x50($29);
    daddu      $17, $4, $0;
    sd         $19, 0x70($29);
    sd         $16, 0x40($29);
    addiu      $4, $0, 0xF;
    sd         $31, 0x80($29);
    lui        $19, 0x49;
    sd         $18, 0x60($29);
    jal        FileIoLock_11b300;
    addiu     $16, $19, -0x7C40;
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    bnez       $2, L0011D080;
    lui       $2, 0x45;
    jal        SceFsInit_11b428;
    nop;
    lui        $2, 0x45;
  L0011D080:
    sw         $17, 0xC($16);
    addiu      $3, $0, 0x1;
    addiu      $2, $2, 0x6AD0;
    sw         $3, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $2, 0x24($29);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $17, $2, $0;
    addiu      $3, $29, 0x30;
    lui        $2, 0x49;
    sw         $17, -0x7C40($19);
    addiu      $18, $2, -0x7000;
    sw         $3, 0x4($16);
    addiu      $2, $0, 0x4;
    lui        $4, 0x49;
    sw         $2, 0x8($16);
    addiu      $4, $4, -0x6540;
    daddu      $7, $16, $0;
    addiu      $5, $0, 0xF;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    sw         $0, 0x8($29);
    addiu      $8, $0, 0x10;
    daddu      $9, $18, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011D110;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011D148;
    addiu     $2, $0, -0xB;
  L0011D110:
    or         $2, $18, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011D134;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011D148;
    addiu     $2, $0, -0xB;
  L0011D134:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011D148:
    ld         $31, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
