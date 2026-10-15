#include "types.h"

extern f32 Sinf_128fd0(f32 arg0);
extern void PhaseAdvanceWrapPi_28b630(f32 *arg0, f32 arg1);
extern void UiSelFrameAnimStep_28d820(void *arg0, s32 arg1);
extern void GetGridCellPosOffset_28ecd0(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4);
extern void UiMoveWidgetUniform_290f50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
extern const f32 D_0047D1FC __attribute__((section(".sdata")));
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern const f32 D_0047D3FC __attribute__((section(".sdata")));
extern f32 D_00482544;
extern f32 D_0048257C;
extern u8 D_004DB7F0[];

s32 MenuGridCursorBobCb_2b5850(s32 arg0, s32 arg1)
{
    s32 sp3C;
    s32 sp38;
    f32 t;
    s32 v;

    PhaseAdvanceWrapPi_28b630(&D_00482544, D_0047D3B8);
    t = 6.0f * Sinf_128fd0(D_00482544);
    v = (s32)(66.0f + t);
    GetGridCellPosOffset_28ecd0(arg0, &sp3C, &sp38, v, v);
    UiMoveWidgetUniform_290f50(arg1, 0x186, sp3C, sp38, 0, 0.25f);
    D_0048257C = D_0048257C + D_0047D3FC;
    if (!(D_0048257C <= 0.0f)) {
        D_0048257C = D_0048257C - D_0047D1FC;
    }
    UiMoveWidgetUniform_290f50(arg1, 0x182, (s32)(6.0f * Sinf_128fd0(D_0048257C)), 0, 0, 0.25f);
    UiSelFrameAnimStep_28d820(D_004DB7F0, 0x180);
    return 1;
}
