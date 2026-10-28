/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_341730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0047D2CC;
extern s32 D_00482360;
extern f32 D_00482D00;
extern f32 D_00482D08;
extern s16 D_00482D0C;

s32 MenuGridCursorBobCb_341730(s32 arg0) {
    s32 sp2C;
    s32 sp28;

    PhaseAdvanceWrapPi_28b630(&D_00482D00, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, (s32) (8.0f * Sinf_128fd0(D_00482D00)), 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x19E, sp2C, sp28, 0.25f, 0);
    if ((D_00482D08 > 1.0f) || (D_00482D08 < 0.5f)) {
        D_00482D0C = -D_00482D0C;
    }
    D_00482D08 = D_00482D08 + (D_0047D2CC * (f32)D_00482D0C);
    UiSetWidgetAlpha_2907a0(D_00482360, 0x198, D_00482D08);
    return 1;
}
