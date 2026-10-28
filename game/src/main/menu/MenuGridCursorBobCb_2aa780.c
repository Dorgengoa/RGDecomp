/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2aa780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_004824C8;
extern void *D_00482360;
extern u8 D_004DB430[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuGridCursorBobCb_2aa780(void *o)
{
    s32 x;
    s32 y;
    f32 v;

    v = D_0047D3B8;
    PhaseAdvanceWrapPi_28b630(&D_004824C8, v);
    GetGridCellPosOffset_28ecd0(o, &x, &y, (s32)(8.0f * Sinf_128fd0(D_004824C8)), 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x13F, x, y, 0.25f, 0);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
