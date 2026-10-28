/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadYesNoCursorBob_4f69e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F69E0 (220 bytes) -- show or hide the insect-menu caption, and
 * when showing it, nudge its Y by the eased fade value.
 *
 * ★ The hide arm RETURNS, so the show arm is the fall-through and the common
 * tail belongs to the show path only; retail's `b` out of the show arm carries
 * the gp float load for the next call in its delay slot.
 * ★ `lwc1 $f0` on a slot that func_3770B0 filled with an INTEGER, followed by
 * cvt.s.w, is a plain `(f32)x` on an s32 out-parameter. */

extern u8 insmenu_D_004FA180[];
extern f32 D_0047D3B8;          /* gp - 0x7DB8 */
extern f32 D_0048434C;          /* gp - 0xE24 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsLoadYesNoCursorBob_4f69e0(void *obj, s32 b, s32 show)
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
    SaveMsgBoxGetYesNoCursorPos_3770b0(insmenu_D_004FA180, obj, &x, &y);
    x = (s32)((f32)x + lift);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x890A, x, y);
    SaveMsgBoxSetCursorMaybe_3773a0(insmenu_D_004FA180, obj);
}
