#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `supplement_crt0`
   (ethteck/kh1 src/lib/libkernl/initsys.c), kept as `SupplementCrt0_1206c8` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/SupplementCrt0_1206c8.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void CreateSema(void);

asm void SupplementCrt0_1206c8(void)
{
    .set noreorder;
    lui        $2, 0x45;
    lui        $5, 0x45;
    addiu      $29, $29, -0x50;
    addiu      $3, $0, 0x1;
    addiu      $2, $2, 0x6CB0;
    addiu      $5, $5, 0x6CC0;
    sd         $31, 0x40($29);
    daddu      $4, $29, $0;
    sw         $2, 0x14($29);
    sw         $3, 0x28($29);
    sw         $5, 0x34($29);
    sw         $3, 0x4($29);
    sw         $3, 0x8($29);
    jal        CreateSema;
    sw        $3, 0x24($29);
    lui        $3, 0x44;
    addiu      $4, $29, 0x20;
    jal        CreateSema;
    sw        $2, 0x6930($3);
    lui        $3, 0x44;
    ld         $31, 0x40($29);
    sw         $2, 0x6934($3);
    jr         $31;
    addiu     $29, $29, 0x50;
}
