/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuGridCursorBobToCell_5209c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005209C0 -- advance the shared phase by 0.1570796f, take its sine,
 * scale by 6.0 and offset the two integer arguments by it.  The product
 * 6.0f * sinf(phase) is used twice, so it is a NAMED local -- that is what
 * keeps the `mul.s` out of a madd and fixes the add.s operand order.
 * 0x0047D3D0 is a mwcc .lit4 POOL ENTRY, so it must be spelled as the float
 * LITERAL -- an `extern f32` load is pinned below the callee-saved `sq`
 * stores and rotates the whole prologue by one slot. */

extern f32 D_00484944;            /* gp - 0x82C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ThinkMenuGridCursorBobToCell_5209c0(void *a, void *b, s32 c, s32 d)
{
    s32 ox;
    s32 oy;
    f32 s;

    PhaseAdvanceWrapPi_28b630(&D_00484944, 0.1570796371f);
    s = 6.0f * Sinf_128fd0(D_00484944);
    GetGridCellPosOffset_28ecd0(a, &ox, &oy, (s32)(s + (f32)c), (s32)(s + (f32)d));
    UiMoveWidgetUniform_290f50(b, 0x7544, ox, oy, 0.5f, 0);
    return 1;
}
