#include "types.h"

extern f32 Sinf_128fd0(f32 arg0);
extern void PhaseAdvanceWrapPi_28b630(f32 *arg0, f32 arg1);
extern void GetGridCellPosOffset_28ecd0(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4);
extern void UiSetWidgetAlpha_2907a0(s32 arg0, s32 arg1, f32 arg2);
extern void UiMoveWidgetUniform_290f50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
extern f32 D_0047D2CC;
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00482E80;
extern f32 D_00482E8C;
extern f32 D_00482E90;

s32 MenuGridCursorBobCb_34e740(s32 arg0, s32 arg1)
{
    s32 sp3C;
    s32 sp38;
    f32 temp_f12;

    PhaseAdvanceWrapPi_28b630(&D_00482E80, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp3C, &sp38, (s32)(8.0f * Sinf_128fd0(D_00482E80)), 0);
    UiMoveWidgetUniform_290f50(arg1, 0x219, sp3C, sp38, 0, 0.25f);
    if (!(D_00482E8C <= 1.0f) || (D_00482E8C < 0.5f)) {
        D_00482E90 *= -1.0f;
    }
    D_00482E8C = D_00482E8C + D_0047D2CC * D_00482E90;
    UiSetWidgetAlpha_2907a0(D_00482360, 0x218, D_00482E8C);
    return 1;
}
