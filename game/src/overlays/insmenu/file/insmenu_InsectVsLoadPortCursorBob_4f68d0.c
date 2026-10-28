/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPortCursorBob_4f68d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F68D0 (260 bytes) -- the caption-placement twin of
 * insmenu_InsectVsLoadYesNoCursorBob_4f69e0 sixteen bytes later: same show/hide guard, same eased
 * lift, but it measures with func_376FD0 and then either sets the position or
 * fades it in at full alpha.
 *
 * ★ The hide arm RETURNS, so the show arm is the fall-through and the gp float
 * load for the next call rides the `b` out of it.
 * ★ `mtc1 $2, $f12` off `lui 0x3F80` is the literal `1.0f`. */

extern u8 insmenu_D_004FA180[];
extern f32 D_0047D3B8;          /* gp - 0x7DB8 */
extern f32 D_0048434C;          /* gp - 0xE24 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsLoadPortCursorBob_4f68d0(void *obj, s32 place, s32 show)
{
    f32 lift;
    s32 x;
    s32 y;

    if (show) {
        UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x890A, 1, -1);
    } else {
        UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x890A, 0, -1);
        return;
    }
    PhaseAdvanceWrapPi_28b630(&D_0048434C, D_0047D3B8);
    lift = 6.0f * Sinf_128fd0(D_0048434C);
    SaveMsgBoxGetPortCursorPos_376fd0(insmenu_D_004FA180, obj, &x, &y);
    x = (s32)((f32)x + lift);
    if (place) {
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x890A, x, y);
    } else {
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x890A, x, y, 1.0f, 0);
    }
}
