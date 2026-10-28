#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcChdir`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcChdir_12d588` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcChdir_12d588.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void PollSema(void);
extern void SignalSema(void);
extern void strncpy(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);

asm void sceMcChdir_12d588(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    lui        $2, 0x49;
    sd         $23, 0x80($29);
    sd         $22, 0x70($29);
    addiu      $23, $2, -0x1000;
    sd         $21, 0x60($29);
    daddu      $22, $7, $0;
    sd         $20, 0x50($29);
    daddu      $21, $5, $0;
    sd         $18, 0x30($29);
    daddu      $20, $4, $0;
    sd         $31, 0x90($29);
    sd         $19, 0x40($29);
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    lw         $2, 0x24($23);
    bnez       $2, L0012D5D8;
    daddu     $18, $6, $0;
    b          L0012D69C;
    addiu     $2, $0, -0x64;
  L0012D5D8:
    lui        $19, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($19);
    bltz       $2, L0012D69C;
    addiu     $2, $0, -0xC8;
    beqz       $18, L0012D600;
    nop;
    lb         $2, 0x0($18);
    bnez       $2, L0012D610;
    lui       $2, 0x49;
  L0012D600:
    jal        SignalSema;
    lw        $4, -0x6AA4($19);
    b          L0012D69C;
    addiu     $2, $0, -0xD2;
  L0012D610:
    lui        $16, 0x49;
    addiu      $17, $2, -0xF50;
    addiu      $16, $16, -0xA40;
    sw         $20, -0xF50($2);
    daddu      $5, $18, $0;
    sw         $21, 0x4($17);
    addiu      $4, $17, 0x14;
    sw         $16, 0x10($17);
    jal        strncpy;
    addiu     $6, $0, 0x3FF;
    daddu      $4, $16, $0;
    sb         $0, 0x413($17);
    jal        sceSifWriteBackDCache;
    addiu     $5, $0, 0x400;
    lui        $9, 0x49;
    lui        $11, 0x13;
    sw         $22, 0x0($29);
    daddu      $4, $23, $0;
    daddu      $7, $17, $0;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x2B08;
    addiu      $5, $0, 0xC;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x414;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012D690;
    addiu     $2, $0, 0xC;
    jal        SignalSema;
    lw        $4, -0x6AA4($19);
    b          L0012D69C;
    addiu     $2, $0, -0x5B;
  L0012D690:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012D69C:
    ld         $31, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}
