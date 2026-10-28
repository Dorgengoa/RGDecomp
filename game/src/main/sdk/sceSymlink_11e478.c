#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceSymlink`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceSymlink_11e478` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceSymlink_11e478.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void CreateSema(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void FileIoUnlock_11b330(void);
extern void WaitSema(void);

asm void sceSymlink_11e478(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $16, 0x40($29);
    sd         $17, 0x50($29);
    daddu      $16, $4, $0;
    sd         $22, 0xA0($29);
    daddu      $17, $5, $0;
    sd         $18, 0x60($29);
    addiu      $4, $0, 0x11;
    sd         $31, 0xB0($29);
    lui        $22, 0x49;
    sd         $21, 0x90($29);
    addiu      $18, $22, -0x7C40;
    sd         $20, 0x80($29);
    jal        FileIoLock_11b300;
    sd        $19, 0x70($29);
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnel       $3, $0, L0011E4D0;
    lbu       $2, 0x0($16);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($16);
  L0011E4D0:
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011E524;
    sb        $2, 0xC($18);
    lui        $7, 0x45;
    addiu      $19, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
    addiu      $5, $5, 0x1;
    nop;
  L0011E4F8:
    slti       $2, $5, 0x400;
    beqz       $2, L0011E534;
    addu      $2, $16, $5;
    addu       $4, $18, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0xC($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011E4F8;
    addiu     $5, $5, 0x1;
    b          L0011E538;
    addiu     $2, $0, 0x400;
  L0011E524:
    lui        $7, 0x45;
    addiu      $19, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
  L0011E534:
    addiu      $2, $0, 0x400;
  L0011E538:
    beql       $5, $2, L0011E540;
    sb        $0, 0x40B($18);
  L0011E540:
    lbu        $2, 0x0($17);
    daddu      $5, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011E584;
    sb        $2, 0x40C($18);
    addiu      $6, $18, 0x40C;
    addiu      $5, $5, 0x1;
    nop;
  L0011E560:
    slti       $2, $5, 0x400;
    beqz       $2, L0011E584;
    addu      $2, $17, $5;
    addu       $4, $6, $5;
    lbu        $3, 0x0($2);
    sb         $3, 0x0($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011E560;
    addiu     $5, $5, 0x1;
  L0011E584:
    addiu      $2, $0, 0x400;
    beql       $5, $2, L0011E590;
    sb        $0, 0x80B($18);
  L0011E590:
    addiu      $2, $7, 0x6BC0;
    addiu      $3, $0, 0x1;
    sw         $3, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $2, 0x24($29);
    addiu      $16, $20, -0x7000;
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $17, $2, $0;
    sw         $19, 0x4($18);
    addiu      $2, $0, 0x4;
    sw         $17, 0x0($18);
    sw         $2, 0x8($18);
    addiu      $4, $21, -0x6540;
    addiu      $7, $22, -0x7C40;
    addiu      $5, $0, 0x18;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    sw         $0, 0x8($29);
    addiu      $8, $0, 0x80C;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011E610;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011E648;
    addiu     $2, $0, -0xB;
  L0011E610:
    or         $2, $16, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011E634;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011E648;
    addiu     $2, $0, -0xB;
  L0011E634:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011E648:
    ld         $31, 0xB0($29);
    ld         $22, 0xA0($29);
    ld         $21, 0x90($29);
    ld         $20, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}
