#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceRead`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceRead_11bf70` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceRead_11bf70.s -- the SDK
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

asm void sceRead_11bf70(void)
{
    .set noreorder;
    addiu      $29, $29, -0xE0;
    sd         $30, 0xC0($29);
    sd         $23, 0xB0($29);
    daddu      $30, $6, $0;
    sd         $21, 0x90($29);
    daddu      $23, $5, $0;
    sd         $17, 0x50($29);
    lui        $21, 0x49;
    sd         $16, 0x40($29);
    addiu      $17, $21, -0x7C40;
    sd         $31, 0xD0($29);
    sd         $22, 0xA0($29);
    sd         $20, 0x80($29);
    sd         $19, 0x70($29);
    jal        FileIoGetSlot_11ae80;
    sd        $18, 0x60($29);
    daddu      $16, $2, $0;
    jal        FileIoLock_11b300;
    addiu     $4, $0, 0x2;
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    beqz       $2, L0011BFE0;
    nop;
    beqz       $16, L0011BFE0;
    nop;
    lw         $20, 0x4($16);
    bnez       $20, L0011BFF0;
    lui       $2, 0x49;
  L0011BFE0:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C1AC;
    addiu     $2, $0, -0x9;
  L0011BFF0:
    lw         $4, 0x0($16);
    addiu      $2, $2, -0x6740;
    lui        $3, 0x45;
    subu       $2, $16, $2;
    sw         $4, 0xC($17);
    sra        $2, $2, 4;
    addiu      $3, $3, 0x6A28;
    sw         $2, 0x1C($17);
    addiu      $5, $0, 0x1;
    sw         $5, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $3, 0x24($29);
    andi       $16, $20, 0x8000;
    sw         $23, 0x10($17);
    sw         $30, 0x14($17);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $19, $2, $0;
    addiu      $3, $0, 0x4;
    addiu      $2, $29, 0x30;
    sw         $3, 0x8($17);
    sw         $2, 0x4($17);
    beqz       $16, L0011C0DC;
    sw        $19, -0x7C40($21);
    lui        $22, 0x44;
    jal        WaitSema;
    lw        $4, 0x62AC($22);
    lui        $7, 0x44;
    daddu      $6, $0, $0;
    lw         $3, 0x6218($7);
    addiu      $2, $0, -0x1;
    bne        $3, $2, L0011C090;
    daddu     $18, $16, $0;
    lw         $3, -0x7C40($21);
    lui        $16, (0x490000 >> 16);
    negu       $2, $3;
    sw         $3, 0x6218($7);
    b          L0011C0CC;
    sw        $2, -0x7C40($21);
    nop;
  L0011C090:
    lui        $16, 0x49;
    addiu      $6, $6, 0x1;
  L0011C098:
    slti       $2, $6, 0x20;
    beqz       $2, L0011C0CC;
    sll       $2, $6, 2;
    addiu      $3, $7, 0x6218;
    addu       $5, $2, $3;
    addiu      $4, $0, -0x1;
    lw         $2, 0x0($5);
    bne        $2, $4, L0011C098;
    addiu     $6, $6, 0x1;
    lw         $2, 0x0($17);
    negu       $3, $2;
    sw         $2, 0x0($5);
    sw         $3, 0x0($17);
  L0011C0CC:
    jal        SignalSema;
    lw        $4, 0x62AC($22);
    b          L0011C0E8;
    lui       $22, (0x20000000 >> 16);
  L0011C0DC:
    lui        $16, 0x49;
    daddu      $18, $0, $0;
    lui        $22, (0x20000000 >> 16);
  L0011C0E8:
    and        $2, $20, $22;
    bnez       $2, L0011C104;
    daddu     $4, $17, $0;
    daddu      $4, $23, $0;
    jal        sceSifWriteBackDCache;
    daddu     $5, $30, $0;
    daddu      $4, $17, $0;
  L0011C104:
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x20;
    addiu      $16, $16, -0x7000;
    lui        $2, 0x49;
    addiu      $7, $21, -0x7C40;
    addiu      $4, $2, -0x6540;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x2;
    sw         $18, 0x8($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x20;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011C160;
    or        $2, $22, $16;
    jal        DeleteSema;
    daddu     $4, $19, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011C1AC;
    addiu     $2, $0, -0xB;
  L0011C160:
    jal        FileIoUnlock_11b330;
    lw        $16, 0x0($2);
    bnez       $16, L0011C180;
    nop;
    jal        DeleteSema;
    daddu     $4, $19, $0;
    b          L0011C1AC;
    addiu     $2, $0, -0xB;
  L0011C180:
    beqz       $18, L0011C198;
    nop;
    jal        DeleteSema;
    daddu     $4, $19, $0;
    b          L0011C1AC;
    daddu     $2, $0, $0;
  L0011C198:
    jal        WaitSema;
    daddu     $4, $19, $0;
    jal        DeleteSema;
    daddu     $4, $19, $0;
    lw         $2, 0x30($29);
  L0011C1AC:
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
