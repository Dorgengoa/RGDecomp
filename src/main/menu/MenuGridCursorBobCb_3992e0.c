#include "types.h"

f32 Sinf_128fd0(f32);                              /* extern */
s32 PhaseAdvanceWrapPi_28b630(f32 *, f32);                         /* extern */
s32 GetGridCellPosOffset_28ecd0(s32, s32 *, s32 *, s32, s32);          /* extern */
s32 UiSetWidgetAlpha_2907a0(s32, s32, f32);                        /* extern */
s32 UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);             /* extern */
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00483590;
extern f32 D_0048359C;
extern f32 D_004835A0;
extern  f32 D_0047D2CC;

s32 MenuGridCursorBobCb_3992e0(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    f32 temp_f12;

    PhaseAdvanceWrapPi_28b630(&D_00483590, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, (s32) (8.0f * Sinf_128fd0(D_00483590)), 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x219, sp2C, sp28, 0, 0.25f);
    if (!(D_0048359C <= 1.0f) || (D_0048359C < 0.5f)) {
        D_004835A0 *= -1.0f;
    }
    D_0048359C = D_0048359C + D_0047D2CC * D_004835A0;
    UiSetWidgetAlpha_2907a0(D_00482360, 0x218, D_0048359C);
    return 1;
}
