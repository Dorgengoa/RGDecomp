#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceGetstat`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceGetstat_11d510` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceGetstat_11d510.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void CreateSema(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void FileIoUnlock_11b330(void);
extern void WaitSema(void);

asm void sceGetstat_11d510(void)
{
    .set noreorder;
    addiu      $29, $29, -0xD0;
    sd         $17, 0x50($29);
    sd         $22, 0xA0($29);
    daddu      $17, $4, $0;
    sd         $23, 0xB0($29);
    daddu      $22, $5, $0;
    sd         $18, 0x60($29);
    addiu      $4, $0, 0xC;
    sd         $31, 0xC0($29);
    lui        $23, 0x49;
    sd         $21, 0x90($29);
    addiu      $18, $23, -0x7C40;
    sd         $20, 0x80($29);
    sd         $19, 0x70($29);
    jal        FileIoLock_11b300;
    sd        $16, 0x40($29);
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnel       $3, $0, L0011D56C;
    lbu       $2, 0x0($17);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($17);
  L0011D56C:
    daddu      $16, $0, $0;
    daddu      $3, $2, $0;
    beqz       $3, L0011D5B8;
    sb        $2, 0x10($18);
    lui        $5, 0x45;
    addiu      $19, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
    nop;
  L0011D590:
    addiu      $16, $16, 0x1;
    slti       $2, $16, 0x400;
    beqz       $2, L0011D5C8;
    addu      $2, $17, $16;
    addu       $4, $18, $16;
    lbu        $3, 0x0($2);
    bnez       $3, L0011D590;
    sb        $3, 0x10($4);
    b          L0011D5CC;
    addiu     $2, $0, 0x400;
  L0011D5B8:
    lui        $5, 0x45;
    addiu      $19, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
  L0011D5C8:
    addiu      $2, $0, 0x400;
  L0011D5CC:
    bnel       $16, $2, L0011D5E0;
    sw        $22, 0xC($18);
    sb         $0, 0x40F($18);
    addiu      $16, $0, 0x3FF;
    sw         $22, 0xC($18);
  L0011D5E0:
    addiu      $3, $5, 0x6B18;
    addiu      $2, $0, 0x1;
    addiu      $4, $29, 0x10;
    sw         $2, 0x14($29);
    addiu      $20, $20, -0x7000;
    sw         $3, 0x24($29);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $17, $2, $0;
    sw         $19, 0x4($18);
    addiu      $2, $0, 0x4;
    sw         $17, 0x0($18);
    sw         $2, 0x8($18);
    addiu      $4, $21, -0x6540;
    addiu      $7, $23, -0x7C40;
    addiu      $8, $16, 0x11;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0xC;
    sw         $0, 0x8($29);
    daddu      $6, $0, $0;
    daddu      $9, $20, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011D660;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011D698;
    addiu     $2, $0, -0xB;
  L0011D660:
    or         $2, $20, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011D684;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011D698;
    addiu     $2, $0, -0xB;
  L0011D684:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011D698:
    ld         $31, 0xC0($29);
    ld         $23, 0xB0($29);
    ld         $22, 0xA0($29);
    ld         $21, 0x90($29);
    ld         $20, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0xD0;
}
