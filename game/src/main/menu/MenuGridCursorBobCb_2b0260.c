/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2b0260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern u8 D_004823CC __attribute__((section(".sdata")));
extern f32 D_004824C8;
extern u8 D_004DB430[0x100];

s32 MenuGridCursorBobCb_2b0260(s32 arg0) {
    s32 sp2C;
    s32 sp28;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, (s32)(8.0f * Sinf_128fd0(D_004824C8)), 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x1A7, sp2C, sp28, 0.25f, 0);
    if (D_004823CC != 0) {
        MenuWidgetPulseColor_2b3200();
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
