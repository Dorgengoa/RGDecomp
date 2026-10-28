#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceIoctl`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceIoctl_11c4a0` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceIoctl_11c4a0.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoGetSlot_11ae80(void);
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void FileIoUnlock_11b330(void);
extern void WaitSema(void);
extern void SignalSema(void);
extern void CreateSema(void);
extern void sceSifWriteBackDCache(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);

asm void sceIoctl_11c4a0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $18, 0x60($29);
    sd         $17, 0x50($29);
    daddu      $18, $6, $0;
    sd         $22, 0xA0($29);
    daddu      $17, $5, $0;
    sd         $21, 0x90($29);
    lui        $22, 0x49;
    sd         $20, 0x80($29);
    addiu      $21, $0, 0x1;
    sd         $19, 0x70($29);
    lui        $20, 0x49;
    sd         $16, 0x40($29);
    sd         $31, 0xB0($29);
    jal        FileIoGetSlot_11ae80;
    addiu     $19, $22, -0x7C40;
    daddu      $16, $2, $0;
    jal        FileIoLock_11b300;
    addiu     $4, $0, 0x5;
    lui        $2, 0x44;
    sw         $18, -0x7C78($20);
    lw         $3, 0x629C($2);
    bnez       $3, L0011C508;
    nop;
    jal        SceFsInit_11b428;
    nop;
  L0011C508:
    beqz       $16, L0011C51C;
    nop;
    lw         $2, 0x4($16);
    bnel       $2, $0, L0011C52C;
    sw        $0, 0x414($19);
  L0011C51C:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C800;
    addiu     $2, $0, -0x9;
  L0011C52C:
    addiu      $2, $0, 0x2;
    beq        $17, $2, L0011C5D8;
    sw        $0, 0x418($19);
    slti       $2, $17, 0x3;
    beqz       $2, L0011C554;
    addiu     $2, $0, 0x3;
    beql       $17, $21, L0011C564;
    lui       $16, 0x44;
    b          L0011C640;
    lw        $2, 0x0($16);
  L0011C554:
    beq        $17, $2, L0011C608;
    lui       $4, 0x44;
    b          L0011C640;
    lw        $2, 0x0($16);
  L0011C564:
    jal        WaitSema;
    lw        $4, 0x62AC($16);
    lui        $5, 0x44;
    daddu      $4, $0, $0;
    lw         $3, 0x6218($5);
    addiu      $2, $0, -0x1;
    bne        $3, $2, L0011C5AC;
    addiu     $2, $0, 0x20;
    addiu      $3, $5, 0x6218;
    addiu      $5, $0, -0x1;
    addiu      $4, $4, 0x1;
  L0011C590:
    slti       $2, $4, 0x20;
    beqz       $2, L0011C5A8;
    addiu     $3, $3, 0x4;
    lw         $2, 0x0($3);
    beql       $2, $5, L0011C590;
    addiu     $4, $4, 0x1;
  L0011C5A8:
    addiu      $2, $0, 0x20;
  L0011C5AC:
    bne        $4, $2, L0011C5C0;
    lw        $3, -0x7C78($20);
    lw         $2, -0x7C78($20);
    b          L0011C5C8;
    sw        $0, 0x0($2);
  L0011C5C0:
    addiu      $2, $0, 0x1;
    sw         $2, 0x0($3);
  L0011C5C8:
    jal        SignalSema;
    lw        $4, 0x62AC($16);
    b          L0011C630;
    nop;
  L0011C5D8:
    lui        $4, 0x44;
    addiu      $5, $0, 0x440;
    lw         $2, 0x6298($4);
    lui        $3, 0x49;
    addiu      $3, $3, -0x6FB0;
    lui        $4, (0x20000000 >> 16);
    mult       $2, $2, $5;
    addu       $2, $2, $3;
    or         $2, $2, $4;
    lw         $3, (0x20000000 & 0xFFFF)($2);
    b          L0011C630;
    sw        $3, 0x0($18);
  L0011C608:
    addiu      $5, $0, 0x440;
    lw         $2, 0x6298($4);
    lui        $3, 0x49;
    addiu      $3, $3, -0x6FB0;
    lui        $4, (0x20000000 >> 16);
    mult       $2, $2, $5;
    addu       $2, $2, $3;
    or         $2, $2, $4;
    ld         $3, (0x20000000 & 0xFFFF)($2);
    sd         $3, 0x0($18);
  L0011C630:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C800;
    daddu     $2, $0, $0;
  L0011C640:
    sw         $17, 0x10($19);
    bnez       $18, L0011C664;
    sw        $2, 0xC($19);
    sw         $0, 0x41C($19);
    lui        $3, 0x45;
    addiu      $18, $29, 0x30;
    lui        $21, 0x49;
    b          L0011C738;
    lui       $17, 0x49;
  L0011C664:
    daddu      $6, $18, $0;
    addiu      $4, $19, 0x14;
    addiu      $3, $0, 0x400;
    or         $2, $6, $4;
    andi       $2, $2, 0x7;
    beqz       $2, L0011C6F0;
    sw        $3, 0x41C($19);
    addiu      $2, $6, 0x400;
    lui        $3, 0x45;
    addiu      $18, $29, 0x30;
    lui        $21, 0x49;
    lui        $17, 0x49;
  L0011C694:
    ldl        $5, 0x7($6);
    ldr        $5, 0x0($6);
    ldl        $7, 0xF($6);
    ldr        $7, 0x8($6);
    ldl        $8, 0x17($6);
    ldr        $8, 0x10($6);
    ldl        $9, 0x1F($6);
    ldr        $9, 0x18($6);
    sdl        $5, 0x7($4);
    sdr        $5, 0x0($4);
    sdl        $7, 0xF($4);
    sdr        $7, 0x8($4);
    sdl        $8, 0x17($4);
    sdr        $8, 0x10($4);
    sdl        $9, 0x1F($4);
    sdr        $9, 0x18($4);
    addiu      $6, $6, 0x20;
    addiu      $4, $4, 0x20;
    nop;
    bne        $6, $2, L0011C694;
    nop;
    b          L0011C73C;
    addiu     $3, $3, 0x6A58;
  L0011C6F0:
    addiu      $2, $6, 0x400;
    lui        $3, 0x45;
    addiu      $18, $29, 0x30;
    lui        $21, 0x49;
    lui        $17, 0x49;
  L0011C704:
    ld         $5, 0x0($6);
    ld         $7, 0x8($6);
    ld         $8, 0x10($6);
    ld         $9, 0x18($6);
    sd         $5, 0x0($4);
    sd         $7, 0x8($4);
    sd         $8, 0x10($4);
    sd         $9, 0x18($4);
    addiu      $6, $6, 0x20;
    addiu      $4, $4, 0x20;
    nop;
    bne        $6, $2, L0011C704;
    nop;
  L0011C738:
    addiu      $3, $3, 0x6A58;
  L0011C73C:
    addiu      $2, $0, 0x1;
    sw         $2, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $3, 0x24($29);
    addiu      $20, $17, -0x7000;
    sw         $0, 0x18($29);
    jal        CreateSema;
    addiu     $16, $22, -0x7C40;
    daddu      $17, $2, $0;
    daddu      $4, $16, $0;
    addiu      $2, $0, 0x4;
    sw         $18, 0x4($19);
    sw         $2, 0x8($19);
    addiu      $5, $0, 0x420;
    jal        sceSifWriteBackDCache;
    sw        $17, 0x0($19);
    addiu      $4, $21, -0x6540;
    daddu      $7, $16, $0;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x5;
    sw         $0, 0x8($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x420;
    daddu      $9, $20, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011C7C8;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C800;
    addiu     $2, $0, -0xB;
  L0011C7C8:
    or         $2, $20, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011C7EC;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011C800;
    addiu     $2, $0, -0xB;
  L0011C7EC:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011C800:
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
