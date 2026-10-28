#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `sceDopen`
   (ethteck/kh1 src/lib/filestub.c), kept as `sceDopen_11d188` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/sceDopen_11d188.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void FileIoUnlock_11b330(void);
extern void FileIoAllocSlot_11ad08(void);
extern void FileIoPathCmdRpc_11ca10(void);
extern void WaitSema(void);
extern void SignalSema(void);

asm void sceDopen_11d188(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x30($29);
    sd         $18, 0x20($29);
    addiu      $4, $0, 0x9;
    jal        FileIoLock_11b300;
    sd        $17, 0x10($29);
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    bnez       $2, L0011D1C0;
    nop;
    jal        SceFsInit_11b428;
    nop;
  L0011D1C0:
    jal        FileIoUnlock_11b330;
    nop;
    jal        FileIoAllocSlot_11ad08;
    nop;
    daddu      $18, $2, $0;
    bnez       $18, L0011D1E4;
    daddu     $4, $16, $0;
    b          L0011D238;
    addiu     $2, $0, -0x13;
  L0011D1E4:
    jal        FileIoPathCmdRpc_11ca10;
    addiu     $5, $0, 0x9;
    daddu      $17, $2, $0;
    bgez       $17, L0011D20C;
    lui       $16, 0x44;
    jal        WaitSema;
    lw        $4, 0x62A8($16);
    sw         $0, 0x4($18);
    b          L0011D22C;
    lw        $4, 0x62A8($16);
  L0011D20C:
    jal        WaitSema;
    lw        $4, 0x62A8($16);
    lui        $3, 0x49;
    sw         $17, 0x0($18);
    addiu      $3, $3, -0x6740;
    lw         $4, 0x62A8($16);
    subu       $3, $18, $3;
    sra        $17, $3, 4;
  L0011D22C:
    jal        SignalSema;
    nop;
    daddu      $2, $17, $0;
  L0011D238:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
