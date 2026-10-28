/* rgp:protos */
#define RGP_SELF_normal_LeaderHudBannerSlide_507d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00507D70 -- slide widget 7 in/out, anchored on the measured box
 * that func_289A40 writes back.
 *
 * Two named locals carry the whole match:
 *   `d = x - a` placed BEFORE the D_00484570 guard -- it is what buys the
 *   fifth callee-saved register ($20) and puts the subu in the guard's delay
 *   slot; computing it after the guard leaves that slot to the NEXT branch and
 *   the unit comes back one word SHORT.  (Its declaration POSITION is inert:
 *   first vs last gave one object, 9ff0d206c9ee0fb6a1b9dc998b03af46bd47b322.)
 *   `e = x - a` in the else arm, after the a==0 fixup and BEFORE the c guard
 *   -- this is what mwcc duplicates into retail's `bnel` delay slot.  Without
 *   it the else arm is `bnez` + nop and 6 words are wrong. */

extern f32   D_0047D440;          /* gp - 0x7D30 */
extern void *D_00484564;          /* gp - 0xC0C  */
extern void *D_0048456C;          /* gp - 0xC04  */
extern u8    D_00484570;          /* gp - 0xC00  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_LeaderHudBannerSlide_507d70(s32 a, s32 b, s32 c)
{
    s32 d;
    s32 e;
    s32 x;
    s32 y;
    s32 z;
    s32 t;

    UiGetWidgetAlpha_290770(D_00484564, 7);
    DrawEnvGetScreenInfo_289a40(D_0048456C, &x, &y, &z);
    t = 0;
    d = x - a;
    if (D_00484570 != 0) {
        t = 0x19;
    }
    if (b != 0) {
        if (c != 0) {
            UiSetWidgetPos_290f60(D_00484564, 7, x + 0x20, t + 8);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 7, d - 8, t + 8, D_0047D440, 0);
    } else {
        if (a == 0) {
            a = 0x100;
        }
        e = x - a;
        if (c != 0) {
            UiSetWidgetPos_290f60(D_00484564, 7, e, t + 8);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 7, x + 0x28, t + 8, D_0047D440, 0);
    }
    return 1;
}
