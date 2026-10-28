#include "types.h"

/* kh1 cross-reference, 2026-09-08: retail identity is `_InitSys`
   (ethteck/kh1 src/lib/libkernl/initsys.c), kept as `InitSys_120918` per the project's
   FUN_<addr>-while-decomping naming policy -- see config/names.txt.
   MEDIUM: RG makes ~9 calls where kh1's shown body makes 6
   Naked `asm void` (lever 6): retail's own bytes, transcribed by
   scripts/naked_asm_gen.py from asm/matchings/main/InitSys_120918.s -- the SDK
   library band is a compiler-identity wall for ordinary C, see
   config/levers.d/main-library-band (sd/sq callee-saved shape). */
extern void SupplementCrt0_1206c8(void);
extern void GetSystemCallTableEntry_120808(void);
extern void InitAlarm_120df8(void);
extern void InitTimer_120f70(void);
extern void StartTimerSystemTime_1211b0(void);
extern void InitThread_117378(void);
extern void InitExecPS2_120a40(void);
extern void InitTLBFunctions_11ff30(void);
extern void IopResetCallbacksInitMaybe_122630(void);

asm void InitSys_120918(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        SupplementCrt0_1206c8;
    nop;
    jal        GetSystemCallTableEntry_120808;
    nop;
    jal        InitAlarm_120df8;
    nop;
    jal        InitTimer_120f70;
    addiu     $4, $0, 0x2;
    jal        StartTimerSystemTime_1211b0;
    nop;
    jal        InitThread_117378;
    nop;
    jal        InitExecPS2_120a40;
    nop;
    jal        InitTLBFunctions_11ff30;
    nop;
    ld         $31, 0x0($29);
    j          IopResetCallbacksInitMaybe_122630;
    addiu     $29, $29, 0x10;
}
