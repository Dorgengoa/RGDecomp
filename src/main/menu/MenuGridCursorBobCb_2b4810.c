#include "types.h"

f32 Sinf_128fd0(f32);
s32 PhaseAdvanceWrapPi_28b630(f32 *, f32);
s32 GetGridCellPosOffset_28ecd0(s32, s32 *, s32 *, s32, s32);
s32 UiSetWidgetAlpha_2907a0(s32, s32, f32);
s32 UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0047D2CC;
extern s32 D_00482360;
extern f32 D_00482544;
extern f32 D_00482584;
extern s16 D_00482588;

s32 MenuGridCursorBobCb_2b4810(s32 arg0, s32 arg1) {
    s32 sp3C;
    s32 sp38;

    PhaseAdvanceWrapPi_28b630(&D_00482544, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp3C, &sp38, (s32)(8.0f * Sinf_128fd0(D_00482544)), 0);
    UiMoveWidgetUniform_290f50(arg1, 0x183, sp3C, sp38, 0, 0.25f);
    if (D_00482584 > 1.0f || D_00482584 < 0.5f) {
        D_00482588 = -D_00482588;
    }
    D_00482584 = D_00482584 + D_0047D2CC * (f32)D_00482588;
    UiSetWidgetAlpha_2907a0(D_00482360, 0x12C, D_00482584);
    return 1;
}
