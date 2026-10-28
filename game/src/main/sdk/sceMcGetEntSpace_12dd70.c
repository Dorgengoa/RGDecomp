#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcGetEntSpace`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcGetEntSpace_12dd70` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcGetEntSpace_12dd70.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void PollSema(void);
extern void SignalSema(void);
extern void strncpy(void);
extern void sceSifCallRpc(void);

asm void sceMcGetEntSpace_12dd70(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    lui        $2, 0x49;
    sd         $20, 0x50($29);
    sd         $19, 0x40($29);
    addiu      $20, $2, -0x1000;
    sd         $18, 0x30($29);
    daddu      $19, $4, $0;
    sd         $16, 0x10($29);
    daddu      $18, $5, $0;
    sd         $31, 0x60($29);
    sd         $17, 0x20($29);
    lw         $2, 0x24($20);
    bnez       $2, L0012DDB0;
    daddu     $16, $6, $0;
    b          L0012DE5C;
    addiu     $2, $0, -0x64;
  L0012DDB0:
    lui        $17, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($17);
    bltz       $2, L0012DE5C;
    addiu     $2, $0, -0xC8;
    beqz       $16, L0012DDD8;
    nop;
    lb         $2, 0x0($16);
    bnez       $2, L0012DDE8;
    lui       $2, 0x49;
  L0012DDD8:
    jal        SignalSema;
    lw        $4, -0x6AA4($17);
    b          L0012DE5C;
    addiu     $2, $0, -0xD2;
  L0012DDE8:
    daddu      $5, $16, $0;
    addiu      $16, $2, -0xF50;
    sw         $19, -0xF50($2);
    sw         $18, 0x4($16);
    addiu      $4, $16, 0x14;
    jal        strncpy;
    addiu     $6, $0, 0x3FF;
    lui        $9, 0x49;
    lui        $11, 0x13;
    sb         $0, 0x413($16);
    daddu      $4, $20, $0;
    daddu      $7, $16, $0;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x3738;
    addiu      $5, $0, 0x12;
    sw         $0, 0x0($29);
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x414;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012DE50;
    addiu     $2, $0, 0x12;
    jal        SignalSema;
    lw        $4, -0x6AA4($17);
    b          L0012DE5C;
    addiu     $2, $0, -0x5B;
  L0012DE50:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012DE5C:
    ld         $31, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}
