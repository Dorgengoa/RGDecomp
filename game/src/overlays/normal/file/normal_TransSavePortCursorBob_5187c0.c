/* rgp:protos */
#define RGP_SELF_normal_TransSavePortCursorBob_5187c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005187C0 -- the 0x80EC gauge.  The `c == 0` arm returns through the
 * far epilogue, so the function is void.  The 6.0f product is NAMED (f20) --
 * that is what keeps the `cvt.w.s` on the plain path and the `add.s` operands
 * in retail's order.  The float in the `b` delay slot is func_28B630's $f12
 * argument, not a dead load. */

extern void *D_00484714;          /* gp - 0xA5C */
extern f32   D_0047D3B8;          /* gp - 0x7DB8 */
extern f32   D_004847E4;          /* gp - 0x98C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_TransSavePortCursorBob_5187c0(s32 a, s32 b, s32 c)
{
    s32 x;
    s32 y;
    f32 t;

    if (c != 0) {
        UiSetWidgetVisible_290010(D_00484714, 0x80EC, 1, -1);
    } else {
        UiSetWidgetVisible_290010(D_00484714, 0x80EC, 0, -1);
        return;
    }
    PhaseAdvanceWrapPi_28b630(&D_004847E4, D_0047D3B8);
    t = 6.0f * Sinf_128fd0(D_004847E4);
    x = 0;
    y = 0;
    SaveMsgBoxGetPortCursorPos_376fd0(D_00484714, a, &x, &y);
    x = (s32)((f32)x + t);
    if (b != 0) {
        UiSetWidgetPos_290f60(D_00484714, 0x80EC, x, y);
    } else {
        UiMoveWidgetUniform_290f50(D_00484714, 0x80EC, x, y, 0.25f, 0);
    }
}
