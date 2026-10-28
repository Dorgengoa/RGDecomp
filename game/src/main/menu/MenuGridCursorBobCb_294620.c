/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_294620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;
struct Obj1;

extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_004823B8;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuGridCursorBobCb_294620(s32 p0, s32 p1)
{
    s32 v0;
    s32 v1;

    PhaseAdvanceWrapPi_28b630((struct Obj0 *)&D_004823B8, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(p0, (struct Obj0 *)&v0, (struct Obj1 *)&v1, (s32)(6.0f * Sinf_128fd0(D_004823B8)), 0);
    UiMoveWidgetUniform_290f50(p1, 0x1B2, v0, v1, 0.25f, 0);
    return 1;
}
