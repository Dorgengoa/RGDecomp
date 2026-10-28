#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcSeek`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcSeek_12cc78` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcSeek_12cc78.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void PollSema(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceMcSeek_12cc78(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    lui        $2, 0x49;
    sd         $19, 0x40($29);
    sd         $18, 0x30($29);
    addiu      $19, $2, -0x1000;
    sd         $17, 0x20($29);
    daddu      $18, $6, $0;
    sd         $16, 0x10($29);
    daddu      $17, $5, $0;
    sd         $31, 0x60($29);
    sd         $20, 0x50($29);
    lw         $2, 0x24($19);
    bnez       $2, L0012CCB8;
    daddu     $16, $4, $0;
    b          L0012CD38;
    addiu     $2, $0, -0x64;
  L0012CCB8:
    lui        $20, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($20);
    bgez       $2, L0012CCD4;
    lui       $3, 0x49;
    b          L0012CD38;
    addiu     $2, $0, -0xC8;
  L0012CCD4:
    lui        $9, 0x49;
    addiu      $2, $3, -0xF80;
    sw         $16, -0xF80($3);
    lui        $11, 0x13;
    sw         $17, 0x10($2);
    sw         $18, 0x14($2);
    daddu      $4, $19, $0;
    daddu      $7, $2, $0;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x3738;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x4;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x30;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012CD2C;
    addiu     $2, $0, 0x4;
    jal        SignalSema;
    lw        $4, -0x6AA4($20);
    b          L0012CD38;
    addiu     $2, $0, -0x5B;
  L0012CD2C:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012CD38:
    ld         $31, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}
