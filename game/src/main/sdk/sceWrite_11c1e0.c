#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceWrite`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceWrite_11c1e0` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceWrite_11c1e0.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoGetSlot_11ae80(void);
extern void FileIoLock_11b300(void);
extern void FileIoUnlock_11b330(void);
extern void CreateSema(void);
extern void WaitSema(void);
extern void SignalSema(void);
extern void sceSifWriteBackDCache(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);

asm void sceWrite_11c1e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xE0;
    sd         $22, 0xA0($29);
    sd         $17, 0x50($29);
    daddu      $22, $6, $0;
    sd         $30, 0xC0($29);
    daddu      $17, $5, $0;
    sd         $18, 0x60($29);
    lui        $30, 0x49;
    sd         $16, 0x40($29);
    addiu      $18, $30, -0x7C40;
    sd         $31, 0xD0($29);
    sd         $23, 0xB0($29);
    sd         $21, 0x90($29);
    sd         $20, 0x80($29);
    jal        FileIoGetSlot_11ae80;
    sd        $19, 0x70($29);
    daddu      $16, $2, $0;
    jal        FileIoLock_11b300;
    addiu     $4, $0, 0x3;
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    beqz       $2, L0011C250;
    nop;
    beqz       $16, L0011C250;
    nop;
    lw         $23, 0x4($16);
    bnez       $23, L0011C260;
    lui       $2, 0x49;
  L0011C250:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C470;
    addiu     $2, $0, -0x9;
  L0011C260:
    lw         $4, 0x0($16);
    addiu      $2, $2, -0x6740;
    lui        $3, 0x45;
    subu       $2, $16, $2;
    sw         $4, 0xC($18);
    sra        $2, $2, 4;
    addiu      $3, $3, 0x6A40;
    sw         $2, 0x2C($18);
    addiu      $5, $0, 0x1;
    sw         $5, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $3, 0x24($29);
    andi       $16, $23, 0x8000;
    sw         $22, 0x14($18);
    sw         $17, 0x10($18);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $21, $2, $0;
    addiu      $3, $0, 0x4;
    addiu      $2, $29, 0x30;
    sw         $3, 0x8($18);
    sw         $2, 0x4($18);
    beqz       $16, L0011C34C;
    sw        $21, -0x7C40($30);
    lui        $19, 0x44;
    jal        WaitSema;
    lw        $4, 0x62AC($19);
    lui        $7, 0x44;
    daddu      $6, $0, $0;
    lw         $3, 0x6218($7);
    addiu      $2, $0, -0x1;
    bne        $3, $2, L0011C300;
    daddu     $20, $16, $0;
    lw         $3, -0x7C40($30);
    andi       $16, $17, 0xF;
    negu       $2, $3;
    sw         $3, 0x6218($7);
    b          L0011C33C;
    sw        $2, -0x7C40($30);
    nop;
  L0011C300:
    andi       $16, $17, 0xF;
    addiu      $6, $6, 0x1;
  L0011C308:
    slti       $2, $6, 0x20;
    beqz       $2, L0011C33C;
    sll       $2, $6, 2;
    addiu      $3, $7, 0x6218;
    addu       $5, $2, $3;
    addiu      $4, $0, -0x1;
    lw         $2, 0x0($5);
    bne        $2, $4, L0011C308;
    addiu     $6, $6, 0x1;
    lw         $2, 0x0($18);
    negu       $3, $2;
    sw         $2, 0x0($5);
    sw         $3, 0x0($18);
  L0011C33C:
    jal        SignalSema;
    lw        $4, 0x62AC($19);
    b          L0011C354;
    nop;
  L0011C34C:
    andi       $16, $17, 0xF;
    daddu      $20, $0, $0;
  L0011C354:
    bnez       $16, L0011C364;
    srl       $2, $17, 4;
    b          L0011C370;
    daddu     $16, $0, $0;
  L0011C364:
    addiu      $3, $17, -0x10;
    sll        $2, $2, 4;
    subu       $16, $2, $3;
  L0011C370:
    slt        $3, $22, $16;
    lui        $19, (0x20000000 >> 16);
    and        $2, $23, $19;
    bnez       $2, L0011C390;
    movn      $16, $22, $3;
    daddu      $5, $22, $0;
    jal        sceSifWriteBackDCache;
    daddu     $4, $17, $0;
  L0011C390:
    or         $17, $17, $19;
    sw         $16, 0x18($18);
    blez       $16, L0011C3C8;
    daddu     $5, $0, $0;
    addiu      $6, $18, 0x1C;
    nop;
  L0011C3A8:
    addu       $2, $17, $5;
    addu       $4, $6, $5;
    lbu        $3, (0x20000000 & 0xFFFF)($2);
    addiu      $5, $5, 0x1;
    slt        $2, $5, $16;
    sb         $3, 0x0($4);
    bnez       $2, L0011C3A8;
    nop;
  L0011C3C8:
    lui        $2, 0x49;
    addiu      $7, $30, -0x7C40;
    addiu      $16, $2, -0x7000;
    sw         $0, 0x0($29);
    lui        $2, 0x49;
    sw         $20, 0x8($29);
    addiu      $4, $2, -0x6540;
    addiu      $5, $0, 0x3;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x30;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011C420;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $21, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C470;
    addiu     $2, $0, -0xB;
  L0011C420:
    or         $2, $16, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011C444;
    nop;
    jal        DeleteSema;
    daddu     $4, $21, $0;
    b          L0011C470;
    addiu     $2, $0, -0xB;
  L0011C444:
    beqz       $20, L0011C45C;
    nop;
    jal        DeleteSema;
    daddu     $4, $21, $0;
    b          L0011C470;
    daddu     $2, $0, $0;
  L0011C45C:
    jal        WaitSema;
    daddu     $4, $21, $0;
    jal        DeleteSema;
    daddu     $4, $21, $0;
    lw         $2, 0x30($29);
  L0011C470:
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
