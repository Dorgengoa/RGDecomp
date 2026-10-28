/* rgp:protos */
#define RGP_SELF_normal_TransMenuCursorBobToCell_514ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00514AD0 -- the scaled-offset placement call.  `6.0f * f` is NAMED
 * (the float-product lever) so the madd contraction and the IEEE fptosi path
 * both go away; the two conversions then come out as plain `cvt.w.s`.
 * `lwc1 $f12,-0x7DB8($28)` is the POOL ENTRY 0x0047D3B8 = 0.078539819f (pi/40);
 * written as an `extern f32` its load is PINNED and sinks below the callee-saved
 * saves -- only the LITERAL reproduces retail's schedule. */

typedef struct Obj { u8 pad00[0x12]; s16 f12; } Obj;

extern f32 D_00484780;            /* gp - 0x9F0  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuCursorBobToCell_514ad0(Obj *p, void *w, s32 dx, s32 dy)
{
    s32 ox;
    s32 oy;
    f32 t;

    PhaseAdvanceWrapPi_28b630(&D_00484780, 0.078539819f);
    t = 6.0f * Sinf_128fd0(D_00484780);
    GetGridCellPosOffset_28ecd0(p, &ox, &oy, (s32)(t + dx), (s32)(p->f12 + (t + dy)));
    UiMoveWidgetUniform_290f50(w, 0x7556, ox, oy, 0.25f, 0);
    return 1;
}
