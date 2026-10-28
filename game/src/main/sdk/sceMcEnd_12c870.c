#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcEnd`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcEnd_12c870` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   MEDIUM-HIGH: RG deletes an extra semaphore kh1's body doesn't show
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcEnd_12c870.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void sceMcSync_12d098(void);
extern void DeleteSema(void);

asm void sceMcEnd_12c870(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    lui        $16, 0x45;
    sd         $31, 0x10($29);
    lw         $2, -0x6AA4($16);
    bltz       $2, L0012C8B4;
    daddu     $4, $0, $0;
    daddu      $5, $0, $0;
    jal        sceMcSync_12d098;
    daddu     $6, $0, $0;
    jal        DeleteSema;
    lw        $4, -0x6AA4($16);
    lui        $3, 0x45;
    addiu      $2, $0, -0x1;
    lw         $4, -0x6AA0($3);
    jal        DeleteSema;
    sw        $2, -0x6AA4($16);
  L0012C8B4:
    ld         $31, 0x10($29);
    addiu      $2, $0, 0x1;
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
