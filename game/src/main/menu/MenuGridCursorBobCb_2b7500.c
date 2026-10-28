/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2b7500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_00482548;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuGridCursorBobCb_2b7500(s32 p0, s32 p1)
{
    s32 v0;
    s32 v1;
    s32 k;

    PhaseAdvanceWrapPi_28b630(&D_00482548, D_0047D3B8);
    k = (s32)(6.0f * Sinf_128fd0(D_00482548));
    GetGridCellPosOffset_28ecd0(p0, &v0, &v1, k, k);
    UiMoveWidgetUniform_290f50(p1, 0x185, v0, v1, 0.25f, 0);
    return 1;
}
