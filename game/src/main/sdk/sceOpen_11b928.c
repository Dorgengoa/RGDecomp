#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceOpen`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceOpen_11b928` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceOpen_11b928.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void FsVersion_11b630(void);
extern void FileIoUnlock_11b330(void);
extern void FileIoAllocSlot_11ad08(void);
extern void CreateSema(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void WaitSema(void);
extern void SignalSema(void);

asm void sceOpen_11b928(void)
{
    .set noreorder;
    addiu      $29, $29, -0x150;
    sd         $16, 0x40($29);
    sd         $23, 0xB0($29);
    daddu      $16, $4, $0;
    sd         $30, 0xC0($29);
    daddu      $23, $5, $0;
    sd         $17, 0x50($29);
    daddu      $4, $0, $0;
    sd         $31, 0xD0($29);
    lui        $30, 0x49;
    sd         $22, 0xA0($29);
    addiu      $17, $30, -0x7C40;
    sd         $21, 0x90($29);
    sd         $20, 0x80($29);
    sd         $19, 0x70($29);
    sd         $18, 0x60($29);
    sd         $6, 0x120($29);
    sd         $7, 0x128($29);
    sd         $8, 0x130($29);
    sd         $9, 0x138($29);
    sd         $10, 0x140($29);
    jal        FileIoLock_11b300;
    sd        $11, 0x148($29);
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    bnez       $2, L0011B99C;
    nop;
    jal        SceFsInit_11b428;
    nop;
  L0011B99C:
    jal        FsVersion_11b630;
    nop;
    beqz       $2, L0011B9C0;
    nop;
    jal        FileIoUnlock_11b330;
    nop;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011BB88;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011B9C0:
    jal        FileIoAllocSlot_11ad08;
    nop;
    daddu      $19, $2, $0;
    bnel       $19, $0, L0011B9E4;
    lbu       $3, 0x0($16);
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011BB88;
    addiu     $2, $0, -0x13;
  L0011B9E4:
    daddu      $6, $0, $0;
    lw         $8, 0x120($29);
    sll        $2, $3, 24;
    beqz       $2, L0011BA3C;
    sb        $3, 0x14($17);
    lui        $7, 0x49;
    lui        $5, 0x45;
    addiu      $18, $29, 0x30;
    lui        $22, 0x49;
    lui        $20, 0x49;
    addiu      $6, $6, 0x1;
  L0011BA10:
    slti       $2, $6, 0x400;
    beqz       $2, L0011BA50;
    addu      $2, $16, $6;
    addu       $4, $17, $6;
    lbu        $3, 0x0($2);
    sb         $3, 0x14($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011BA10;
    addiu     $6, $6, 0x1;
    b          L0011BA54;
    addiu     $2, $0, 0x400;
  L0011BA3C:
    lui        $7, 0x49;
    lui        $5, 0x45;
    addiu      $18, $29, 0x30;
    lui        $22, 0x49;
    lui        $20, 0x49;
  L0011BA50:
    addiu      $2, $0, 0x400;
  L0011BA54:
    beql       $6, $2, L0011BA5C;
    sb        $0, 0x413($17);
  L0011BA5C:
    addiu      $2, $7, -0x6740;
    lui        $3, (0x7FFFFFFF >> 16);
    subu       $2, $19, $2;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    sra        $21, $2, 4;
    and        $3, $23, $3;
    sw         $3, 0xC($17);
    addiu      $5, $5, 0x69E0;
    sw         $8, 0x10($17);
    addiu      $2, $0, 0x1;
    sw         $2, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $5, 0x24($29);
    addiu      $20, $20, -0x7000;
    sw         $21, 0x414($17);
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $16, $2, $0;
    sw         $18, 0x4($17);
    addiu      $2, $0, 0x4;
    sw         $16, 0x0($17);
    sw         $2, 0x8($17);
    addiu      $4, $22, -0x6540;
    addiu      $7, $30, -0x7C40;
    daddu      $5, $0, $0;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    sw         $0, 0x8($29);
    addiu      $8, $0, 0x418;
    daddu      $9, $20, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011BB00;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $16, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011BB88;
    addiu     $2, $0, -0xB;
  L0011BB00:
    or         $2, $20, $2;
    jal        FileIoUnlock_11b330;
    lw        $17, (0x20000000 & 0xFFFF)($2);
    bnez       $17, L0011BB24;
    nop;
    jal        DeleteSema;
    daddu     $4, $16, $0;
    b          L0011BB88;
    addiu     $2, $0, -0xB;
  L0011BB24:
    jal        WaitSema;
    daddu     $4, $16, $0;
    jal        DeleteSema;
    daddu     $4, $16, $0;
    lw         $3, 0x30($29);
    bgez       $3, L0011BB5C;
    lui       $16, 0x44;
    jal        WaitSema;
    lw        $4, 0x62A8($16);
    sw         $0, 0x4($19);
    jal        SignalSema;
    lw        $4, 0x62A8($16);
    b          L0011BB88;
    lw        $2, 0x30($29);
  L0011BB5C:
    daddu      $17, $21, $0;
    jal        WaitSema;
    lw        $4, 0x62A8($16);
    lw         $3, 0x4($19);
    lw         $2, 0x30($29);
    lw         $4, 0x62A8($16);
    or         $3, $3, $23;
    sw         $3, 0x4($19);
    jal        SignalSema;
    sw        $2, 0x0($19);
    daddu      $2, $17, $0;
  L0011BB88:
    ld         $31, 0xD0($29);
    ld         $30, 0xC0($29);
    ld         $23, 0xB0($29);
    ld         $22, 0xA0($29);
    ld         $21, 0x90($29);
    ld         $20, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0x150;
}
