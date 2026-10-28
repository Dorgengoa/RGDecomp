#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceChstat`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceChstat_11d6c8` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceChstat_11d6c8.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void CreateSema(void);
extern void sceSifWriteBackDCache(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void FileIoUnlock_11b330(void);
extern void WaitSema(void);

asm void sceChstat_11d6c8(void)
{
    .set noreorder;
    addiu      $29, $29, -0xE0;
    sd         $18, 0x60($29);
    sd         $23, 0xB0($29);
    daddu      $18, $4, $0;
    sd         $16, 0x40($29);
    daddu      $23, $6, $0;
    sd         $30, 0xC0($29);
    daddu      $16, $5, $0;
    sd         $19, 0x70($29);
    addiu      $4, $0, 0xD;
    sd         $31, 0xD0($29);
    lui        $30, 0x49;
    sd         $22, 0xA0($29);
    addiu      $19, $30, -0x7C40;
    sd         $21, 0x90($29);
    sd         $20, 0x80($29);
    jal        FileIoLock_11b300;
    sd        $17, 0x50($29);
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    bnel       $2, $0, L0011D72C;
    lbu       $2, 0x0($18);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($18);
  L0011D72C:
    daddu      $17, $0, $0;
    daddu      $3, $2, $0;
    beqz       $3, L0011D778;
    sb        $2, 0x50($19);
    lui        $5, 0x45;
    addiu      $20, $29, 0x30;
    lui        $22, 0x49;
    lui        $21, 0x49;
    nop;
  L0011D750:
    addiu      $17, $17, 0x1;
    slti       $2, $17, 0x400;
    beqz       $2, L0011D788;
    addu      $2, $18, $17;
    addu       $4, $19, $17;
    lbu        $3, 0x0($2);
    bnez       $3, L0011D750;
    sb        $3, 0x50($4);
    b          L0011D78C;
    addiu     $2, $0, 0x400;
  L0011D778:
    lui        $5, 0x45;
    addiu      $20, $29, 0x30;
    lui        $22, 0x49;
    lui        $21, 0x49;
  L0011D788:
    addiu      $2, $0, 0x400;
  L0011D78C:
    bne        $17, $2, L0011D79C;
    addiu     $3, $5, 0x6B30;
    sb         $0, 0x44F($19);
    addiu      $17, $0, 0x3FF;
  L0011D79C:
    addiu      $2, $0, 0x1;
    ldl        $4, 0x7($16);
    ldr        $4, 0x0($16);
    ldl        $5, 0xF($16);
    ldr        $5, 0x8($16);
    ldl        $6, 0x17($16);
    ldr        $6, 0x10($16);
    ldl        $7, 0x1F($16);
    ldr        $7, 0x18($16);
    sdl        $4, 0x17($19);
    sdr        $4, 0x10($19);
    sdl        $5, 0x1F($19);
    sdr        $5, 0x18($19);
    sdl        $6, 0x27($19);
    sdr        $6, 0x20($19);
    sdl        $7, 0x2F($19);
    sdr        $7, 0x28($19);
    ldl        $4, 0x27($16);
    ldr        $4, 0x20($16);
    ldl        $5, 0x2F($16);
    ldr        $5, 0x28($16);
    ldl        $6, 0x37($16);
    ldr        $6, 0x30($16);
    ldl        $7, 0x3F($16);
    ldr        $7, 0x38($16);
    sdl        $4, 0x37($19);
    sdr        $4, 0x30($19);
    sdl        $5, 0x3F($19);
    sdr        $5, 0x38($19);
    sdl        $6, 0x47($19);
    sdr        $6, 0x40($19);
    sdl        $7, 0x4F($19);
    sdr        $7, 0x48($19);
    addiu      $21, $21, -0x7000;
    sw         $23, 0xC($19);
    addiu      $4, $29, 0x10;
    sw         $2, 0x14($29);
    addiu      $16, $30, -0x7C40;
    sw         $3, 0x24($29);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $18, $2, $0;
    daddu      $4, $16, $0;
    addiu      $2, $0, 0x4;
    sw         $20, 0x4($19);
    sw         $2, 0x8($19);
    addiu      $5, $0, 0x450;
    jal        sceSifWriteBackDCache;
    sw        $18, 0x0($19);
    addiu      $4, $22, -0x6540;
    daddu      $7, $16, $0;
    addiu      $8, $17, 0x51;
    sw         $0, 0x0($29);
    sw         $0, 0x8($29);
    addiu      $5, $0, 0xD;
    daddu      $6, $0, $0;
    daddu      $9, $21, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011D8AC;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $18, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011D8E4;
    addiu     $2, $0, -0xB;
  L0011D8AC:
    or         $2, $21, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011D8D0;
    nop;
    jal        DeleteSema;
    daddu     $4, $18, $0;
    b          L0011D8E4;
    addiu     $2, $0, -0xB;
  L0011D8D0:
    jal        WaitSema;
    daddu     $4, $18, $0;
    jal        DeleteSema;
    daddu     $4, $18, $0;
    lw         $2, 0x30($29);
  L0011D8E4:
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
