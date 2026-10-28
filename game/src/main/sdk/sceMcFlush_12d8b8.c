#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcFlush`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcFlush_12d8b8` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcFlush_12d8b8.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void PollSema(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceMcFlush_12d8b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    lui        $3, 0x49;
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    addiu      $17, $3, -0x1000;
    sd         $31, 0x40($29);
    sd         $18, 0x30($29);
    lw         $2, 0x24($17);
    bnez       $2, L0012D8E8;
    daddu     $16, $4, $0;
    b          L0012D95C;
    addiu     $2, $0, -0x64;
  L0012D8E8:
    lui        $18, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($18);
    bgez       $2, L0012D904;
    lui       $7, 0x49;
    b          L0012D95C;
    addiu     $2, $0, -0xC8;
  L0012D904:
    lui        $9, 0x49;
    lui        $11, 0x13;
    sw         $16, -0xF80($7);
    daddu      $4, $17, $0;
    addiu      $7, $7, -0xF80;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x3738;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0xA;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x30;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012D950;
    addiu     $2, $0, 0xA;
    jal        SignalSema;
    lw        $4, -0x6AA4($18);
    b          L0012D95C;
    addiu     $2, $0, -0x5B;
  L0012D950:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012D95C:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
