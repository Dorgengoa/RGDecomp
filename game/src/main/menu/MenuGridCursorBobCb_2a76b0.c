/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2a76b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_004824C8;
extern void *D_00482360;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuGridCursorBobCb_2a76b0(void *a0)
{
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(a0, &x, &y, (s32)(6.0f * Sinf_128fd0(D_004824C8)), 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x146, x, y, 0.25f, 0);
    return 1;
}
