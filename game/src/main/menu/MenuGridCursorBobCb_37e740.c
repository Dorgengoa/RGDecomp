/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_37e740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0048323C;
extern u8 D_004E9230[0x100];

s32 MenuGridCursorBobCb_37e740(s32 arg0, s32 arg1)
{
    s32 sp3C;
    s32 sp38;

    PhaseAdvanceWrapPi_28b630(&D_0048323C, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp3C, &sp38, (s32)(8.0f * Sinf_128fd0(D_0048323C)), 0);
    UiMoveWidgetUniform_290f50(arg1, 0x762B, sp3C, sp38, 0.25f, 0);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
