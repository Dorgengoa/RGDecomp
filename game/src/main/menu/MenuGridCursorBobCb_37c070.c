/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_37c070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0048323C;
extern void *D_00484710;
extern u8 D_004E9230[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuGridCursorBobCb_37c070(void *o)
{
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_0048323C, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(o, &x, &y, (s32)(8.0f * Sinf_128fd0(D_0048323C)), 0);
    UiMoveWidgetUniform_290f50(D_00484710, 0x762C, x, y, 0.25f, 0);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
