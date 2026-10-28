#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcUdCheckNewCard`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcUdCheckNewCard_12d338` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcUdCheckNewCard_12d338.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void sceSifCallRpc(void);
extern void scePrintf_119288(void);

asm void sceMcUdCheckNewCard_12d338(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    lui        $4, 0x49;
    sd         $16, 0x10($29);
    lui        $7, 0x49;
    lui        $16, 0x49;
    lui        $11, 0x13;
    sd         $31, 0x20($29);
    addiu      $4, $4, -0x1000;
    addiu      $7, $7, -0xF80;
    addiu      $11, $11, -0x3738;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x35;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x30;
    addiu      $9, $16, 0x5C0;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012D394;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7E40;
    b          L0012D398;
    addiu     $2, $0, -0x5B;
  L0012D394:
    lw         $2, 0x5C0($16);
  L0012D398:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
