#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceMcRename`
   (ethteck/kh1 src/lib/libmc.c), kept as `sceMcRename_12db48` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceMcRename_12db48.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void PollSema(void);
extern void SignalSema(void);
extern void strncpy(void);
extern void FlushCache(void);
extern void sceSifCallRpc(void);

asm void sceMcRename_12db48(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    lui        $2, 0x49;
    sd         $22, 0x70($29);
    sd         $20, 0x50($29);
    addiu      $22, $2, -0x1000;
    sd         $19, 0x40($29);
    daddu      $20, $4, $0;
    sd         $18, 0x30($29);
    daddu      $19, $5, $0;
    sd         $16, 0x10($29);
    daddu      $18, $7, $0;
    sd         $31, 0x80($29);
    sd         $21, 0x60($29);
    sd         $17, 0x20($29);
    lw         $2, 0x24($22);
    bnez       $2, L0012DB94;
    daddu     $16, $6, $0;
    b          L0012DC78;
    addiu     $2, $0, -0x64;
  L0012DB94:
    lui        $21, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA4($21);
    bltz       $2, L0012DC78;
    addiu     $2, $0, -0xC8;
    beqz       $16, L0012DBC4;
    nop;
    lb         $2, 0x0($16);
    beqz       $2, L0012DBC4;
    nop;
    bnez       $18, L0012DBD4;
    lui       $2, 0x49;
  L0012DBC4:
    jal        SignalSema;
    lw        $4, -0x6AA4($21);
    b          L0012DC78;
    addiu     $2, $0, -0xD2;
  L0012DBD4:
    addiu      $3, $0, 0x10;
    addiu      $17, $2, -0xF50;
    sw         $20, -0xF50($2);
    daddu      $5, $16, $0;
    sw         $19, 0x4($17);
    sw         $3, 0x8($17);
    addiu      $4, $17, 0x14;
    jal        strncpy;
    addiu     $6, $0, 0x3FF;
    lui        $16, 0x49;
    daddu      $5, $18, $0;
    addiu      $16, $16, -0xFA0;
    sb         $0, 0x413($17);
    daddu      $4, $16, $0;
    jal        strncpy;
    addiu     $6, $0, 0x20;
    addiu      $16, $16, -0x20;
    daddu      $4, $0, $0;
    jal        FlushCache;
    sw        $16, 0x10($17);
    lui        $9, 0x49;
    lui        $11, 0x13;
    daddu      $4, $22, $0;
    daddu      $7, $17, $0;
    addiu      $9, $9, 0x5C0;
    addiu      $11, $11, -0x3738;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0xE;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x414;
    jal        sceSifCallRpc;
    addiu     $10, $0, 0x4;
    beqz       $2, L0012DC6C;
    addiu     $2, $0, 0x13;
    jal        SignalSema;
    lw        $4, -0x6AA4($21);
    b          L0012DC78;
    addiu     $2, $0, -0x5B;
  L0012DC6C:
    lui        $3, 0x45;
    sw         $2, -0x6AA8($3);
    daddu      $2, $0, $0;
  L0012DC78:
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
