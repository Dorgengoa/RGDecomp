/* rgp:protos */
#define RGP_SELF_normal_LeaderHudBannerSlideEdge_507e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00507E90 -- sibling of 0x00507D70: same widget 7, but the anchor is
 * the literal 0x200 screen edge instead of a measured box. */

extern f32   D_0047D440;          /* gp - 0x7D30 */
extern void *D_00484564;          /* gp - 0xC0C  */
extern u8    D_00484570;          /* gp - 0xC00  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_LeaderHudBannerSlideEdge_507e90(s32 a, s32 b, s32 c)
{
    s32 t;

    t = 0;
    if (D_00484570 != 0) {
        t = 0x19;
    }
    if (b != 0) {
        if (a == 0) {
            UiSetWidgetVisible_290010(D_00484564, 7, 0, -1);
        } else {
            UiSetWidgetVisible_290010(D_00484564, 7, 1, -1);
        }
        if (c != 0) {
            UiSetWidgetPos_290f60(D_00484564, 7, -(a + 8), t + 8);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 7, 0x200 - (a + 8), t + 8, 0.5f, 0);
        UiFadeWidgetAlpha_290690(D_00484564, 7, 1.0f, 0.0625f, 0.0f);
    } else {
        if (a == 0) {
            a = 0x100;
        }
        if (c != 0) {
            UiSetWidgetPos_290f60(D_00484564, 7, 0x200 - (a + 8), t + 8);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 7, 0x200, t + 8, D_0047D440, 0);
        UiFadeWidgetAlpha_290690(D_00484564, 7, 0.0f, 0.0625f, 1.0f);
    }
    return 1;
}
