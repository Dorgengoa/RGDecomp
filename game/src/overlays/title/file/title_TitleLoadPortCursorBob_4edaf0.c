/* rgp:protos */
#define RGP_SELF_title_TitleLoadPortCursorBob_4edaf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDAF0 -- the twin of title_FUN_004EDC00: same
 * wrapping phase, a different placement helper, and a second branch choosing
 * between the four-argument and the six-argument draw call.
 */

extern f32 D_0047D1FC;
extern f32 D_0047D3B8;
extern f32 D_004841F4;
extern void *D_00484174;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void title_TitleLoadPortCursorBob_4edaf0(s16 a, s32 mode, s32 flag)
{
    f32 t;
    f32 k;
    s32 x;
    s32 y;

    if (flag != 0) {
        UiSetWidgetVisible_290010(D_00484174, 0xCA, 1, -1);
        goto on;
    }
    UiSetWidgetVisible_290010(D_00484174, 0xCA, 0, -1);
    return;
on:
    {
        t = D_004841F4 + D_0047D3B8;
        D_004841F4 = t;
        if (t > 0.0f) {
            D_004841F4 = t - D_0047D1FC;
        }
        k = 6.0f * Sinf_128fd0(D_004841F4);
        SaveMsgBoxGetPortCursorPos_376fd0(D_00484174, a, &x, &y);
        x = (s32)((f32)x + k);
        if (mode != 0) {
            UiSetWidgetPos_290f60(D_00484174, 0xCA, x, y);
        } else {
            UiMoveWidgetUniform_290f50(D_00484174, 0xCA, x, y, 0.5f, 0);
        }
    }
}
