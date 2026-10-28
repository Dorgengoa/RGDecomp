/* rgp:protos */
#define RGP_SELF_normal_TransSaveYesNoCursorBob_5188c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005188C0 -- the gauge publisher.  `ori $5,$0,0x80EC` (not addiu) is
 * the u16 id.  The two stack ints live at sp+0x3C and sp+0x38 and are written
 * back after the float bias, which is why 0x3C is re-stored. */

extern void *D_00484714;   /* gp - 0xA5C  */
extern f32   D_004847E4;   /* gp - 0x98C  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_TransSaveYesNoCursorBob_5188c0(s32 a, s32 b, s32 c)
{
    s32 x;
    s32 y;
    f32 bias;

    if (c != 0) {
        UiSetWidgetVisible_290010(D_00484714, 0x80EC, 1, -1);
    } else {
        UiSetWidgetVisible_290010(D_00484714, 0x80EC, 0, -1);
        return;
    }
    PhaseAdvanceWrapPi_28b630(&D_004847E4, 0.078539818525314331f);
    bias = 6.0f * Sinf_128fd0(D_004847E4);
    x = 0;
    y = 0;
    SaveMsgBoxGetYesNoCursorPos_3770b0(D_00484714, a, &x, &y);
    x = (s32)((f32)x + bias);
    UiSetWidgetPos_290f60(D_00484714, 0x80EC, x, y);
    SaveMsgBoxSetCursorMaybe_3773a0(D_00484714, a);
}
