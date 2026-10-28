#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcGetDir`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcGetDir_12d3a8` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcGetDir_12d3a8.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void PollSema(void);
extern void SignalSema(void);
extern void strncpy(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);

asm void sceMcGetDir_12d3a8(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    lui        $2, 0x49;
    sd         $23, 0x80($29);
    sd         $22, 0x70($29);
    addiu      $23, $2, -0x1000;
    sd         $20, 0x50($29);
    daddu      $22, $4, $0;
    sd         $19, 0x40($29);
    daddu      $20, $5, $0;
    sd         $18, 0x30($29);
    daddu      $19, $7, $0;
    sd         $17, 0x20($29);
    daddu      $18, $9, $0;
    sd         $16, 0x10($29);
    daddu      $17, $8, $0;
    sd         $31, 0x90($29);
    sd         $21, 0x60($29);
    lw         $2, 0x24($23);
    bnez       $2, L0012D400;
    daddu     $16, $6, $0;
    b          L0012D4C8;
    addiu     $2, $0, -0x64;
  L0012D400:
    lui        $21, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($21);
    bltz       $2, L0012D4C8;
    addiu     $2, $0, -0xC8;
    beqz       $16, L0012D428;
    nop;
    lb         $2, 0x0($16);
    bnez       $2, L0012D438;
    lui       $2, 0x49;
  L0012D428:
    jal        SignalSema;
    lw        $4, -0x6AA4($21);
    b          L0012D4C8;
    addiu     $2, $0, -0xD2;
  L0012D438:
    daddu      $5, $16, $0;
    addiu      $16, $2, -0xF50;
    sw         $22, -0xF50($2);
    sw         $20, 0x4($16);
    addiu      $4, $16, 0x14;
    sw         $19, 0x8($16);
    addiu      $6, $0, 0x3FF;
    sw         $17, 0xC($16);
    jal        strncpy;
    sw        $18, 0x10($16);
    bltz       $17, L0012D474;
    sb        $0, 0x413($16);
    daddu      $4, $18, $0;
    jal        sceSifWriteBackDCache;
    sll       $5, $17, 6;
  L0012D474:
    lui        $9, 0x49;
    lui        $11, 0x13;
    daddu      $4, $23, $0;
    daddu      $7, $16, $0;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x3738;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0xD;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x414;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012D4BC;
    addiu     $2, $0, 0xD;
    jal        SignalSema;
    lw        $4, -0x6AA4($21);
    b          L0012D4C8;
    addiu     $2, $0, -0x5B;
  L0012D4BC:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012D4C8:
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
