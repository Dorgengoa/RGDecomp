#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `GetSystemCallTableEntry`
   (ethteck/kh1 src/lib/libkernl/initsys.c), kept as `GetSystemCallTableEntry_120808` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   MEDIUM: RG makes a 2-target loop where kh1 shows a single search-and-subtract
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/GetSystemCallTableEntry_120808.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void RFU116_SetSyscall_2(void);
extern void FindAddress_1207c0(void);

asm void GetSystemCallTableEntry_120808(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    lui        $2, 0x44;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    lui        $21, 0x12;
    sd         $19, 0x30($29);
    lui        $20, 0x12;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x70($29);
    addiu      $16, $2, 0x6920;
    sd         $22, 0x60($29);
    lw         $4, 0x6920($2);
    jal        RFU116_SetSyscall_2;
    lw        $5, 0x4($16);
    lw         $5, 0xC($16);
    jal        RFU116_SetSyscall_2;
    lw        $4, 0x8($16);
    lui        $4, (0x80000000 >> 16);
    lui        $5, (0x80080000 >> 16);
    jal        FindAddress_1207c0;
    addiu     $6, $21, 0x780;
    daddu      $19, $2, $0;
    lui        $4, (0x80000000 >> 16);
    lui        $5, (0x80080000 >> 16);
    jal        FindAddress_1207c0;
    addiu     $6, $20, 0x748;
    addiu      $17, $19, -0x20C;
    daddu      $18, $2, $0;
    addiu      $16, $18, -0x168;
    beq        $17, $16, L001208D8;
    lui       $22, 0x44;
    sltu       $2, $17, $16;
  L00120890:
    beqz       $2, L001208B0;
    addiu     $4, $19, 0x4;
    lui        $5, (0x80080000 >> 16);
    jal        FindAddress_1207c0;
    addiu     $6, $21, 0x780;
    daddu      $19, $2, $0;
    b          L001208C8;
    addiu     $17, $19, -0x20C;
  L001208B0:
    addiu      $4, $18, 0x4;
    lui        $5, (0x80080000 >> 16);
    jal        FindAddress_1207c0;
    addiu     $6, $20, 0x748;
    daddu      $18, $2, $0;
    addiu      $16, $18, -0x168;
  L001208C8:
    bne        $17, $16, L00120890;
    sltu      $2, $17, $16;
    b          L001208DC;
    sw        $17, 0x6918($22);
  L001208D8:
    sw         $17, 0x6918($22);
  L001208DC:
    ld         $31, 0x70($29);
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
