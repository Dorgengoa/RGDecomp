#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `scePowerOffHandler`
   (ethteck/kh1 src/lib/filestub.c), kept as `scePowerOffHandler_11b340` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/scePowerOffHandler_11b340.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void FileIoUnlock_11b330(void);

asm void scePowerOffHandler_11b340(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    daddu      $19, $4, $0;
    sd         $20, 0x40($29);
    daddu      $18, $5, $0;
    sd         $16, 0x0($29);
    addiu      $4, $0, 0x1B;
    sd         $31, 0x50($29);
    lui        $16, 0x49;
    sd         $17, 0x10($29);
    jal        FileIoLock_11b300;
    addiu     $20, $16, -0x64C0;
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnez       $3, L0011B38C;
    nop;
    jal        SceFsInit_11b428;
    nop;
  L0011B38C:
    jal        DisableIntr_120660;
    nop;
    lw         $17, -0x64C0($16);
    lui        $3, 0x49;
    sw         $18, 0x4($20);
    sw         $19, -0x64C0($16);
    beqz       $2, L0011B3B4;
    sw        $28, -0x6480($3);
    jal        EnableIntr_1206b0;
    nop;
  L0011B3B4:
    jal        FileIoUnlock_11b330;
    nop;
    daddu      $2, $17, $0;
    ld         $31, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
