#include "types.h"

extern f32 Sinf_128fd0(f32);
extern void PhaseAdvanceWrapPi_28b630(f32 *, f32);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern void GetGridCellPosOffset_28ecd0(s32, s32 *, s32 *, s32, s32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0048323C;
extern u8 D_004E9230[0x100];

s32 MenuGridCursorBobCb_37e740(s32 arg0, s32 arg1)
{
    s32 sp3C;
    s32 sp38;

    PhaseAdvanceWrapPi_28b630(&D_0048323C, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp3C, &sp38, (s32)(8.0f * Sinf_128fd0(D_0048323C)), 0);
    UiMoveWidgetUniform_290f50(arg1, 0x762B, sp3C, sp38, 0, 0.25f);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
