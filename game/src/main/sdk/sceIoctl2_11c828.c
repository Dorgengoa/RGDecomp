#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceIoctl2`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceIoctl2_11c828` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceIoctl2_11c828.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoGetSlot_11ae80(void);
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void FileIoUnlock_11b330(void);
extern void memcpy(void);
extern void CreateSema(void);
extern void sceSifWriteBackDCache(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void WaitSema(void);

asm void sceIoctl2_11c828(void)
{
    .set noreorder;
    addiu      $29, $29, -0xD0;
    sd         $23, 0xB0($29);
    sd         $21, 0x90($29);
    daddu      $23, $8, $0;
    sd         $20, 0x80($29);
    daddu      $21, $5, $0;
    sd         $19, 0x70($29);
    daddu      $20, $9, $0;
    sd         $16, 0x40($29);
    daddu      $19, $7, $0;
    sd         $22, 0xA0($29);
    daddu      $16, $6, $0;
    sd         $18, 0x60($29);
    lui        $22, 0x49;
    sd         $17, 0x50($29);
    sd         $31, 0xC0($29);
    jal        FileIoGetSlot_11ae80;
    addiu     $17, $22, -0x7C40;
    daddu      $18, $2, $0;
    jal        FileIoLock_11b300;
    addiu     $4, $0, 0x1A;
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnez       $3, L0011C894;
    nop;
    jal        SceFsInit_11b428;
    nop;
  L0011C894:
    beqz       $18, L0011C8A8;
    nop;
    lw         $2, 0x4($18);
    bnez       $2, L0011C8B8;
    sltiu     $2, $19, 0x401;
  L0011C8A8:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C9E4;
    addiu     $2, $0, -0x9;
  L0011C8B8:
    beqz       $2, L0011C8C8;
    sltiu     $2, $20, 0x401;
    bnez       $2, L0011C8D8;
    nop;
  L0011C8C8:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C9E4;
    addiu     $2, $0, -0x16;
  L0011C8D8:
    bnez       $16, L0011C8E8;
    daddu     $5, $16, $0;
    b          L0011C8F4;
    sw        $0, 0x41C($17);
  L0011C8E8:
    addiu      $4, $17, 0x14;
    jal        memcpy;
    daddu     $6, $19, $0;
  L0011C8F4:
    lw         $3, 0x0($18);
    lui        $2, 0x45;
    sw         $21, 0x10($17);
    addiu      $2, $2, 0x6A70;
    sw         $3, 0xC($17);
    addiu      $5, $0, 0x1;
    sw         $19, 0x41C($17);
    addiu      $4, $29, 0x10;
    sw         $5, 0x14($29);
    addiu      $16, $22, -0x7C40;
    sw         $2, 0x24($29);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $18, $2, $0;
    addiu      $3, $0, 0x4;
    addiu      $2, $29, 0x30;
    sw         $20, 0x418($17);
    sw         $2, 0x4($17);
    daddu      $4, $16, $0;
    sw         $3, 0x8($17);
    addiu      $5, $0, 0x420;
    sw         $23, 0x414($17);
    jal        sceSifWriteBackDCache;
    sw        $18, 0x0($17);
    lui        $2, 0x49;
    lui        $4, 0x49;
    addiu      $17, $2, -0x7000;
    addiu      $4, $4, -0x6540;
    daddu      $7, $16, $0;
    sw         $0, 0x0($29);
    sw         $0, 0x8($29);
    addiu      $5, $0, 0x1A;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x420;
    daddu      $9, $17, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011C9AC;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $18, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C9E4;
    addiu     $2, $0, -0xB;
  L0011C9AC:
    or         $2, $17, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011C9D0;
    nop;
    jal        DeleteSema;
    daddu     $4, $18, $0;
    b          L0011C9E4;
    addiu     $2, $0, -0xB;
  L0011C9D0:
    jal        WaitSema;
    daddu     $4, $18, $0;
    jal        DeleteSema;
    daddu     $4, $18, $0;
    lw         $2, 0x30($29);
  L0011C9E4:
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
