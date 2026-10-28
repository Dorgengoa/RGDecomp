#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceLseek`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceLseek_11bd30` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceLseek_11bd30.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoGetSlot_11ae80(void);
extern void FileIoLock_11b300(void);
extern void FileIoUnlock_11b330(void);
extern void CreateSema(void);
extern void WaitSema(void);
extern void SignalSema(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);

asm void sceLseek_11bd30(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $21, 0x90($29);
    sd         $19, 0x70($29);
    daddu      $21, $6, $0;
    sd         $20, 0x80($29);
    daddu      $19, $5, $0;
    sd         $17, 0x50($29);
    lui        $20, 0x49;
    sd         $16, 0x40($29);
    addiu      $17, $20, -0x7C40;
    sd         $31, 0xB0($29);
    sd         $22, 0xA0($29);
    jal        FileIoGetSlot_11ae80;
    sd        $18, 0x60($29);
    daddu      $16, $2, $0;
    jal        FileIoLock_11b300;
    addiu     $4, $0, 0x4;
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    beqz       $2, L0011BD98;
    nop;
    beqz       $16, L0011BD98;
    nop;
    lw         $18, 0x4($16);
    bnez       $18, L0011BDA8;
    lui       $2, 0x49;
  L0011BD98:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011BF44;
    addiu     $2, $0, -0x9;
  L0011BDA8:
    lw         $4, 0x0($16);
    addiu      $2, $2, -0x6740;
    lui        $3, 0x45;
    subu       $2, $16, $2;
    sw         $4, 0xC($17);
    sra        $2, $2, 4;
    sw         $19, 0x10($17);
    sw         $21, 0x14($17);
    addiu      $3, $3, 0x6A10;
    sw         $2, 0x18($17);
    addiu      $5, $0, 0x1;
    addiu      $4, $29, 0x10;
    sw         $5, 0x14($29);
    sw         $3, 0x24($29);
    andi       $16, $18, 0x8000;
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $19, $2, $0;
    addiu      $3, $0, 0x4;
    addiu      $2, $29, 0x30;
    sw         $3, 0x8($17);
    sw         $2, 0x4($17);
    beqz       $16, L0011BE98;
    sw        $19, -0x7C40($20);
    lui        $21, 0x44;
    jal        WaitSema;
    lw        $4, 0x62AC($21);
    lui        $7, 0x44;
    daddu      $6, $0, $0;
    lw         $3, 0x6218($7);
    addiu      $2, $0, -0x1;
    bne        $3, $2, L0011BE48;
    daddu     $18, $16, $0;
    lw         $3, -0x7C40($20);
    lui        $22, (0x490000 >> 16);
    lui        $16, (0x490000 >> 16);
    negu       $2, $3;
    sw         $3, 0x6218($7);
    b          L0011BE88;
    sw        $2, -0x7C40($20);
  L0011BE48:
    lui        $22, 0x49;
    lui        $16, 0x49;
    addiu      $6, $6, 0x1;
  L0011BE54:
    slti       $2, $6, 0x20;
    beqz       $2, L0011BE88;
    sll       $2, $6, 2;
    addiu      $3, $7, 0x6218;
    addu       $5, $2, $3;
    addiu      $4, $0, -0x1;
    lw         $2, 0x0($5);
    bne        $2, $4, L0011BE54;
    addiu     $6, $6, 0x1;
    lw         $2, 0x0($17);
    negu       $3, $2;
    sw         $2, 0x0($5);
    sw         $3, 0x0($17);
  L0011BE88:
    jal        SignalSema;
    lw        $4, 0x62AC($21);
    b          L0011BEA8;
    addiu     $16, $16, -0x7000;
  L0011BE98:
    lui        $22, 0x49;
    lui        $16, 0x49;
    daddu      $18, $0, $0;
    addiu      $16, $16, -0x7000;
  L0011BEA8:
    addiu      $4, $22, -0x6540;
    addiu      $7, $20, -0x7C40;
    sw         $0, 0x0($29);
    sw         $18, 0x8($29);
    addiu      $5, $0, 0x4;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x1C;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011BEF4;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $19, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011BF44;
    addiu     $2, $0, -0xB;
  L0011BEF4:
    or         $2, $16, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011BF18;
    nop;
    jal        DeleteSema;
    daddu     $4, $19, $0;
    b          L0011BF44;
    addiu     $2, $0, -0xB;
  L0011BF18:
    beqz       $18, L0011BF30;
    nop;
    jal        DeleteSema;
    daddu     $4, $19, $0;
    b          L0011BF44;
    daddu     $2, $0, $0;
  L0011BF30:
    jal        WaitSema;
    daddu     $4, $19, $0;
    jal        DeleteSema;
    daddu     $4, $19, $0;
    lw         $2, 0x30($29);
  L0011BF44:
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
