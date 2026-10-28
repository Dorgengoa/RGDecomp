#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcRead`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcRead_12ce08` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcRead_12ce08.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void PollSema(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceMcRead_12ce08(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    lui        $2, 0x49;
    sd         $21, 0x60($29);
    sd         $20, 0x50($29);
    addiu      $21, $2, -0x1000;
    sd         $19, 0x40($29);
    daddu      $20, $4, $0;
    sd         $18, 0x30($29);
    daddu      $19, $5, $0;
    sd         $31, 0x80($29);
    sd         $22, 0x70($29);
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    lw         $2, 0x24($21);
    bnez       $2, L0012CE50;
    daddu     $18, $6, $0;
    b          L0012CEF4;
    addiu     $2, $0, -0x64;
  L0012CE50:
    lui        $22, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($22);
    bgez       $2, L0012CE6C;
    lui       $2, 0x49;
    b          L0012CEF4;
    addiu     $2, $0, -0xC8;
  L0012CE6C:
    lui        $16, 0x49;
    addiu      $17, $2, -0xF80;
    addiu      $16, $16, -0xB00;
    sw         $20, -0xF80($2);
    daddu      $4, $19, $0;
    daddu      $5, $18, $0;
    sw         $19, 0x18($17);
    sw         $18, 0xC($17);
    jal        sceSifWriteBackDCache;
    sw        $16, 0x1C($17);
    daddu      $4, $16, $0;
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0xC0;
    lui        $9, 0x49;
    lui        $11, 0x13;
    sw         $16, 0x0($29);
    daddu      $4, $21, $0;
    daddu      $7, $17, $0;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x32A8;
    addiu      $5, $0, 0x5;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x30;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012CEE8;
    addiu     $2, $0, 0x5;
    jal        SignalSema;
    lw        $4, -0x6AA4($22);
    b          L0012CEF4;
    addiu     $2, $0, -0x5B;
  L0012CEE8:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012CEF4:
    ld         $31, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
