/* PARK s16d: 1 round trip, length 0x134 vs retail 0x12C (2 words over).
   Buffer sizes for spF0/spB0/sp90/sp80/sp70/sp60/sp50 are inferred from
   the retail stack-slot gaps, not confirmed against the callees' real
   struct layouts. Not re-tried past round 1 given lane time budget. */
#include "types.h"
#pragma peephole off

extern s32 SrtMatMul_1c7470(void *, void *, void *);
extern void SrtCtor48_1c7510(void *);
extern void MatToRotPos_1cade0(void *, void *, void *);
extern void MatMul_1cb700(void *, void *, void *);
extern void VecNormalize_1cbb80(void *, void *);
extern s32 EventPathEvalXformByName_2e3d20(s32, void *, s32, s32, s32);
extern void TargetRefDetachFromParent_2e5890(void *);
extern void TargetRefSetTranslation_2e5bf0(void *, void *);
extern void TargetRefSetRotation_2e5d10(void *, void *);
extern s32 TargetRefResolve_2e5ed0(void);
extern void TargetRefGetMatrix_2e6870(void *, void *);
extern void NodeCalcWorldMatrixThunk_186130(s32, void *);

s32 TargetRefPairAlignToNodeMaybe_338460(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 spF0[0x30];
    u8 spB0[0x40];
    u8 sp70[0x40];
    u8 sp60[0x10];
    u8 sp50[0x10];
    s32 r;

    if (arg1 == 0) return 0;
    if (TargetRefResolve_2e5ed0() == 0) return 0;
    if (*(s32 *)(arg0 + 0x60) == 0) return 0;
    SrtCtor48_1c7510(spF0);
    r = EventPathEvalXformByName_2e3d20(*(s32 *)(arg0 + 0x60), spF0, arg2, arg3, 0) & 0xFF;
    NodeCalcWorldMatrixThunk_186130(arg1, sp70);
    TargetRefGetMatrix_2e6870(arg0, spB0);
    MatMul_1cb700(sp70, sp70, spB0);
    VecNormalize_1cbb80(sp70, sp70);
    VecNormalize_1cbb80(sp70 + 0x10, sp70 + 0x10);
    VecNormalize_1cbb80(sp70 + 0x20, sp70 + 0x20);
    SrtMatMul_1c7470(spF0, spB0, sp70);
    MatToRotPos_1cade0(sp60, sp50, spB0);
    TargetRefDetachFromParent_2e5890(arg0 + 0x30);
    TargetRefSetRotation_2e5d10(arg0 + 0x30, sp60);
    TargetRefSetTranslation_2e5bf0(arg0 + 0x30, sp50);
    return r;
}
